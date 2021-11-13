
#include "../buildtimestamp.h"
#include "../focal_transmit.h"
#include "../lockedQueue/locked_queue.h"
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

#define MAX 80
#define destinationIP "74.198.53.47"
#define destinationPort "27873"
#define SA struct sockaddr
#define INVALID_SOCKET          (~0)//(SOCKET)(~0)
#define SOCKET_ERROR            (-1)

l_queue* send_pkt_q = NULL;
static int tsock;

struct timeval tv;

void transmit() {
    AVPacket* pkt;
	int ret;
	while(1) {
        if (q_is_dead(send_pkt_q)) {
            printf("Transmit: Received signal to terminate, transmit shutting down\n");
            break;
        }
        /* grab pkt off of send_pkt_q from encode thread*/
        gettimeofday(&tv, NULL);
        fprintf(stderr, "dummy_sender,calling,q_dequeue,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
        if (q_dequeue(send_pkt_q , (void**) &pkt) < 0) {
            fprintf(stderr, "transmit: stream ended. Transmitter shutting down\n");
            q_kill(send_pkt_q); // signal kill on pkt queue so encoder thread knows to terminate
            return; 
        }
        gettimeofday(&tv, NULL);
        fprintf(stderr, "dummy_sender,returning,q_dequeue,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), pkt->size, pkt->pts);
		
		if (pkt != NULL) {
			uint32_t size = pkt->size;
			const uint8_t *data = (uint8_t *)malloc(size * sizeof(uint8_t)); //allocate space for new frame
			gettimeofday(&tv, NULL);
			fprintf(stderr, "dummy_sender,calling,memcpy,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), pkt->size, pkt->pts);
			memcpy(data, pkt->data, size); // copy frame for transmission
			gettimeofday(&tv, NULL);
			fprintf(stderr, "dummy_sender,returning,memcpy,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			

            printf("Sending packet size\n");
            printf("size = %d\n", size);
            int sendval = htonl(size);
            printf("byte1 = %x, byte2 = %x, byte3 = %x, byte4 = %x\n", (sendval & 0xff000000) >> 24, (sendval & 0x00ff0000) >> 16, (sendval & 0x0000ff00) >> 8, (sendval & 0x000000ff));
			gettimeofday(&tv, NULL);
			fprintf(stderr, "dummy_sender,calling,send,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			ret = send(tsock, &sendval, 4, NULL);
            if (ret < 0) {
                printf("Unable to send packet info\n");
            }
			gettimeofday(&tv, NULL);
			fprintf(stderr, "dummy_sender,returning,send,%f,size:%d,pts:n/a\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), ret);
            printf("SENDING PACKET\n");
			gettimeofday(&tv, NULL);
			fprintf(stderr, "dummy_sender,calling,send,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			ret = send(tsock, data, size, NULL);
            if (ret < 0) {
                printf("Unable to send packet\n");
            }
			gettimeofday(&tv, NULL);
			fprintf(stderr, "dummy_sender,returning,send,%f,size:%d,pts:n/a\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), ret);
			free(data);
			av_packet_free(&pkt); // this sets pointer to NULL after free
		}
	}
}

void *transmit_connect(void *pkt_queue)
{
	send_pkt_q = (l_queue*) pkt_queue;
	int sockfd, len, iResult;
	struct sockaddr_in servaddr;
    struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;
	// socket create and varification
	sockfd = INVALID_SOCKET;
	int iSendResult;
	bzero(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	// Resolve the server address and port
    printf("Resolving server address to connect to\n");
	iResult = getaddrinfo(destinationIP, destinationPort, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		return;
	}

	// Attempt to connect to an address until one succeeds
    printf("iterating through result to establish strong connection\n");
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        // Create a SOCKET for connecting to server
        sockfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (sockfd == -1) {
		    printf("socket creation failed...\n");
		    exit(0);
        }
        else {
            printf("Socket successfully created..\n");
        }
		// Connect to server.
        printf("Attempting to connect to socket: %d\n", sockfd);
		iResult = connect(sockfd, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			close(sockfd);
			sockfd = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (sockfd == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		return;
	}
    printf("Connection established with server\n");
	// function for chat
	tsock = sockfd;
	q_ready(send_pkt_q);
	transmit();
	
	printf("Closing connection");
	// close the socket
	close(tsock);
}
