

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

#define RTP_PORT "5000"
#define TCP_PORT "5001"
#define DESTINATION_IP "192.168.1.60"

fd_set master; // holds all tracked file descriptors
int fdmax; // max filedescriptor in master
static transmit_interface_t *ti;

void transmit() {
    int sendall(int s, char *buf, int *len); // declaration of sendall function to avoid partial sends (for TCP messages)

    fd_set read_fds; // set to hold tcp socket fd for control requests from server
    fd_set send_fds; // set to hold sockets used for sending data
    int ret;

    // clear file descriptor sets before use
    FD_ZERO(&read_fds);
    FD_ZERO(&send_fds);
    char send_buf[65507]; //buffer to store rtp packet with header into before send (max size of udp packet)
    int nbytes;

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

void *transmit_connect(void *transmit_interface) {
    void *get_in_addr(struct sockaddr *sa);

    ti = (transmit_interface_t *)transmit_interface;

    int tcp_sock;
    int rtp_sock;
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen;

    char remoteIP[INET6_ADDRSTRLEN];

    // int yes = 1; // used in setsockopt() with SO_REUSEADDR to allow no wait to bind to port below
    int i, j, ret;

    struct addrinfo hints, *res, *p;

    // clear file descriptor sets before use
    FD_ZERO(&master);

    // setup hints to resolve connection to server with tcp connection
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	// Resolve the server address and por
    printf("Resolving server address to connect to\n");
	ret = getaddrinfo(DESTINATION_IP, TCP_PORT, &hints, &res);
	if (ret != 0) {
		printf("getaddrinfo failed with error: %s\n", gai_strerror(ret));
		return;
	}

	// walk through res list and attempting to connect to server
    printf("iterating through result to establish strong connection\n");
	for (p = res; p != NULL; p = p->ai_next) {
        // Create a SOCKET for connecting to server
        tcp_sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (tcp_sock < 0) {
		    printf("socket creation failed...\n");
		    continue;
        }
        else {
            printf("Socket successfully created..\n");
        }
		// Connect to server.
        printf("Attempting to connect to socket: %d\n", tcp_sock);
		ret = connect(tcp_sock, p->ai_addr, p->ai_addrlen);
		if (ret == -1) {
			close(tcp_sock);
			continue;
		}
		break;
	}

	freeaddrinfo(res);

    // if p is null then loop walked through the entire list and didn't find any viable options
	if (p == NULL) {
		printf("Unable to connect to server!\n");
		return;
	}

    // get printable address connected to and the socket used to print message
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), remoteIP, sizeof remoteIP);
    printf("Connection established with server at %s via tcp on socket %d\n", remoteIP, tcp_sock);

    FD_SET(tcp_sock, &master);
    fdmax = tcp_sock;
	
	// reset hints and setup for rtp socket creation with getaddrinfo()
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    ret = getaddrinfo(DESTINATION_IP, RTP_PORT, &hints, &res); // maybe need a call to reset res before this call
    if (ret != 0) {
        fprintf(stderr, "error occured in getaddrinfo call with error %s\n", gai_strerror(ret));
        return;
    }

    // walk this list to establish strong connection
    printf("iterating through result to establish strong connection\n");
	for (p = res; p != NULL; p = p->ai_next) {
        // Create a SOCKET for connecting to server
        rtp_sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (rtp_sock < 0) {
		    printf("socket creation failed...\n");
		    continue;
        }
        else {
            printf("Socket successfully created..\n");
        }
		// Connect to server.
        printf("Attempting to connect to socket: %d\n", rtp_sock);
		ret = connect(rtp_sock, p->ai_addr, p->ai_addrlen); // since this is a udp connection this doesnt actually connect, it just allows easier call send() instead of sendto()
		if (ret == -1) {
			close(rtp_sock);
			continue;
		}
		break;
	}

	freeaddrinfo(res);

    // if p is null then loop walked through the entire list and didn't find any viable options
	if (p == NULL) {
		printf("Unable to connect to server!\n");
		return;
	}

    // get printable address connected to and the socket used to print message
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), remoteIP, sizeof remoteIP);
    printf("Connection established with server at %s via udp on socket %d\n", remoteIP, rtp_sock);

    // add rtp_sock to master file descriptor set
    FD_SET(rtp_sock, &master);
    if (rtp_sock > fdmax) {
        fdmax = rtp_sock;
    }

	transmit();
}


// fetch the address from sockaddr struct for either IPv4 or IPv6 connections
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// function which enseures all data is sent. Use same as send
int sendall(int s, char *buf, int *len) {
    int total = 0; // how many bytes we've sent
    int bytesleft = *len; // how many we have left to send
    int n;
    while(total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
        }
    *len = total; // return number actually sent here

    return n==-1?-1:0; // return -1 on failure, 0 on success
}
