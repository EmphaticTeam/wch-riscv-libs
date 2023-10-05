#ifndef __USART__H__
#define __USART__H__

#include "Common.hpp"

#define USART_TX_BUF_LEN    512
#define USART_RX_BUF_LEN    512

namespace ch32v_lib::interfaces
{
    typedef void (*UsartRxCallback)(u8* data, u32 len);

    class Usart
    {
    public:
        USART_TypeDef* instance = nullptr;
        u32 baudRate = 9600;

        void Init(USART_TypeDef *inst, u32 baudRate);
        void SetBaudrate(u32 baudrate);
        int SendMessage(const u8* msg, const u32 len);
        // void SendMessageIT(u8* msg, u32 len);
        // void SendMessageDMA(u8* msg, u32 len);

        void ReceiveIT(UsartRxCallback callback);
        void ReceiveStartContinuous(UsartRxCallback callback, u32 threshold);
        void ReceiveStopContinuous();

        void InterruptHandler();
    private:
        u8 _txBuffer[USART_TX_BUF_LEN];
        u8 _rxBuffer[USART_RX_BUF_LEN];

        ErrorStatus WaitFlag(u16 flag, FlagStatus expectState, u32 timeout);
    };
}

#endif  //!__USART__H__
