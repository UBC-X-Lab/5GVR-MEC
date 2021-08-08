#ifndef ENCODER_TRANSMIT_H
#define ENCODER_TRANSMIT_H

#include <stdbool.h>
#include <libavformat/avformat.h>
#include <pthread.h>

typedef struct transmit_interface
{
    pthread_mutex_t mutex; //This mutex should be held when accessing this struct
    bool ready;
    bool kill;
    bool newPacket;
    const AVPacket* pkt;
} transmit_interface_t;

void *transmit_connect(void* transmit_interface);

void transmit();

#endif