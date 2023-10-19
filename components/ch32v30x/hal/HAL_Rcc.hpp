#ifndef __HAL_RCC__H__
#define __HAL_RCC__H__

#include "Common.h"

#define RCC_PREDIV1_SRC_HSE             ((u32)0x00000000)
#define RCC_PREDIV1_SRC_PLL2            ((u32)0x00000001)

#define RCC_PREDIV1_DIV1                ((u32)0x00000000)
#define RCC_PREDIV1_DIV2                ((u32)0x00000001)
#define RCC_PREDIV1_DIV3                ((u32)0x00000002)
#define RCC_PREDIV1_DIV4                ((u32)0x00000003)
#define RCC_PREDIV1_DIV5                ((u32)0x00000004)
#define RCC_PREDIV1_DIV6                ((u32)0x00000005)
#define RCC_PREDIV1_DIV7                ((u32)0x00000006)
#define RCC_PREDIV1_DIV8                ((u32)0x00000007)
#define RCC_PREDIV1_DIV9                ((u32)0x00000008)
#define RCC_PREDIV1_DIV10               ((u32)0x00000009)
#define RCC_PREDIV1_DIV11               ((u32)0x0000000A)
#define RCC_PREDIV1_DIV12               ((u32)0x0000000B)
#define RCC_PREDIV1_DIV13               ((u32)0x0000000C)
#define RCC_PREDIV1_DIV14               ((u32)0x0000000D)
#define RCC_PREDIV1_DIV15               ((u32)0x0000000E)
#define RCC_PREDIV1_DIV16               ((u32)0x0000000F)

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

        ALWAYS_INLINE static void EnableHSE()
        {
            SET_BIT(RCC->CTLR, RCC_HSEON);
        }

        ALWAYS_INLINE static void DisableHSE()
        {
            CLEAR_BIT(RCC->CTLR, RCC_HSEON);
        }

        ALWAYS_INLINE static void EnableBypassHSE()
        {
            SET_BIT(RCC->CTLR, RCC_HSEBYP);
        }

        ALWAYS_INLINE static void DisableBypassHSE()
        {
            SET_BIT(RCC->CTLR, RCC_HSEBYP);
        }

        ALWAYS_INLINE static void Prediv1Config(u32 source, u32 div)
        {

        }
    private:
    };
}

#endif //!__HAL_RCC__H__