#ifndef SERVER_H
#define SERVER_H

#include <stdbool.h>
#include <libavformat/avformat.h>
#include <pthread.h>

#include "lockedQueue/locked_queue.h"

// a finalizer for frames stored in queue
void frame_finalizer(void* frame_pntr);

// a finalizer for packets stored in queue
void packet_finalizer(void* pkt_pntr);

#endif