/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: stop_live_stream.proto */

#ifndef PROTOBUF_C_stop_5flive_5fstream_2eproto__INCLUDED
#define PROTOBUF_C_stop_5flive_5fstream_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__StopLiveStream Insta360__Messages__StopLiveStream;
typedef struct Insta360__Messages__StopLiveStreamResp Insta360__Messages__StopLiveStreamResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__StopLiveStream
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__STOP_LIVE_STREAM__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__stop_live_stream__descriptor) \
     }


struct  Insta360__Messages__StopLiveStreamResp
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__STOP_LIVE_STREAM_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__stop_live_stream_resp__descriptor) \
     }


/* Insta360__Messages__StopLiveStream methods */
void   insta360__messages__stop_live_stream__init
                     (Insta360__Messages__StopLiveStream         *message);
size_t insta360__messages__stop_live_stream__get_packed_size
                     (const Insta360__Messages__StopLiveStream   *message);
size_t insta360__messages__stop_live_stream__pack
                     (const Insta360__Messages__StopLiveStream   *message,
                      uint8_t             *out);
size_t insta360__messages__stop_live_stream__pack_to_buffer
                     (const Insta360__Messages__StopLiveStream   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StopLiveStream *
       insta360__messages__stop_live_stream__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__stop_live_stream__free_unpacked
                     (Insta360__Messages__StopLiveStream *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__StopLiveStreamResp methods */
void   insta360__messages__stop_live_stream_resp__init
                     (Insta360__Messages__StopLiveStreamResp         *message);
size_t insta360__messages__stop_live_stream_resp__get_packed_size
                     (const Insta360__Messages__StopLiveStreamResp   *message);
size_t insta360__messages__stop_live_stream_resp__pack
                     (const Insta360__Messages__StopLiveStreamResp   *message,
                      uint8_t             *out);
size_t insta360__messages__stop_live_stream_resp__pack_to_buffer
                     (const Insta360__Messages__StopLiveStreamResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StopLiveStreamResp *
       insta360__messages__stop_live_stream_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__stop_live_stream_resp__free_unpacked
                     (Insta360__Messages__StopLiveStreamResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__StopLiveStream_Closure)
                 (const Insta360__Messages__StopLiveStream *message,
                  void *closure_data);
typedef void (*Insta360__Messages__StopLiveStreamResp_Closure)
                 (const Insta360__Messages__StopLiveStreamResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__stop_live_stream__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__stop_live_stream_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_stop_5flive_5fstream_2eproto__INCLUDED */
