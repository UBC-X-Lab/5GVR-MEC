/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: button_press.proto */

#ifndef PROTOBUF_C_button_5fpress_2eproto__INCLUDED
#define PROTOBUF_C_button_5fpress_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct Insta360__Messages__ButtonPressOptions Insta360__Messages__ButtonPressOptions;


/* --- enums --- */

typedef enum _Insta360__Messages__ButtonPressMode {
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__DO_NOT_CHANGE = 0,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__DO_NOTHING = 1,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__SHUT_DOWN = 2,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__TAKE_PICTURE = 3,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__CAPTURE = 4,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__SELFTIMER = 5,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__TIMELAPSE = 6,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__HIGH_FRAME_RATE = 7,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__ACTION_TIMELAPSE_VIDEO = 8,
  INSTA360__MESSAGES__BUTTON_PRESS_MODE__INTERVAL_SHOOTING = 9
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__BUTTON_PRESS_MODE)
} Insta360__Messages__ButtonPressMode;

/* --- messages --- */

struct  Insta360__Messages__ButtonPressOptions
{
  ProtobufCMessage base;
  Insta360__Messages__ButtonPressMode click;
  Insta360__Messages__ButtonPressMode double_click;
  Insta360__Messages__ButtonPressMode triple_click;
  Insta360__Messages__ButtonPressMode long_press;
};
#define INSTA360__MESSAGES__BUTTON_PRESS_OPTIONS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__button_press_options__descriptor) \
    , INSTA360__MESSAGES__BUTTON_PRESS_MODE__DO_NOT_CHANGE, INSTA360__MESSAGES__BUTTON_PRESS_MODE__DO_NOT_CHANGE, INSTA360__MESSAGES__BUTTON_PRESS_MODE__DO_NOT_CHANGE, INSTA360__MESSAGES__BUTTON_PRESS_MODE__DO_NOT_CHANGE }


/* Insta360__Messages__ButtonPressOptions methods */
void   insta360__messages__button_press_options__init
                     (Insta360__Messages__ButtonPressOptions         *message);
size_t insta360__messages__button_press_options__get_packed_size
                     (const Insta360__Messages__ButtonPressOptions   *message);
size_t insta360__messages__button_press_options__pack
                     (const Insta360__Messages__ButtonPressOptions   *message,
                      uint8_t             *out);
size_t insta360__messages__button_press_options__pack_to_buffer
                     (const Insta360__Messages__ButtonPressOptions   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__ButtonPressOptions *
       insta360__messages__button_press_options__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__button_press_options__free_unpacked
                     (Insta360__Messages__ButtonPressOptions *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__ButtonPressOptions_Closure)
                 (const Insta360__Messages__ButtonPressOptions *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    insta360__messages__button_press_mode__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__button_press_options__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_button_5fpress_2eproto__INCLUDED */