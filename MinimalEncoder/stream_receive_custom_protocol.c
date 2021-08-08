

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <errno.h>

#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include "stream_receive.h"
#include "lockedQueue/locked_queue.h"

#define MAX 80
#define PORT 4096
#define ADDRESS "192.168.1.60"
#define SA struct sockaddr

l_queue* pkt_q = NULL;

static char* SRC_STREAM = NULL;
AVFormatContext* format_context = NULL;

static int tsock;

struct timeval tv;

void* handle_input_to_startup_receiver(void* arg_struct) {
    r_input* r_in = (r_input*) arg_struct;
    l_queue* queue_pkt_q = r_in->pkt_q;
    AVFormatContext* context = r_in->f_ctx;
    free(r_in);
    setup_receiver(queue_pkt_q, context);
} 

void setup_receiver(l_queue* queue_pkt_q, AVFormatContext* ctx) {
    pkt_q = queue_pkt_q;
    format_context = ctx;
	printf("Receiver Starting...\n");
    int listenfd, connfd;
    struct sockaddr_in servaddr, cli;
	int iResult;

	// Initialize socket
	iResult = (listenfd = socket(AF_INET, SOCK_STREAM, 0));
	if (iResult < 0) {
		fprintf(stderr, "RECEIVER: Socket creation failed with error: %d\n", iResult);
		return;
	}

	bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    iResult = bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    if (iResult < 0) {
        fprintf(stderr, "RECEIVER: Socket bind error.\n"); 
        return;
    }

    iResult = listen(listenfd, 5);
    if (iResult < 0) {
        fprintf(stderr, "RECEIVER: Error listening on socket\n");
        return;
    }

    printf("RECEIVER: waiting for a connection on port %d\n", PORT);
    fflush(stdout);
    int len = sizeof(cli);
    iResult = (connfd = accept(listenfd, (SA*) &cli, &len));
    if (iResult < 0) {
        fprintf(stderr, "RECEIVER: Server unable to establish connection\n");
        return;
    }
    tsock = connfd;
    run_receiver();

    //cleanup 
    close(connfd);
    close(listenfd);
    q_kill(pkt_q);
}

void run_receiver() {
    AVPacket* pkt;
    int iResult;
    fprintf(stdout, "running receive thread\n");
    while(1) {
        if (q_is_dead(pkt_q)) {
            fprintf(stdout, "Receive thread received kill signal\n");
            break;
        }
        pkt = av_packet_alloc();
        while(1) {
            fprintf(stdout, "RECEIVER: Receiving frame from stream\n");
            uint8_t recvlen[4];
            iResult = recv(tsock, (char*)recvlen, 4, MSG_WAITALL);
            printf("RECEIVER: Recieved length: iResult = %d\n", iResult);
			uint32_t len = -1;
            printf("byte1 = %x, byte2 = %x, byte3 = %x, byte4 = %x\n", recvlen[0], recvlen[1], recvlen[2], recvlen[3]);
			if (iResult > 0) {
                len = (recvlen[0] << 24) | (recvlen[1] << 16) | (recvlen[2] << 8) | (recvlen[3]);
			}
			else if (iResult == 0) {
				fprintf(stderr, "RECEIVER: Connection closing...\n");
			}
			else {
				fprintf(stdout, "RECEIVER: Connection closing...\n");
				return;
			}

            if (len != -1) {
                char* receivedata = (char*)malloc(len);
                iResult = recv(tsock, receivedata, len, MSG_WAITALL);
                printf("RECEIVER: Recieved data: %d\n", iResult);
                printf("RECEIVER: Received packet of len %d, read %d bytes\n", len, iResult);
				if (iResult > 0) {
					printf("Receiver got packet of len %d\n", len);
					int ret = av_new_packet(pkt, len);
					if (ret) {
						fprintf(stderr, "RECEIVER: Error allocating packet\n");
						return;
					}
					memcpy(pkt->data, receivedata, len);
					free(receivedata);
                    break;
				}
				else if (iResult == 0) {
					fprintf(stdout, "RECEIVER: Connection closing...\n");
				}
				else {
					fprintf(stderr, "RECEIVER: recv failed\n");
					return;
				}
            }
            av_packet_unref(pkt);
        }
        printf("RECEIVER: frame has data stream index: %d, size %d, flags %d\n", pkt->stream_index, pkt->size, pkt->flags);
        fprintf(stdout, "RECEIVER: New frame queued for decoding\n");
        q_enqueue(pkt_q, pkt);
        pkt = NULL;
    }
    // fprintf(stdout, "Receiver: Freeing packet used for receival\n");
    close(tsock);
    av_packet_free(&pkt);
    fprintf(stdout, "Receiver: Closing input\n");
}