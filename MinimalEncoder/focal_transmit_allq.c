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

static l_queue* pkt_q;
static int tsock;

struct timeval tv;

void transmit() {
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
			printf("size = %d\n", size);
			ret = send(tsock, &size, 4, NULL);
            if (ret < 0) {
                printf("Unable to send packet info\n");
            }
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,returning,send,%f,size:%d,pts:n/a\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), ret);
			printf("SENDING PACKET\n");
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,calling,send,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			ret = send(tsock, data, size, NULL);
            if (ret < 0) {
                printf("Unable to send packet\n");
            }
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,returning,send,%f,size:%d,pts:n/a\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), ret);
			free(data);
			av_packet_free(&pkt);
		}
	}
}

void *transmit_connect(void *pkt_queue)
{
	pkt_q = (l_queue*) pkt_queue;
	int yes = 1;// for setsockopt() SO_REUSEADDR, below
	int ret;
	
	int sockfd, connfd, len;

	struct sockaddr_in servaddr, cli;
	struct sockaddr_storage their_addr;
	struct addrinfo hints, *serverinfo, *p;
	socklen_t sin_size;

	char s[INET6_ADDRSTRLEN]; // to store connection addr

	//setup hints and getaddr info for establishing good connection
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET; // IPV4 or 6 doesn't matter
	hints.ai_socktype = SOCK_STREAM; // this enables a TCP connection 
	hints.ai_flags = AI_PASSIVE;
	if ((ret = getaddrinfo(NULL, PORT, &hints, &serverinfo)) != 0) {
		fprintf(stdout, "getaddrinfo: %s\n", gai_strerror(ret));
		return 1;
	}

	// walk serverinfo linked list and bind to first valid address
	for (p = serverinfo; p != NULL; p = p->ai_next) {
		//create socket
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("transmit_server: socket");
			continue; 
		}
		printf("Socket successfully created..\n");
		// to avoid address already in use error messages and allow binding
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		// attempt to bind to socket
		if ((ret = bind(sockfd, p->ai_addr, p->ai_addrlen)) == -1) {
			close(sockfd);
			perror("transmit_server: bind");
			continue;
		}

		printf("Socket successfully binded..\n");
		//found a good one
		break; 
	}
	// don't need this anymore
	freeaddrinfo(serverinfo);

	// check to make sure socket actually binded and that the loop did not just run out of entries
	if (p == NULL) {
		fprintf(stderr, "transmit_server: failed to bind\n");
		exit(1);
	}

    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(1); 
    } 
	printf("Server listening...\n");
	void* get_in_addr(struct sockaddr *sa);

	while(1) {
		sin_size = sizeof their_addr;
		printf("Waiting for connection...\n");
		// accept connection
    	connfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size); 
    	if (connfd < 0) { 
        	printf("server accept failed...%s\n", gai_strerror(errno));
        	continue; 
    	}
		printf("server accepted client\n");
		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&cli), s, sizeof s);
		printf("transmit_server: accepted connection from %s\n", s);
		break;

	}
	
	tsock = connfd;
	// signal ready for encoder
	q_ready(pkt_queue);

	//enter transmit loop
	transmit();
	
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
