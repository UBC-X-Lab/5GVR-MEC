/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: close_camera_oled.proto */

#ifndef PROTOBUF_C_close_5fcamera_5foled_2eproto__INCLUDED
#define PROTOBUF_C_close_5fcamera_5foled_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__CloseCameraOled Insta360__Messages__CloseCameraOled;
typedef struct Insta360__Messages__CloseCameraOledResp Insta360__Messages__CloseCameraOledResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__CloseCameraOled
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__CLOSE_CAMERA_OLED__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__close_camera_oled__descriptor) \
     }


struct  Insta360__Messages__CloseCameraOledResp
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__CLOSE_CAMERA_OLED_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__close_camera_oled_resp__descriptor) \
     }


/* Insta360__Messages__CloseCameraOled methods */
void   insta360__messages__close_camera_oled__init
                     (Insta360__Messages__CloseCameraOled         *message);
size_t insta360__messages__close_camera_oled__get_packed_size
                     (const Insta360__Messages__CloseCameraOled   *message);
size_t insta360__messages__close_camera_oled__pack
                     (const Insta360__Messages__CloseCameraOled   *message,
                      uint8_t             *out);
size_t insta360__messages__close_camera_oled__pack_to_buffer
                     (const Insta360__Messages__CloseCameraOled   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__CloseCameraOled *
       insta360__messages__close_camera_oled__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__close_camera_oled__free_unpacked
                     (Insta360__Messages__CloseCameraOled *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__CloseCameraOledResp methods */
void   insta360__messages__close_camera_oled_resp__init
                     (Insta360__Messages__CloseCameraOledResp         *message);
size_t insta360__messages__close_camera_oled_resp__get_packed_size
                     (const Insta360__Messages__CloseCameraOledResp   *message);
size_t insta360__messages__close_camera_oled_resp__pack
                     (const Insta360__Messages__CloseCameraOledResp   *message,
                      uint8_t             *out);
size_t insta360__messages__close_camera_oled_resp__pack_to_buffer
                     (const Insta360__Messages__CloseCameraOledResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__CloseCameraOledResp *
       insta360__messages__close_camera_oled_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__close_camera_oled_resp__free_unpacked
                     (Insta360__Messages__CloseCameraOledResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__CloseCameraOled_Closure)
                 (const Insta360__Messages__CloseCameraOled *message,
                  void *closure_data);
typedef void (*Insta360__Messages__CloseCameraOledResp_Closure)
                 (const Insta360__Messages__CloseCameraOledResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__close_camera_oled__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__close_camera_oled_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_close_5fcamera_5foled_2eproto__INCLUDED */
