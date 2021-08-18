#include "focal_transmit.h"
#include "buildtimestamp.h"
#include <time.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80
#define PORT 3495
#define SA struct sockaddr

static transmit_interface_t *ti;
static int tsock;

struct timeval tv;

void transmit()
{
	ti->ready = 1; // set to not ready because it has recieved a frame
	while (!ti->kill) // while new frames are still comming (ie encoder is live) 
	{
		pthread_mutex_lock(&ti->mutex);
		if (ti->newPacket)
		{
			uint32_t size = ti->pkt->size;
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,n/a,transmit_interface_recieve,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), ti->pkt->size, ti->pkt->pts);
			const uint8_t *data = (uint8_t *)malloc(size * sizeof(uint8_t)); //allocate space for new frame
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,calling,memcpy,%f,size:%d,pts:%ld\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec), ti->pkt->size, ti->pkt->pts);
			memcpy(data, ti->pkt->data, size); // copy frame for transmission
			gettimeofday(&tv, NULL);
			fprintf(stderr, "focal_transmit,returning,memcpy,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
			ti->newPacket = 0;
			pthread_mutex_unlock(&ti->mutex); // unlock mutex as soon as possible
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
		}
		else
		{
			pthread_mutex_unlock(&ti->mutex);
		}
		gettimeofday(&tv, NULL);
		fprintf(stderr, "focal_transmit,calling,sched_yield,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
		sched_yield();
		gettimeofday(&tv, NULL);
		fprintf(stderr, "focal_transmit,returning,sched_yield,%f\n", buildtimestamp((long) tv.tv_sec, (long) tv.tv_usec));
	}
	printf("Closing connection");
	// close the socket
	close(tsock);
}

void *transmit_connect(void *transmit_interface)
{
	int yes = 1;// for setsockopt() SO_REUSEADDR, below
	ti = (transmit_interface_t *)transmit_interface;
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
    else
        printf("server accept the client...\n"); 

	// function for chat
	tsock = connfd;
	transmit();
}
