/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: options.proto */

#ifndef PROTOBUF_C_options_2eproto__INCLUDED
#define PROTOBUF_C_options_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "photo.pb-c.h"
#include "video.pb-c.h"
#include "battery.pb-c.h"
#include "storage.pb-c.h"
#include "button_press.pb-c.h"

typedef struct Insta360__Messages__Options Insta360__Messages__Options;
typedef struct Insta360__Messages__Options__GyroFilterConfig Insta360__Messages__Options__GyroFilterConfig;
typedef struct Insta360__Messages__Options__WifiInfo Insta360__Messages__Options__WifiInfo;
typedef struct Insta360__Messages__Options__WifiChannelList Insta360__Messages__Options__WifiChannelList;


/* --- enums --- */

typedef enum _Insta360__Messages__Options__WifiInfo__Mode {
  INSTA360__MESSAGES__OPTIONS__WIFI_INFO__MODE__AP = 0,
  INSTA360__MESSAGES__OPTIONS__WIFI_INFO__MODE__STA = 1,
  INSTA360__MESSAGES__OPTIONS__WIFI_INFO__MODE__P2P = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTIONS__WIFI_INFO__MODE)
} Insta360__Messages__Options__WifiInfo__Mode;
typedef enum _Insta360__Messages__Options__AccFullScaleRange {
  INSTA360__MESSAGES__OPTIONS__ACC_FULL_SCALE_RANGE__RANGE_2G = 0,
  INSTA360__MESSAGES__OPTIONS__ACC_FULL_SCALE_RANGE__RANGE_4G = 1,
  INSTA360__MESSAGES__OPTIONS__ACC_FULL_SCALE_RANGE__RANGE_8G = 2,
  INSTA360__MESSAGES__OPTIONS__ACC_FULL_SCALE_RANGE__RANGE_16G = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTIONS__ACC_FULL_SCALE_RANGE)
} Insta360__Messages__Options__AccFullScaleRange;
typedef enum _Insta360__Messages__Options__GyroFullScaleRange {
  INSTA360__MESSAGES__OPTIONS__GYRO_FULL_SCALE_RANGE__RANGE_250DPS = 0,
  INSTA360__MESSAGES__OPTIONS__GYRO_FULL_SCALE_RANGE__RANGE_500DPS = 1,
  INSTA360__MESSAGES__OPTIONS__GYRO_FULL_SCALE_RANGE__RANGE_1000DPS = 2,
  INSTA360__MESSAGES__OPTIONS__GYRO_FULL_SCALE_RANGE__RANGE_2000DPS = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTIONS__GYRO_FULL_SCALE_RANGE)
} Insta360__Messages__Options__GyroFullScaleRange;
typedef enum _Insta360__Messages__Options__AdoptionSystem {
  INSTA360__MESSAGES__OPTIONS__ADOPTION_SYSTEM__PHONE_IOS = 0,
  INSTA360__MESSAGES__OPTIONS__ADOPTION_SYSTEM__PHONE_ANDROID = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTIONS__ADOPTION_SYSTEM)
} Insta360__Messages__Options__AdoptionSystem;
typedef enum _Insta360__Messages__Options__WifiStatus {
  INSTA360__MESSAGES__OPTIONS__WIFI_STATUS__AUTO = 0,
  INSTA360__MESSAGES__OPTIONS__WIFI_STATUS__ON = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTIONS__WIFI_STATUS)
} Insta360__Messages__Options__WifiStatus;
typedef enum _Insta360__Messages__Options__EvoStatusMode {
  INSTA360__MESSAGES__OPTIONS__EVO_STATUS_MODE__UNKNOWN_STATUS_MODE = 0,
  INSTA360__MESSAGES__OPTIONS__EVO_STATUS_MODE__DEGREE180 = 1,
  INSTA360__MESSAGES__OPTIONS__EVO_STATUS_MODE__DEGREE360 = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTIONS__EVO_STATUS_MODE)
} Insta360__Messages__Options__EvoStatusMode;
typedef enum _Insta360__Messages__Options__BTRemoteType {
  INSTA360__MESSAGES__OPTIONS__BTREMOTE_TYPE__UNKNOWN_BT_REMOTE = 0,
  INSTA360__MESSAGES__OPTIONS__BTREMOTE_TYPE__BT_REMOTE_WITHOUT_GPS = 1,
  INSTA360__MESSAGES__OPTIONS__BTREMOTE_TYPE__BT_REMOTE_WITH_GPS = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTIONS__BTREMOTE_TYPE)
} Insta360__Messages__Options__BTRemoteType;
typedef enum _Insta360__Messages__Options__QualitySetting {
  INSTA360__MESSAGES__OPTIONS__QUALITY_SETTING__HIGH_QUALITY = 0,
  INSTA360__MESSAGES__OPTIONS__QUALITY_SETTING__LOW_QUALITY = 1
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTIONS__QUALITY_SETTING)
} Insta360__Messages__Options__QualitySetting;
typedef enum _Insta360__Messages__FunctionMode {
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_NORMAL = 0,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_LIVE_STREAM = 1,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_TIMELAPSE = 2,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_INTERVAL_SHOOTING = 3,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_HIGH_FRAME_RATE = 4,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_BURST = 5,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_NORMAL_IMAGE = 6,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_NORMAL_VIDEO = 7,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_HDR_IMAGE = 8,
  INSTA360__MESSAGES__FUNCTION_MODE__FUNCTION_MODE_HDR_VIDEO = 9
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__FUNCTION_MODE)
} Insta360__Messages__FunctionMode;
typedef enum _Insta360__Messages__OptionType {
  INSTA360__MESSAGES__OPTION_TYPE__OPTION_UNKNOWN = 0,
  INSTA360__MESSAGES__OPTION_TYPE__VIDEO_RESOLUTION = 1,
  INSTA360__MESSAGES__OPTION_TYPE__PHOTO_SIZE = 2,
  INSTA360__MESSAGES__OPTION_TYPE__VIDEO_BITRATE = 3,
  INSTA360__MESSAGES__OPTION_TYPE__AUDIO_BITRATE = 4,
  INSTA360__MESSAGES__OPTION_TYPE__AUDIO_SAMPLERATE = 5,
  INSTA360__MESSAGES__OPTION_TYPE__ORIGIN_OFFSET = 6,
  INSTA360__MESSAGES__OPTION_TYPE__CAPTURE_TIME_LIMIT = 7,
  INSTA360__MESSAGES__OPTION_TYPE__GPS_TIMEOUT = 8,
  INSTA360__MESSAGES__OPTION_TYPE__REMAINING_CAPTURE_TIME = 9,
  INSTA360__MESSAGES__OPTION_TYPE__REMAINING_PICTURES = 10,
  INSTA360__MESSAGES__OPTION_TYPE__BATTERY_STATUS = 11,
  INSTA360__MESSAGES__OPTION_TYPE__LOCAL_TIME = 12,
  INSTA360__MESSAGES__OPTION_TYPE__TIME_ZONE = 13,
  INSTA360__MESSAGES__OPTION_TYPE__MUTE = 14,
  INSTA360__MESSAGES__OPTION_TYPE__SERIAL_NUMBER = 15,
  INSTA360__MESSAGES__OPTION_TYPE__UUID = 16,
  INSTA360__MESSAGES__OPTION_TYPE__BUTTON_PRESS_OPTIONS = 17,
  INSTA360__MESSAGES__OPTION_TYPE__ACTIVATE_TIME = 19,
  INSTA360__MESSAGES__OPTION_TYPE__STORAGE_STATE = 20,
  INSTA360__MESSAGES__OPTION_TYPE__LENS_INDEX = 21,
  INSTA360__MESSAGES__OPTION_TYPE__MEDIA_OFFSET = 22,
  INSTA360__MESSAGES__OPTION_TYPE__SELF_TIMER = 23,
  INSTA360__MESSAGES__OPTION_TYPE__GYRO_SAMPLE_RATE = 24,
  INSTA360__MESSAGES__OPTION_TYPE__ACC_FULL_SCALE_RANGE = 25,
  INSTA360__MESSAGES__OPTION_TYPE__GYRO_FULL_SCALE_RANGE = 26,
  INSTA360__MESSAGES__OPTION_TYPE__TAKE_RAW_PICTURE = 27,
  INSTA360__MESSAGES__OPTION_TYPE__LOG_MODE = 28,
  INSTA360__MESSAGES__OPTION_TYPE__MEDIA_TIME = 29,
  INSTA360__MESSAGES__OPTION_TYPE__FIRMWAREREVISION = 30,
  INSTA360__MESSAGES__OPTION_TYPE__SYS_ADOPTION = 31,
  INSTA360__MESSAGES__OPTION_TYPE__CPU_TYPE = 32,
  INSTA360__MESSAGES__OPTION_TYPE__GYRO_FILTER = 33,
  INSTA360__MESSAGES__OPTION_TYPE__MCTF_ENABLE = 34,
  INSTA360__MESSAGES__OPTION_TYPE__SPORT_MODE_ENABLE = 35,
  INSTA360__MESSAGES__OPTION_TYPE__WIFI_INFO = 36,
  INSTA360__MESSAGES__OPTION_TYPE__WIFI_CHANNEL_LIST = 37,
  INSTA360__MESSAGES__OPTION_TYPE__AUTHORIZATION_ID = 38,
  INSTA360__MESSAGES__OPTION_TYPE__CALIBRATION_OFFSET = 39,
  INSTA360__MESSAGES__OPTION_TYPE__PHOTO_SUB_MODE = 40,
  INSTA360__MESSAGES__OPTION_TYPE__VIDEO_SUB_MODE = 41,
  INSTA360__MESSAGES__OPTION_TYPE__SECOND_STREAM_RES = 42,
  INSTA360__MESSAGES__OPTION_TYPE__WIFI_STATUS = 43,
  INSTA360__MESSAGES__OPTION_TYPE__EVO_STATUS_MODE = 44,
  INSTA360__MESSAGES__OPTION_TYPE__ORIGIN_OFFSET_3D = 45,
  INSTA360__MESSAGES__OPTION_TYPE__MEDIA_OFFSET_3D = 46,
  INSTA360__MESSAGES__OPTION_TYPE__CALIBRATION_OFFSET_3D = 47,
  INSTA360__MESSAGES__OPTION_TYPE__CAMERA_TYPE = 48,
  INSTA360__MESSAGES__OPTION_TYPE__BT_REMOTE_VERSION = 49,
  INSTA360__MESSAGES__OPTION_TYPE__BT_REMOTE_TYPE = 50,
  INSTA360__MESSAGES__OPTION_TYPE__QUALITY_SETTING = 51,
  INSTA360__MESSAGES__OPTION_TYPE__OVERHEAT_PROTECTION = 52,
  INSTA360__MESSAGES__OPTION_TYPE__OPTIONS_NUM = 53
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__OPTION_TYPE)
} Insta360__Messages__OptionType;

