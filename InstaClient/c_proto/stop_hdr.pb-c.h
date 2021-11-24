/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: stop_hdr.proto */

#ifndef PROTOBUF_C_stop_5fhdr_2eproto__INCLUDED
#define PROTOBUF_C_stop_5fhdr_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "video.pb-c.h"
#include "extra_info.pb-c.h"

typedef struct Insta360__Messages__StopHdr Insta360__Messages__StopHdr;
typedef struct Insta360__Messages__StopHdrResp Insta360__Messages__StopHdrResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__StopHdr
{
  ProtobufCMessage base;
  Insta360__Messages__ExtraMetadata *extra_metadata;
};
#define INSTA360__MESSAGES__STOP_HDR__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__stop_hdr__descriptor) \
    , NULL }


struct  Insta360__Messages__StopHdrResp
{
  ProtobufCMessage base;
  Insta360__Messages__Video *video;
};
#define INSTA360__MESSAGES__STOP_HDR_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__stop_hdr_resp__descriptor) \
    , NULL }


/* Insta360__Messages__StopHdr methods */
void   insta360__messages__stop_hdr__init
                     (Insta360__Messages__StopHdr         *message);
size_t insta360__messages__stop_hdr__get_packed_size
                     (const Insta360__Messages__StopHdr   *message);
size_t insta360__messages__stop_hdr__pack
                     (const Insta360__Messages__StopHdr   *message,
                      uint8_t             *out);
size_t insta360__messages__stop_hdr__pack_to_buffer
                     (const Insta360__Messages__StopHdr   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StopHdr *
       insta360__messages__stop_hdr__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__stop_hdr__free_unpacked
                     (Insta360__Messages__StopHdr *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__StopHdrResp methods */
void   insta360__messages__stop_hdr_resp__init
                     (Insta360__Messages__StopHdrResp         *message);
size_t insta360__messages__stop_hdr_resp__get_packed_size
                     (const Insta360__Messages__StopHdrResp   *message);
size_t insta360__messages__stop_hdr_resp__pack
                     (const Insta360__Messages__StopHdrResp   *message,
                      uint8_t             *out);
size_t insta360__messages__stop_hdr_resp__pack_to_buffer
                     (const Insta360__Messages__StopHdrResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StopHdrResp *
       insta360__messages__stop_hdr_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__stop_hdr_resp__free_unpacked
                     (Insta360__Messages__StopHdrResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__StopHdr_Closure)
                 (const Insta360__Messages__StopHdr *message,
                  void *closure_data);
typedef void (*Insta360__Messages__StopHdrResp_Closure)
                 (const Insta360__Messages__StopHdrResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__stop_hdr__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__stop_hdr_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_stop_5fhdr_2eproto__INCLUDED */