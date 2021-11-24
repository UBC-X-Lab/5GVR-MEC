/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: timelapse.proto */

#ifndef PROTOBUF_C_timelapse_2eproto__INCLUDED
#define PROTOBUF_C_timelapse_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__TimelapseOptions Insta360__Messages__TimelapseOptions;


/* --- enums --- */

typedef enum _Insta360__Messages__TimelapseOptions__OutputType {
  INSTA360__MESSAGES__TIMELAPSE_OPTIONS__OUTPUT_TYPE__DoNotChange = 0,
  INSTA360__MESSAGES__TIMELAPSE_OPTIONS__OUTPUT_TYPE__Video = 1,
  INSTA360__MESSAGES__TIMELAPSE_OPTIONS__OUTPUT_TYPE__Images = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__TIMELAPSE_OPTIONS__OUTPUT_TYPE)
} Insta360__Messages__TimelapseOptions__OutputType;
typedef enum _Insta360__Messages__TimelapseMode {
  INSTA360__MESSAGES__TIMELAPSE_MODE__TIMELAPSE_MIXED = 0,
  INSTA360__MESSAGES__TIMELAPSE_MODE__TIMELAPSE_VIDEO = 1,
  INSTA360__MESSAGES__TIMELAPSE_MODE__TIMELAPSE_INTERVAL_SHOOTING = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__TIMELAPSE_MODE)
} Insta360__Messages__TimelapseMode;

/* --- messages --- */

struct  Insta360__Messages__TimelapseOptions
{
  ProtobufCMessage base;
  uint32_t duration;
  uint32_t lapsetime;
  Insta360__Messages__TimelapseOptions__OutputType output_type;
};
#define INSTA360__MESSAGES__TIMELAPSE_OPTIONS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__timelapse_options__descriptor) \
    , 0, 0, INSTA360__MESSAGES__TIMELAPSE_OPTIONS__OUTPUT_TYPE__DoNotChange }


/* Insta360__Messages__TimelapseOptions methods */
void   insta360__messages__timelapse_options__init
                     (Insta360__Messages__TimelapseOptions         *message);
size_t insta360__messages__timelapse_options__get_packed_size
                     (const Insta360__Messages__TimelapseOptions   *message);
size_t insta360__messages__timelapse_options__pack
                     (const Insta360__Messages__TimelapseOptions   *message,
                      uint8_t             *out);
size_t insta360__messages__timelapse_options__pack_to_buffer
                     (const Insta360__Messages__TimelapseOptions   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__TimelapseOptions *
       insta360__messages__timelapse_options__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__timelapse_options__free_unpacked
                     (Insta360__Messages__TimelapseOptions *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__TimelapseOptions_Closure)
                 (const Insta360__Messages__TimelapseOptions *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    insta360__messages__timelapse_mode__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__timelapse_options__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__timelapse_options__output_type__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_timelapse_2eproto__INCLUDED */
