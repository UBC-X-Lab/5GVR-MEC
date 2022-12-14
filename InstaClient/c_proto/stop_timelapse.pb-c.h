/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: stop_timelapse.proto */

#ifndef PROTOBUF_C_stop_5ftimelapse_2eproto__INCLUDED
#define PROTOBUF_C_stop_5ftimelapse_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "video.pb-c.h"
#include "timelapse.pb-c.h"
#include "extra_info.pb-c.h"

typedef struct Insta360__Messages__StopTimelapse Insta360__Messages__StopTimelapse;
typedef struct Insta360__Messages__StopTimelapseResp Insta360__Messages__StopTimelapseResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__StopTimelapse
{
  ProtobufCMessage base;
  Insta360__Messages__TimelapseMode mode;
  Insta360__Messages__ExtraMetadata *extra_metadata;
};
#define INSTA360__MESSAGES__STOP_TIMELAPSE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__stop_timelapse__descriptor) \
    , INSTA360__MESSAGES__TIMELAPSE_MODE__TIMELAPSE_MIXED, NULL }


struct  Insta360__Messages__StopTimelapseResp
{
  ProtobufCMessage base;
  Insta360__Messages__Video *video;
};
#define INSTA360__MESSAGES__STOP_TIMELAPSE_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__stop_timelapse_resp__descriptor) \
    , NULL }


/* Insta360__Messages__StopTimelapse methods */
void   insta360__messages__stop_timelapse__init
                     (Insta360__Messages__StopTimelapse         *message);
size_t insta360__messages__stop_timelapse__get_packed_size
                     (const Insta360__Messages__StopTimelapse   *message);
size_t insta360__messages__stop_timelapse__pack
                     (const Insta360__Messages__StopTimelapse   *message,
                      uint8_t             *out);
size_t insta360__messages__stop_timelapse__pack_to_buffer
                     (const Insta360__Messages__StopTimelapse   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StopTimelapse *
       insta360__messages__stop_timelapse__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__stop_timelapse__free_unpacked
                     (Insta360__Messages__StopTimelapse *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__StopTimelapseResp methods */
void   insta360__messages__stop_timelapse_resp__init
                     (Insta360__Messages__StopTimelapseResp         *message);
size_t insta360__messages__stop_timelapse_resp__get_packed_size
                     (const Insta360__Messages__StopTimelapseResp   *message);
size_t insta360__messages__stop_timelapse_resp__pack
                     (const Insta360__Messages__StopTimelapseResp   *message,
                      uint8_t             *out);
size_t insta360__messages__stop_timelapse_resp__pack_to_buffer
                     (const Insta360__Messages__StopTimelapseResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StopTimelapseResp *
       insta360__messages__stop_timelapse_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__stop_timelapse_resp__free_unpacked
                     (Insta360__Messages__StopTimelapseResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__StopTimelapse_Closure)
                 (const Insta360__Messages__StopTimelapse *message,
                  void *closure_data);
typedef void (*Insta360__Messages__StopTimelapseResp_Closure)
                 (const Insta360__Messages__StopTimelapseResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__stop_timelapse__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__stop_timelapse_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_stop_5ftimelapse_2eproto__INCLUDED */
