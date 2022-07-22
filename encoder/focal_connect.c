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
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


#define MAXBUFLEN 188

enum connection_status {disconnected, connected_awaiting_data};

void *x264_focal_connect(x264_focal_input_t* ptr){
    /* do not crash on SIGPIPE */
    signal(SIGPIPE, SIG_IGN);

    //Init
    // char* dataPort = "27871"; // the port listened on for UDP "data" connection
    char* dataPortEnv = getenv("UDP_PORT");
    char* dataPort;
    if (dataPortEnv == NULL){
        dataPort = "27871";
        printf("Data port not given, set to default 27871\n");
    }else{
        dataPort = dataPortEnv;
        printf("Setup Head Direction Server at Port %s\n", dataPort);
    }

    enum connection_status cStatus = disconnected;

    int d_sockfd, numbytes;  // dtcp_sockfd
	struct addrinfo hints, d_hints, *servinfo, *d_servinfo, *p, *d_p;
    
    char d_buf[MAXBUFLEN];
    
	int rv, ret;
    int yes = 1; // for setsockopt() SO_REUSEADDR, below

	struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];

    struct sockaddr_in cliaddr;
    socklen_t cliaddr_len;
    char s_buf[MAXBUFLEN];
    int forward_ready = 0;

    // memset(&cliaddr, 0, sizeof(cliaddr));

    x264_focal_input_t* pos_data = ptr;

    if( x264_pthread_mutex_init( &pos_data->mutex, NULL ) ){
        printf("focal_connect: failed creating mutex\n");
        return -1; 
    }

    x264_pthread_mutex_lock(&pos_data->mutex);
    pos_data->status = uninitialized;
    x264_pthread_mutex_unlock(&pos_data->mutex);

    // int isTCP = 0;
    // char* input_protocol = getenv("PROTOCOL");
    // if(input_protocol!=NULL) {
    //     // strcmp returns 0 if they are equal
    //     isTCP = (!strcmp("TCP", input_protocol));
    // }

    int isHLClient = 0;
    char* HLClient = getenv("HLCLIENT");
    if (HLClient != NULL){
        isHLClient = atoi(HLClient);
    }


    while(1){
        switch(cStatus){
            case disconnected:

                x264_pthread_mutex_lock(&pos_data->mutex);
                if(pos_data->status == valid){
                    pos_data->status = stale;
                }
                x264_pthread_mutex_unlock(&pos_data->mutex);

                //Open socket for position data connection
                memset(&d_hints, 0, sizeof d_hints);
	            d_hints.ai_family = AF_UNSPEC;
                // if (isTCP) {
                //     d_hints.ai_socktype = SOCK_STREAM;
                // } else {
                d_hints.ai_socktype = SOCK_DGRAM;
                //}
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

                // if (isTCP) {
                //     // Now server is ready to listen and verification 
                //     if ((listen(d_sockfd, 5)) != 0) { 
                //         printf("Listen failed...\n"); 
                //         exit(1); 
                //     } 
	            //     printf("Server listening...\n");
	            //     void* x264_get_in_addr(struct sockaddr *sa);

	            //     while(1) {
		        //         sin_size = sizeof their_addr;
		        //         printf("Waiting for connection...\n");
		        //         // accept connection
    	        //         dtcp_sockfd = accept(d_sockfd, (struct sockaddr *)&their_addr, &sin_size); 
    	        //         if (dtcp_sockfd < 0) { 
                //     	printf("server accept failed...%s\n", strerror(errno));
                //         	continue; 
    	        //         }
		        //         printf("server accepted client\n");
		        //         inet_ntop(their_addr.ss_family, x264_get_in_addr((struct sockaddr *)&cli), s, sizeof s);
		        //         printf("x264_focal_connect: accepted connection from %s\n", s);
                //         // close(d_sockfd);
		        //         break;
	            //     }
                //     d_sockfd = dtcp_sockfd;
                // }

                freeaddrinfo(d_servinfo); // all done with this structure

                cStatus = connected_awaiting_data;
                break;
            case connected_awaiting_data:
                // if (isTCP) {
                //     if ((numbytes = recv(d_sockfd, d_buf, 12, MSG_WAITALL)) == -1) {
                //         cStatus = disconnected;
                //         break;
                //     }
                // } else {
                cliaddr_len = sizeof(cliaddr);
                if ((numbytes = recvfrom(d_sockfd, d_buf, MAXBUFLEN-1 , 0, (struct sockaddr *) &cliaddr, &cliaddr_len)) == -1) {
                    printf("[FOCAL CONNECT] RECEIVE FAILED!\n");
                    break;
                }
                // }

                if(numbytes == 12){
                    float* xp = (float*) &d_buf[0];
                    float* yp = (float*) &d_buf[4];
                    float* zp = (float*) &d_buf[8];
                    memcpy(s_buf, d_buf, 12);
                    forward_ready = 1;
                    float x = *xp;
                    float y = *yp;
                    float z = *zp;
                    x264_pthread_mutex_lock(&pos_data->mutex);
                    pos_data->status = valid;
                    pos_data->x = x;
                    pos_data->y = y;
                    pos_data->z = z;
                    x264_pthread_mutex_unlock(&pos_data->mutex);
                }else if (numbytes == 4 && isHLClient){
                    printf("Forward head data to the hololens client!\n");
                    if (forward_ready){
                        printf("IP address is: %s\n", inet_ntoa(cliaddr.sin_addr));
                        printf("port is: %d\n", (int) ntohs(cliaddr.sin_port));
                        if (sendto(d_sockfd, s_buf, 12, 0, (struct sockaddr *) &cliaddr, cliaddr_len) == -1){
                            printf("FORWARD FAILED!");
                        }
                    }
                }else{
                    printf("Error in focal_connect: Received incorrect number of bytes: %d %s\n", numbytes, strerror(errno));
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