/* --- messages --- */

struct  Insta360__Messages__Options__GyroFilterConfig
{
  ProtobufCMessage base;
  uint32_t dlpf_value;
};
#define INSTA360__MESSAGES__OPTIONS__GYRO_FILTER_CONFIG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__options__gyro_filter_config__descriptor) \
    , 0 }


struct  Insta360__Messages__Options__WifiInfo
{
  ProtobufCMessage base;
  char *ssid;
  char *password;
  int32_t channel;
  Insta360__Messages__Options__WifiInfo__Mode mode;
};
#define INSTA360__MESSAGES__OPTIONS__WIFI_INFO__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__options__wifi_info__descriptor) \
    , (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, 0, INSTA360__MESSAGES__OPTIONS__WIFI_INFO__MODE__AP }


struct  Insta360__Messages__Options__WifiChannelList
{
  ProtobufCMessage base;
  char *country_code;
  ProtobufCBinaryData channel_list;
};
#define INSTA360__MESSAGES__OPTIONS__WIFI_CHANNEL_LIST__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__options__wifi_channel_list__descriptor) \
    , (char *)protobuf_c_empty_string, {0,NULL} }


struct  Insta360__Messages__Options
{
  ProtobufCMessage base;
  Insta360__Messages__VideoResolution video_resolution;
  Insta360__Messages__PhotoSize photo_size;
  uint32_t video_bitrate;
  uint32_t audio_bitrate;
  uint32_t audio_samplerate;
  char *origin_offset;
  uint32_t capture_time_limit;
  uint32_t gps_timeout;
  uint32_t remaining_capture_time;
  uint32_t remaining_pictures;
  Insta360__Messages__BatteryStatus *battery_status;
  uint64_t local_time;
  int32_t time_zone_seconds_from_gmt;
  protobuf_c_boolean mute;
  char *serial_number;
  char *uuid;
  Insta360__Messages__ButtonPressOptions *pressoptions;
  uint64_t activate_time;
  Insta360__Messages__StorageState *storage_state;
  uint32_t lens_index;
  char *media_offset;
  uint32_t self_timer;
  uint32_t gyro_sample_rate;
  Insta360__Messages__Options__AccFullScaleRange acc_range;
  Insta360__Messages__Options__GyroFullScaleRange gyro_range;
  protobuf_c_boolean take_raw_picture;
  protobuf_c_boolean log_mode;
  int64_t media_time;
  char *firmwarerevision;
  Insta360__Messages__Options__AdoptionSystem sys_adoption;
  char *cpu_type;
  Insta360__Messages__Options__GyroFilterConfig *gyro_filter_config;
  protobuf_c_boolean mctf_enable;
  protobuf_c_boolean sport_mode_enable;
  Insta360__Messages__Options__WifiInfo *wifi_info;
  Insta360__Messages__Options__WifiChannelList *wifi_channel_list;
  char *authorization_id;
  char *calibration_offset;
  Insta360__Messages__PhotoSubMode photo_sub_mode;
  Insta360__Messages__VideoSubMode video_sub_mode;
  Insta360__Messages__VideoResolution second_stream_res;
  Insta360__Messages__Options__WifiStatus wifi_status;
  Insta360__Messages__Options__EvoStatusMode evo_status_mode;
  char *origin_offset_3d;
  char *media_offset_3d;
  char *calibration_offset_3d;
  char *camera_type;
  char *bt_remote_version;
  Insta360__Messages__Options__BTRemoteType bt_remote_type;
  Insta360__Messages__Options__QualitySetting quality_setting;
  protobuf_c_boolean over_heat_protection;
};
#define INSTA360__MESSAGES__OPTIONS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&insta360__messages__options__descriptor) \
    , INSTA360__MESSAGES__VIDEO_RESOLUTION__RES_3840_1920P30, INSTA360__MESSAGES__PHOTO_SIZE__Size_6912_3456, 0, 0, 0, (char *)protobuf_c_empty_string, 0, 0, 0, 0, NULL, 0, 0, 0, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, NULL, 0, NULL, 0, (char *)protobuf_c_empty_string, 0, 0, INSTA360__MESSAGES__OPTIONS__ACC_FULL_SCALE_RANGE__RANGE_2G, INSTA360__MESSAGES__OPTIONS__GYRO_FULL_SCALE_RANGE__RANGE_250DPS, 0, 0, 0, (char *)protobuf_c_empty_string, INSTA360__MESSAGES__OPTIONS__ADOPTION_SYSTEM__PHONE_IOS, (char *)protobuf_c_empty_string, NULL, 0, 0, NULL, NULL, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, INSTA360__MESSAGES__PHOTO_SUB_MODE__PHOTO_SINGLE, INSTA360__MESSAGES__VIDEO_SUB_MODE__VIDEO_NORMAL, INSTA360__MESSAGES__VIDEO_RESOLUTION__RES_3840_1920P30, INSTA360__MESSAGES__OPTIONS__WIFI_STATUS__AUTO, INSTA360__MESSAGES__OPTIONS__EVO_STATUS_MODE__UNKNOWN_STATUS_MODE, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, (char *)protobuf_c_empty_string, INSTA360__MESSAGES__OPTIONS__BTREMOTE_TYPE__UNKNOWN_BT_REMOTE, INSTA360__MESSAGES__OPTIONS__QUALITY_SETTING__HIGH_QUALITY, 0 }


