

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

#include "focal_transmit.h"

/* Parameters */
static char *SRC_STREAM = "rist://@0.0.0.0:4000";
struct timeval tv;
static pthread_t transmit_thread;
static transmit_interface_t ti = {};

/* ffmpeg state */
static struct SwsContext *g_swsContext = NULL;
static AVFormatContext *g_avFormatContext = NULL;
static AVStream *g_avVideoStream = NULL;
static AVCodecContext *g_avVideoCodecContext = NULL;
static AVPacket *g_avPacket = NULL;

static int g_avVideoStreamIndex;
static int g_videoWidth = 1920; //TODO compute this num
static int g_videoHeight = 1080; //TODO compute this num

/* Point to packet with ti and mark as packet ready */

static void send_packet(const AVPacket *pkt)
{
    pthread_mutex_lock(&ti.mutex);
    ti.pkt = pkt;
    ti.newPacket = 1;
    pthread_mutex_unlock(&ti.mutex);
    sched_yield();
}

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
    fprintf(stdout, "Code calling into avformat_open_input\n");
    if (avformat_open_input(&g_avFormatContext, SRC_STREAM, NULL, NULL) < 0)
    {
        fprintf(stderr, "Could not open source file %s\n", SRC_STREAM);
        return;
    }
    fprintf(stdout, "Code successfuly returned from call into avformat_open_input\n");
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
            fprintf(stdout, "video started");
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
            gettimeofday(&tv, NULL);
            printf("timestamp right before receive: %d \n", tv.tv_usec);
            int ret = av_read_frame(g_avFormatContext, g_avPacket);
            gettimeofday(&tv, NULL);
            printf("timestamp right after receive: %d \n", tv.tv_usec);
            // printf("grabbed with context, %x \n", g_avFormatContext->ctx_flags);
            // printf("packet has stream_index: %x, and flags: %x \n", g_avPacket->stream_index, g_avPacket->flags);
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
        gettimeofday(&tv, NULL);
        printf("timestamp right before decode: %d \n", tv.tv_usec);
        avcodec_send_packet(g_avVideoCodecContext, g_avPacket);
        gettimeofday(&tv, NULL);
        printf("timestamp right after decode: %d \n", tv.tv_usec);
        fprintf(stdout, "sending packet");
        if (g_avPacket)
            av_packet_unref(g_avPacket);
    }
}

static void encode(AVCodecContext *ctx, AVPacket *pkt, AVFrame *frame)
{
    int ret;
    ret = avcodec_send_frame(ctx, frame);
    if (ret < 0)
    {
        fprintf(stderr, "Error sending a frame for encoding\n");
        exit(1);
    }
    while (1)
    {
        while (ti.newPacket)
        {
            sched_yield();
        }
        ret = avcodec_receive_packet(ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0)
        {
            fprintf(stderr, "Error during encoding\n");
            exit(1);
        }
        send_packet(pkt);
    }
}

int main(int argc, char **argv)
{
    const AVCodec *codec;
    AVCodecContext *ctx = NULL; //The encoder
    AVFrame *frame; //Current frame being worked on
    AVPacket *pkt;
    int ret;
    pkt = av_packet_alloc();
    if (!pkt)
        exit(1);
    /** Encoder init **/
    codec = avcodec_find_encoder_by_name("libx264");
    if (!codec)
    {
        fprintf(stderr, "Encoder codec not found\n");
        exit(1);
    }
    ctx = avcodec_alloc_context3(codec);
    if (!ctx)
    {
        fprintf(stderr, "Could not allocate encoder codec context\n");
        exit(1);
    }
    /* resolution must be a multiple of two */
    ctx->width = g_videoWidth;
    ctx->height = g_videoHeight;
    /* frames per second */
    ctx->time_base = (AVRational){1, 25}; //TODO edit this to be dynamically set based off of input video <----------------------------------------
    ctx->framerate = (AVRational){25, 1}; //TODO edit this to be dynamically set based on fed video <---------------------------------------------
    av_opt_set(ctx->priv_data, "preset", "ultrafast", 0); // required to have low latency steaming
    av_opt_set(ctx->priv_data, "tune", "zerolatency", 0); // this introduces a no wait frame send (does not wait to send frame)
    av_opt_set(ctx->priv_data, "x264-params", "nal-hrd=cbr:force-cfr=1", 0);
    if((argc != 3) && (argc != 2)){
        printf("invalid number of arguments. please provide 1 integer for bitrate\n& a different if you wish to change the stream");
        exit(1);
    }
    printf("Encoding with bitrate: %d\n", atoi(argv[1]));
    if (argc == 3) {
        SRC_STREAM = argv[3];
    }
    ctx->bit_rate = atoi(argv[1]);
    ctx->rc_max_rate = atoi(argv[1]);
    ctx->rc_min_rate = atoi(argv[1]);
    ctx->rc_buffer_size = atoi(argv[1]);
    ctx->pix_fmt = AV_PIX_FMT_YUV420P;
    /* open it */
    ret = avcodec_open2(ctx, codec, NULL);
    if (ret < 0)
    {
        fprintf(stderr, "Could not open codec: %s\n", av_err2str(ret));
        exit(1);
    }
    frame = av_frame_alloc();
    if (!frame)
    {
        fprintf(stderr, "Could not allocate input frame\n");
        exit(1);
    }
    frame->format = ctx->pix_fmt;
    frame->width = ctx->width;
    frame->height = ctx->height;
    ret = av_frame_get_buffer(frame, 0);
    if (ret < 0)
    {
        fprintf(stderr, "Could not allocate the video frame data\n");
        exit(1);
    }
    /* Initialize data transmission */
    if (pthread_mutex_init(&ti.mutex, NULL)) // intializes mutex
    {
        printf("focal_transmit: failed creating mutex\n");
    }
    // **All of these values are shared with focalEncoder**
    ti.ready = 0; // indicates wether or not the encoder is ready for a new frame
    ti.kill = 0; // indicates the end of frames being pushed
    ti.newPacket = 0; // indicates if there is a new packet to recieve
    if (pthread_create(&transmit_thread, NULL, transmit_connect, &ti))
    {
        printf("Encoder failed to create thread for focal_transmit\n");
    }
    while (!ti.ready) //spin (yeild) while waiting for frames
    {
        sched_yield();
    }

    while (ti.ready)
    {
        read_frame(frame);
        gettimeofday(&tv, NULL);
        printf("timestamp right before encode: %d \n", tv.tv_usec); // will be used to determine sleeptime
        encode(ctx, pkt, frame);
        gettimeofday(&tv, NULL);
        printf("timestamp right after encode: %d \n", tv.tv_usec);
        /* crappy rate control */
        usleep(33000); //TODO need to dynamically determine this sleep time. Only works for the given video <------------------------------------------
    }
    /* flush encoder and decoder */
    encode(ctx, pkt, NULL);
    avcodec_free_context(&ctx);
    av_frame_free(&frame);
    av_packet_free(&pkt);
}
