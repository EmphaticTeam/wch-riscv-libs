///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
/// @file Usart.cpp
/// @author {authors}
/// @brief
/// @date 2023-10-05
///
/// Copyright (c) 2023
///

#include "Usart.hpp"

#define TX_TIMEOUT 10000

namespace ch32v_lib::interfaces
{
    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief USART Initialization
    ///
    /// Initializes the USART instance with the specified parameters.
    ///
    /// @param[inst] Pointer to the USART peripheral instance.
    /// @param[baudRate] The baud rate for USART communication.
    ///
    void Usart::Init(USART_TypeDef *inst, u32 baudrate)
    {
        instance = inst;
        instance->CTLR1 |= USART_CTLR1_UE;
        instance->CTLR1 |= USART_CTLR1_RE | USART_CTLR1_TE | USART_CTLR1_RXNEIE | USART_CTLR1_IDLEIE;
        instance->CTLR3 |= USART_CTLR3_EIE;
        SetBaudrate(baudrate);
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Set USART Baudrate
    ///
    /// Sets the baud rate for USART communication.
    ///
    /// @param[baudrate] The desired baud rate.
    ///
    void Usart::SetBaudrate(u32 baudrate)
    {
        u32 freq = SystemCoreClock / 16;
        u32 mantisa = (freq / baudrate) & 0xfff;
        u32 fraction = ((freq % baudrate) / (baudrate / 16)) & 0xf;
        instance->BRR = (mantisa << 4) | fraction;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Send Message via USART
    ///
    /// Sends a message through USART with the specified length.
    ///
    /// @param[msg] Pointer to the message buffer.
    /// @param[len] Length of the message.
    /// @return int The number of bytes sent.
    ///
    int Usart::SendMessage(const u8 *msg, const u32 len)
    {
        u32 i = 0;
        for (; i < len; i++)
        {
            if (WaitFlag(USART_STATR_TXE, SET, TX_TIMEOUT) != READY)
                return i;
            instance->DATAR = msg[i];
        }
        return i;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Receive Data with Interrupts
    ///
    /// Prepares to receive a specified number of bytes via USART interrupts.
    ///
    /// @param[count] The expected number of bytes to receive.
    /// @return ErrorStatus READY if the operation can be performed, NoREADY otherwise.
    ///
    ErrorStatus Usart::ReceiveIT(u16 count)
    {
        if (count > USART_RX_BUF_LEN)
            return NoREADY;
        _expectCounter = count;
        return READY;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Receive Data Until Idle
    ///
    /// Prepares to receive data until the USART line goes idle.
    ///
    /// @return ErrorStatus READY if the operation can be performed, NoREADY otherwise.
    ///
    ErrorStatus Usart::ReceiveUntilIdle()
    {
        _currentCounter = 0;
        _untilIdle = true;
        return READY;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief USART Interrupt Handler
    ///
    /// Handles USART interrupts and processes received data.
    ///
    void Usart::InterruptHandler()
    {
        u32 len = 0;

        if (READ_BIT(instance->STATR, USART_STATR_RXNE) != 0)
        {
            _rxBuffer[_currentCounter] = (u16)(instance->DATAR & (u16)0x01FF);
            _currentCounter++;

            if (_currentCounter >= USART_RX_BUF_LEN || (!_untilIdle && (_currentCounter == _expectCounter)))
            {
                len = _currentCounter;
                _currentCounter = 0;
                if (rxCallback != 0)
                    rxCallback(_rxBuffer, len);
            }
        }
        else if (READ_BIT(instance->STATR, USART_STATR_IDLE) != 0)
        {
            _rxBuffer[_currentCounter] = (u16)(instance->DATAR & (u16)0x01FF);
            _currentCounter++;

            if (_untilIdle)
            {
                len = _currentCounter;
                _currentCounter = 0;
                _untilIdle = false;
                if (rxCallback != 0)
                    rxCallback(_rxBuffer, len);
            }
        }
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Wait for USART Flag
    ///
    /// Waits for a specific USART flag to reach the expected state with a timeout.
    ///
    /// @param[flag] The USART flag to check.
    /// @param[expectState] The expected state of the flag (SET or RESET).
    /// @param[timeout] The timeout in number of iterations.
    /// @return ErrorStatus READY if the flag reaches the expected state, NoREADY otherwise.
    ///
    ErrorStatus Usart::WaitFlag(u16 flag, FlagStatus expectState, u32 timeout)
    {
        __IO u32 _counter = 0;
        FlagStatus flagStatus = RESET;

        do
        {
            flagStatus = ((instance->STATR & flag) != 0) ? SET : RESET;
            _counter++;
        } while ((_counter < timeout) && (flagStatus != expectState));

        if (flagStatus == expectState)
            return READY;
        else
            return NoREADY;
    }
}
