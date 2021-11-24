/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: take_picture_state_update.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "take_picture_state_update.pb-c.h"
void   insta360__messages__notification_take_picture_state_update__init
                     (Insta360__Messages__NotificationTakePictureStateUpdate         *message)
{
  static const Insta360__Messages__NotificationTakePictureStateUpdate init_value = INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__INIT;
  *message = init_value;
}
size_t insta360__messages__notification_take_picture_state_update__get_packed_size
                     (const Insta360__Messages__NotificationTakePictureStateUpdate *message)
{
  assert(message->base.descriptor == &insta360__messages__notification_take_picture_state_update__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__notification_take_picture_state_update__pack
                     (const Insta360__Messages__NotificationTakePictureStateUpdate *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__notification_take_picture_state_update__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__notification_take_picture_state_update__pack_to_buffer
                     (const Insta360__Messages__NotificationTakePictureStateUpdate *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__notification_take_picture_state_update__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__NotificationTakePictureStateUpdate *
       insta360__messages__notification_take_picture_state_update__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__NotificationTakePictureStateUpdate *)
     protobuf_c_message_unpack (&insta360__messages__notification_take_picture_state_update__descriptor,
                                allocator, len, data);
}
void   insta360__messages__notification_take_picture_state_update__free_unpacked
                     (Insta360__Messages__NotificationTakePictureStateUpdate *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__notification_take_picture_state_update__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCEnumValue insta360__messages__notification_take_picture_state_update__take_picture_state__enum_values_by_number[3] =
{
  { "SHUTTER", "INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__TAKE_PICTURE_STATE__SHUTTER", 0 },
  { "COMPRESS", "INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__TAKE_PICTURE_STATE__COMPRESS", 1 },
  { "WRITE_FILE", "INSTA360__MESSAGES__NOTIFICATION_TAKE_PICTURE_STATE_UPDATE__TAKE_PICTURE_STATE__WRITE_FILE", 2 },
};
static const ProtobufCIntRange insta360__messages__notification_take_picture_state_update__take_picture_state__value_ranges[] = {
{0, 0},{0, 3}
};
static const ProtobufCEnumValueIndex insta360__messages__notification_take_picture_state_update__take_picture_state__enum_values_by_name[3] =
{
  { "COMPRESS", 1 },
  { "SHUTTER", 0 },
  { "WRITE_FILE", 2 },
};
const ProtobufCEnumDescriptor insta360__messages__notification_take_picture_state_update__take_picture_state__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "insta360.messages.NotificationTakePictureStateUpdate.TakePictureState",
  "TakePictureState",
  "Insta360__Messages__NotificationTakePictureStateUpdate__TakePictureState",
  "insta360.messages",
  3,
  insta360__messages__notification_take_picture_state_update__take_picture_state__enum_values_by_number,
  3,
  insta360__messages__notification_take_picture_state_update__take_picture_state__enum_values_by_name,
  1,
  insta360__messages__notification_take_picture_state_update__take_picture_state__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor insta360__messages__notification_take_picture_state_update__field_descriptors[1] =
{
  {
    "state",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__NotificationTakePictureStateUpdate, state),
    &insta360__messages__notification_take_picture_state_update__take_picture_state__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__notification_take_picture_state_update__field_indices_by_name[] = {
  0,   /* field[0] = state */
};
static const ProtobufCIntRange insta360__messages__notification_take_picture_state_update__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor insta360__messages__notification_take_picture_state_update__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.NotificationTakePictureStateUpdate",
  "NotificationTakePictureStateUpdate",
  "Insta360__Messages__NotificationTakePictureStateUpdate",
  "insta360.messages",
  sizeof(Insta360__Messages__NotificationTakePictureStateUpdate),
  1,
  insta360__messages__notification_take_picture_state_update__field_descriptors,
  insta360__messages__notification_take_picture_state_update__field_indices_by_name,
  1,  insta360__messages__notification_take_picture_state_update__number_ranges,
  (ProtobufCMessageInit) insta360__messages__notification_take_picture_state_update__init,
  NULL,NULL,NULL    /* reserved[123] */
};
