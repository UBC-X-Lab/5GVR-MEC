/*****************************************************************************
 * focal_connect.h: connects to remote server for position data used in
 *****************************************************************************
 * Copyright (C) 2003-2020 x264 project
 *
 * Authors: Ailin Saggau-Lyons <ailin.saggau@alumni.ubc.ca>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@x264.com.
 *****************************************************************************/

#include "focal_connect.h"
#include "common/common.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXBUFLEN 188

enum connection_status {disconnected, connected_send_parameters, connected_awaiting_data};

void *x264_focal_connect(x264_focal_input_t* ptr){
    //Init
    char* host = "0.0.0.0"; //The IP address to connect to
    char* controlPort = "27870"; // the port connected to for TCP "control" connection
    char* dataPort = "27871"; // the port listened on for UDP "data" connection
    clock_t resend_parameters;

    enum connection_status cStatus = disconnected;

    int sockfd, d_sockfd, dtcp_sockfd, numbytes;  
	struct addrinfo hints, d_hints, *servinfo, *d_servinfo, *p, *d_p;
    char d_buf[MAXBUFLEN];
	int rv, ret;
    int yes = 1; // for setsockopt() SO_REUSEADDR, below
    struct sockaddr_in servaddr, cli;
	struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];

    x264_focal_input_t* pos_data = ptr;

    x264_pthread_mutex_lock(&pos_data->mutex);
    pos_data->status = uninitialized;
    x264_pthread_mutex_unlock(&pos_data->mutex);

    if( x264_pthread_mutex_init( &pos_data->mutex, NULL ) ){
        printf("focal_connect: failed creating mutex\n");
        return -1; 
    }

    int isTCP = 0;
    char* input_protocol = getenv("PROTOCOL");
    if(input_protocol!=NULL) {
        // strcmp returns 0 if they are equal
        isTCP = (!strcmp("TCP", input_protocol));
    }


    while(1){
        switch(cStatus){
            case disconnected:

                x264_pthread_mutex_lock(&pos_data->mutex);
                if(pos_data->status == valid){
                    pos_data->status = stale;
                }
                x264_pthread_mutex_unlock(&pos_data->mutex);

            //Open socket for TCP control connection
                sockfd = x264_tcp_connection_helper(controlPort);
                if (send(sockfd, "r34\n", 4, 0) == -1)
                    printf("sendError\n");
                if (send(sockfd, "p3491\n", 6, 0) == -1)
                    printf("sendError\n");
                cStatus = connected_awaiting_data;
                printf("Focal is running...\n");

            //Open socket for UDP data connection
                memset(&d_hints, 0, sizeof d_hints);
	            d_hints.ai_family = AF_UNSPEC;
                if (isTCP) {
                    d_hints.ai_socktype = SOCK_STREAM;
                } else {
                    d_hints.ai_socktype = SOCK_DGRAM;
                }
                d_hints.ai_flags = AI_PASSIVE;

                if ((rv = getaddrinfo(NULL, dataPort, &d_hints, &d_servinfo)) != 0) {
                    printf("Error in focal_connect: Invalid address: %s\n", gai_strerror(rv));
                    return 1;
                }

                // loop through all the results and connect to the first we can
                for(d_p = d_servinfo; d_p != NULL; d_p = d_p->ai_next) {
                    if ((d_sockfd = socket(d_p->ai_family, d_p->ai_socktype, d_p->ai_protocol)) == -1) {
                        perror("MADE IT IN HERE THE SOCKET DID NOT START");
                        continue;
                    }
                    // to avoid address already in use error messages and allow binding
		            if (setsockopt(d_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			            perror("setsockopt");
                        wait(1000); //Wait one second and try again
			            break;
		            }
                    if(bind(d_sockfd, d_p->ai_addr, d_p->ai_addrlen)){
                        perror("[Focal connect] bind");
                        close(d_sockfd);
                        continue;
                    }
                    break;
                }
                if (d_p == NULL) {
                    printf("focal_connect: failed to bind to socket\n");
                    wait(1000); //Wait one second and try again
                    break;
                }

                if (isTCP) {
                    // Now server is ready to listen and verification 
                    if ((listen(d_sockfd, 5)) != 0) { 
                        printf("Listen failed...\n"); 
                        exit(1); 
                    } 
	                printf("Server listening...\n");
	                void* x264_get_in_addr(struct sockaddr *sa);

	                while(1) {
		                sin_size = sizeof their_addr;
		                printf("Waiting for connection...\n");
		                // accept connection
    	                dtcp_sockfd = accept(d_sockfd, (struct sockaddr *)&their_addr, &sin_size); 
    	                if (dtcp_sockfd < 0) { 
                    	printf("server accept failed...%s\n", strerror(errno));
                        	continue; 
    	                }
		                printf("server accepted client\n");
		                inet_ntop(their_addr.ss_family, x264_get_in_addr((struct sockaddr *)&cli), s, sizeof s);
		                printf("x264_focal_connect: accepted connection from %s\n", s);
                        close(d_sockfd);
		                break;
	                }
                }

                d_sockfd = dtcp_sockfd;

                if(fcntl(d_sockfd, F_SETFL, O_NONBLOCK) == -1){
                    printf("Data socket could not be set to non-blocking");
                }
                freeaddrinfo(d_servinfo); // all done with this structure

                cStatus = connected_send_parameters;
                break;
            case connected_send_parameters:
                resend_parameters = clock() + CLOCKS_PER_SEC;
                if (send(sockfd, "r34\n", 4, 0) == -1)
                    printf("sendError\n");
                if (send(sockfd, "p3491\n", 6, 0) == -1)
                    printf("sendError\n");
                cStatus = connected_awaiting_data;
                printf("Focal is running...\n");
                break;
            case connected_awaiting_data:
                if(clock() >= resend_parameters){
                    cStatus = connected_send_parameters;
                }
                // struct sockaddr_in sin;
                // socklen_t len = sizeof(sin);
                // if (getsockname(d_sockfd, (struct sockaddr *)&sin, &len) == -1)
                //     perror("getsockname");
                // else
                //     printf("port number %d\n", ntohs(sin.sin_port));

                if (isTCP) {
                    if ((numbytes = recv(d_sockfd, d_buf, MAXBUFLEN-1, 0)) == -1) {
                        break;
                    }
                } else {
                    if ((numbytes = recvfrom(d_sockfd, d_buf, MAXBUFLEN-1 , 0, NULL, NULL)) == -1) {
                        break;
                    }
                }
                if(numbytes != 12){
                    printf("Error in focal_connect: Received incorrect number of bytes");
                }else{
                    float* xp = (float*) &d_buf[0];
                    float* yp = (float*) &d_buf[4];
                    float* zp = (float*) &d_buf[8];
                    float x = *xp;
                    float y = *yp;
                    float z = *zp;
                    x264_pthread_mutex_lock(&pos_data->mutex);
                    pos_data->status = valid;
                    pos_data->x = x;
                    pos_data->y = y;
                    pos_data->z = z;
                    x264_pthread_mutex_unlock(&pos_data->mutex);
                }
                break;
        }
    }
}

