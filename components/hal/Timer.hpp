#ifndef __TIMER__H__
#define __TIMER__H__

#include "Common.h"

#define TIMER_ENTITIES_MAX  10

namespace ch32v_lib::timers
{
    typedef void (*SoftTimerCallback)();

    struct SoftTimer
    {
        u32 maxCount = 0;
        u32 counter = 0;
        bool isEnable = false;
        bool isEvent = false;
        SoftTimerCallback callback = nullptr;
    };

    class Timer
    {
    public:
        TIM_TypeDef* timer;
        virtual void Init(TIM_TypeDef* timer) = 0;
        ErrorStatus AddSoftTimer(SoftTimer softTimer);

        void Start()
        {
            timer->CTLR1 |= TIM_CEN;
        };

        void InterruptHandler();

    private:
        u8 _softTimersCount = 0;
        SoftTimer _softTimers[TIMER_ENTITIES_MAX];
    };
}

#endif  //!__TIMER__H__