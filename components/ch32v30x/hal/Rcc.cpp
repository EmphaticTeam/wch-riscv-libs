#include "Rcc.hpp"

namespace ch32v_lib
{
    const PeripheralID Rcc::PORTA = {(u32*)&(RCC->APB2PCENR), RCC_IOPAEN};
    const PeripheralID Rcc::PORTB = {(u32*)&(RCC->APB2PCENR), RCC_IOPBEN};
    const PeripheralID Rcc::PORTC = {(u32*)&(RCC->APB2PCENR), RCC_IOPCEN};
    const PeripheralID Rcc::PORTD = {(u32*)&(RCC->APB2PCENR), RCC_IOPDEN};
    const PeripheralID Rcc::ALTFUNC = {(u32*)&(RCC->APB2PCENR), RCC_AFIOEN};




}
