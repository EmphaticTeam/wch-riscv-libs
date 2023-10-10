///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
/// @file Usart.hpp
/// @author {authors}
/// @brief
/// @date 2023-10-05
///
/// Copyright (c) 2023
///

#ifndef __USART__H__
#define __USART__H__

#include "Common.h"

#define USART_TX_BUF_LEN 256
#define USART_RX_BUF_LEN 256

namespace ch32v_lib::interfaces
{
    class Usart;
    typedef void (*UsartRxCallback)(u8 *data, u32 len);

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief USART Communication Class
    ///
    /// This class provides functionality for USART (Universal Synchronous/Asynchronous Receiver/Transmitter) communication.
    ///
    class Usart
    {
    public:
        USART_TypeDef *instance = nullptr;
        UsartRxCallback rxCallback;

        void Init(USART_TypeDef *inst, u32 baudrate);
        void SetBaudrate(u32 baudrate);
        int SendMessage(const u8 *msg, const u32 len);
        // void SendMessageIT(u8* msg, u32 len);
        // void SendMessageDMA(u8* msg, u32 len);

        ErrorStatus ReceiveIT(u16 count);
        ErrorStatus ReceiveUntilIdle();
        void InterruptHandler();

    private:
        u8 _txBuffer[USART_TX_BUF_LEN];
        u8 _rxBuffer[USART_RX_BUF_LEN];
        u16 _currentCounter = 0;
        u16 _expectCounter = 0;
        bool _untilIdle = false;

        ErrorStatus WaitFlag(u16 flag, FlagStatus expectState, u32 timeout);
    };
}

#endif //!__USART__H__
