/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: set_file_extra.proto */

#ifndef PROTOBUF_C_set_5ffile_5fextra_2eproto__INCLUDED
#define PROTOBUF_C_set_5ffile_5fextra_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "media.pb-c.h"
#include "extra_info.pb-c.h"

typedef struct Insta360__Messages__SetFileExtra Insta360__Messages__SetFileExtra;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__SetFileExtra
{
  ProtobufCMessage base;
  char *uri;
  uint32_t extra_type;
  ProtobufCBinaryData data;
};
#define INSTA360__MESSAGES__SET_FILE_EXTRA__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__set_file_extra__descriptor) \
    , (char *)protobuf_c_empty_string, 0, {0,NULL} }


/* Insta360__Messages__SetFileExtra methods */
void   insta360__messages__set_file_extra__init
                     (Insta360__Messages__SetFileExtra         *message);
size_t insta360__messages__set_file_extra__get_packed_size
                     (const Insta360__Messages__SetFileExtra   *message);
size_t insta360__messages__set_file_extra__pack
                     (const Insta360__Messages__SetFileExtra   *message,
                      uint8_t             *out);
size_t insta360__messages__set_file_extra__pack_to_buffer
                     (const Insta360__Messages__SetFileExtra   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__SetFileExtra *
       insta360__messages__set_file_extra__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__set_file_extra__free_unpacked
                     (Insta360__Messages__SetFileExtra *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__SetFileExtra_Closure)
                 (const Insta360__Messages__SetFileExtra *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__set_file_extra__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_set_5ffile_5fextra_2eproto__INCLUDED */
