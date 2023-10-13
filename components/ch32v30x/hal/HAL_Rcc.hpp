#ifndef __HAL_RCC__H__
#define __HAL_RCC__H__

#include "Common.h"

namespace ch32v_lib
{
    class Rcc
    {
    public:
        ALWAYS_INLINE static void EnableAHBPeriph(u32 bitMask)
        {
            SET_BIT(RCC->AHBPCENR, bitMask);
        }

        ALWAYS_INLINE static void DisableAHBPeriph(u32 bitMask)
        {
            CLEAR_BIT(RCC->AHBPCENR, bitMask);
        }

        ALWAYS_INLINE static void EnableAPB1Periph(u32 bitMask)
        {
            SET_BIT(RCC->APB1PCENR, bitMask);
        }

        ALWAYS_INLINE static void DisableAPB1Periph(u32 bitMask)
        {
            CLEAR_BIT(RCC->APB1PCENR, bitMask);
        }

        ALWAYS_INLINE static void EnableAPB2Periph(u32 bitMask)
        {
            SET_BIT(RCC->APB2PCENR, bitMask);
        }

        ALWAYS_INLINE static void DisableAPB2Periph(u32 bitMask)
        {
            CLEAR_BIT(RCC->APB2PCENR, bitMask);
        }

        static void Deinit()
        {
            SET_BIT(RCC->CTLR, RCC_HSION);
            CLEAR_BIT(RCC->CFGR0, 0xF8FF0000);
            CLEAR_BIT(RCC->CTLR, 0xFEF6FFFF);
            CLEAR_BIT(RCC->CTLR, 0xFFFBFFFF);
            CLEAR_BIT(RCC->CFGR0, 0xFF80FFFF);
            CLEAR_BIT(RCC->CTLR, 0xEBFFFFFF);
            WRITE_REG(RCC->INTR, 0x00FF0000);
            WRITE_REG(RCC->CFGR2, 0x00000000);
        }

        static void EnableHSE()
        {
            CLEAR_BIT(RCC->CTLR, RCC_HSEON | RCC_HSEBYP);
            SET_BIT(RCC->CTLR, RCC_HSEON);
        }

        static void DisableHSE()
        {
            CLEAR_BIT(RCC->CTLR, RCC_HSEON | RCC_HSEBYP);
        }

        static void EnableBypassHSE()
        {
            SET_BIT(RCC->CTLR, RCC_HSEON | RCC_HSEBYP);
        }

        static void Prediv1Config(u32 source, u32 div)
        {

        }
    private:
    };
}

#endif //!__HAL_RCC__H__