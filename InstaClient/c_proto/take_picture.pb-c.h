/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: take_picture.proto */

#ifndef PROTOBUF_C_take_5fpicture_2eproto__INCLUDED
#define PROTOBUF_C_take_5fpicture_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "photo.pb-c.h"
#include "media.pb-c.h"
#include "extra_info.pb-c.h"

typedef struct Insta360__Messages__TakePicture Insta360__Messages__TakePicture;
typedef struct Insta360__Messages__TakePictureResponse Insta360__Messages__TakePictureResponse;


/* --- enums --- */

typedef enum _Insta360__Messages__TakePicture__Mode {
  INSTA360__MESSAGES__TAKE_PICTURE__MODE__NORMAL = 0,
  INSTA360__MESSAGES__TAKE_PICTURE__MODE__AEB = 1,
  INSTA360__MESSAGES__TAKE_PICTURE__MODE__RAW = 2,
  INSTA360__MESSAGES__TAKE_PICTURE__MODE__BURST = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__TAKE_PICTURE__MODE)
} Insta360__Messages__TakePicture__Mode;

/* --- messages --- */

struct  Insta360__Messages__TakePicture
{
  ProtobufCMessage base;
  Insta360__Messages__TakePicture__Mode mode;
  Insta360__Messages__ExtraMetadata *extra_metadata;
  size_t n_aeb_ev_bias;
  int32_t *aeb_ev_bias;
};
#define INSTA360__MESSAGES__TAKE_PICTURE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__take_picture__descriptor) \
    , INSTA360__MESSAGES__TAKE_PICTURE__MODE__NORMAL, NULL, 0,NULL }


struct  Insta360__Messages__TakePictureResponse
{
  ProtobufCMessage base;
  Insta360__Messages__Photo *image;
  size_t n_aeb_images;
  Insta360__Messages__Photo **aeb_images;
  size_t n_burst_images;
  Insta360__Messages__Photo **burst_images;
};
#define INSTA360__MESSAGES__TAKE_PICTURE_RESPONSE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__take_picture_response__descriptor) \
    , NULL, 0,NULL, 0,NULL }


/* Insta360__Messages__TakePicture methods */
void   insta360__messages__take_picture__init
                     (Insta360__Messages__TakePicture         *message);
size_t insta360__messages__take_picture__get_packed_size
                     (const Insta360__Messages__TakePicture   *message);
size_t insta360__messages__take_picture__pack
                     (const Insta360__Messages__TakePicture   *message,
                      uint8_t             *out);
size_t insta360__messages__take_picture__pack_to_buffer
                     (const Insta360__Messages__TakePicture   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__TakePicture *
       insta360__messages__take_picture__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__take_picture__free_unpacked
                     (Insta360__Messages__TakePicture *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__TakePictureResponse methods */
void   insta360__messages__take_picture_response__init
                     (Insta360__Messages__TakePictureResponse         *message);
size_t insta360__messages__take_picture_response__get_packed_size
                     (const Insta360__Messages__TakePictureResponse   *message);
size_t insta360__messages__take_picture_response__pack
                     (const Insta360__Messages__TakePictureResponse   *message,
                      uint8_t             *out);
size_t insta360__messages__take_picture_response__pack_to_buffer
                     (const Insta360__Messages__TakePictureResponse   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__TakePictureResponse *
       insta360__messages__take_picture_response__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__take_picture_response__free_unpacked
                     (Insta360__Messages__TakePictureResponse *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__TakePicture_Closure)
                 (const Insta360__Messages__TakePicture *message,
                  void *closure_data);
typedef void (*Insta360__Messages__TakePictureResponse_Closure)
                 (const Insta360__Messages__TakePictureResponse *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__take_picture__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__take_picture__mode__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__take_picture_response__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_take_5fpicture_2eproto__INCLUDED */
