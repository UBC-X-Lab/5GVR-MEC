#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#include "message_code.pb-c.h"
#include "start_live_stream.pb-c.h"

static int next_msgid = 1;

enum PacketType {
  PACKET_TYPE_STREAM_DATA = 1,
  PACKET_TYPE_MESSAGE = 4,
  PACKET_TYPE_HEART_BEAT = 5,
  PACKET_TYPE_SYNC = 6,
  PACKET_TYPE_TUNNEL_DATA = 7,
};

enum StreamType {
  STREAM_TYPE_AUDIO = 0x10,
  STREAM_TYPE_VIDEO_1 = 0x20,
  STREAM_TYPE_VIDEO_2 = 0x21,
  STREAM_TYPE_VIDEO_SEC = 0x22,
  STREAM_TYPE_GYRO = 0x30,
  STREAM_TYPE_EXPOSURE = 0x40,
};

struct packet_header {
  uint32_t size;
  uint8_t type;
  uint16_t padding_len;
} __attribute__((packed));

struct message_header {
  struct packet_header packet;
  uint16_t code;
  uint8_t content_type;
  uint32_t message_id;
  uint16_t unknown;
} __attribute__((packed));

struct stream_header {
  struct packet_header packet;
  uint8_t type;
  uint64_t timestamp;
} __attribute__((packed));

int connect_tcp(struct sockaddr_in *sa, int timeout_ms) {
  fd_set rset, wset;
  struct timeval timeout;
  int res, error;

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("socket");
    return -1;
  }

  int flags = fcntl(fd, F_GETFL, 0);
  if (flags < 0) {
    perror("fcntl");
    close(fd);
    return -1;
  }
  res = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  if (res < 0) {
    perror("fcntl");
    close(fd);
    return -1;
  }

  res = connect(fd, (struct sockaddr *)sa, sizeof(struct sockaddr_in));
  if (res < 0 && errno != EINPROGRESS) {
    perror("connect");
    close(fd);
    return -1;
  }

  if (res == 0) {
    // connect worked immediately
    goto done;
  }

  FD_ZERO(&rset);
  FD_SET(fd, &rset);
  wset = rset;
  timeout.tv_sec = timeout_ms / 1000;
  timeout.tv_usec = (timeout_ms % 1000) * 1000;

  res = select(fd + 1, &rset, &wset, NULL, timeout_ms ? &timeout : NULL);
  if (res == 0) {
    // timeout
    errno = ETIMEDOUT;
    perror("connect");
    close(fd);
    return -1;
  }

  assert(FD_ISSET(fd, &rset) || FD_ISSET(fd, &wset));
  socklen_t errorlen = sizeof(error);
  if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &errorlen) < 0) {
    perror("getsockopt");
    close(fd);
    return -1;
  }
  if (error) {
    errno = error;
    perror("connect");
    close(fd);
    return -1;
  }

done:
  res = fcntl(fd, F_SETFL, flags);
  if (res < 0) {
    perror("fcntl");
    close(fd);
    return -1;
  }
  return fd;
}

void xsendall(int sock, const void *buf, int len) {
  while (len) {
    int res = send(sock, buf, len, 0);
    if (res < 0) {
      if (errno == EINTR) {
        continue;
      }
      perror("send");
      exit(-1);
    }
    if (res == 0) {
      fprintf(stderr, "send returned zero - closed?\n");
      exit(-1);
    }
    buf = (const char *)buf + res;
    len = len - res;
  }
}

int recvall(int sock, void *buf, int len) {
  while (len) {
    int res = recv(sock, buf, len, 0);
    if (res < 0) {
      if (errno == EINTR) {
        continue;
      }
      perror("recv");
      return -1;
    }
    if (res == 0) {
      fprintf(stderr, "recv returned zero - closed?\n");
      return -1;
    }
    buf = (char *)buf + res;
    len = len - res;
  }
  return 0;
}

struct recv_thread_args {
  int camera_fd;
  int dest_fd;
};

