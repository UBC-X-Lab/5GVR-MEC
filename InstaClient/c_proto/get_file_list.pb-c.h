/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: get_file_list.proto */

#ifndef PROTOBUF_C_get_5ffile_5flist_2eproto__INCLUDED
#define PROTOBUF_C_get_5ffile_5flist_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "media.pb-c.h"

typedef struct Insta360__Messages__GetFileList Insta360__Messages__GetFileList;
typedef struct Insta360__Messages__GetFileListResp Insta360__Messages__GetFileListResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__GetFileList
{
  ProtobufCMessage base;
  Insta360__Messages__MediaType media_type;
  uint32_t start;
  uint32_t limit;
};
#define INSTA360__MESSAGES__GET_FILE_LIST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__get_file_list__descriptor) \
    , INSTA360__MESSAGES__MEDIA_TYPE__VIDEO, 0, 0 }


struct  Insta360__Messages__GetFileListResp
{
  ProtobufCMessage base;
  size_t n_uri;
  char **uri;
  uint32_t total_count;
};
#define INSTA360__MESSAGES__GET_FILE_LIST_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__get_file_list_resp__descriptor) \
    , 0,NULL, 0 }


/* Insta360__Messages__GetFileList methods */
void   insta360__messages__get_file_list__init
                     (Insta360__Messages__GetFileList         *message);
size_t insta360__messages__get_file_list__get_packed_size
                     (const Insta360__Messages__GetFileList   *message);
size_t insta360__messages__get_file_list__pack
                     (const Insta360__Messages__GetFileList   *message,
                      uint8_t             *out);
size_t insta360__messages__get_file_list__pack_to_buffer
                     (const Insta360__Messages__GetFileList   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__GetFileList *
       insta360__messages__get_file_list__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__get_file_list__free_unpacked
                     (Insta360__Messages__GetFileList *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__GetFileListResp methods */
void   insta360__messages__get_file_list_resp__init
                     (Insta360__Messages__GetFileListResp         *message);
size_t insta360__messages__get_file_list_resp__get_packed_size
                     (const Insta360__Messages__GetFileListResp   *message);
size_t insta360__messages__get_file_list_resp__pack
                     (const Insta360__Messages__GetFileListResp   *message,
                      uint8_t             *out);
size_t insta360__messages__get_file_list_resp__pack_to_buffer
                     (const Insta360__Messages__GetFileListResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__GetFileListResp *
       insta360__messages__get_file_list_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__get_file_list_resp__free_unpacked
                     (Insta360__Messages__GetFileListResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__GetFileList_Closure)
                 (const Insta360__Messages__GetFileList *message,
                  void *closure_data);
typedef void (*Insta360__Messages__GetFileListResp_Closure)
                 (const Insta360__Messages__GetFileListResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__get_file_list__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__get_file_list_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_get_5ffile_5flist_2eproto__INCLUDED */