

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>

#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include "server_controller.h"
#include "stream_decode.h"
#include "lockedQueue/locked_queue.h"

/* Parameters */
struct timeval tv;

static char* SRC_STREAM = "../../test_files/360sample1080s.mp4"; // TODO figure out what to assign here for testing

static pthread_t decode_thread;

static l_queue* receive_decode_pkt_q;
static l_queue* decode_encode_frame_q;

/* ffmpeg state required variables for thread initialization */
static AVFormatContext *g_avFormatContext = NULL;\

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

int main(int argc, char **argv)
{
    if(argc != 1) {
        printf("invalid number of arguments. test_encoder does not take arguments");
        exit(1);
    }
    /* get AVFormatContext for decode thread */
    printf("Process opening input %s\n", SRC_STREAM);
    if (avformat_open_input(&g_avFormatContext, SRC_STREAM, NULL, NULL) < 0) {
        fprintf(stderr, "Error: could not open source stream %s\n", SRC_STREAM);
        avformat_close_input(&g_avFormatContext);
        exit(1);
    }
    printf("successfully opened %s\n", SRC_STREAM);
    printf("Finding more information on stream\n");
    if (avformat_find_stream_info(g_avFormatContext, NULL) < 0) {
        fprintf(stderr, "Error: could not find stream information\n");
        avformat_close_input(&g_avFormatContext);
        exit(1);
    }
    printf("Information found correctly, stored in g_avFormatContext\n");

    /* allocate and initialize queues for thread pipeline */
    printf("Allocating packet and frame queues for decoder to use\n");
    receive_decode_pkt_q = q_queue_alloc();
    decode_encode_frame_q = q_queue_alloc();

    // TODO need code to receive packets from stream to feed into decoder
    AVPacket* buff[8];
    AVPacket* test_pkt;
    for (int i = 0; i < 8; i++) {
        test_pkt = av_packet_alloc();
        printf("About to read from stream for the %d time\n", i);
        int ret = av_read_frame(g_avFormatContext, test_pkt);
        if (ret < 0) {
            fprintf(stderr, "Error in main: Stream should not indicate that it has ended in within the first 3 frames\n");
            av_packet_free(&test_pkt);
            avformat_close_input(&g_avFormatContext);
            abort();
        }
        printf("pkt has data stream index: %d, size %d, flags %d\n", test_pkt->stream_index, test_pkt->size, test_pkt->flags);
        buff[i] = test_pkt;
        printf("adding pkt to queue for decode thread to decode\n");
        q_enqueue(receive_decode_pkt_q, test_pkt);
        test_pkt = NULL;
    }
    printf("Successfully made it through collection.\n");
    // TODO need code to develop frames to asssert decoder worked

    /* initialize decode thread */
    printf("Allocating handoff struct to pass context and queues to decode thread\n");
    d_input* d_in = malloc(sizeof(d_input));
    d_in->avformat_context = g_avFormatContext;
    d_in->frame_q = decode_encode_frame_q;
    d_in->pkt_q = receive_decode_pkt_q;

    printf("Creating decode thread\n");
    if (pthread_create(&decode_thread, NULL, handle_input_to_startup_decoder, d_in)) {
        fprintf(stderr, "Error: failed to create decode thread\n");
        avformat_close_input(&g_avFormatContext);
        q_free_queue(receive_decode_pkt_q, NULL);
        q_free_queue(decode_encode_frame_q, NULL);
        abort();
    }
    sleep(1);

    printf("Signalling kill on both queues\n");
    q_kill(receive_decode_pkt_q);
    q_kill(decode_encode_frame_q);
    printf("Waiting for decode thread to end it's process\n");
    pthread_join(decode_thread, NULL);
    printf("Decode thread has terminated\n");

    for (int j = 0; j < 8; j++) {
        AVFrame* sanity_frame;
        printf("dequing frame from queue\n");
        q_dequeue(decode_encode_frame_q, (void**) &sanity_frame);
        printf("frame has data: flags %d, key_frame %d, sample_rate %d, pkt_size %d\n", sanity_frame->flags, sanity_frame->key_frame, sanity_frame->sample_rate, sanity_frame->pkt_size);
        av_frame_free(&sanity_frame);
    }

    /* free queues and associted memory */
    printf("Freeing frame queue\n");
    q_free_queue(decode_encode_frame_q, frame_finalizer);
    printf("Freeing packet queue\n");
    q_free_queue(receive_decode_pkt_q, packet_finalizer);
    return 0;
}
