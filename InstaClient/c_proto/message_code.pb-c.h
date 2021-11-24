/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: message_code.proto */

#ifndef PROTOBUF_C_message_5fcode_2eproto__INCLUDED
#define PROTOBUF_C_message_5fcode_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004000 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif




/* --- enums --- */

typedef enum _Insta360__Messages__MessageCode {
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_BEGIN = 0,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_START_LIVE_STREAM = 1,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_STOP_LIVE_STREAM = 2,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_TAKE_PICTURE = 3,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_START_CAPTURE = 4,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_STOP_CAPTURE = 5,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_CANCEL_CAPTURE = 6,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_SET_OPTIONS = 7,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_OPTIONS = 8,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_SET_PHOTOGRAPHY_OPTIONS = 9,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_PHOTOGRAPHY_OPTIONS = 10,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_FILE_EXTRA = 11,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_DELETE_FILES = 12,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_FILE_LIST = 13,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_TAKE_PICTURE_WITHOUT_STORING = 14,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_CURRENT_CAPTURE_STATUS = 15,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_SET_FILE_EXTRA = 16,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_TIMELAPSE_OPTIONS = 17,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_SET_TIMELAPSE_OPTIONS = 18,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_GYRO = 19,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_START_TIMELAPSE = 22,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_STOP_TIMELAPSE = 23,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_ERASE_SD_CARD = 24,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_CALIBRATE_GYRO = 25,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_SCAN_BT_PERIPHERAL = 26,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_CONNECT_TO_BT_PERIPHERAL = 27,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_DISCONNECT_BT_PERIPHERAL = 28,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_CONNECTED_BT_PERIPHERALS = 29,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_MINI_THUMBNAIL = 30,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_TEST_SD_CARD_SPEED = 31,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_REBOOT_CAMERA = 32,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_OPEN_CAMERA_WIFI = 33,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_CLOSE_CAMERA_WIFI = 34,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_OPEN_IPERF = 35,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_CLOSE_IPERF = 36,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_IPERF_AVERAGE = 37,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_FILEINFO_LIST = 38,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_CHECK_AUTHORIZATION = 39,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_CANCEL_AUTHORIZATION = 40,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_START_BULLETTIME_CAPTURE = 41,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_SET_SUBMODE_OPTIONS = 42,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_SUBMODE_OPTIONS = 43,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_STOP_BULLETTIME_CAPTURE = 48,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_OPEN_OLED = 49,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_CLOSE_OLED = 50,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_START_HDR_CAPTURE = 51,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_STOP_HDR_CAPTURE = 52,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_UPLOAD_GPS = 53,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_SET_SYNC_CAPTURE_MODE = 54,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_COMMAND_GET_SYNC_CAPTURE_MODE = 55,
  INSTA360__MESSAGES__MESSAGE_CODE__PHONE_REQUEST_BEGIN = 4096,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_BEGIN = 8192,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_FIRMWARE_UPGRADE_COMPLETE = 8193,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_CAPTURE_AUTO_SPLIT = 8194,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_BATTERY_UPDATE = 8195,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_BATTERY_LOW = 8196,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_SHUTDOWN = 8197,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_STORAGE_UPDATE = 8198,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_STORAGE_FULL = 8199,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_KEY_PRESSED = 8200,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_CAPTURE_STOPPED = 8201,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_TAKE_PICTURE_STATE_UPDATE = 8202,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_DELETE_FILES_PROGRESS = 8203,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_PHONE_INSERT = 8204,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_BT_DISCOVER_PERIPHERAL = 8205,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_BT_CONNECTED_TO_PERIPHERAL = 8206,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_BT_DISCONNECTED_PERIPHERAL = 8207,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_CURRENT_CAPTURE_STATUS = 8208,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_AUTHORIZATION_RESULT = 8209,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_TIMELAPSE_STATUS_UPDATE = 8210,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_SYNC_CAPTURE_MODE_UPDATE = 8211,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_SYNC_BUTTON_TRIGGER = 8212,
  INSTA360__MESSAGES__MESSAGE_CODE__CAMERA_NOTIFICATION_BT_REMOTE_VER_UPDATED = 8213,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_BEGIN = 12288,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_OLED_TEST = 12289,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_LED_TEST = 12290,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_SPEAKER_TEST = 12291,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_OLED_ROW_EVEN = 12292,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_OLED_ROW_UNEVEN = 12293,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_OLED_LINE_EVEN = 12294,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_OLED_LINE_UNEVEN = 12295,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_WIFI_STATUS_TEST = 12296,
  INSTA360__MESSAGES__MESSAGE_CODE__FACTORY_COMMAND_BLUETOOTH_STATUS_TEST = 12297
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(INSTA360__MESSAGES__MESSAGE_CODE)
} Insta360__Messages__MessageCode;

/* --- messages --- */

/* --- per-message closures --- */


/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    insta360__messages__message_code__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_message_5fcode_2eproto__INCLUDED */
