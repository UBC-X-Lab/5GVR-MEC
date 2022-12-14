/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: set_options.proto */

#ifndef PROTOBUF_C_set_5foptions_2eproto__INCLUDED
#define PROTOBUF_C_set_5foptions_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "options.pb-c.h"

typedef struct Insta360__Messages__SetOptions Insta360__Messages__SetOptions;
typedef struct Insta360__Messages__SetOptionsResp Insta360__Messages__SetOptionsResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__SetOptions
{
  ProtobufCMessage base;
  size_t n_option_types;
  Insta360__Messages__OptionType *option_types;
  Insta360__Messages__Options *value;
};
#define INSTA360__MESSAGES__SET_OPTIONS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__set_options__descriptor) \
    , 0,NULL, NULL }


struct  Insta360__Messages__SetOptionsResp
{
  ProtobufCMessage base;
  size_t n_option_types;
  Insta360__Messages__OptionType *option_types;
};
#define INSTA360__MESSAGES__SET_OPTIONS_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__set_options_resp__descriptor) \
    , 0,NULL }


/* Insta360__Messages__SetOptions methods */
void   insta360__messages__set_options__init
                     (Insta360__Messages__SetOptions         *message);
size_t insta360__messages__set_options__get_packed_size
                     (const Insta360__Messages__SetOptions   *message);
size_t insta360__messages__set_options__pack
                     (const Insta360__Messages__SetOptions   *message,
                      uint8_t             *out);
size_t insta360__messages__set_options__pack_to_buffer
                     (const Insta360__Messages__SetOptions   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__SetOptions *
       insta360__messages__set_options__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__set_options__free_unpacked
                     (Insta360__Messages__SetOptions *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__SetOptionsResp methods */
void   insta360__messages__set_options_resp__init
                     (Insta360__Messages__SetOptionsResp         *message);
size_t insta360__messages__set_options_resp__get_packed_size
                     (const Insta360__Messages__SetOptionsResp   *message);
size_t insta360__messages__set_options_resp__pack
                     (const Insta360__Messages__SetOptionsResp   *message,
                      uint8_t             *out);
size_t insta360__messages__set_options_resp__pack_to_buffer
                     (const Insta360__Messages__SetOptionsResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__SetOptionsResp *
       insta360__messages__set_options_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__set_options_resp__free_unpacked
                     (Insta360__Messages__SetOptionsResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__SetOptions_Closure)
                 (const Insta360__Messages__SetOptions *message,
                  void *closure_data);
typedef void (*Insta360__Messages__SetOptionsResp_Closure)
                 (const Insta360__Messages__SetOptionsResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__set_options__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__set_options_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_set_5foptions_2eproto__INCLUDED */
