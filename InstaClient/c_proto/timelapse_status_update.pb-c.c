/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: timelapse_status_update.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "timelapse_status_update.pb-c.h"
void   insta360__messages__notification_time_lapse_status_update__init
                     (Insta360__Messages__NotificationTimeLapseStatusUpdate         *message)
{
  static const Insta360__Messages__NotificationTimeLapseStatusUpdate init_value = INSTA360__MESSAGES__NOTIFICATION_TIME_LAPSE_STATUS_UPDATE__INIT;
  *message = init_value;
}
size_t insta360__messages__notification_time_lapse_status_update__get_packed_size
                     (const Insta360__Messages__NotificationTimeLapseStatusUpdate *message)
{
  assert(message->base.descriptor == &insta360__messages__notification_time_lapse_status_update__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__notification_time_lapse_status_update__pack
                     (const Insta360__Messages__NotificationTimeLapseStatusUpdate *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__notification_time_lapse_status_update__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__notification_time_lapse_status_update__pack_to_buffer
                     (const Insta360__Messages__NotificationTimeLapseStatusUpdate *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__notification_time_lapse_status_update__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__NotificationTimeLapseStatusUpdate *
       insta360__messages__notification_time_lapse_status_update__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__NotificationTimeLapseStatusUpdate *)
     protobuf_c_message_unpack (&insta360__messages__notification_time_lapse_status_update__descriptor,
                                allocator, len, data);
}
void   insta360__messages__notification_time_lapse_status_update__free_unpacked
                     (Insta360__Messages__NotificationTimeLapseStatusUpdate *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__notification_time_lapse_status_update__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor insta360__messages__notification_time_lapse_status_update__field_descriptors[1] =
{
  {
    "interval_count",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__NotificationTimeLapseStatusUpdate, interval_count),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__notification_time_lapse_status_update__field_indices_by_name[] = {
  0,   /* field[0] = interval_count */
};
static const ProtobufCIntRange insta360__messages__notification_time_lapse_status_update__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor insta360__messages__notification_time_lapse_status_update__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.NotificationTimeLapseStatusUpdate",
  "NotificationTimeLapseStatusUpdate",
  "Insta360__Messages__NotificationTimeLapseStatusUpdate",
  "insta360.messages",
  sizeof(Insta360__Messages__NotificationTimeLapseStatusUpdate),
  1,
  insta360__messages__notification_time_lapse_status_update__field_descriptors,
  insta360__messages__notification_time_lapse_status_update__field_indices_by_name,
  1,  insta360__messages__notification_time_lapse_status_update__number_ranges,
  (ProtobufCMessageInit) insta360__messages__notification_time_lapse_status_update__init,
  NULL,NULL,NULL    /* reserved[123] */
};