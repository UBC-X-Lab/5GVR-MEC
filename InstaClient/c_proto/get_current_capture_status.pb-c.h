/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: get_current_capture_status.proto */

#ifndef PROTOBUF_C_get_5fcurrent_5fcapture_5fstatus_2eproto__INCLUDED
#define PROTOBUF_C_get_5fcurrent_5fcapture_5fstatus_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "capture_state.pb-c.h"

typedef struct Insta360__Messages__CameraCaptureStatus Insta360__Messages__CameraCaptureStatus;
typedef struct Insta360__Messages__GetCurrentCaptureStatusResp Insta360__Messages__GetCurrentCaptureStatusResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__CameraCaptureStatus
{
  ProtobufCMessage base;
  Insta360__Messages__CameraCaptureState state;
  uint32_t capture_time;
};
#define INSTA360__MESSAGES__CAMERA_CAPTURE_STATUS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__camera_capture_status__descriptor) \
    , INSTA360__MESSAGES__CAMERA_CAPTURE_STATE__NOT_CAPTURE, 0 }


struct  Insta360__Messages__GetCurrentCaptureStatusResp
{
  ProtobufCMessage base;
  Insta360__Messages__CameraCaptureStatus *status;
};
#define INSTA360__MESSAGES__GET_CURRENT_CAPTURE_STATUS_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__get_current_capture_status_resp__descriptor) \
    , NULL }


/* Insta360__Messages__CameraCaptureStatus methods */
void   insta360__messages__camera_capture_status__init
                     (Insta360__Messages__CameraCaptureStatus         *message);
size_t insta360__messages__camera_capture_status__get_packed_size
                     (const Insta360__Messages__CameraCaptureStatus   *message);
size_t insta360__messages__camera_capture_status__pack
                     (const Insta360__Messages__CameraCaptureStatus   *message,
                      uint8_t             *out);
size_t insta360__messages__camera_capture_status__pack_to_buffer
                     (const Insta360__Messages__CameraCaptureStatus   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__CameraCaptureStatus *
       insta360__messages__camera_capture_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__camera_capture_status__free_unpacked
                     (Insta360__Messages__CameraCaptureStatus *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__GetCurrentCaptureStatusResp methods */
void   insta360__messages__get_current_capture_status_resp__init
                     (Insta360__Messages__GetCurrentCaptureStatusResp         *message);
size_t insta360__messages__get_current_capture_status_resp__get_packed_size
                     (const Insta360__Messages__GetCurrentCaptureStatusResp   *message);
size_t insta360__messages__get_current_capture_status_resp__pack
                     (const Insta360__Messages__GetCurrentCaptureStatusResp   *message,
                      uint8_t             *out);
size_t insta360__messages__get_current_capture_status_resp__pack_to_buffer
                     (const Insta360__Messages__GetCurrentCaptureStatusResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__GetCurrentCaptureStatusResp *
       insta360__messages__get_current_capture_status_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__get_current_capture_status_resp__free_unpacked
                     (Insta360__Messages__GetCurrentCaptureStatusResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__CameraCaptureStatus_Closure)
                 (const Insta360__Messages__CameraCaptureStatus *message,
                  void *closure_data);
typedef void (*Insta360__Messages__GetCurrentCaptureStatusResp_Closure)
                 (const Insta360__Messages__GetCurrentCaptureStatusResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__camera_capture_status__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__get_current_capture_status_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_get_5fcurrent_5fcapture_5fstatus_2eproto__INCLUDED */
