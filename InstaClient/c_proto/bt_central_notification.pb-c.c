/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: bt_central_notification.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "bt_central_notification.pb-c.h"
void   insta360__messages__notificatoin_discover_btperipheral__init
                     (Insta360__Messages__NotificatoinDiscoverBTPeripheral         *message)
{
  static const Insta360__Messages__NotificatoinDiscoverBTPeripheral init_value = INSTA360__MESSAGES__NOTIFICATOIN_DISCOVER_BTPERIPHERAL__INIT;
  *message = init_value;
}
size_t insta360__messages__notificatoin_discover_btperipheral__get_packed_size
                     (const Insta360__Messages__NotificatoinDiscoverBTPeripheral *message)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_discover_btperipheral__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__notificatoin_discover_btperipheral__pack
                     (const Insta360__Messages__NotificatoinDiscoverBTPeripheral *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_discover_btperipheral__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__notificatoin_discover_btperipheral__pack_to_buffer
                     (const Insta360__Messages__NotificatoinDiscoverBTPeripheral *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_discover_btperipheral__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__NotificatoinDiscoverBTPeripheral *
       insta360__messages__notificatoin_discover_btperipheral__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__NotificatoinDiscoverBTPeripheral *)
     protobuf_c_message_unpack (&insta360__messages__notificatoin_discover_btperipheral__descriptor,
                                allocator, len, data);
}
void   insta360__messages__notificatoin_discover_btperipheral__free_unpacked
                     (Insta360__Messages__NotificatoinDiscoverBTPeripheral *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__notificatoin_discover_btperipheral__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   insta360__messages__notificatoin_connected_to_peripheral__init
                     (Insta360__Messages__NotificatoinConnectedToPeripheral         *message)
{
  static const Insta360__Messages__NotificatoinConnectedToPeripheral init_value = INSTA360__MESSAGES__NOTIFICATOIN_CONNECTED_TO_PERIPHERAL__INIT;
  *message = init_value;
}
size_t insta360__messages__notificatoin_connected_to_peripheral__get_packed_size
                     (const Insta360__Messages__NotificatoinConnectedToPeripheral *message)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_connected_to_peripheral__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__notificatoin_connected_to_peripheral__pack
                     (const Insta360__Messages__NotificatoinConnectedToPeripheral *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_connected_to_peripheral__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__notificatoin_connected_to_peripheral__pack_to_buffer
                     (const Insta360__Messages__NotificatoinConnectedToPeripheral *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_connected_to_peripheral__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__NotificatoinConnectedToPeripheral *
       insta360__messages__notificatoin_connected_to_peripheral__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__NotificatoinConnectedToPeripheral *)
     protobuf_c_message_unpack (&insta360__messages__notificatoin_connected_to_peripheral__descriptor,
                                allocator, len, data);
}
void   insta360__messages__notificatoin_connected_to_peripheral__free_unpacked
                     (Insta360__Messages__NotificatoinConnectedToPeripheral *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__notificatoin_connected_to_peripheral__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   insta360__messages__notificatoin_disconnected_peripheral__init
                     (Insta360__Messages__NotificatoinDisconnectedPeripheral         *message)
{
  static const Insta360__Messages__NotificatoinDisconnectedPeripheral init_value = INSTA360__MESSAGES__NOTIFICATOIN_DISCONNECTED_PERIPHERAL__INIT;
  *message = init_value;
}
size_t insta360__messages__notificatoin_disconnected_peripheral__get_packed_size
                     (const Insta360__Messages__NotificatoinDisconnectedPeripheral *message)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_disconnected_peripheral__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__notificatoin_disconnected_peripheral__pack
                     (const Insta360__Messages__NotificatoinDisconnectedPeripheral *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_disconnected_peripheral__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__notificatoin_disconnected_peripheral__pack_to_buffer
                     (const Insta360__Messages__NotificatoinDisconnectedPeripheral *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__notificatoin_disconnected_peripheral__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__NotificatoinDisconnectedPeripheral *
       insta360__messages__notificatoin_disconnected_peripheral__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__NotificatoinDisconnectedPeripheral *)
     protobuf_c_message_unpack (&insta360__messages__notificatoin_disconnected_peripheral__descriptor,
                                allocator, len, data);
}
void   insta360__messages__notificatoin_disconnected_peripheral__free_unpacked
                     (Insta360__Messages__NotificatoinDisconnectedPeripheral *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__notificatoin_disconnected_peripheral__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor insta360__messages__notificatoin_discover_btperipheral__field_descriptors[1] =
{
  {
    "peripherals",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Insta360__Messages__NotificatoinDiscoverBTPeripheral, n_peripherals),
    offsetof(Insta360__Messages__NotificatoinDiscoverBTPeripheral, peripherals),
    &insta360__messages__btperipheral__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__notificatoin_discover_btperipheral__field_indices_by_name[] = {
  0,   /* field[0] = peripherals */
};
static const ProtobufCIntRange insta360__messages__notificatoin_discover_btperipheral__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor insta360__messages__notificatoin_discover_btperipheral__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.NotificatoinDiscoverBTPeripheral",
  "NotificatoinDiscoverBTPeripheral",
  "Insta360__Messages__NotificatoinDiscoverBTPeripheral",
  "insta360.messages",
  sizeof(Insta360__Messages__NotificatoinDiscoverBTPeripheral),
  1,
  insta360__messages__notificatoin_discover_btperipheral__field_descriptors,
  insta360__messages__notificatoin_discover_btperipheral__field_indices_by_name,
  1,  insta360__messages__notificatoin_discover_btperipheral__number_ranges,
  (ProtobufCMessageInit) insta360__messages__notificatoin_discover_btperipheral__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor insta360__messages__notificatoin_connected_to_peripheral__field_descriptors[1] =
{
  {
    "peripheral",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__NotificatoinConnectedToPeripheral, peripheral),
    &insta360__messages__btperipheral__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__notificatoin_connected_to_peripheral__field_indices_by_name[] = {
  0,   /* field[0] = peripheral */
};
static const ProtobufCIntRange insta360__messages__notificatoin_connected_to_peripheral__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor insta360__messages__notificatoin_connected_to_peripheral__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.NotificatoinConnectedToPeripheral",
  "NotificatoinConnectedToPeripheral",
  "Insta360__Messages__NotificatoinConnectedToPeripheral",
  "insta360.messages",
  sizeof(Insta360__Messages__NotificatoinConnectedToPeripheral),
  1,
  insta360__messages__notificatoin_connected_to_peripheral__field_descriptors,
  insta360__messages__notificatoin_connected_to_peripheral__field_indices_by_name,
  1,  insta360__messages__notificatoin_connected_to_peripheral__number_ranges,
  (ProtobufCMessageInit) insta360__messages__notificatoin_connected_to_peripheral__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor insta360__messages__notificatoin_disconnected_peripheral__field_descriptors[1] =
{
  {
    "peripheral",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__NotificatoinDisconnectedPeripheral, peripheral),
    &insta360__messages__btperipheral__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__notificatoin_disconnected_peripheral__field_indices_by_name[] = {
  0,   /* field[0] = peripheral */
};
static const ProtobufCIntRange insta360__messages__notificatoin_disconnected_peripheral__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor insta360__messages__notificatoin_disconnected_peripheral__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.NotificatoinDisconnectedPeripheral",
  "NotificatoinDisconnectedPeripheral",
  "Insta360__Messages__NotificatoinDisconnectedPeripheral",
  "insta360.messages",
  sizeof(Insta360__Messages__NotificatoinDisconnectedPeripheral),
  1,
  insta360__messages__notificatoin_disconnected_peripheral__field_descriptors,
  insta360__messages__notificatoin_disconnected_peripheral__field_indices_by_name,
  1,  insta360__messages__notificatoin_disconnected_peripheral__number_ranges,
  (ProtobufCMessageInit) insta360__messages__notificatoin_disconnected_peripheral__init,
  NULL,NULL,NULL    /* reserved[123] */
};
