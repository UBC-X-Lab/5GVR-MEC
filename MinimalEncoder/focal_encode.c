

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include "focal_encode_allq.h"
#include "buildtimestamp.h"
#include "focal_transmit_allq.h"
#include "lockedQueue/locked_queue.h"

l_queue* frame_q = NULL;
l_queue* transmit_pkt_q = NULL;
// transmit_interface_t* ti = NULL;

AVPacket* g_avPacket = NULL;
AVFrame* g_avFrame = NULL;
AVCodecContext* ctx = NULL;

static int g_avVideoStreamIndex;

/* -- not needed --
static int g_videoWidth = 1920; //TODO compute this num dynamically based on recieved stream
static int g_videoHeight = 1080; //TODO compute this num dynamically based on recieved stream
*/

static int fps = 30; //TODO compute this num dynamically based on recieved stream

struct timeval tv;

void encode(AVCodecContext *ctx, AVPacket *pkt, AVFrame *frame) {
    int ret;
    ret = avcodec_send_frame(ctx, frame);
    if (ret < 0)
    {
        fprintf(stderr, "Error sending a frame for encoding\n");
        exit(1);
    }
    //av_frame_free(&frame); // this is ok, as in all cases the pointer handed in is set to NULL after, destroyed when scope is removed, or not touched again. no dangling pointer.
    ret = avcodec_receive_packet(ctx, pkt);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
        return;
    }
    else if (ret < 0)
    {
        fprintf(stderr, "Error during encoding\n");
        av_frame_free(&frame);
        exit(1);
    }
    q_enqueue(transmit_pkt_q, pkt);

    av_frame_free(&frame); // this sets pointer to NULL after
}

/* static void send_packet(const AVPacket *pkt) {
    pthread_mutex_lock(&ti->mutex);
    gettimeofday(&tv, NULL);
    fprintf(stderr, "focal_encode,n/a,transmit_interface_add,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), pkt->size, pkt->pts);
    ti->pkt = pkt;
    ti->newPacket = 1;
    pthread_mutex_unlock(&ti->mutex);
} */

void* handle_input_to_startup_encoder(void* arg_struct) {
    e_input* e_in = (e_input*) arg_struct;
    l_queue* frame_q = e_in->frame_q;
    l_queue* pkt_qp = e_in->pkt_q;
    int br = e_in->bitrate;
    // printf("freeing handoff struct\n");
    free(e_in);
    setup_encoder(frame_q, pkt_qp, br);
}

void setup_encoder(l_queue* _q, l_queue* _pq, int _bitrate) {
    frame_q = _q;
    transmit_pkt_q = _pq;
    int bitrate = _bitrate;

    const AVCodec* codec;
    AVFrame* frame; // frame varaiable which holds frame to be encoded
    int ret; 
    printf("Setting up encoder thread\n");    
    /** Encoder init **/
    codec = avcodec_find_encoder_by_name("libx264");
    if (!codec) {
        fprintf(stderr, "Error: x264 codec not found\n");
        exit(1);
    }
    ctx = avcodec_alloc_context3(codec);
    if (!ctx) {
        fprintf(stderr, "Error: could not allocate encoder codec context\n");
        exit(1);
    }
    
    // set frame rate (fps) for context
    ctx->time_base = (AVRational){1, fps}; //TODO make this dynamic
    ctx->framerate = (AVRational){fps, 1}; //TODO make this dynamic
    av_opt_set(ctx->priv_data, "preset", "ultrafast", 0); // required to have low latency steaming
    av_opt_set(ctx->priv_data, "tune", "zerolatency", 0); // this introduces a no wait frame send (does not wait to send frame)
    int length = snprintf( NULL, 0, "nal-hrd=cbr:force-cfr=1:keyint=%d:keyint_min=%d", (fps*2), (fps*2));
    char* str = malloc(length+1);
    snprintf(str, length+1, "nal-hrd=cbr:force-cfr=1:keyint=%d:keyint_min=%d", (fps*2), (fps*2));
    //printf(str);
    av_opt_set(ctx->priv_data, "x264-params", str, 0); // constant bitrate
    free(str);
    printf("Encoding with bitrate: %d\n", bitrate);
    ctx->bit_rate = bitrate;
    ctx->rc_max_rate = bitrate;
    ctx->rc_min_rate = bitrate;
    ctx->rc_buffer_size = bitrate;
    //ctx->keyint_min = fps * 2;
    while (1) {
        /* receive single frame from queue to set context feilds */
        printf("Encode thread waiting for setup frame\n");
        if (q_dequeue(frame_q, (void**) &frame)) {
            fprintf(stderr, "could not receive frame to set up context");
            exit(1); // TODO maybe implement dump and retry instead
        }
        printf("Frame Received\n");
        //ctx->pix_fmt = AV_PIX_FMT_YUV420P; // <-------this should be gotten from frame off queue
        if (frame->format == -1) {
            continue;
        }
        ctx->pix_fmt = frame->format;
        /* note: resolution must be a multiple of two */
        //ctx->width = g_videoWidth; // <-------this should be gotten from frame off queue
        //ctx->height = g_videoHeight; // <-------this should be gotten from frame off queue 
        ctx->width = frame->width;
        ctx->height = frame->height;
        /* open context */
        ret = avcodec_open2(ctx, codec, NULL);
        if (ret < 0)
        {
            fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
            av_frame_free(&frame);
        }
        /* This might not be necissary as we already have exisiting frames
        ret = av_frame_get_buffer(frame, 0);
        if (ret < 0) {
            fprintf(stderr, "Could not allocate the video frame data\n");
            exit(1);
        }
        */
       fprintf(stdout, "ENCODE: Codec opened: %s\n", av_err2str(ret));
       break;
    }
    run_encoder(frame);
}

void run_encoder(AVFrame* init_frame) {
    AVPacket* pkt; // packet variable used to receive and send encoded frame
    AVFrame* frame;
    pkt = av_packet_alloc();
    if (!pkt) {
        fprintf(stderr, "Error: unable to allocate packet\n");
        exit(1);
    }
    /* send initial frame off to be encoded */
    encode(ctx, pkt, init_frame);
    pkt = NULL;
    
    /* run encoder loop */
    
    while(1) {
        if (q_is_dead(frame_q)) {
            printf("Encoder: Received signal to terminate, encoder shutting down\n");
            break;
        }
        if (q_is_dead(transmit_pkt_q)) {
            printf("Encoder: Received signal to terminate, encoder shutting down\n");
            break;
        }
        /* grab frame off frame_q from decode tread */
        if (q_dequeue(frame_q, (void**) &frame) < 0) {
            fprintf(stderr, "Stream Ended Encoder shutting down\n");
            avcodec_free_context(&ctx);
            return; 
        }
        pkt = av_packet_alloc();
        encode(ctx, pkt, frame);
        pkt = NULL;
    }
    avcodec_free_context(&ctx);
}