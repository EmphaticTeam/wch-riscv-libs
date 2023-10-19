#ifndef __HAL_TIMERGENERAL__H__
#define __HAL_TIMERGENERAL__H__

#include "Common.h"
#include "HAL_TimerBasic.hpp"

namespace ch32v_lib::timers
{
    enum class ChMode : u8
    {
        Frozen = 0x0,
        Active = 0x1,
        Inactive = 0x2,
        Overturn = 0x3,
        ActiveForce = 0x4,
        InactiveForce = 0x5,
        PWM1 = 0x6,
        PWM2 = 0x7
    };

    enum class State : u8
    {
        Disable = 0x0,
        Enable = 0x1
    };

    class TimerGeneral : public TimerBasic
    {
    public:
        void OutputConfigure(u8 ch, ChMode mode, State preload, State fast);
        void OutputState(u8 ch, State state);
        void CompareSet(u8 ch, u16 value);
    private:

    };
}

#endif  //!__HAL_TIMERGENERAL__H__