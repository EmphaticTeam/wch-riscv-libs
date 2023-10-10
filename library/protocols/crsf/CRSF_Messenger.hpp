#ifndef __CRSF_MESSENGER__H__
#define __CRSF_MESSENGER__H__

#include "Common.h"
#include "CRSF.h"
#include "Usart.hpp"
#include "CRC8.hpp"

namespace ch32v_lib::protocols
{
    typedef void (*CRSF_Callback)(CRSF_FrameId frameId, u8 *data, u8 len);

    class CRSFMessenger
    {
    public:
        interfaces::Usart *usart;
        CRSF_Callback messageCallback;

        void Init(interfaces::Usart *usart);
        void UsartCallback(u8 *data, u32 len);

        static s16 Uint11ToInt16(u16 value)
        {
            return (s16)value - 1024;
        }

    private:
        u16 _counterChars;
        u32 _timeCounterUs;
        static CRC8 crc8;
    };
}

#endif //!__CRSF_MESSENGER__H__