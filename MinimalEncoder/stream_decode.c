

#include <stdio.h>
#include <time.h>
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

#include "stream_decode.h"
#include "buildtimestamp.h"
#include "lockedQueue/locked_queue.h"

l_queue* decode_pkt_q = NULL;
l_queue* decode_frame_q = NULL;

/* ffmpeg state */
static AVPacket* g_avPacket = NULL;
static AVFrame* g_avFrame = NULL;
AVCodecContext* decode_ctx = NULL;

static int g_avSteamIndex;

struct timeval tv; 

static int open_codec_context(int *stream_idx, AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx, enum AVMediaType type) {
    int ret, stream_index;
    AVStream *st;
    AVCodec *dec = NULL;
    AVDictionary *opts = NULL;

    ret = av_find_best_stream(fmt_ctx, type, -1, -1, NULL, 0);
    if (ret < 0)
    {
        fprintf(stderr, "Could not find %s stream in input file\n",
                av_get_media_type_string(type));
        return ret;
    }
    else
    {
        stream_index = ret;
        st = fmt_ctx->streams[stream_index];

        /* find decoder for the stream */
        dec = avcodec_find_decoder(st->codecpar->codec_id);
        if (!dec)
        {
            fprintf(stderr, "Failed to find %s codec\n",
                    av_get_media_type_string(type));
            return AVERROR(EINVAL);
        }

        /* Allocate a codec context for the decoder */
        *dec_ctx = avcodec_alloc_context3(dec);
        if (!*dec_ctx)
        {
            fprintf(stderr, "Failed to allocate the %s codec context\n",
                    av_get_media_type_string(type));
            return AVERROR(ENOMEM);
        }

        /* Copy codec parameters from input stream to output codec context */
        if ((ret = avcodec_parameters_to_context(*dec_ctx, st->codecpar)) < 0)
        {
            fprintf(stderr, "Failed to copy %s codec parameters to decoder context\n",
                    av_get_media_type_string(type));
            return ret;
        }

        av_opt_set((*dec_ctx)->priv_data, "preset", "ultrafast", 0); // required to have low latency steaming
        av_opt_set((*dec_ctx)->priv_data, "tune", "zerolatency:fastdecode", 0); // this introduces a no wait frame send (does not wait to send frame)

        /* Init the decoders */
        if ((ret = avcodec_open2(*dec_ctx, dec, &opts)) < 0)
        {
            fprintf(stderr, "Failed to open %s codec\n",
                    av_get_media_type_string(type));
            return ret;
        }
        *stream_idx = stream_index;
    }

    return 0;
}

int decode(AVCodecContext *ctx, AVPacket *pkt, AVFrame *frame) {
    int ret;
    /* call to decoder to decode pkt */
    // printf("DECODE: send pkt with data: stream index %d, size %d, flags %d to ffmpeg for decode\n", pkt->stream_index, pkt->size, pkt->flags);
    ret = avcodec_send_packet(ctx, pkt);
    if (ret < 0) {
        fprintf(stderr, "Error: could not send packet to decoder for decoding\n");
        av_packet_free(&pkt);
        return -1;
    }
    // printf("DECODE: Successfully returned from packet delivery\n");
    /* call to decoder to receive output */
    // printf("DECODE: receiving frame from ffmpeg decoder\n");
    ret = avcodec_receive_frame(ctx, frame);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) { 
        //frames not ready or flushed
        return -1;
    } else if (ret < 0) {
        fprintf(stderr, "Error: an error occured decoding\n");
        av_packet_free(&pkt);
        return -1;
    }
    // deallocate pkt since it is nolonger used
    av_packet_free(&pkt);
    return 0;
}

void* handle_input_to_startup_decoder(void* arg_struct) {
    d_input* d_in = (d_input*) arg_struct;
    AVFormatContext* fmt_ctx = d_in->avformat_context;
    l_queue* queue_decode_pkt_q = d_in->pkt_q;
    l_queue* queue_decode_frame_q = d_in->frame_q;
    // printf("Freeing handoff struct to set up decode thread\n");
    free(d_in); 
    setup_decoder(queue_decode_pkt_q, queue_decode_frame_q, fmt_ctx);
}

void setup_decoder(l_queue* queue_decode_pkt_q, l_queue* queue_decode_frame_q, AVFormatContext* fmt_ctx) {
    //printf("DECODE: setting up decoder\n");
    int ret;
    decode_pkt_q = queue_decode_pkt_q;
    decode_frame_q = queue_decode_frame_q;
    /* create Codec Context for decoder */
    //printf("DECODE: making call into open codec context to set up context\n");
    ret = open_codec_context(&g_avSteamIndex, &decode_ctx, fmt_ctx, AVMEDIA_TYPE_VIDEO);
    if (ret < 0) {
        fprintf(stderr, "Error in Decoder: Could not open video steam\n");
        avformat_close_input(&fmt_ctx);
        exit(1);
    }
    //printf("DECODE: successfully returned from context creation\n");
    //printf("DECODE: closing format_context needed to set up avcontext. No longer needed close/free so it may be used for receive thread\n");

    pthread_mutex_lock(&decode_pkt_q->mutex);
    /* when doing independent testing needs close input here, when running program in parallel requires q_ready signal to let receiver know it 
    is safe to use the format context <-------------------------------------                */
    // avformat_close_input(&fmt_ctx); // this is fine because pointer in main was set to null, so no risk of dangling pointer
    decode_pkt_q->ready = true;
    pthread_cond_signal(&decode_pkt_q->avail);
    pthread_mutex_unlock(&decode_pkt_q->mutex);

    run_decoder();
}

void run_decoder() {
    printf("DECODE: running decode thread\n");
    int ret;
    AVPacket* pkt;
    AVFrame* frame;
    while(1) {
        if (q_is_dead(decode_frame_q)) {
            printf("DECODE: Received signal to terminate, decoder shutting down\n");
            break;
        }
        /* grab pkt off of decode_pkt_q from receive thread*/
        if (q_dequeue(decode_pkt_q, (void**) &pkt) < 0) {
            fprintf(stderr, "DECODE: stream Ended Decoder shutting down\n");
            q_kill(decode_frame_q); // signal kill on frame queue so encoder thread knows to terminate
            avcodec_free_context(&decode_ctx);
            return; 
        }
        frame = av_frame_alloc();
        ret = decode(decode_ctx, pkt, frame);
        if (ret < 0) {
            continue;
        }
        fprintf(stderr, "frame has size:%d,pts:%ld, key: %d\n", frame->pkt_size, frame->pts, frame->key_frame);


        /* throws decoded decode_frame_q to go to encode thread */
        q_enqueue(decode_frame_q, frame);
        frame = NULL;
    }
    printf("DECODE: freeing the av codec context associated with decode thread\n");
    avcodec_free_context(&decode_ctx);
}