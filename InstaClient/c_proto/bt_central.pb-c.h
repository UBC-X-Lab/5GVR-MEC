/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: bt_central.proto */

#ifndef PROTOBUF_C_bt_5fcentral_2eproto__INCLUDED
#define PROTOBUF_C_bt_5fcentral_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "bluetooth.pb-c.h"

typedef struct Insta360__Messages__ScanBTPeripheral Insta360__Messages__ScanBTPeripheral;
typedef struct Insta360__Messages__ConnectToBTPeripheral Insta360__Messages__ConnectToBTPeripheral;
typedef struct Insta360__Messages__DisconnectBTPeripheral Insta360__Messages__DisconnectBTPeripheral;
typedef struct Insta360__Messages__GetConnectedBTPeripheral Insta360__Messages__GetConnectedBTPeripheral;
typedef struct Insta360__Messages__GetConnectedBTPeripheralResp Insta360__Messages__GetConnectedBTPeripheralResp;


/* --- enums --- */


/* --- messages --- */

struct  Insta360__Messages__ScanBTPeripheral
{
  ProtobufCMessage base;
  Insta360__Messages__BTPeripheralType peripheral_type;
};
#define INSTA360__MESSAGES__SCAN_BTPERIPHERAL__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__scan_btperipheral__descriptor) \
    , INSTA360__MESSAGES__BTPERIPHERAL_TYPE__ALL }


struct  Insta360__Messages__ConnectToBTPeripheral
{
  ProtobufCMessage base;
  Insta360__Messages__BTPeripheral *peripheral;
};
#define INSTA360__MESSAGES__CONNECT_TO_BTPERIPHERAL__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__connect_to_btperipheral__descriptor) \
    , NULL }


struct  Insta360__Messages__DisconnectBTPeripheral
{
  ProtobufCMessage base;
  Insta360__Messages__BTPeripheral *peripheral;
};
#define INSTA360__MESSAGES__DISCONNECT_BTPERIPHERAL__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__disconnect_btperipheral__descriptor) \
    , NULL }


struct  Insta360__Messages__GetConnectedBTPeripheral
{
  ProtobufCMessage base;
  Insta360__Messages__BTPeripheralType peripheral_type;
};
#define INSTA360__MESSAGES__GET_CONNECTED_BTPERIPHERAL__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__get_connected_btperipheral__descriptor) \
    , INSTA360__MESSAGES__BTPERIPHERAL_TYPE__ALL }


struct  Insta360__Messages__GetConnectedBTPeripheralResp
{
  ProtobufCMessage base;
  size_t n_peripherals;
  Insta360__Messages__BTPeripheral **peripherals;
};
#define INSTA360__MESSAGES__GET_CONNECTED_BTPERIPHERAL_RESP__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__get_connected_btperipheral_resp__descriptor) \
    , 0,NULL }


/* Insta360__Messages__ScanBTPeripheral methods */
void   insta360__messages__scan_btperipheral__init
                     (Insta360__Messages__ScanBTPeripheral         *message);
size_t insta360__messages__scan_btperipheral__get_packed_size
                     (const Insta360__Messages__ScanBTPeripheral   *message);
size_t insta360__messages__scan_btperipheral__pack
                     (const Insta360__Messages__ScanBTPeripheral   *message,
                      uint8_t             *out);
