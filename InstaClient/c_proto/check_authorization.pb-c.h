/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: check_authorization.proto */

#ifndef PROTOBUF_C_check_5fauthorization_2eproto__INCLUDED
#define PROTOBUF_C_check_5fauthorization_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__CheckAuthorization Insta360__Messages__CheckAuthorization;
typedef struct Insta360__Messages__CheckAuthorizationResp Insta360__Messages__CheckAuthorizationResp;


/* --- enums --- */

typedef enum _Insta360__Messages__CheckAuthorizationResp__AuthorizationStatus {
  INSTA360__MESSAGES__CHECK_AUTHORIZATION_RESP__AUTHORIZATION_STATUS__AUTHORIZED = 0,
  INSTA360__MESSAGES__CHECK_AUTHORIZATION_RESP__AUTHORIZATION_STATUS__UNAUTHORIZED = 1,
  INSTA360__MESSAGES__CHECK_AUTHORIZATION_RESP__AUTHORIZATION_STATUS__SYSTEMBUSY = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__CHECK_AUTHORIZATION_RESP__AUTHORIZATION_STATUS)
} Insta360__Messages__CheckAuthorizationResp__AuthorizationStatus;

/* --- messages --- */

struct  Insta360__Messages__CheckAuthorization
{
  ProtobufCMessage base;
  char *id;
};
#define INSTA360__MESSAGES__CHECK_AUTHORIZATION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__check_authorization__descriptor) \
    , (char *)protobuf_c_empty_string }


struct  Insta360__Messages__CheckAuthorizationResp
{
  ProtobufCMessage base;
  Insta360__Messages__CheckAuthorizationResp__AuthorizationStatus authorization_status;
};
#define INSTA360__MESSAGES__CHECK_AUTHORIZATION_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__check_authorization_resp__descriptor) \
    , INSTA360__MESSAGES__CHECK_AUTHORIZATION_RESP__AUTHORIZATION_STATUS__AUTHORIZED }


/* Insta360__Messages__CheckAuthorization methods */
void   insta360__messages__check_authorization__init
                     (Insta360__Messages__CheckAuthorization         *message);
size_t insta360__messages__check_authorization__get_packed_size
                     (const Insta360__Messages__CheckAuthorization   *message);
size_t insta360__messages__check_authorization__pack
                     (const Insta360__Messages__CheckAuthorization   *message,
                      uint8_t             *out);
size_t insta360__messages__check_authorization__pack_to_buffer
                     (const Insta360__Messages__CheckAuthorization   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__CheckAuthorization *
       insta360__messages__check_authorization__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__check_authorization__free_unpacked
                     (Insta360__Messages__CheckAuthorization *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__CheckAuthorizationResp methods */
void   insta360__messages__check_authorization_resp__init
                     (Insta360__Messages__CheckAuthorizationResp         *message);
size_t insta360__messages__check_authorization_resp__get_packed_size
                     (const Insta360__Messages__CheckAuthorizationResp   *message);
size_t insta360__messages__check_authorization_resp__pack
                     (const Insta360__Messages__CheckAuthorizationResp   *message,
                      uint8_t             *out);
size_t insta360__messages__check_authorization_resp__pack_to_buffer
                     (const Insta360__Messages__CheckAuthorizationResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__CheckAuthorizationResp *
       insta360__messages__check_authorization_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__check_authorization_resp__free_unpacked
                     (Insta360__Messages__CheckAuthorizationResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__CheckAuthorization_Closure)
                 (const Insta360__Messages__CheckAuthorization *message,
                  void *closure_data);
typedef void (*Insta360__Messages__CheckAuthorizationResp_Closure)
                 (const Insta360__Messages__CheckAuthorizationResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__check_authorization__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__check_authorization_resp__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__check_authorization_resp__authorization_status__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_check_5fauthorization_2eproto__INCLUDED */