//get sockaddr, IPv4 or IPv6:
void *x264_get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// helper function to listen and set up tcp connection
int x264_tcp_connection_helper(char* port) {
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
	if ((ret = getaddrinfo(NULL, port, &hints, &serverinfo)) != 0) {
		fprintf(stdout, "%s: port=%s %s\n", __func__, port, gai_strerror(ret));
		return 1;
	}

	// walk serverinfo linked list and bind to first valid address
	for (p = serverinfo; p != NULL; p = p->ai_next) {
		//create socket
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("[Focal connect]socket");
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
			perror("[Focal connect] bind");
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
		fprintf(stderr, "[Focal connect] failed to bind\n");
		exit(1);
	}

    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("[Focal connect] Listen failed...\n"); 
        exit(1); 
    } 
	printf("[Focal connect] listening...\n");

	while(1) {
		sin_size = sizeof their_addr;
		printf("[Focal connect] Waiting for connection...\n");
		// accept connection
    	connfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size); 
    	if (connfd < 0) { 
        	printf("server accept failed...%s\n", gai_strerror(errno));
        	continue; 
    	}
		printf("server accepted client\n");
		inet_ntop(their_addr.ss_family, x264_get_in_addr((struct sockaddr *)&cli), s, sizeof s);
		printf("[Focal connect] accepted connection from %s\n", s);
		break;

	}
	return connfd;
}
