#include "HAL_TimerGeneral.hpp"

namespace ch32v_lib::timers
{
    void TimerGeneral::OutputConfigure(u8 ch, ChMode mode, State preload, State fast)
    {
        u16* reg;
        u16 shift = ((ch-1) % 2) * 8;

        if(ch == 1 || ch == 2)
            reg = (u16*)&timer->CHCTLR1;
        else if(ch == 3 || ch == 4)
            reg = (u16*)&timer->CHCTLR1;
        else return;

        auto temp = *reg;
        temp &= ~(0xFF << shift);
        temp |= ((u16)mode << 4) | ((u16)preload << 3) | ((u16)fast << 2);
        *reg = temp;
    }

    void TimerGeneral::OutputState(u8 ch, State state)
    {
        if(ch < 1 || ch > 4) return;
        u16 shift = (ch-1) * 4;

        auto temp = timer->CCER;
        temp &= ~(0x1 << shift);
        temp |= ((u16)state << shift);
        timer->CCER = temp;
    }

    void TimerGeneral::CompareSet(u8 ch, u16 value)
    {
        if(ch < 1 || ch > 4) return;
        ((u32*)&timer->CH1CVR)[ch-1] = value;
    }
}
