/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: current_capture_status.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "current_capture_status.pb-c.h"
void   insta360__messages__capture_status__init
                     (Insta360__Messages__CaptureStatus         *message)
{
  static const Insta360__Messages__CaptureStatus init_value = INSTA360__MESSAGES__CAPTURE_STATUS__INIT;
  *message = init_value;
}
size_t insta360__messages__capture_status__get_packed_size
                     (const Insta360__Messages__CaptureStatus *message)
{
  assert(message->base.descriptor == &insta360__messages__capture_status__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__capture_status__pack
                     (const Insta360__Messages__CaptureStatus *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__capture_status__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__capture_status__pack_to_buffer
                     (const Insta360__Messages__CaptureStatus *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__capture_status__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__CaptureStatus *
       insta360__messages__capture_status__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__CaptureStatus *)
     protobuf_c_message_unpack (&insta360__messages__capture_status__descriptor,
                                allocator, len, data);
}
void   insta360__messages__capture_status__free_unpacked
                     (Insta360__Messages__CaptureStatus *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__capture_status__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor insta360__messages__capture_status__field_descriptors[2] =
{
  {
    "state",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__CaptureStatus, state),
    &insta360__messages__camera_capture_state__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "capture_time",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__CaptureStatus, capture_time),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__capture_status__field_indices_by_name[] = {
  1,   /* field[1] = capture_time */
  0,   /* field[0] = state */
};
static const ProtobufCIntRange insta360__messages__capture_status__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor insta360__messages__capture_status__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.CaptureStatus",
  "CaptureStatus",
  "Insta360__Messages__CaptureStatus",
  "insta360.messages",
  sizeof(Insta360__Messages__CaptureStatus),
  2,
  insta360__messages__capture_status__field_descriptors,
  insta360__messages__capture_status__field_indices_by_name,
  1,  insta360__messages__capture_status__number_ranges,
  (ProtobufCMessageInit) insta360__messages__capture_status__init,
  NULL,NULL,NULL    /* reserved[123] */
};