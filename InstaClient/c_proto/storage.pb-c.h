/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: storage.proto */

#ifndef PROTOBUF_C_storage_2eproto__INCLUDED
#define PROTOBUF_C_storage_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__StorageState Insta360__Messages__StorageState;


/* --- enums --- */

typedef enum _Insta360__Messages__CardState {
  INSTA360__MESSAGES__CARD_STATE__STOR_CS_PASS = 0,
  INSTA360__MESSAGES__CARD_STATE__STOR_CS_NOCARD = 1,
  INSTA360__MESSAGES__CARD_STATE__STOR_CS_NOSPACE = 2,
  INSTA360__MESSAGES__CARD_STATE__STOR_CS_INVALID_FORMAT = 3,
  INSTA360__MESSAGES__CARD_STATE__STOR_CS_WPCARD = 4,
  INSTA360__MESSAGES__CARD_STATE__STOR_CS_OTHER_ERROR = 5
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__CARD_STATE)
} Insta360__Messages__CardState;

/* --- messages --- */

struct  Insta360__Messages__StorageState
{
  ProtobufCMessage base;
  Insta360__Messages__CardState card_state;
  uint64_t free_space;
  uint64_t total_space;
};
#define INSTA360__MESSAGES__STORAGE_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__storage_state__descriptor) \
    , INSTA360__MESSAGES__CARD_STATE__STOR_CS_PASS, 0, 0 }


/* Insta360__Messages__StorageState methods */
void   insta360__messages__storage_state__init
                     (Insta360__Messages__StorageState         *message);
size_t insta360__messages__storage_state__get_packed_size
                     (const Insta360__Messages__StorageState   *message);
size_t insta360__messages__storage_state__pack
                     (const Insta360__Messages__StorageState   *message,
                      uint8_t             *out);
size_t insta360__messages__storage_state__pack_to_buffer
                     (const Insta360__Messages__StorageState   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__StorageState *
       insta360__messages__storage_state__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__storage_state__free_unpacked
                     (Insta360__Messages__StorageState *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__StorageState_Closure)
                 (const Insta360__Messages__StorageState *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    insta360__messages__card_state__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__storage_state__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_storage_2eproto__INCLUDED */