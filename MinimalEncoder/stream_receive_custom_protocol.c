

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

#include "buildtimestamp.h"
#include "stream_receive.h"
#include "lockedQueue/locked_queue.h"

#define MAX 80
// #define ADDRESS "192.168.1.60"
#define SA struct sockaddr

l_queue* pkt_q = NULL;
char* PORT;

static char* SRC_STREAM = NULL;
AVFormatContext* format_context = NULL;

static int tsock;

struct timeval tv;

void* handle_input_to_startup_receiver(void* arg_struct) {
    r_input* r_in = (r_input*) arg_struct;
    l_queue* queue_pkt_q = r_in->pkt_q;
    AVFormatContext* context = r_in->f_ctx;
	PORT = r_in->PORT;
    free(r_in);
    setup_receiver(queue_pkt_q, context);
} 

void setup_receiver(l_queue* queue_pkt_q, AVFormatContext* ctx) {
    pkt_q = queue_pkt_q;
    format_context = ctx;
	printf("Receiver Starting...\n");
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

	hints.ai_family = AF_INET; // IPV4
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
			perror("stream_receive_custom_protocol: socket");
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
			perror("stream_receive_custom_protocol: bind");
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
		fprintf(stderr, "stream_receive_custom_protocol: failed to bind\n");
		exit(1);
	}

    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(1); 
    } 
	printf("Server listening...\n");
	void* get_in_addr(struct sockaddr *sa);

	sin_size = sizeof their_addr;
	printf("Waiting for connection at port %s\n", PORT);
	// accept connection
	connfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size); 
	if (connfd < 0) { 
		printf("server accept failed...%s\n", gai_strerror(errno));
		exit(1);
	}
	printf("server accepted client\n");
	inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&cli), s, sizeof s);
	printf("stream_receive_custom_protocoltransmit_server: accepted connection from %s\n", s);
	
	tsock = connfd;
	// signal ready
	q_ready(pkt_q);

	//run receiver loop
	run_receiver();
	
	//cleanup
	printf("Closing connection");
	close(tsock);
    q_kill(pkt_q);
}

void run_receiver() {
    AVPacket* pkt;
    int iResult;
    fprintf(stdout, "running receive thread\n");
	int k = 0;
    while(1) {
        if (q_is_dead(pkt_q)) {
            fprintf(stdout, "Receive thread received kill signal\n");
            break;
        }
        pkt = av_packet_alloc();
        while(1) {
            uint8_t recvlen[4];
            iResult = recv(tsock, (char*)recvlen, 4, MSG_WAITALL);
			uint32_t len = -1;
			if (iResult > 0) {
                len = (recvlen[0] << 24) | (recvlen[1] << 16) | (recvlen[2] << 8) | (recvlen[3]);
			}
			else if (iResult == 0) {
				fprintf(stderr, "RECEIVER: Connection closing...\n");
				return;
			}
			else {
				fprintf(stdout, "RECEIVER: Connection closing...\n");
				return;
			}

            if (len != -1) {
                char* receivedata = (char*)malloc(len);
                iResult = recv(tsock, receivedata, len, MSG_WAITALL);
				if (iResult > 0) {
					printf("Receiver got packet of len %d\n", len);
					int ret = av_new_packet(pkt, len);
					if (ret) {
						fprintf(stderr, "RECEIVER: Error allocating packet\n");
						return;
					}
                    k++;
                    pkt->pts = k;
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
        //printf("RECEIVER: frame has data stream index: %d, size %d, flags %d\n", pkt->stream_index, pkt->size, pkt->flags);
        q_enqueue(pkt_q, pkt);
        pkt = NULL;
    }
    // fprintf(stdout, "Receiver: Freeing packet used for receival\n");
    close(tsock);
    av_packet_free(&pkt);
    fprintf(stdout, "Receiver: Closing input\n");
}
