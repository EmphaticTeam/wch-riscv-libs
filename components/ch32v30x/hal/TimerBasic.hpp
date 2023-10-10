#ifndef __TIMERBASIC__H__
#define __TIMERBASIC__H__

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

        void EventClear()
        {
            isEvent = false;
        }
    };

    class TimerBasic
    {
    public:
        TIM_TypeDef* timer;

        void Init(TIM_TypeDef* tim, u32 prescaler, u32 autoreload);
        void InterruptHandler();
        ErrorStatus AddSoftTimer(SoftTimer* softTimer);

        void Start() const
        {
            timer->CTLR1 |= TIM_CEN;
        };

        void Stop() const
        {
            timer->CTLR1 &= ~TIM_CEN;
        };

        void SetSingleShotMode(FunctionalState state) const
        {
            if(state == ENABLE) timer->CTLR1 |= TIM_OPM;
            else timer->CTLR1 &= ~TIM_OPM;
        }

    private:
        u8 _softTimersCount = 0;
        SoftTimer* _softTimers[TIMER_ENTITIES_MAX];
    };
}

#endif  //!__TIMERBASIC__H__