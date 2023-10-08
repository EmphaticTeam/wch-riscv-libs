#include "Usart.hpp"

#define TX_TIMEOUT  10000

namespace ch32v_lib::interfaces
{
    void Usart::Init(USART_TypeDef *inst, u32 baudRate)
    {
        instance = inst;
        instance->CTLR1 = USART_CTLR1_UE | USART_CTLR1_TE | USART_CTLR1_RE;

        SetBaudrate(baudRate);
    }

    void Usart::SetBaudrate(u32 baudrate)
    {
        u32 freq = SystemCoreClock / 16;
        u32 mantisa = (freq / baudrate) & 0xfff;
        u32 fraction = ((freq % baudrate) / (baudrate / 16)) & 0xf;
        instance->BRR = (mantisa << 4) | fraction;
    }

    int Usart::SendMessage(const u8 *msg, const u32 len)
    {
        u32 i = 0;
        for(; i < len; i++)
        {
            if(WaitFlag(USART_STATR_TXE, SET, TX_TIMEOUT) != SUCCESS) return i;
            instance->DATAR = msg[i];
        }
        return i;
    }

    /**
     * @brief 
     * 
     */
    void Usart::InterruptHandler()
    {

    }

    ErrorStatus Usart::WaitFlag(u16 flag, FlagStatus expectState, u32 timeout)
    {
        __IO uint32_t _counter = 0;
        FlagStatus flagStatus = RESET;
        
        do
        {
            flagStatus = ((instance->STATR & flag) != 0) ? SET : RESET;
            _counter++;  
        } while((_counter < timeout) && (flagStatus != expectState));
        
        if (flagStatus == expectState) 
            return SUCCESS;
        else 
            return ERROR;
    }
}
