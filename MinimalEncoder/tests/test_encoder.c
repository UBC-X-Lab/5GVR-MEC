

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
#include <assert.h>

#include "server_controller.h"
#include "focal_transmit.h"
#include "focal_encode.h"
#include "lockedQueue/locked_queue.h"

/* Parameters */
struct timeval tv;

static pthread_t encode_thread;
static pthread_t transmit_thread;

static char *SRC_FILENAME = "../../test_files/360sample1080s.mp4";
static transmit_interface_t ti = {};
static l_queue* decode_encode_frame_q;
int bitrate;

/* test ffmpeg state */
static struct SwsContext *g_swsContext = NULL;
static AVFormatContext *g_avFormatContext = NULL;
static AVStream *g_avVideoStream = NULL;
static AVCodecContext *g_avVideoCodecContext = NULL;
static AVPacket *g_avPacket = NULL;

static int g_avVideoStreamIndex;
static int g_videoWidth = 1920;
static int g_videoHeight = 1080;

void frame_finalizer(void* frame_pntr);
void packet_finalizer(void* pkt_pntr);

void frame_finalizer(void* frame_pntr) {
    AVFrame* frm = (AVFrame*) frame_pntr;
    // does not matter if source of frame_pntr is dangling as it is destroyed when removed from stack when recursive call in q_free_queue returns;
    av_frame_free(&frm);
}

void packet_finalizer(void* pkt_pntr) {
    AVPacket* pkt = (AVPacket*) pkt_pntr;
    // does not matter if source of pkt_pntr is dangling as it is destroyed when removed from stack when recursive call in q_free_queue returns;
    av_packet_free(&pkt); 
}

