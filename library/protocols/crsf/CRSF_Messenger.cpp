#include "CRSF_Messenger.hpp"

#define CRSF_CRC_POLYNOM 0xd5

#define CRSF_FRAME_LEN_POS      1
#define CRSF_FRAME_ID_POS       2
#define CRSF_FRAME_DATA_POS     3
#define CRSF_FRAME_CRC_POS(x)   (x-1)

namespace ch32v_lib::protocols
{
    CRC8 CRSFMessenger::crc8;

    void CRSFMessenger::Init(interfaces::Usart *usart)
    {
        crc8.Init(CRSF_CRC_POLYNOM);
        this->usart = usart;
        this->usart->ReceiveUntilIdle();
    }

    void CRSFMessenger::UsartCallback(u8 *data, u32 len)
    {
        if(crc8.Check(&data[CRSF_FRAME_ID_POS], len-4, data[CRSF_FRAME_CRC_POS(len)]))
            messageCallback((CRSF_FrameId)data[CRSF_FRAME_ID_POS], &data[CRSF_FRAME_DATA_POS], len-2);

        this->usart->ReceiveUntilIdle();
    }

    s16 CRSFMessenger::Uint11ToInt16(u16 value)
    {
        return (s16)value - 1024;
    }
}
