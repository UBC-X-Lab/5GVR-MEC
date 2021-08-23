#ifndef RTP_FUNCTIONS_H
#define RTP_FUNCTIONS_H

#include <sys/time.h>
#include <libavformat/avformat.h>

void encapsulate_w_rtp_header(int last_seq_num, timeval tv, void* in_data, void* return_rtp_pkt); 

int unpack_rtp_packet(void* in_pkt, void* return_data, int* seq_num);

#endif