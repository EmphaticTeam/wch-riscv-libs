///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
/// @file Gpio.hpp
/// @author {authors}
/// @brief 
/// @date 2023-10-05
/// 
/// Copyright (c) 2023
/// 

#ifndef __GPIO__H__
#define __GPIO__H__

#include "Common.h"

namespace ch32v_lib
{
    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Enumerating gpio modes
    /// 
    enum GpioMode : u32
    {
        Input = 0,          ///< Input mode
        Output_10MHz = 1,   ///< Output 10MHz mode 
        Output_2MHz = 2,    ///< Output 2MHz mode
        Output_50MHz = 3    ///< Output 50MHz mode
    };

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Enumerating gpio purpose
    /// 
    enum GpioConfig : u32
    {
        In_Analog = 0x0,            ///< Input analog purpose
        In_Floating = 0x1,          ///< Input floating purpose
        In_PullDown = 0x02,         ///< Input pull-down purpose
        In_PullUp = 0x12,           ///< Input pull-up purpose
        Output_PushPull = 0x0,      ///< Output push-pull purpose
        Output_OpenDrain = 0x1,     ///< Output open-drain purpose
        Alternate_PushPull = 0x2,   ///< Alternative push-pull purpose
        Alternate_OpenDrain = 0x3   ///< Alternative open-drain purpose
    };

    class Gpio
    {
    public:
        static void PinInit(GPIO_TypeDef* port, u8 pinNbr, GpioMode direction, GpioConfig config);
        static void PinSet(GPIO_TypeDef* port, u8 pinNbr);
        static void PinReset(GPIO_TypeDef* port, u8 pinNbr);
        static void PinWrite(GPIO_TypeDef* port, u8 pinNbr, FunctionalState state);
    };
}

#endif  //!__GPIO__H__
