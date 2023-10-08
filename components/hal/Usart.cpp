///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
/// @file Usart.cpp
/// @author {authors}
/// @brief 
/// @date 2023-10-05
/// 
/// Copyright (c) 2023
/// 

#include "Usart.hpp"

#define TX_TIMEOUT  10000

namespace ch32v_lib::interfaces
{
    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief 
    /// 
    /// @param[inst]
    /// @param[baudRate]
    ///
    void Usart::Init(USART_TypeDef *inst, u32 baudrate)
    {
        instance = inst;
        // instance->CTLR1 &= ~USART_CTLR1_UE;
        instance->CTLR1 |= USART_CTLR1_UE;
        instance->CTLR1 |= USART_CTLR1_RE | USART_CTLR1_TE | USART_CTLR1_RXNEIE;
        instance->CTLR3 |= USART_CTLR3_EIE;
        SetBaudrate(baudrate);
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief 
    /// 
    /// @param[baudrate]
    ///
    void Usart::SetBaudrate(u32 baudrate)
    {
        u32 freq = SystemCoreClock / 16;
        u32 mantisa = (freq / baudrate) & 0xfff;
        u32 fraction = ((freq % baudrate) / (baudrate / 16)) & 0xf;
        instance->BRR = (mantisa << 4) | fraction;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief 
    /// 
    /// @param[msg]
    /// @param[len]
    /// @return int 
    ///
    int Usart::SendMessage(const u8 *msg, const u32 len)
    {
        u32 i = 0;
        for(; i < len; i++)
        {
            if(WaitFlag(USART_STATR_TXE, SET, TX_TIMEOUT) != READY) return i;
            instance->DATAR = msg[i];
        }
        return i;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief 
    /// 
    /// @param[count]
    /// @return ErrorStatus 
    ///
    ErrorStatus Usart::ReceiveIT(u16 count)
    {
        if(count > USART_RX_BUF_LEN) return NoREADY;
        _currentCounter = 0;
        _expectCounter = count;
        return READY;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief 
    /// 
    ///
    void Usart::InterruptHandler()
    {
        if((instance->STATR & USART_STATR_RXNE) != 0)
        {
            _rxBuffer[_currentCounter++] = (uint16_t)(instance->DATAR & (uint16_t)0x01FF);
            if((_currentCounter == _expectCounter) && rxCallback) 
            {
                rxCallback(this, _rxBuffer, _currentCounter);
                _currentCounter++;
            }
        }
        instance->STATR = 0;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief 
    /// 
    /// @param[flag]
    /// @param[expectState]
    /// @param[timeout]
    /// @return ErrorStatus 
    ///
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
            return READY;
        else 
            return NoREADY;
    }
}
