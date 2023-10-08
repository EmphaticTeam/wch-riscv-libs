#include "CRSF_Messenger.hpp"
#include <memory.h>
#include <functional>

namespace ch32v_lib::protocols
{
    void CRSFMessenger::Init(interfaces::Usart *usart)
    {
        this->usart = usart;
        // this->usart->rxCallback = test.TestCallback;
        this->usart->ReceiveIT(3);
    }

    void CRSFMessenger::UsartCallback(interfaces::Usart* object, u8 *data, u32 len)
    {
        if (READ_BIT(usart->instance->STATR, USART_STATR_RXNE))
        {
            if(_counterChars == 0 && len == 3)
            {
                // Start timeout timer
                
                memcpy(&_header, data, len);
                this->usart->ReceiveIT(_header.length);
            }
            else if (_header.frameId != 0)
            {
                messageCallback(_header.frameId, data, len);
                _header.frameId = CRSF_FrameId::None;
                this->usart->ReceiveIT(3);
            }
        }
    }
}
