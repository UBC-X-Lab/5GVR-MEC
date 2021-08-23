/* rtp functions */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAX_UDP_SIZE 65507
#define HEADER_SIZE 12

void encapsulate_w_rtp_header(int hostaddr, int last_seq_num, timeval* tv, void* in_data, void* return_rtp_pkt){
    // packets will all have very similar format for our needs
    char* header = mallloc(HEADER_SIZE);

    // set up header parameters
    char nal_unit = 1; //we force this for speed
    char version = 0b10;// version 2 of rtp
    char extension = 0; // not needed for our packets
    char cc = 0; // only single contributor so no cc's
    char marker = 0; 
    if (last_seq_num == -1) {
        marker == 1; // set marker to -1 in this case (last frame)
    }
    int timestamp = gettimeofday(tv, NULL);

    // padding calculations 
    char padding_present = 0; 
    int padding_size_needed = 0;

    //caluclation for how much padding needed


    //assemble header

    header[0] = (version << 6) | (padding_present << 5) | (extension << 4) | cc);
    header[1] = (marker << 7) | nal_unit; 
    header[2] = (char) (last_seq_num  >> 8);
    header[3] = (char) (last_seq_num);
    memcpy(header+4, timestamp, 4);
    memcpy(header+8, hostaddr, 4);

    // fill buffer with fully encapsulated packet
    memcpy(return_rtp_pkt, header, HEADER_SIZE);
    memcpy(return_rtp_pkt+HEADER_SIZE, in_data, sizeof(in_data));
    memset(return_rtp_pkt+HEADER_SIZE+sizeof(in_data), 0, padding_size_needed);
} 

int unpack_rtp_packet(void* in_pkt, void* return_data, int* seq_num){
    // unwrap packet header bit by bit
    char* pkt = (char*) in_pkt;
    char first_byte = pkt[0];

    // check to make sure packet matches our rtp format
    int version = (int) ((first_byte & 0b11000000) >> 6);
    int extension = (int) ((first_byte & 0b00010000) >> 4);
    int cc = (int) (first_byte & 0b00001111); 

    if ((version != 2) || (extension == 0) || (cc == 0)) {
        fprintf(stderr, "Invalid rtp packet received, not suppported by application!\n"); 
        memset(return_data, 0, sizeof (return_data)); 
        return -1;
    }

    // check if padding present and if so store the value for use later
    int padding_present = (int) ((first_byte & 0b00100000) >> 5);
    char padding_size = 0;
    if (padding_present != 0) {
        padding_size = pkt[sizeof(pkt) - 1];
    }

    // set seq_num to the sequence number in the header
    *seq_num = ntohs((((short) pkt[2]) << 8) | ((short) pkt[3]));

    // check marker to find out if last pkt
    char second_byte = pkt[1];
    int marker = (int) (second_byte >> 7);
    if (marker == 1) {
        *seq_num = -1; // indicates this is the last frame of the stream
    }
    
    // save nal unit first byte
    char nal_unit = ((second_byte << 1) >> 1);
    
    // to confirm sender is correct we could use SSRC the identifier (but not needed)

    // set return_data to the rest of the packet minus the padding
    memcpy(return_data, (pkt+HEADER_SIZE), sizeof(in_pkt) - HEADER_SIZE - padding_size);
}
