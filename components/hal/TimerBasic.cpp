#include "TimerBasic.hpp"

namespace ch32v_lib::timers
{
    void TimerBasic::Init(TIM_TypeDef* tim)
    {
        timer = tim;
    }
}
