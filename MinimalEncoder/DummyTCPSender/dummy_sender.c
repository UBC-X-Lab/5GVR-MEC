
#include "../focal_transmit.h"
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
#define destinationIP "192.168.1.60"
#define destinationPort "4096"
#define SA struct sockaddr
#define INVALID_SOCKET          (~0)//(SOCKET)(~0)
#define SOCKET_ERROR            (-1)

static transmit_interface_t *ti;
static int tsock;

void transmit() {
    int iResult;
	ti->ready = 1; // set to not ready because it has recieved a frame
	while (!ti->kill) // while new frames are still comming (ie encoder is live) 
	{
		pthread_mutex_lock(&ti->mutex);
		if (ti->newPacket)
		{
			uint32_t size = ti->pkt->size;
			const uint8_t *data = (uint8_t *)malloc(size * sizeof(uint8_t)); //allocate space for new frame
			memcpy(data, ti->pkt->data, size); // copy frame for transmission
			ti->newPacket = 0;
			pthread_mutex_unlock(&ti->mutex); // unlock mutex as soon as possible
            printf("Sending packet size\n");
            printf("size = %d\n", size);
            int sendval = htonl(size);
            printf("byte1 = %x, byte2 = %x, byte3 = %x, byte4 = %x\n", (sendval & 0xff000000) >> 24, (sendval & 0x00ff0000) >> 16, (sendval & 0x0000ff00) >> 8, (sendval & 0x000000ff));
			iResult = send(tsock, &sendval, 4, NULL);
            if (iResult < 0) {
                printf("Unable to send packet info\n");
            }
            printf("SENDING PACKET\n");
			iResult = send(tsock, data, size, NULL);
            if (iResult < 0) {
                printf("Unable to send packet\n");
            }
			free(data);
		}
		else
		{
			pthread_mutex_unlock(&ti->mutex);
		}
		sched_yield();
	}
	printf("Closing connection");
	// close the socket
	close(tsock);
}

void *transmit_connect(void *transmit_interface)
{
	ti = (transmit_interface_t *)transmit_interface;
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
	transmit();
}