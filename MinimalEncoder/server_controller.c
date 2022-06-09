

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include "server_controller.h"
#include "focal_transmit.h"
#include "stream_decode.h"
#include "stream_receive.h"
#include "focal_encode.h"
#include "lockedQueue/locked_queue.h"

/* Parameters */
//static char* SRC_STREAM = "udp://@0.0.0.0:4000";
static char* SRC_STREAM = "../test_files/spiderman1080.mp4";
struct timeval tv;

pthread_attr_t attr;
static pthread_t transmit_thread;
static pthread_t encode_thread;
static pthread_t decode_thread;
static pthread_t receive_thread;

static l_queue* receive_decode_pkt_q;
static l_queue* decode_encode_frame_q;
static l_queue* encode_transmit_pkt_q;

/* ffmpeg state required variables for thread initialization */
static AVFormatContext *g_avFormatContext = NULL;

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
    // get pid for testing purpose
    pid_t pid = getpid();
    printf("Running on pid: %d\n", pid);

    int bitrate;
    int ret;
    size_t stacksize;

    /* set variables from arguments passed to main */
    if((argc != 3) && (argc != 2)){
        printf("invalid number of arguments. please provide 1 integer for bitrate\n& a different url if you wish to change the stream\n");
        exit(1);
    }
    printf("Encoding with bitrate: %d\n", atoi(argv[1])); //TODO turn this dynamic
    if (argc == 3) {
        strcpy(SRC_STREAM, argv[2]);
    }
    bitrate = atoi(argv[1]);

    /* allocate and initialize queues for thread pipeline */
    receive_decode_pkt_q = q_queue_alloc();
    decode_encode_frame_q = q_queue_alloc();
    encode_transmit_pkt_q = q_queue_alloc();

    if (pthread_create(&transmit_thread, NULL, transmit_connect, encode_transmit_pkt_q))
    {
        fprintf(stderr, "Error: failed to create transmit thread");
        avformat_close_input(&g_avFormatContext);
        q_free_queue(receive_decode_pkt_q, NULL);
        q_free_queue(decode_encode_frame_q, NULL);
        q_free_queue(encode_transmit_pkt_q, NULL);
        abort();
    }
    
    /* spin until transmit thread creates connection with unity end of the project */ 
    // while(!encode_transmit_pkt_q->ready) {
    //     sched_yield();
    // }

    // put thread into sleep while waiting for connection
    pthread_mutex_lock(&encode_transmit_pkt_q->mutex);
    while (!encode_transmit_pkt_q->ready)
        pthread_cond_wait(&encode_transmit_pkt_q->avail, &encode_transmit_pkt_q->mutex);
    pthread_mutex_unlock(&encode_transmit_pkt_q->mutex);

    printf("woke up!");

    /* get AVFormatContext for decode thread and receive thread - NOTE it should only be open for one thread at a time NOT THREAD SAFE*/
    av_register_all();
    avcodec_register_all();
    char* errbuf;
    if ((ret = avformat_open_input(&g_avFormatContext, SRC_STREAM, NULL, NULL)) < 0) {
        fprintf(stderr, "Error: could not open source stream %s\n", SRC_STREAM);
	av_strerror(ret, errbuf, 100);
	printf("error indicated by av_strerror: %s\n", errbuf);
        avformat_close_input(&g_avFormatContext);
        exit(1);
    }
    if (avformat_find_stream_info(g_avFormatContext, NULL) < 0) {
        fprintf(stderr, "Error: could not find stream information\n");
        avformat_close_input(&g_avFormatContext);
        exit(1);
    }

    /* here we initialize decode first because it should be listening on the receive_decode_pkt_q for the first frame which it uses to complete its setup. 
       in order to facilitate this with minimal wait time we create the decode thread before the receive thread.*/

    /* initialize decode thread */
    d_input* d_in = malloc(sizeof(d_input));
    d_in->avformat_context = g_avFormatContext;
    d_in->frame_q = decode_encode_frame_q;
    d_in->pkt_q = receive_decode_pkt_q;

    if (pthread_create(&decode_thread, NULL, handle_input_to_startup_decoder, d_in)) {
        fprintf(stderr, "Error: failed to create decode thread\n");
        avformat_close_input(&g_avFormatContext);
        q_free_queue(receive_decode_pkt_q, NULL);
        q_free_queue(decode_encode_frame_q, NULL);
        q_free_queue(encode_transmit_pkt_q, NULL);
        abort();
    }

    /* again we spin while decode finishes its setup with the avformat, we do not want the format to be open and in use in two different locations at once */
    // while(!receive_decode_pkt_q->ready) {
    //     sched_yield();
    // }

    // put thread into sleep while waiting for avformat setup
    pthread_mutex_lock(&receive_decode_pkt_q->mutex);
    while (!receive_decode_pkt_q->ready)
        pthread_cond_wait(&receive_decode_pkt_q->avail, &receive_decode_pkt_q->mutex);
    pthread_mutex_unlock(&receive_decode_pkt_q->mutex);

    /* initialize receive thread */
    r_input* r_in = malloc(sizeof(r_input));
    r_in->pkt_q = receive_decode_pkt_q;
    r_in->f_ctx = g_avFormatContext;
    g_avFormatContext = NULL;

    if (pthread_create(&receive_thread, NULL, handle_input_to_startup_receiver, r_in)) {
        fprintf(stderr, "Error: failed to create receive thread\n");
        avformat_close_input(&g_avFormatContext);
        q_free_queue(receive_decode_pkt_q, NULL);
        q_free_queue(decode_encode_frame_q, NULL);
        q_free_queue(encode_transmit_pkt_q, NULL);
        abort();
    }

    /* initialize encode thread */
    e_input* e_in = malloc(sizeof(e_in));
    e_in->frame_q = decode_encode_frame_q;
    e_in->pkt_q = encode_transmit_pkt_q;
    e_in->bitrate = bitrate;

    if (pthread_create(&encode_thread, NULL, handle_input_to_startup_encoder, e_in)) {
        fprintf(stderr, "Error: failed to create encode thread\n");
        avformat_close_input(&g_avFormatContext);
        q_free_queue(receive_decode_pkt_q, NULL);
        q_free_queue(decode_encode_frame_q, NULL);
        q_free_queue(encode_transmit_pkt_q, NULL);
        abort();
    }

    /* keep process alive untill all threads have finished - if transmit thread finishes signal kill to other threads*/
    pthread_join(transmit_thread, NULL);
    fprintf(stdout, "Connection with client ended, shutting down\n");
    q_kill(decode_encode_frame_q);
    q_kill(receive_decode_pkt_q);
    q_kill(encode_transmit_pkt_q);
    pthread_join(encode_thread, NULL);
    pthread_join(decode_thread, NULL);
    pthread_join(receive_thread, NULL);

    /* free queues and associted memory */
    fprintf(stdout, "freeing pipeline\n");
    q_free_queue(decode_encode_frame_q, frame_finalizer);
    q_free_queue(receive_decode_pkt_q, packet_finalizer);
    q_free_queue(encode_transmit_pkt_q, packet_finalizer);
    return 0;
}
