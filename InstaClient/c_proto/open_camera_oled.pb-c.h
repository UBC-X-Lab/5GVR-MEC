/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: open_camera_oled.proto */

#ifndef PROTOBUF_C_open_5fcamera_5foled_2eproto__INCLUDED
#define PROTOBUF_C_open_5fcamera_5foled_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__OpenCameraOled Insta360__Messages__OpenCameraOled;
typedef struct Insta360__Messages__OpenCameraOledResp Insta360__Messages__OpenCameraOledResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__OpenCameraOled
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__OPEN_CAMERA_OLED__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__open_camera_oled__descriptor) \
     }


struct  Insta360__Messages__OpenCameraOledResp
{
  ProtobufCMessage base;
};
#define INSTA360__MESSAGES__OPEN_CAMERA_OLED_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__open_camera_oled_resp__descriptor) \
     }


/* Insta360__Messages__OpenCameraOled methods */
void   insta360__messages__open_camera_oled__init
                     (Insta360__Messages__OpenCameraOled         *message);
size_t insta360__messages__open_camera_oled__get_packed_size
                     (const Insta360__Messages__OpenCameraOled   *message);
size_t insta360__messages__open_camera_oled__pack
                     (const Insta360__Messages__OpenCameraOled   *message,
                      uint8_t             *out);
size_t insta360__messages__open_camera_oled__pack_to_buffer
                     (const Insta360__Messages__OpenCameraOled   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__OpenCameraOled *
       insta360__messages__open_camera_oled__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__open_camera_oled__free_unpacked
                     (Insta360__Messages__OpenCameraOled *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__OpenCameraOledResp methods */
void   insta360__messages__open_camera_oled_resp__init
                     (Insta360__Messages__OpenCameraOledResp         *message);
size_t insta360__messages__open_camera_oled_resp__get_packed_size
                     (const Insta360__Messages__OpenCameraOledResp   *message);
size_t insta360__messages__open_camera_oled_resp__pack
                     (const Insta360__Messages__OpenCameraOledResp   *message,
                      uint8_t             *out);
size_t insta360__messages__open_camera_oled_resp__pack_to_buffer
                     (const Insta360__Messages__OpenCameraOledResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__OpenCameraOledResp *
       insta360__messages__open_camera_oled_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__open_camera_oled_resp__free_unpacked
                     (Insta360__Messages__OpenCameraOledResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__OpenCameraOled_Closure)
                 (const Insta360__Messages__OpenCameraOled *message,
                  void *closure_data);
typedef void (*Insta360__Messages__OpenCameraOledResp_Closure)
                 (const Insta360__Messages__OpenCameraOledResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__open_camera_oled__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__open_camera_oled_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_open_5fcamera_5foled_2eproto__INCLUDED */
