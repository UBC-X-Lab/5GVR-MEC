/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: battery_low.proto */

#ifndef PROTOBUF_C_battery_5flow_2eproto__INCLUDED
#define PROTOBUF_C_battery_5flow_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "battery.pb-c.h"

typedef struct Insta360__Messages__NotificationBatteryLow Insta360__Messages__NotificationBatteryLow;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__NotificationBatteryLow
{
  ProtobufCMessage base;
  Insta360__Messages__BatteryStatus *battery_status;
};
#define INSTA360__MESSAGES__NOTIFICATION_BATTERY_LOW__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__notification_battery_low__descriptor) \
    , NULL }


/* Insta360__Messages__NotificationBatteryLow methods */
void   insta360__messages__notification_battery_low__init
                     (Insta360__Messages__NotificationBatteryLow         *message);
size_t insta360__messages__notification_battery_low__get_packed_size
                     (const Insta360__Messages__NotificationBatteryLow   *message);
size_t insta360__messages__notification_battery_low__pack
                     (const Insta360__Messages__NotificationBatteryLow   *message,
                      uint8_t             *out);
size_t insta360__messages__notification_battery_low__pack_to_buffer
                     (const Insta360__Messages__NotificationBatteryLow   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__NotificationBatteryLow *
       insta360__messages__notification_battery_low__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__notification_battery_low__free_unpacked
                     (Insta360__Messages__NotificationBatteryLow *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__NotificationBatteryLow_Closure)
                 (const Insta360__Messages__NotificationBatteryLow *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__notification_battery_low__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_battery_5flow_2eproto__INCLUDED */
