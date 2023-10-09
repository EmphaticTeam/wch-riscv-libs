#ifndef __TIMERBASIC__H__
#define __TIMERBASIC__H__

#include "Timer.hpp"

namespace ch32v_lib::timers
{
    class TimerBasic : public Timer
    {
    public:
        void Init(TIM_TypeDef* timer);
    private:

    };
}


#endif  //!__TIMERBASIC__H__