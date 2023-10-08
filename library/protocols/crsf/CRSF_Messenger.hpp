#ifndef __CRSF_MESSENGER__H__
#define __CRSF_MESSENGER__H__

#include "Common.h"
#include "Usart.hpp"
#include "CRSF.h"

namespace ch32v_lib::protocols
{

    typedef void (*CRSF_Callback)(CRSF_FrameId frameId, u8 *data, u8 len);

    class CRSFMessenger
    {
    public:
        interfaces::Usart* usart;
        CRSF_Callback messageCallback;

        void Init(interfaces::Usart *usart);
        // void Init(USART_TypeDef *usart);

        // static void UsartRxCallbackWrapper(CRSFMessenger* object, u8* data, u32 len)
        // {
        //     object->UsartRxCallback(&object->usart, data, len);
        // }
        void UsartCallback(interfaces::Usart *object, u8 *data, u32 len);

    private:
        u16 _counterChars;
        u32 _timeCounterUs;
        CRSF_Frame _header = {
            .frameId = CRSF_FrameId::None};

    };
}

#endif //!__CRSF_MESSENGER__H__