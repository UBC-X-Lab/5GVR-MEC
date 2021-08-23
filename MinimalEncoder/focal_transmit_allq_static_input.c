#include "focal_transmit_allq.h"
#include "buildtimestamp.h"
#include "lockedQueue/locked_queue.h"
#include <time.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAX 80
#define PORT "3495"
#define SA struct sockaddr

static l_queue* pkt_q;
static int tsock;

struct timeval tv;

void transmit() {
	printf("Transmit server starting...\n");
	AVPacket* pkt;
	int ret;
	while(1) {
        if (q_is_dead(pkt_q)) {
            printf("Transmit: Received signal to terminate, transmit shutting down\n");
            break;
        }
        /* grab pkt off of pkt_q from encode thread*/
        gettimeofday(&tv, NULL);
        fprintf(stderr, "focal_transmit,calling,q_dequeue,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
        if (q_dequeue(pkt_q, (void**) &pkt) < 0) {
            fprintf(stderr, "transmit: stream ended. Transmitter shutting down\n");
            q_kill(pkt_q); // signal kill on pkt queue so encoder thread knows to terminate
            return; 
        }
        gettimeofday(&tv, NULL);
        fprintf(stderr, "focal_transmit,returning,q_dequeue,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), pkt->size, pkt->pts);

		if (pkt != NULL) {
			uint32_t size = pkt->size;
			const uint8_t *data = (uint8_t *)malloc(size * sizeof(uint8_t)); //allocate space for new frame
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,calling,memcpy,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), pkt->size, pkt->pts);
			memcpy(data, pkt->data, size); // copy frame for transmission
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,returning,memcpy,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,calling,send,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			send(tsock, &size, 4,NULL);
			printf("size = %d\n", size);
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,returning,send,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			printf("SENDING PACKET\n");
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,calling,send,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			send(tsock, data, size, NULL);
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,returning,send,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			free(data);
			av_free_packet(pkt);
		}
	}
}

void *transmit_connect(void *pkt_queue)
{
	pkt_q = (l_queue*) pkt_queue;
	int yes = 1;// for setsockopt() SO_REUSEADDR, below
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and varification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	//servaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); // to avoid address already in use error messages and allow binding

	// Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 

	// Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server accept failed...\n"); 
        exit(0); 
    }
    printf("server accept the client...\n"); 

	// function for chat
	tsock = connfd;
	transmit();
	q_ready(pkt_queue);
	//close socket
	printf("Closing connection");
	close(tsock);
}

// get sockaddr, IPV4/6 check BEEJ's guide for more info on types seen here
void* get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*) sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*) sa)->sin6_addr);
}