size_t insta360__messages__scan_btperipheral__pack_to_buffer
                     (const Insta360__Messages__ScanBTPeripheral   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__ScanBTPeripheral *
       insta360__messages__scan_btperipheral__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__scan_btperipheral__free_unpacked
                     (Insta360__Messages__ScanBTPeripheral *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__ConnectToBTPeripheral methods */
void   insta360__messages__connect_to_btperipheral__init
                     (Insta360__Messages__ConnectToBTPeripheral         *message);
size_t insta360__messages__connect_to_btperipheral__get_packed_size
                     (const Insta360__Messages__ConnectToBTPeripheral   *message);
size_t insta360__messages__connect_to_btperipheral__pack
                     (const Insta360__Messages__ConnectToBTPeripheral   *message,
                      uint8_t             *out);
size_t insta360__messages__connect_to_btperipheral__pack_to_buffer
                     (const Insta360__Messages__ConnectToBTPeripheral   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__ConnectToBTPeripheral *
       insta360__messages__connect_to_btperipheral__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__connect_to_btperipheral__free_unpacked
                     (Insta360__Messages__ConnectToBTPeripheral *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__DisconnectBTPeripheral methods */
void   insta360__messages__disconnect_btperipheral__init
                     (Insta360__Messages__DisconnectBTPeripheral         *message);
size_t insta360__messages__disconnect_btperipheral__get_packed_size
                     (const Insta360__Messages__DisconnectBTPeripheral   *message);
size_t insta360__messages__disconnect_btperipheral__pack
                     (const Insta360__Messages__DisconnectBTPeripheral   *message,
                      uint8_t             *out);
size_t insta360__messages__disconnect_btperipheral__pack_to_buffer
                     (const Insta360__Messages__DisconnectBTPeripheral   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__DisconnectBTPeripheral *
       insta360__messages__disconnect_btperipheral__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__disconnect_btperipheral__free_unpacked
                     (Insta360__Messages__DisconnectBTPeripheral *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__GetConnectedBTPeripheral methods */
void   insta360__messages__get_connected_btperipheral__init
                     (Insta360__Messages__GetConnectedBTPeripheral         *message);
size_t insta360__messages__get_connected_btperipheral__get_packed_size
                     (const Insta360__Messages__GetConnectedBTPeripheral   *message);
size_t insta360__messages__get_connected_btperipheral__pack
                     (const Insta360__Messages__GetConnectedBTPeripheral   *message,
                      uint8_t             *out);
size_t insta360__messages__get_connected_btperipheral__pack_to_buffer
                     (const Insta360__Messages__GetConnectedBTPeripheral   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__GetConnectedBTPeripheral *
       insta360__messages__get_connected_btperipheral__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__get_connected_btperipheral__free_unpacked
                     (Insta360__Messages__GetConnectedBTPeripheral *message,
                      ProtobufCAllocator *allocator);
/* Insta360__Messages__GetConnectedBTPeripheralResp methods */
void   insta360__messages__get_connected_btperipheral_resp__init
                     (Insta360__Messages__GetConnectedBTPeripheralResp         *message);
size_t insta360__messages__get_connected_btperipheral_resp__get_packed_size
                     (const Insta360__Messages__GetConnectedBTPeripheralResp   *message);
size_t insta360__messages__get_connected_btperipheral_resp__pack
                     (const Insta360__Messages__GetConnectedBTPeripheralResp   *message,
                      uint8_t             *out);
size_t insta360__messages__get_connected_btperipheral_resp__pack_to_buffer
                     (const Insta360__Messages__GetConnectedBTPeripheralResp   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__GetConnectedBTPeripheralResp *
       insta360__messages__get_connected_btperipheral_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__get_connected_btperipheral_resp__free_unpacked
                     (Insta360__Messages__GetConnectedBTPeripheralResp *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__ScanBTPeripheral_Closure)
                 (const Insta360__Messages__ScanBTPeripheral *message,
                  void *closure_data);
typedef void (*Insta360__Messages__ConnectToBTPeripheral_Closure)
                 (const Insta360__Messages__ConnectToBTPeripheral *message,
                  void *closure_data);
typedef void (*Insta360__Messages__DisconnectBTPeripheral_Closure)
                 (const Insta360__Messages__DisconnectBTPeripheral *message,
                  void *closure_data);
typedef void (*Insta360__Messages__GetConnectedBTPeripheral_Closure)
                 (const Insta360__Messages__GetConnectedBTPeripheral *message,
                  void *closure_data);
typedef void (*Insta360__Messages__GetConnectedBTPeripheralResp_Closure)
                 (const Insta360__Messages__GetConnectedBTPeripheralResp *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor insta360__messages__scan_btperipheral__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__connect_to_btperipheral__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__disconnect_btperipheral__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__get_connected_btperipheral__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__get_connected_btperipheral_resp__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_bt_5fcentral_2eproto__INCLUDED */