void *recv_thread(void *arg) {
  struct recv_thread_args *args = arg;
  while (1) {
    struct packet_header pkt;
    int res = recvall(args->camera_fd, &pkt, sizeof(pkt));
    if (res < 0) {
      perror("recvall");
      return NULL;
    }
    if (pkt.size < sizeof(pkt)) {
      fprintf(stderr, "Invalid packet received from server: size=%u\n", pkt.size);
      return NULL;
    }

    void *buf = malloc(pkt.size);
    if (buf == NULL) {
      perror("malloc");
      return NULL;
    }
    memcpy(buf, &pkt, sizeof(pkt));
    res = recvall(args->camera_fd, (char *)buf + sizeof(pkt), pkt.size - sizeof(pkt));
    if (res < 0) {
      perror("recvall");
      return NULL;
    }

    switch (pkt.type) {
    case PACKET_TYPE_STREAM_DATA: {
      if (pkt.size < sizeof(struct stream_header)) {
        fprintf(stderr, "Invalid stream data packet received from server: size=%u\n", pkt.size);
        free(buf);
        break;
      }
      struct stream_header *hdr = (void *)buf;
      fprintf(stderr, "stream data: type=0x%x timestamp=%llu len=%zu\n", hdr->type, hdr->timestamp, pkt.size - sizeof(struct stream_header));
      uint32_t sendsize = pkt.size - sizeof(struct stream_header);
      uint32_t n_sendsize = htonl(sendsize);
      xsendall(args->dest_fd, &n_sendsize, sizeof(n_sendsize));
      xsendall(args->dest_fd, hdr + 1, sendsize);
      free(buf);
      break;
    }
    case PACKET_TYPE_MESSAGE: {
      if (pkt.size < sizeof(struct message_header)) {
        fprintf(stderr, "Invalid stream data packet received from server: size=%u\n", pkt.size);
        free(buf);
        break;
      }
      struct message_header *hdr = (void *)buf;
      printf("message reply: code=%d message_id=0x%x len=%zu\n", hdr->code, hdr->message_id, pkt.size - sizeof(struct message_header));
      free(buf);
      break;
    }
    case PACKET_TYPE_HEART_BEAT: {
      printf("heartbeat packet\n");
      free(buf);
      break;
    }
    case PACKET_TYPE_SYNC: {
      printf("sync packet\n");
      free(buf);
      break;
    }
    case PACKET_TYPE_TUNNEL_DATA:
    default:
      printf("Unknown packet type %d, size %u\n", pkt.type, pkt.size);
      for(int i=0; i<pkt.size; i++) {
        printf("%02x", ((unsigned char *)buf)[i]);
      }
      printf("\n");
      free(buf);
    }
  }
}

int main(int argc, char **argv) {
  struct sockaddr_in sa = {0};
  int res;

  sa.sin_family = AF_INET;
  sa.sin_port = htons(6666);
  inet_pton(AF_INET, "192.168.42.1", &sa.sin_addr);
  int camera_sock = connect_tcp(&sa, 1000);
  if (camera_sock < 0) {
    perror("connect_tcp camera");
    exit(-1);
  }

  sa.sin_family = AF_INET;
  sa.sin_port = htons(27873);
  inet_pton(AF_INET, "10.249.146.111", &sa.sin_addr);
  int dest_sock = connect_tcp(&sa, 1000);
  if (dest_sock < 0) {
    perror("connect_tcp mec");
    exit(-1);
  }

  pthread_t recv_tid;
  struct recv_thread_args recv_thread_args = {
    .camera_fd = camera_sock,
    .dest_fd = dest_sock,
  };
  res = pthread_create(&recv_tid, NULL, recv_thread, &recv_thread_args);
  if (res < 0) {
    perror("pthread_create");
    exit(-1);
  }

  sleep(3);
  printf("Sending start message...\n");

  struct Insta360__Messages__StartLiveStream sls = INSTA360__MESSAGES__START_LIVE_STREAM__INIT;
  sls.enableaudio = 1;
  sls.enablevideo = 1;
  sls.audiotype = INSTA360__MESSAGES__AACBSTYPE__ADTS;
  sls.audiosamplerate = 48000;
//   sls.audiobitrate = 320000;
//   sls.videobitrate = 40000000;
  sls.resolution = INSTA360__MESSAGES__VIDEO_RESOLUTION__RES_2880_2880P30;
  sls.enablegyro = 0;

  size_t payload_len = insta360__messages__start_live_stream__get_packed_size(&sls);
  int msgid = next_msgid++;
  struct message_header msghdr = {
    .packet.size = payload_len + sizeof(struct message_header),
    .packet.type = PACKET_TYPE_MESSAGE,
    .packet.padding_len = 0,
    .code = INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_START_LIVE_STREAM,
    .content_type = 2,
    .message_id = 0x80000000 | msgid,
    .unknown = 0,
  };
  void *buf = malloc(payload_len);
  insta360__messages__start_live_stream__pack(&sls, buf);
  xsendall(camera_sock, &msghdr, sizeof(struct message_header));
  xsendall(camera_sock, buf, payload_len);

  struct packet_header keepalive_msg = {
    .size = sizeof(struct packet_header),
    .type = PACKET_TYPE_HEART_BEAT,
    .padding_len = 0,
  };
  while (1) {
    sleep(3);
    xsendall(camera_sock, &keepalive_msg, sizeof(struct packet_header));
  }
}
