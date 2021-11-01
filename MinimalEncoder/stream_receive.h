#ifndef STREAM_RECEIVE_H
#define STREAM_RECEIVE_H

#include <stdbool.h>
#include <libavformat/avformat.h>
#include <pthread.h>

#include "lockedQueue/locked_queue.h"

typedef struct receive_input {
    l_queue* pkt_q;
    AVFormatContext* f_ctx;
} r_input;

// sets up call to setup_receiver with given arguments
void* handle_input_to_startup_receiver(void* arg_struct);

// sets up receiver. Opens formatcontext to read from stream
void setup_receiver(l_queue* queue_pkt_q, AVFormatContext* ctx);

// receives encoded frames from stream and sends them to decoder thread
void run_receiver();

#endif