/* Insta360__Messages__Options__GyroFilterConfig methods */
void   insta360__messages__options__gyro_filter_config__init
                     (Insta360__Messages__Options__GyroFilterConfig         *message);
/* Insta360__Messages__Options__WifiInfo methods */
void   insta360__messages__options__wifi_info__init
                     (Insta360__Messages__Options__WifiInfo         *message);
/* Insta360__Messages__Options__WifiChannelList methods */
void   insta360__messages__options__wifi_channel_list__init
                     (Insta360__Messages__Options__WifiChannelList         *message);
/* Insta360__Messages__Options methods */
void   insta360__messages__options__init
                     (Insta360__Messages__Options         *message);
size_t insta360__messages__options__get_packed_size
                     (const Insta360__Messages__Options   *message);
size_t insta360__messages__options__pack
                     (const Insta360__Messages__Options   *message,
                      uint8_t             *out);
size_t insta360__messages__options__pack_to_buffer
                     (const Insta360__Messages__Options   *message,
                      ProtobufCBuffer     *buffer);
Insta360__Messages__Options *
       insta360__messages__options__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   insta360__messages__options__free_unpacked
                     (Insta360__Messages__Options *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Insta360__Messages__Options__GyroFilterConfig_Closure)
                 (const Insta360__Messages__Options__GyroFilterConfig *message,
                  void *closure_data);
typedef void (*Insta360__Messages__Options__WifiInfo_Closure)
                 (const Insta360__Messages__Options__WifiInfo *message,
                  void *closure_data);
typedef void (*Insta360__Messages__Options__WifiChannelList_Closure)
                 (const Insta360__Messages__Options__WifiChannelList *message,
                  void *closure_data);
typedef void (*Insta360__Messages__Options_Closure)
                 (const Insta360__Messages__Options *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    insta360__messages__function_mode__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__option_type__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__options__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__options__gyro_filter_config__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__options__wifi_info__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__options__wifi_info__mode__descriptor;
extern const ProtobufCMessageDescriptor insta360__messages__options__wifi_channel_list__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__options__acc_full_scale_range__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__options__gyro_full_scale_range__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__options__adoption_system__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__options__wifi_status__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__options__evo_status_mode__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__options__btremote_type__descriptor;
extern const ProtobufCEnumDescriptor    insta360__messages__options__quality_setting__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_options_2eproto__INCLUDED */
