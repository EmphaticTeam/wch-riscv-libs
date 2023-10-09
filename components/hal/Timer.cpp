#include "Timer.hpp"

namespace ch32v_lib::timers
{
    ErrorStatus Timer::AddSoftTimer(SoftTimer softTimer)
    {
        if(_softTimersCount >= TIMER_ENTITIES_MAX) return NoREADY;
        _softTimers[_softTimersCount] = softTimer;
        _softTimersCount++;
        return READY;
    }

    void Timer::InterruptHandler()
    {
        for(int i = 0; i < _softTimersCount; i++)
        {
            auto ent = &_softTimers[i];
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
    }
}