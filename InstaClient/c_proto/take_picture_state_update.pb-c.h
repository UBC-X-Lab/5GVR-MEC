/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: take_picture_state_update.proto */

#ifndef PROTOBUF_C_take_5fpicture_5fstate_5fupdate_2eproto__INCLUDED
#define PROTOBUF_C_take_5fpicture_5fstate_5fupdate_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__NotificationTakePictureStateUpdate Insta360__Messages__NotificationTakePictureStateUpdate;


/* --- enums --- */

typedef enum _Insta360__Messages__NotificationTakePictureStateUpdate__TakePictureState {
  INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__TAKE_PICTURE_STATE__SHUTTER = 0,
  INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__TAKE_PICTURE_STATE__COMPRESS = 1,
  INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__TAKE_PICTURE_STATE__WRITE_FILE = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__TAKE_PICTURE_STATE)
} Insta360__Messages__NotificationTakePictureStateUpdate__TakePictureState;

/* --- messages --- */

struct  Insta360__Messages__NotificationTakePictureStateUpdate
{
  ProtobufCMessage base;
  Insta360__Messages__NotificationTakePictureStateUpdate__TakePictureState state;
};
#define INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__notification_take_picture_state_update__descriptor) \
    , INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__TAKE_PICTURE_STATE__SHUTTER }


/* Insta360__Messages__NotificationTakePictureStateUpdate methods */
void   insta360__messages__notification_take_picture_state_update__init
                     (Insta360__Messages__NotificationTakePictureStateUpdate         *message);
size_t insta360__messages__notification_take_picture_state_update__get_packed_size
                     (const Insta360__Messages__NotificationTakePictureStateUpdate   *message);
size_t insta360__messages__notification_take_picture_state_update__pack
                     (const Insta360__Messages__NotificationTakePictureStateUpdate   *message,
                      uint8_t             *out);
size_t insta360__messages__notification_take_picture_state_update__pack_to_buffer
                     (const Insta360__Messages__NotificationTakePictureStateUpdate   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__NotificationTakePictureStateUpdate *
       insta360__messages__notification_take_picture_state_update__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__notification_take_picture_state_update__free_unpacked
                     (Insta360__Messages__NotificationTakePictureStateUpdate *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__NotificationTakePictureStateUpdate_Closure)
                 (const Insta360__Messages__NotificationTakePictureStateUpdate *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__notification_take_picture_state_update__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__notification_take_picture_state_update__take_picture_state__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_take_5fpicture_5fstate_5fupdate_2eproto__INCLUDED */
