#ifndef __CRSF__H__
#define __CRSF__H__

enum CRSF_Address : u8
{
    BROADCAST_ADDRESS = 0x00,
    RADIO_ADDRESS = 0xEA,
    MODULE_ADDRESS =  0xEE,
};

enum CRSF_FrameId : u8
{
    None = 0x0,
    GPS_ID = 0x02,
    CF_VARIO_ID = 0x07,
    BATTERY_ID = 0x08,
    LINK_ID = 0x14,
    CHANNELS_ID = 0x16,
    ATTITUDE_ID = 0x1E,
    FLIGHT_MODE_ID = 0x21,
    PING_DEVICES_ID = 0x28,
    DEVICE_INFO_ID = 0x29,
    REQUEST_SETTINGS_ID = 0x2A,
};

typedef struct
{
    u8 deviceAddress;
    u8 length;
    CRSF_FrameId frameId;
} CRSF_Frame;


typedef struct
{
    u16 ch0 : 11;
    u16 ch1 : 11;
    u16 ch2 : 11;
    u16 ch3 : 11;
    u16 ch4 : 11;
    u16 ch5 : 11;
    u16 ch6 : 11;
    u16 ch7 : 11;
    u16 ch8 : 11;
    u16 ch9 : 11;
    u16 ch10 : 11;
    u16 ch11 : 11;
    u16 ch12 : 11;
    u16 ch13 : 11;
    u16 ch14 : 11;
    u16 ch15 : 11;
} CRSF_ChannelsFrame;

#endif  //!__CRSF__H__