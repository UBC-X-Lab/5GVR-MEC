

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

#include "buildtimestamp.h"
#include "stream_receive.h"
#include "lockedQueue/locked_queue.h"


l_queue* pkt_q = NULL;

static char* SRC_STREAM = NULL;
AVFormatContext* format_context = NULL;
static int g_avVideoStreamIndex;

struct timeval tv;

void* handle_input_to_startup_receiver(void* arg_struct) {
    r_input* r_in = (r_input*) arg_struct;
    l_queue* queue_pkt_q = r_in->pkt_q;
    AVFormatContext* context = r_in->f_ctx;
    free(r_in);
    setup_receiver(queue_pkt_q, context);
} 

void setup_receiver(l_queue* queue_pkt_q, AVFormatContext* ctx) {
    int ret;
    pkt_q = queue_pkt_q;
    format_context = ctx;
    ret = av_find_best_stream(format_context, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (ret < 0)
    {
        fprintf(stderr, "Could not find %s stream in input file\n",
                av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
                exit(1);
    }
    else
    {
        g_avVideoStreamIndex = ret;
    }
    run_receiver();
}

void run_receiver() {
    AVPacket* pkt;
    fprintf(stdout, "running receive thread\n");
    printf("Please start input stream if not already started\n");

    gettimeofday(&tv, NULL);
    double start = buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec);
    
    while(1) {
        if (q_is_dead(pkt_q)) {
            fprintf(stdout, "Receive thread received kill signal\n");
            break;
        }
        pkt = av_packet_alloc();
        while(1) {
            // fprintf(stdout, "Receiving frame from stream\n");
            // gettimeofday(&tv, NULL);
            // fprintf(stderr, "stream_receive,calling,av_read_frame,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
            // buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec);
            int ret = av_read_frame(format_context, pkt);
            // gettimeofday(&tv, NULL);
            // fprintf(stderr, "stream_receive,returning,av_read_frame,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), pkt->size, pkt->pts);
            // buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec);
            if (ret < 0) {
                fprintf(stdout, "Stream has ended\n");
                q_kill(pkt_q);
                av_packet_free(&pkt);
                avformat_close_input(&format_context);
                return;
            }
            if (pkt->stream_index == g_avVideoStreamIndex) {
                break;
            }
            av_packet_unref(pkt);
        }
        // printf("frame has data stream index: %d, size %d, flags %d\n", pkt->stream_index, pkt->size, pkt->flags);
        // fprintf(stdout, "New frame queued for decoding\n");
        // gettimeofday(&tv, NULL);
        // fprintf(stderr, "stream_receive,calling,q_enqueue,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), pkt->size, pkt->pts);
        // buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec);

        while (1){
            gettimeofday(&tv, NULL);
            double pause = buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec) - start;
            if (pause > 1.0 / 30){
                printf("%f\n", pause);
                q_enqueue(pkt_q, pkt);
                start = buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec);
                break;
            }
        }
        // gettimeofday(&tv, NULL);
        // long pause = (long) ((buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec) - start) * 1000000);
        // usleep(33333 - pause);
        
        // gettimeofday(&tv, NULL);
        // double test_pause = buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec) - start;
        // printf("%f\n", test_pause);
        
        // q_enqueue(pkt_q, pkt);
        // start = buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec);
        pkt = NULL;
    }
    fprintf(stdout, "Receiver: Freeing packet used for receival\n");
    av_packet_free(&pkt);
    fprintf(stdout, "Receiver: Closing input\n");
    avformat_close_input(&format_context);
}