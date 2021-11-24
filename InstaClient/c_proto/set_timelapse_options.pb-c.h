/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: set_timelapse_options.proto */

#ifndef PROTOBUF_C_set_5ftimelapse_5foptions_2eproto__INCLUDED
#define PROTOBUF_C_set_5ftimelapse_5foptions_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "timelapse.pb-c.h"

typedef struct Insta360__Messages__SetTimelapseOptions Insta360__Messages__SetTimelapseOptions;
typedef struct Insta360__Messages__SetTimelapseOptionsResp Insta360__Messages__SetTimelapseOptionsResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__SetTimelapseOptions
{
  ProtobufCMessage base;
  Insta360__Messages__TimelapseOptions *timelapse_options;
  Insta360__Messages__TimelapseMode mode;
};
#define INSTA360__MESSAGES__SET_TIMELAPSE_OPTIONS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__set_timelapse_options__descriptor) \
    , NULL, INSTA360__MESSAGES__TIMELAPSE_MODE__TIMELAPSE_MIXED }


struct  Insta360__Messages__SetTimelapseOptionsResp
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__SET_TIMELAPSE_OPTIONS_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__set_timelapse_options_resp__descriptor) \
     }


/* Insta360__Messages__SetTimelapseOptions methods */
void   insta360__messages__set_timelapse_options__init
                     (Insta360__Messages__SetTimelapseOptions         *message);
size_t insta360__messages__set_timelapse_options__get_packed_size
                     (const Insta360__Messages__SetTimelapseOptions   *message);
size_t insta360__messages__set_timelapse_options__pack
                     (const Insta360__Messages__SetTimelapseOptions   *message,
                      uint8_t             *out);
size_t insta360__messages__set_timelapse_options__pack_to_buffer
                     (const Insta360__Messages__SetTimelapseOptions   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__SetTimelapseOptions *
       insta360__messages__set_timelapse_options__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__set_timelapse_options__free_unpacked
                     (Insta360__Messages__SetTimelapseOptions *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__SetTimelapseOptionsResp methods */
void   insta360__messages__set_timelapse_options_resp__init
                     (Insta360__Messages__SetTimelapseOptionsResp         *message);
size_t insta360__messages__set_timelapse_options_resp__get_packed_size
                     (const Insta360__Messages__SetTimelapseOptionsResp   *message);
size_t insta360__messages__set_timelapse_options_resp__pack
                     (const Insta360__Messages__SetTimelapseOptionsResp   *message,
                      uint8_t             *out);
size_t insta360__messages__set_timelapse_options_resp__pack_to_buffer
                     (const Insta360__Messages__SetTimelapseOptionsResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__SetTimelapseOptionsResp *
       insta360__messages__set_timelapse_options_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__set_timelapse_options_resp__free_unpacked
                     (Insta360__Messages__SetTimelapseOptionsResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__SetTimelapseOptions_Closure)
                 (const Insta360__Messages__SetTimelapseOptions *message,
                  void *closure_data);
typedef void (*Insta360__Messages__SetTimelapseOptionsResp_Closure)
                 (const Insta360__Messages__SetTimelapseOptionsResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__set_timelapse_options__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__set_timelapse_options_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_set_5ftimelapse_5foptions_2eproto__INCLUDED */