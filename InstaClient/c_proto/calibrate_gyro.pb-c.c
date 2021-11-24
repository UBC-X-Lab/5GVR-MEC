/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: calibrate_gyro.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "calibrate_gyro.pb-c.h"
void   insta360__messages__calibrate_gyro__init
                     (Insta360__Messages__CalibrateGyro         *message)
{
  static const Insta360__Messages__CalibrateGyro init_value = INSTA360__MESSAGES__CALIBRATE_GYRO__INIT;
  *message = init_value;
}
size_t insta360__messages__calibrate_gyro__get_packed_size
                     (const Insta360__Messages__CalibrateGyro *message)
{
  assert(message->base.descriptor == &insta360__messages__calibrate_gyro__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__calibrate_gyro__pack
                     (const Insta360__Messages__CalibrateGyro *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__calibrate_gyro__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__calibrate_gyro__pack_to_buffer
                     (const Insta360__Messages__CalibrateGyro *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__calibrate_gyro__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__CalibrateGyro *
       insta360__messages__calibrate_gyro__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__CalibrateGyro *)
     protobuf_c_message_unpack (&insta360__messages__calibrate_gyro__descriptor,
                                allocator, len, data);
}
void   insta360__messages__calibrate_gyro__free_unpacked
                     (Insta360__Messages__CalibrateGyro *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__calibrate_gyro__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor insta360__messages__calibrate_gyro__field_descriptors[1] =
{
  {
    "gyro_count",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__CalibrateGyro, gyro_count),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__calibrate_gyro__field_indices_by_name[] = {
  0,   /* field[0] = gyro_count */
};
static const ProtobufCIntRange insta360__messages__calibrate_gyro__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor insta360__messages__calibrate_gyro__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.CalibrateGyro",
  "CalibrateGyro",
  "Insta360__Messages__CalibrateGyro",
  "insta360.messages",
  sizeof(Insta360__Messages__CalibrateGyro),
  1,
  insta360__messages__calibrate_gyro__field_descriptors,
  insta360__messages__calibrate_gyro__field_indices_by_name,
  1,  insta360__messages__calibrate_gyro__number_ranges,
  (ProtobufCMessageInit) insta360__messages__calibrate_gyro__init,
  NULL,NULL,NULL    /* reserved[123] */
};
