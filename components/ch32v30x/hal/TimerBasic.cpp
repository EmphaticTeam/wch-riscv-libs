#include "TimerBasic.hpp"

namespace ch32v_lib::timers
{
    void TimerBasic::Init(TIM_TypeDef* tim, u32 prescaler, u32 autoreload)
    {
        timer = tim;
        timer->PSC = prescaler;
        timer->ATRLR = autoreload;
        timer->DMAINTENR |= TIM_UIE;
    }

    ErrorStatus TimerBasic::AddSoftTimer(SoftTimer* softTimer)
    {
        if(_softTimersCount >= TIMER_ENTITIES_MAX) return NoREADY;
        _softTimers[_softTimersCount] = softTimer;
        _softTimersCount++;
        return READY;
    }

    void TimerBasic::InterruptHandler()
    {
        if(READ_BIT(timer->INTFR, TIM_UIF) != 0)
        {
            for(int i = 0; i < _softTimersCount; i++)
            {
                auto ent = _softTimers[i];
                if(ent->isEnable)
                {
                    ent->counter++;
                    if(ent->counter >= ent->maxCount)
                    {
                        ent->counter = 0;
                        ent->isEvent = true;
                        if(ent->callback != 0) ent->callback();
                    }
                }
            }
            CLEAR_BIT(timer->INTFR, TIM_UIF);
        }
    }
}
