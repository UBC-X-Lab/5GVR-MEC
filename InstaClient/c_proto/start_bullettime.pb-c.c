/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: start_bullettime.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "start_bullettime.pb-c.h"
void   insta360__messages__start_bullet_time__init
                     (Insta360__Messages__StartBulletTime         *message)
{
  static const Insta360__Messages__StartBulletTime init_value = INSTA360__MESSAGES__START_BULLET_TIME__INIT;
  *message = init_value;
}
size_t insta360__messages__start_bullet_time__get_packed_size
                     (const Insta360__Messages__StartBulletTime *message)
{
  assert(message->base.descriptor == &insta360__messages__start_bullet_time__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__start_bullet_time__pack
                     (const Insta360__Messages__StartBulletTime *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__start_bullet_time__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__start_bullet_time__pack_to_buffer
                     (const Insta360__Messages__StartBulletTime *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__start_bullet_time__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__StartBulletTime *
       insta360__messages__start_bullet_time__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__StartBulletTime *)
     protobuf_c_message_unpack (&insta360__messages__start_bullet_time__descriptor,
                                allocator, len, data);
}
void   insta360__messages__start_bullet_time__free_unpacked
                     (Insta360__Messages__StartBulletTime *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__start_bullet_time__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   insta360__messages__start_bullet_time_resp__init
                     (Insta360__Messages__StartBulletTimeResp         *message)
{
  static const Insta360__Messages__StartBulletTimeResp init_value = INSTA360__MESSAGES__START_BULLET_TIME_RESP__INIT;
  *message = init_value;
}
size_t insta360__messages__start_bullet_time_resp__get_packed_size
                     (const Insta360__Messages__StartBulletTimeResp *message)
{
  assert(message->base.descriptor == &insta360__messages__start_bullet_time_resp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__start_bullet_time_resp__pack
                     (const Insta360__Messages__StartBulletTimeResp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__start_bullet_time_resp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__start_bullet_time_resp__pack_to_buffer
                     (const Insta360__Messages__StartBulletTimeResp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__start_bullet_time_resp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__StartBulletTimeResp *
       insta360__messages__start_bullet_time_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__StartBulletTimeResp *)
     protobuf_c_message_unpack (&insta360__messages__start_bullet_time_resp__descriptor,
                                allocator, len, data);
}
void   insta360__messages__start_bullet_time_resp__free_unpacked
                     (Insta360__Messages__StartBulletTimeResp *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__start_bullet_time_resp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
#define insta360__messages__start_bullet_time__field_descriptors NULL
#define insta360__messages__start_bullet_time__field_indices_by_name NULL
#define insta360__messages__start_bullet_time__number_ranges NULL
const ProtobufCMessageDescriptor insta360__messages__start_bullet_time__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.StartBulletTime",
  "StartBulletTime",
  "Insta360__Messages__StartBulletTime",
  "insta360.messages",
  sizeof(Insta360__Messages__StartBulletTime),
  0,
  insta360__messages__start_bullet_time__field_descriptors,
  insta360__messages__start_bullet_time__field_indices_by_name,
  0,  insta360__messages__start_bullet_time__number_ranges,
  (ProtobufCMessageInit) insta360__messages__start_bullet_time__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define insta360__messages__start_bullet_time_resp__field_descriptors NULL
#define insta360__messages__start_bullet_time_resp__field_indices_by_name NULL
#define insta360__messages__start_bullet_time_resp__number_ranges NULL
const ProtobufCMessageDescriptor insta360__messages__start_bullet_time_resp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.StartBulletTimeResp",
  "StartBulletTimeResp",
  "Insta360__Messages__StartBulletTimeResp",
  "insta360.messages",
  sizeof(Insta360__Messages__StartBulletTimeResp),
  0,
  insta360__messages__start_bullet_time_resp__field_descriptors,
  insta360__messages__start_bullet_time_resp__field_indices_by_name,
  0,  insta360__messages__start_bullet_time_resp__number_ranges,
  (ProtobufCMessageInit) insta360__messages__start_bullet_time_resp__init,
  NULL,NULL,NULL    /* reserved[123] */
};
