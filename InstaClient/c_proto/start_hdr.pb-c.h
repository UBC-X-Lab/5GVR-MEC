/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: start_hdr.proto */

#ifndef PROTOBUF_C_start_5fhdr_2eproto__INCLUDED
#define PROTOBUF_C_start_5fhdr_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__StartHdr Insta360__Messages__StartHdr;
typedef struct Insta360__Messages__StartHdrResp Insta360__Messages__StartHdrResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__StartHdr
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__START_HDR__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__start_hdr__descriptor) \
     }


struct  Insta360__Messages__StartHdrResp
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__START_HDR_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__start_hdr_resp__descriptor) \
     }


/* Insta360__Messages__StartHdr methods */
void   insta360__messages__start_hdr__init
                     (Insta360__Messages__StartHdr         *message);
size_t insta360__messages__start_hdr__get_packed_size
                     (const Insta360__Messages__StartHdr   *message);
size_t insta360__messages__start_hdr__pack
                     (const Insta360__Messages__StartHdr   *message,
                      uint8_t             *out);
size_t insta360__messages__start_hdr__pack_to_buffer
                     (const Insta360__Messages__StartHdr   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StartHdr *
       insta360__messages__start_hdr__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__start_hdr__free_unpacked
                     (Insta360__Messages__StartHdr *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__StartHdrResp methods */
void   insta360__messages__start_hdr_resp__init
                     (Insta360__Messages__StartHdrResp         *message);
size_t insta360__messages__start_hdr_resp__get_packed_size
                     (const Insta360__Messages__StartHdrResp   *message);
size_t insta360__messages__start_hdr_resp__pack
                     (const Insta360__Messages__StartHdrResp   *message,
                      uint8_t             *out);
size_t insta360__messages__start_hdr_resp__pack_to_buffer
                     (const Insta360__Messages__StartHdrResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StartHdrResp *
       insta360__messages__start_hdr_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__start_hdr_resp__free_unpacked
                     (Insta360__Messages__StartHdrResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__StartHdr_Closure)
                 (const Insta360__Messages__StartHdr *message,
                  void *closure_data);
typedef void (*Insta360__Messages__StartHdrResp_Closure)
                 (const Insta360__Messages__StartHdrResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__start_hdr__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__start_hdr_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_start_5fhdr_2eproto__INCLUDED */
