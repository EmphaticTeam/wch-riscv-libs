#include "Common.h"

extern "C" void __cxa_pure_virtual() 
{
    NVIC_SetPendingIRQ(HardFault_IRQn);
}
