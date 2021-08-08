#ifndef STREAM_DECODE_H
#define STREAM_DECODE_H

#include <stdbool.h>
#include <libavformat/avformat.h>
#include <pthread.h>

#include "lockedQueue/locked_queue.h"

typedef struct decode_input {
    l_queue* pkt_q;
    l_queue* frame_q;
    AVFormatContext* avformat_context;
} d_input;

// opens codec context and sets decoder to decoder sensed from stream. Sets stream_idx to best stream found. 
static int open_codec_context(int *stream_idx,
                              AVCodecContext **dec_ctx, AVFormatContext *fmt_ctx, enum AVMediaType type);

// decodes given pkt with ctx. This process allocates a new frame with decoded information. Takes care of pkt free.
int decode(AVCodecContext *ctx, AVPacket *pkt, AVFrame *frame);

// sets up call to setup_decoder with given arguments
void* handle_input_to_startup_decoder(void* arg_struct);

// sets up the context for the decoder to run
void setup_decoder(l_queue* queue_pkt_q, l_queue* queue_frame_q, AVFormatContext* fmt_ctx);

// pulls frames from pkt_queue, decodes them and them places decoded frames on frame_queue. 
void run_decoder();

#endif