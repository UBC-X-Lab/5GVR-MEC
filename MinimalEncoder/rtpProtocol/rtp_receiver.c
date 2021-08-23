

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

#include "../stream_receive.h"
#include "../lockedQueue/locked_queue.h"

#define TCP_PORT "5000"
#define RTP_PORT "5001"
l_queue* pkt_q = NULL;

static char* SRC_STREAM = NULL;
AVFormatContext* format_context = NULL;

fd_set master; // holds all tracked file descriptors
int fdmax; // max filedescriptor in master

struct timeval tv;


void* handle_input_to_startup_receiver(void* arg_struct) {
    r_input* r_in = (r_input*) arg_struct;
    l_queue* queue_pkt_q = r_in->pkt_q;
    AVFormatContext* context = r_in->f_ctx;
    free(r_in);
    setup_receiver(queue_pkt_q, context);
} 

void setup_receiver(l_queue* queue_pkt_q, AVFormatContext* ctx) {
    void* get_in_addr(struct sockaddr* sa);
    pkt_q = queue_pkt_q;
    format_context = ctx;
    int listener_tcp, listener_rtp, tcp_connfd, rtp_connfd;
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen;
    fd_set read_fds;

    char remoteIP[INET6_ADDRSTRLEN];

    struct addrinfo hints, *res, *p;

    int yes = 1; // used in setsockopt() with SO_REUSEADDR to allow no wait to bind to port below
    int i, j, ret;

	printf("Receiver Starting...\n");
    // clear file descriptor sets before use
    FD_ZERO(&master);

    // setup hints to resolve connection to server with tcp connection
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // allows both IPV4/6
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE; // HOST IP USED
    
	// Resolve the server address and por
    printf("Resolving server address to connect to\n");
	ret = getaddrinfo(NULL, TCP_PORT, &hints, &res);
	if (ret != 0) {
		printf("getaddrinfo failed with error: %s\n", gai_strerror(ret));
		return;
	}

	// walk through res list and attempting to bind socket
    printf("iterating through result to establish strong connection\n");
	for (p = res; p != NULL; p = p->ai_next) {
        // Create a SOCKET to bind on for tcp connection
        listener_tcp = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener_tcp < 0) {
		    continue;
        }
        else {
            printf("Socket successfully created..\n");
        }

        // allow rebinds on address so we dont have to wait if one fails.
        setsockopt(listener_tcp, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); 

		// bind listener to port 
        printf("Attempting to bind socket: %d\n", listener_tcp);
		ret = bind(listener_tcp, p->ai_addr, p->ai_addrlen);
		if (ret < 0) {
			close(listener_tcp);
			continue;
		}
		break;
	}

	freeaddrinfo(res);

    // if p is null then loop walked through the entire list and didn't find any viable options
	if (p == NULL) {
		printf("Error! unable to bind on port%s\n", TCP_PORT);
		return;
	}

    if (listen(listener_tcp, 5) == -1) {
        fprintf(stderr, "Receiver: could not listen for TCP connection on PORT %s\n", TCP_PORT);
        return;
    }

    FD_SET(listener_tcp, &master);
    fdmax = listener_tcp;
	
	// reset hints and setup for rtp socket creation with getaddrinfo()
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    ret = getaddrinfo(NULL, RTP_PORT, &hints, &res); // maybe need a call to reset res before this call
    if (ret != 0) {
        fprintf(stderr, "error occured in getaddrinfo call with error %s\n", gai_strerror(ret));
        return;
    }

    // walk this list to establish strong connection
    printf("iterating through result to establish strong connection\n");
	for (p = res; p != NULL; p = p->ai_next) {
        // Create a SOCKET for connecting to server
        listener_rtp = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener_rtp < 0) {
		    continue;
        }
        else {
            printf("Socket successfully created..\n");
        }

        // allow rebinds on address so we dont have to wait if one fails.
        setsockopt(listener_tcp, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); 

		// Connect to server.
        printf("Attempting to bind socket: %s\n", listener_rtp );
		ret = bind(listener_rtp, p->ai_addr, p->ai_addrlen); // since this is a udp connection this doesnt actually connect, it just allows easier call send() instead of sendto()
		if (ret < 0) {
			close(listener_rtp);
			continue;
		}
		break;
	}

	freeaddrinfo(res);

    // if p is null then loop walked through the entire list and didn't find any viable options
	if (p == NULL) {
		printf("Error! unable to bind on port%s\n", RTP_PORT);
		return;
	}

    if (listen(listener_rtp, 5) == -1) {
        fprintf(stderr, "Receiver: could not listen for RTP connection on PORT %s\n", RTP_PORT);
        return;
    }

    // add rtp socket to master file descriptor set
    FD_SET(listener_rtp, &master);
    if (listener_rtp > fdmax) {
        fdmax = listener_rtp;
    }

    //enter setup select process loop
    while(1) {
        // copy fds into read_fds to listen for connection
        read_fds = master;
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            fprintf(stderr, "Something went wrong inside select call during setup!\n");
            close(listener_rtp);
            close(listener_tcp);
            FD_CLR(listener_tcp, &master);
            FD_CLR(listener_rtp, &master);
            return;
        }

        // run through the existing connections looking for connections
        for (i = 0; i <- fdmax, i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == listener_rtp) {
                    // handle rtp connection
                    addrlen = sizeof(remoteaddr);
                    rtp_connfd = accept(listener_rtp, (struct sockaddr *) &remoteaddr, &addrlen); // accept connection

                    if (rtp_connfd == -1) {
                        fprintf(stderr, "Reciever unable to accept connection");
                    } else {
                        // connection good add rtp_connfd to master
                        FD_SET(rtp_connfd, &master);
                        if (rtp_connfd > fdmax) {
                            fdmax = rtp_connfd;
                        }

                        //get printable address and print connection 
                        printtf("rtp connection accepted from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *) &remoteaddr), remoteIP, INET6_ADDRSTRLEN), rtp_connfd);

                        // close listener_rtp since it's not needed anymore
                        close(listener_rtp);
                        FD_CLR(listener_rtp, &master);
                    }
                } 
                if (i == listener_tcp) {
                    // handle tcp connection
                    addrlen = sizeof(remoteaddr);
                    tcp_connfd = accept(listener_tcp, (struct sockaddr *) &remoteaddr, &addrlen); // accept connection

                    if (tcp_connfd == -1) {
                        fprintf(stderr, "Reciever unable to accept connection");
                    } else {
                        // connection good add rtp_connfd to master
                        FD_SET(tcp_connfd, &master);
                        if (tcp_connfd > fdmax) {
                            fdmax = tcp_connfd;
                        }

                        //get printable address and print connection 
                        printtf("tcp connection accepted from %s on socket %d\n", inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *) &remoteaddr), remoteIP, INET6_ADDRSTRLEN), tcp_connfd);
                        
                        // close listener_tcp since it's not needed anymore
                        close(listener_tcp);
                        FD_CLR(listener_tcp, &master);
                    }
                }

                // check if rtp and tcp connections have both occured
                if (!FD_ISSET(listener_tcp, &master) && !FD_ISSET(listener_rtp, &master)) {
                   break;
                }
            }
        }
    }

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

// fetch the address from sockaddr struct for either IPv4 or IPv6 connections
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}