/* next functions up until main are from encoder.c (the static example) */
static int open_codec_context(int *stream_idx,
                              AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx, enum AVMediaType type)
{
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

static void video_start()
{
    if (avformat_open_input(&g_avFormatContext, SRC_FILENAME, NULL, NULL) < 0)
    {
        fprintf(stderr, "Could not open source file %s\n", SRC_FILENAME);
        return;
    }

    if (avformat_find_stream_info(g_avFormatContext, NULL) < 0)
    {
        fprintf(stderr, "Could not find stream information\n");
        return;
    }

    if (open_codec_context(&g_avVideoStreamIndex, &g_avVideoCodecContext, g_avFormatContext, AVMEDIA_TYPE_VIDEO) < 0)
    {
        fprintf(stderr, "Could not open video stream\n");
        return;
    }

    g_avVideoStream = g_avFormatContext->streams[g_avVideoStreamIndex];
    g_swsContext = sws_getCachedContext(g_swsContext,
                                        g_avVideoCodecContext->width, g_avVideoCodecContext->height, g_avVideoCodecContext->pix_fmt,
                                        g_videoWidth, g_videoHeight, AV_PIX_FMT_RGBA,
                                        SWS_BICUBIC, NULL, NULL, NULL);

    if (!g_swsContext)
    {
        fprintf(stderr, "Failed to create swscale context\n");
        return;
    }

    g_avPacket = av_packet_alloc();
    if (!g_avPacket)
    {
        fprintf(stderr, "Could not allocate packet\n");
        return;
    }
}

static void video_stop()
{
    avcodec_free_context(&g_avVideoCodecContext);
    avformat_close_input(&g_avFormatContext);
    av_packet_free(&g_avPacket);
}

static void read_frame(AVFrame *frame)
{
    //static AVFrame *read_frame() {
    int ret = 0;
    while (1)
    {
        if (!g_avVideoCodecContext)
        {
            video_start();
        }

        /* flush any unreceived frames from the decoder */
        ret = avcodec_receive_frame(g_avVideoCodecContext, frame);
        if (ret >= 0)
        {
            return;
        }
        else if (ret != AVERROR_EOF && ret != AVERROR(EAGAIN))
        {
            fprintf(stderr, "error receiving a video frame\n");
            return;
        }

        if (!g_avPacket)
        {
            /* Final packet already submitted - we're done */
            video_stop();
            /* loop - this will restart the stream and get us a new frame */
            printf("Streaming video complete!");
            exit(1);
            continue;
        }

        while (1)
        {
            int ret = av_read_frame(g_avFormatContext, g_avPacket);
            if (ret < 0)
            {
                /* input stream ended - flush decoder */
                av_packet_free(&g_avPacket);
                break;
            }
            if (g_avPacket->stream_index == g_avVideoStreamIndex)
            {
                break;
            }
            av_packet_unref(g_avPacket);
        }
        avcodec_send_packet(g_avVideoCodecContext, g_avPacket);
        if (g_avPacket)
            av_packet_unref(g_avPacket);
    }
}

int main(int argc, char **argv) {
    int ret;
    bitrate = 8000000;
    /* set variables from arguments passed to main */
    if(argc != 1){
        printf("invalid number of arguments. test_encoder does not take arguments");
        exit(1);
    }
    
    /* allocate and initialize queue for thread */
    decode_encode_frame_q = q_queue_alloc();

    /* set up transmit_interface for encode thread to send to */
    if (pthread_mutex_init(&ti.mutex, NULL)) // intializes mutex
    {
        printf("focal_transmit: failed creating mutex\n");
    }

    printf("Initializing transmit interface struct to be handed to encode thread\n");
    // **All of these values are shared with focalEncoder**
    ti.ready = 0; // indicates wether or not the encoder is ready for a new frame
    ti.kill = 0; // indicates the end of frames being pushed
    ti.newPacket = 0; // indicates if there is a new packet to recieve
    
    printf("Creating transmit thread to receive output from encode thread\n");
    if (pthread_create(&transmit_thread, NULL, transmit_connect, &ti))
    {
        printf("Encoder failed to create thread for focal_transmit\n");
    }
    printf("Thread created successfully\n");

    /* spin until connection is established on transmit thread */
    while(!ti.ready) {
        sched_yield();
    }

    /* Generate frames to be handed into the encoder */ 
    printf("Begining to develop frames from %s to plug into encoder thread\n", SRC_FILENAME);
    AVFrame* frame;
    for (int i = 0; i < 180; i++) {
        frame = av_frame_alloc();
        printf("Reading frame\n");
        read_frame(frame);
        printf("frame has data: flags %d, key_frame %d, sample_rate %d, pkt_size %d\n", frame->flags, frame->key_frame, frame->sample_rate, frame->pkt_size);
        printf("throwing frame on queue for encoder");
        q_enqueue(decode_encode_frame_q, frame);
        frame = NULL;
    }

    /* initialize encode thread */
    printf("Allocating handoff struct for setting up encoder thread\n");
    e_input* e_in = malloc(sizeof(e_in));
    e_in->frame_q = decode_encode_frame_q;
    e_in->ti = &ti;
    e_in->bitrate = bitrate;

    printf("Creating encode thread\n");
    if (pthread_create(&encode_thread, NULL, handle_input_to_startup_encoder, e_in)) {
        fprintf(stderr, "Error: failed to create encode thread\n");
        q_free_queue(decode_encode_frame_q, NULL);
        pthread_mutex_destroy(&ti.mutex);
        abort();
    }
    printf("Thread created successfully\n");


    /* signal kill to get the thread to terminate */ 
    //TODO signal
    printf("Waiting for transmit thread to terminate to proceed\n");
    pthread_join(transmit_thread, NULL);
    q_kill(decode_encode_frame_q);
    pthread_join(encode_thread, NULL);

    /* free queues and associted memory */
    printf("freeing queue\n");
    q_free_queue(decode_encode_frame_q, frame_finalizer);

    /* free transmit_interface memory */
    printf("destroying mutex within transmit interface\n");
    pthread_mutex_destroy(&ti.mutex);
    return 0;
}
