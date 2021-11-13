#ifndef ENCODER_ENCODE_H
#define ENCODER_ENCODE_H

#include <stdbool.h>
#include <libavformat/avformat.h>
#include <pthread.h>

#include "focal_transmit.h"
#include "lockedQueue/locked_queue.h"

typedef struct encode_input {
    l_queue* frame_q;
    l_queue* pkt_q;
    int bitrate;
} e_input;

// encodes a given frame with the ctx context provided and stores result in pkt
void encode(AVCodecContext *ctx, AVPacket *pkt, AVFrame *frame);

// sends encoded packet to transmit thread
// static void send_packet(const AVPacket *pkt);

// sets up call to setup_encoder with given arguments
void* handle_input_to_startup_encoder(void* arg_struct);

// Setup ffmpeg state needed for encoding and context fields. Receives a single frame from queue to set parameters which is then passed to run_encoder for encoding
void setup_encoder(l_queue* _q, l_queue* _pq, int _bitrate);

// runs encoder which receives frames from queue encodes them into packets and then sends them to transmit thread
void run_encoder(AVFrame* init_frame);

#endif
