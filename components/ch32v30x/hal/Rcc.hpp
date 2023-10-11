#ifndef __RCC__H__
#define __RCC__H__

#include "Common.h"

namespace ch32v_lib
{
    struct PeripheralID {
        u32* rccRegister;  // Регистр в RCC для управления тактированием (например, RCC->APB1ENR)
        u32 bitMask;      // Битовая маска для включения/отключения тактирования конкретного модуля
    };



    class Rcc
    {
    public:
        static const PeripheralID PORTA;
        static const PeripheralID PORTB;
        static const PeripheralID PORTC;
        static const PeripheralID PORTD;
        static const PeripheralID ALTFUNC;

        static void Enable(PeripheralID periph)
        {
            SET_BIT(*periph.rccRegister, periph.bitMask);
        }

        static void Disable(PeripheralID periph)
        {
            CLEAR_BIT(*periph.rccRegister, periph.bitMask);
        }

    private:
    };
}

#endif //!__RCC__H__