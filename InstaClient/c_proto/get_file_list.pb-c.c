/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: get_file_list.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "get_file_list.pb-c.h"
void   insta360__messages__get_file_list__init
                     (Insta360__Messages__GetFileList         *message)
{
  static const Insta360__Messages__GetFileList init_value = INSTA360__MESSAGES__GET_FILE_LIST__INIT;
  *message = init_value;
}
size_t insta360__messages__get_file_list__get_packed_size
                     (const Insta360__Messages__GetFileList *message)
{
  assert(message->base.descriptor == &insta360__messages__get_file_list__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__get_file_list__pack
                     (const Insta360__Messages__GetFileList *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__get_file_list__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__get_file_list__pack_to_buffer
                     (const Insta360__Messages__GetFileList *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__get_file_list__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__GetFileList *
       insta360__messages__get_file_list__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__GetFileList *)
     protobuf_c_message_unpack (&insta360__messages__get_file_list__descriptor,
                                allocator, len, data);
}
void   insta360__messages__get_file_list__free_unpacked
                     (Insta360__Messages__GetFileList *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__get_file_list__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   insta360__messages__get_file_list_resp__init
                     (Insta360__Messages__GetFileListResp         *message)
{
  static const Insta360__Messages__GetFileListResp init_value = INSTA360__MESSAGES__GET_FILE_LIST_RESP__INIT;
  *message = init_value;
}
size_t insta360__messages__get_file_list_resp__get_packed_size
                     (const Insta360__Messages__GetFileListResp *message)
{
  assert(message->base.descriptor == &insta360__messages__get_file_list_resp__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t insta360__messages__get_file_list_resp__pack
                     (const Insta360__Messages__GetFileListResp *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &insta360__messages__get_file_list_resp__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t insta360__messages__get_file_list_resp__pack_to_buffer
                     (const Insta360__Messages__GetFileListResp *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &insta360__messages__get_file_list_resp__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Insta360__Messages__GetFileListResp *
       insta360__messages__get_file_list_resp__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Insta360__Messages__GetFileListResp *)
     protobuf_c_message_unpack (&insta360__messages__get_file_list_resp__descriptor,
                                allocator, len, data);
}
void   insta360__messages__get_file_list_resp__free_unpacked
                     (Insta360__Messages__GetFileListResp *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &insta360__messages__get_file_list_resp__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor insta360__messages__get_file_list__field_descriptors[3] =
{
  {
    "media_type",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__GetFileList, media_type),
    &insta360__messages__media_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "start",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__GetFileList, start),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "limit",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__GetFileList, limit),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__get_file_list__field_indices_by_name[] = {
  2,   /* field[2] = limit */
  0,   /* field[0] = media_type */
  1,   /* field[1] = start */
};
static const ProtobufCIntRange insta360__messages__get_file_list__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor insta360__messages__get_file_list__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.GetFileList",
  "GetFileList",
  "Insta360__Messages__GetFileList",
  "insta360.messages",
  sizeof(Insta360__Messages__GetFileList),
  3,
  insta360__messages__get_file_list__field_descriptors,
  insta360__messages__get_file_list__field_indices_by_name,
  1,  insta360__messages__get_file_list__number_ranges,
  (ProtobufCMessageInit) insta360__messages__get_file_list__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor insta360__messages__get_file_list_resp__field_descriptors[2] =
{
  {
    "uri",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_STRING,
    offsetof(Insta360__Messages__GetFileListResp, n_uri),
    offsetof(Insta360__Messages__GetFileListResp, uri),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "total_count",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_UINT32,
    0,   /* quantifier_offset */
    offsetof(Insta360__Messages__GetFileListResp, total_count),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned insta360__messages__get_file_list_resp__field_indices_by_name[] = {
  1,   /* field[1] = total_count */
  0,   /* field[0] = uri */
};
static const ProtobufCIntRange insta360__messages__get_file_list_resp__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor insta360__messages__get_file_list_resp__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "insta360.messages.GetFileListResp",
  "GetFileListResp",
  "Insta360__Messages__GetFileListResp",
  "insta360.messages",
  sizeof(Insta360__Messages__GetFileListResp),
  2,
  insta360__messages__get_file_list_resp__field_descriptors,
  insta360__messages__get_file_list_resp__field_indices_by_name,
  1,  insta360__messages__get_file_list_resp__number_ranges,
  (ProtobufCMessageInit) insta360__messages__get_file_list_resp__init,
  NULL,NULL,NULL    /* reserved[123] */
};