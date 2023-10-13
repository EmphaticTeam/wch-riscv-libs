///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
/// @file Gpio.cpp
/// @author {authors}
/// @brief 
/// @date 2023-10-05
/// 
/// Copyright (c) 2023
/// 

#include "HAL_Gpio.hpp"

namespace ch32v_lib
{
    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Initializes one pin of the microcontroller
    /// 
    /// This function initializes a GPIO pin.
    ///
    /// @param port The GPIO port to which the pin belongs.
    /// @param pinNbr The number of the pin to initialize.
    /// @param direction The GPIO mode (GpioMode) for the pin (e.g., GpioMode::Input).
    /// @param config The GPIO configuration for the pin.
    ///
    void Gpio::PinInit(GPIO_TypeDef* port, u8 pinNbr, GpioMode direction, GpioConfig config)
    {
        u32* pCfgReg = 0;
        u32 cfgReg = 0;
        u8 pinShift = 0;

        if(pinNbr <= 7)
        {
            pCfgReg = (u32*)&port->CFGLR;
            pinShift = pinNbr * 4;
        }
        else if(pinNbr <= 15)
        {
            pCfgReg = (u32*)&port->CFGHR;
            pinShift = (pinNbr % 16) * 4;
        }

        cfgReg = *pCfgReg;
        cfgReg &= ~(0xf << pinShift);
        cfgReg |= (direction << pinShift) | ((0xf & config) << (pinShift+2));
        *pCfgReg = cfgReg;

        if(direction == GpioMode::Input)
        {
            u32 outdr = port->OUTDR;
            outdr &= ~(0x1 << pinNbr);
            outdr |= (config & 0xf0) ? (0x1 << pinNbr) : 0x0;
            port->OUTDR = outdr;
        }
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Set the specified GPIO pin HIGH.
    /// 
    /// @param[port] The GPIO port.
    /// @param[pinNbr] The pin number.
    ///
    void Gpio::PinSet(GPIO_TypeDef *port, u8 pinNbr)
    {
        port->BSHR = (1 << pinNbr);
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Reset the specified GPIO pin LOW.
    /// 
    /// @param[port] The GPIO port.
    /// @param[pinNbr] The pin number.
    ///
    void Gpio::PinReset(GPIO_TypeDef *port, u8 pinNbr)
    {
        port->BSHR = (1 << (16 + pinNbr));
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Write a state (HIGH or LOW) to the specified GPIO pin.
    /// 
    /// @param[port] The GPIO port.
    /// @param[pinNbr] The pin number.
    /// @param[state]
    ///
    void Gpio::PinWrite(GPIO_TypeDef *port, u8 pinNbr, FunctionalState state)
    {
        if(state) port->BSHR = (1 << pinNbr);
        else port->BSHR = (1 << (16 + pinNbr));
    }
}
