/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: set_photography_options.proto */

#ifndef PROTOBUF_C_set_5fphotography_5foptions_2eproto__INCLUDED
#define PROTOBUF_C_set_5fphotography_5foptions_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "photography_options.pb-c.h"
#include "options.pb-c.h"

typedef struct Insta360__Messages__SetPhotographyOptions Insta360__Messages__SetPhotographyOptions;
typedef struct Insta360__Messages__SetPhotographyOptionsResp Insta360__Messages__SetPhotographyOptionsResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__SetPhotographyOptions
{
  ProtobufCMessage base;
  size_t n_option_types;
  Insta360__Messages__PhotographyOptionType *option_types;
  Insta360__Messages__PhotographyOptions *value;
  Insta360__Messages__FunctionMode function_mode;
};
#define INSTA360__MESSAGES__SET_PHOTOGRAPHY_OPTIONS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__set_photography_options__descriptor) \
    , 0,NULL, NULL, INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_NORMAL }


struct  Insta360__Messages__SetPhotographyOptionsResp
{
  ProtobufCMessage base;
  size_t n_success_types;
  Insta360__Messages__PhotographyOptionType *success_types;
};
#define INSTA360__MESSAGES__SET_PHOTOGRAPHY_OPTIONS_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__set_photography_options_resp__descriptor) \
    , 0,NULL }


/* Insta360__Messages__SetPhotographyOptions methods */
void   insta360__messages__set_photography_options__init
                     (Insta360__Messages__SetPhotographyOptions         *message);
size_t insta360__messages__set_photography_options__get_packed_size
                     (const Insta360__Messages__SetPhotographyOptions   *message);
size_t insta360__messages__set_photography_options__pack
                     (const Insta360__Messages__SetPhotographyOptions   *message,
                      uint8_t             *out);
size_t insta360__messages__set_photography_options__pack_to_buffer
                     (const Insta360__Messages__SetPhotographyOptions   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__SetPhotographyOptions *
       insta360__messages__set_photography_options__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__set_photography_options__free_unpacked
                     (Insta360__Messages__SetPhotographyOptions *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__SetPhotographyOptionsResp methods */
void   insta360__messages__set_photography_options_resp__init
                     (Insta360__Messages__SetPhotographyOptionsResp         *message);
size_t insta360__messages__set_photography_options_resp__get_packed_size
                     (const Insta360__Messages__SetPhotographyOptionsResp   *message);
size_t insta360__messages__set_photography_options_resp__pack
                     (const Insta360__Messages__SetPhotographyOptionsResp   *message,
                      uint8_t             *out);
size_t insta360__messages__set_photography_options_resp__pack_to_buffer
                     (const Insta360__Messages__SetPhotographyOptionsResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__SetPhotographyOptionsResp *
       insta360__messages__set_photography_options_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__set_photography_options_resp__free_unpacked
                     (Insta360__Messages__SetPhotographyOptionsResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__SetPhotographyOptions_Closure)
                 (const Insta360__Messages__SetPhotographyOptions *message,
                  void *closure_data);
typedef void (*Insta360__Messages__SetPhotographyOptionsResp_Closure)
                 (const Insta360__Messages__SetPhotographyOptionsResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__set_photography_options__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__set_photography_options_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_set_5fphotography_5foptions_2eproto__INCLUDED */