/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: get_mini_thumbnail.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "get_mini_thumbnail.pb-c.h"
void   insta360__messages__get_mini_thumbnail__init
                     (Insta360__Messages__GetMiniThumbnail         *message)
{
  static const Insta360__Messages__GetMiniThumbnail init_value = INSTA360__MESSAGES__GET_MINI_THUMBNAIL__INIT;
  *message = init_value;
}
size_t insta360__messages__get_mini_thumbnail__get_packed_size
                     (const Insta360__Messages__GetMiniThumbnail *message)
{
  assert(message->base.descriptor == &insta360__messages__get_mini_thumbnail__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__get_mini_thumbnail__pack
                     (const Insta360__Messages__GetMiniThumbnail *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__get_mini_thumbnail__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__get_mini_thumbnail__pack_to_buffer
                     (const Insta360__Messages__GetMiniThumbnail *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__get_mini_thumbnail__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__GetMiniThumbnail *
       insta360__messages__get_mini_thumbnail__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__GetMiniThumbnail *)
     protobuf_c_message_unpack (&insta360__messages__get_mini_thumbnail__descriptor,
                                allocator, len, data);
}
void   insta360__messages__get_mini_thumbnail__free_unpacked
                     (Insta360__Messages__GetMiniThumbnail *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__get_mini_thumbnail__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor insta360__messages__get_mini_thumbnail__field_descriptors[1] =
{
  {
    "uri",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__GetMiniThumbnail, uri),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__get_mini_thumbnail__field_indices_by_name[] = {
  0,   /* field[0] = uri */
};
static const ProtobufCIntRange insta360__messages__get_mini_thumbnail__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor insta360__messages__get_mini_thumbnail__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.GetMiniThumbnail",
  "GetMiniThumbnail",
  "Insta360__Messages__GetMiniThumbnail",
  "insta360.messages",
  sizeof(Insta360__Messages__GetMiniThumbnail),
  1,
  insta360__messages__get_mini_thumbnail__field_descriptors,
  insta360__messages__get_mini_thumbnail__field_indices_by_name,
  1,  insta360__messages__get_mini_thumbnail__number_ranges,
  (ProtobufCMessageInit) insta360__messages__get_mini_thumbnail__init,
  NULL,NULL,NULL    /* reserved[123] */
};