#include "Common.h"
#include "Gpio.hpp"
#include "TimerBasic.hpp"

using namespace ch32v_lib;
using namespace ch32v_lib::timers;

TimerBasic mainTimer;

extern "C" __attribute__((interrupt()))
void TIM6_IRQHandler()
{
    mainTimer.InterruptHandler();
}

void SoftTimer3Callback()
{
    GPIOC->OUTDR ^= (1 << 1);
}

SoftTimer softTimer1 = 
{
    .maxCount = 1000,
    .isEnable = true,
};

SoftTimer softTimer2 = 
{
    .maxCount = 500,
    .isEnable = true,
};

SoftTimer softTimer3 = 
{
    .maxCount = 250,
    .isEnable = true,
    .callback = SoftTimer3Callback
};

extern "C" int main()
{
    RCC->APB2PCENR |= RCC_IOPAEN | RCC_IOPCEN | RCC_AFIOEN;
    Gpio::PinInit(GPIOA, 15, GpioMode::Output_10MHz, GpioConfig::Output_PushPull);
    Gpio::PinInit(GPIOC, 0, GpioMode::Output_10MHz, GpioConfig::Output_PushPull);
    Gpio::PinInit(GPIOC, 1, GpioMode::Output_10MHz, GpioConfig::Output_PushPull);
    Gpio::PinReset(GPIOA, 15);
    Gpio::PinReset(GPIOC, 0);
    Gpio::PinReset(GPIOC, 1);

    RCC->APB1PCENR |= 0x10; // TIM6
    NVIC_EnableIRQ(TIM6_IRQn);
    mainTimer.Init(TIM6, 999, 71);
    mainTimer.AddSoftTimer(&softTimer1);
    mainTimer.AddSoftTimer(&softTimer2);
    mainTimer.AddSoftTimer(&softTimer3);
    mainTimer.Start();

    while (1)
    {
        if (softTimer1.isEvent)
        {
            GPIOA->OUTDR ^= (1 << 15);
            softTimer1.isEvent = false;
        }

        if (softTimer2.isEvent)
        {
            GPIOC->OUTDR ^= (1 << 0);
            softTimer2.EventClear();
        }
    }
}
