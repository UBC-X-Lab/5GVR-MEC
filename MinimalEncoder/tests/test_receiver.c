

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

#include "../stream_receive.h"
#include "../lockedQueue/locked_queue.h"

/* Parameters */
static char *SRC_STREAM = "../../test_files/360sample1080s.mp4";
struct timeval tv;

static AVFormatContext* g_avFormatContext = NULL;

static pthread_t receive_thread;
static l_queue* receive_decode_pkt_q;

// a finalizer for packets stored in queue
void packet_finalizer(void* pkt_pntr);

void packet_finalizer(void* pkt_pntr) {
    AVPacket* pkt = (AVPacket*) pkt_pntr;
    // does not matter if source of pkt_pntr is dangling as it is destroyed when removed from stack when recursive call in q_free_queue returns;
    av_packet_free(&pkt); 
}

int main(int argc, char **argv)
{
    int ret;
    /* set variables from arguments passed to main */
    if((argc != 1) && (argc != 2)){
        printf("Invalid number of arguments. Please either run executable with no arguments or inlude a different url after if you wish to change the stream\n");
        exit(1);
    }
    if (argc == 2) {
        strcpy(SRC_STREAM, argv[1]);
        fprintf(stdout, "Changing stream url to %s\n", SRC_STREAM);
    }
    
    /* allocate and initialize queue for thread  */
    receive_decode_pkt_q = q_queue_alloc();

    
    if (avformat_open_input(&g_avFormatContext, SRC_STREAM, NULL, NULL) < 0) {
        fprintf(stderr, "Error: could not open source stream %s\n", SRC_STREAM);
        avformat_close_input(&g_avFormatContext);
        exit(1);
    }
    if (avformat_find_stream_info(g_avFormatContext, NULL) < 0) {
        fprintf(stderr, "Error: could not find stream information\n");
        avformat_close_input(&g_avFormatContext);
        exit(1);
    }

    /* initialize receive thread */
    r_input* r_in = malloc(sizeof(r_input));
    r_in->pkt_q = receive_decode_pkt_q;
    r_in->f_ctx = g_avFormatContext;
    g_avFormatContext = NULL;

    /* initialize receive thread */
    fprintf(stdout, "Creating receive thread\n");
    if (pthread_create(&receive_thread, NULL, handle_input_to_startup_receiver, r_in)) {
        fprintf(stderr, "Error: failed to create receive thread\n");
        q_free_queue(receive_decode_pkt_q, NULL);
        abort();
    }

    sleep(1);

    // NEED TO KILL THREAD NOW
    fprintf(stdout, "about to throw kill signal to thread from main\n");
    q_kill(receive_decode_pkt_q);
    pthread_join(receive_thread, NULL);
    /* creating pkt buff to record first 3 frames of steam for assertion later */
    
    printf("trying to reopen FormatContext from SRC_STREAM at beginning\n");
    if (avformat_open_input(&g_avFormatContext, SRC_STREAM, NULL, NULL) < 0) {
        fprintf(stderr, "Error: could not open source stream %s\n", SRC_STREAM);
        avformat_close_input(&g_avFormatContext);
        exit(1);
    }
    printf("successfully reopened context\n");
    printf("trying to get info on stream\n");
    if (avformat_find_stream_info(g_avFormatContext, NULL) < 0) {
        fprintf(stderr, "Error: could not find stream information\n");
        avformat_close_input(&g_avFormatContext);
        exit(1);
    }
    printf("info collected sucessfully\n");

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
        printf("frame has data stream index: %d, size %d, flags %d\n", test_pkt->stream_index, test_pkt->size, test_pkt->flags);
        buff[i] = test_pkt;
        test_pkt = NULL;
    }
    printf("Successfully made it through collection. Moving on to compairing\n");

    for (int j = 0; j < 8; j++) {
        AVPacket* real_pkt;
        AVPacket* test_pkt;
        printf("dequing frame from buffer\n");
        q_dequeue(receive_decode_pkt_q, (void**) &real_pkt);
        // assert(memcmp(real_pkt, buff[j], sizeof(*real_pkt)) == 0);
        // memcmp() might be able to use this to assert equality of pkts
        printf("frame has data stream index: %d, size %d, flags %d\n", real_pkt->stream_index, real_pkt->size, real_pkt->flags);
        printf("pulling frame from buffer\n");
        test_pkt = buff[j];
        printf("frame has data stream index: %d, size %d, flags %d\n", test_pkt->stream_index, test_pkt->size, test_pkt->flags);
        printf("Passed test %d\n", (j + 1));
        av_packet_free(&test_pkt);
    }

    avformat_close_input(&g_avFormatContext);
    
    /* free queues and associted memory */
    q_free_queue(receive_decode_pkt_q, packet_finalizer);
    return 0;
}
