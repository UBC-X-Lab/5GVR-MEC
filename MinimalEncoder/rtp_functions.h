#ifndef RTP_FUNCTIONS_H
#define RTP_FUNCTIONS_H

// wrap passed pkt data with rtp header information
void encapsulate_w_rtp_header(void* payload, void* out_pkt); 

// strip rtp header and allocate space for payload accordingly
void unpack_rtp_packet(void* in_pkt, void* payload);

#endif