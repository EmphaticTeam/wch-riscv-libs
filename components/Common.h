///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
/// @file Common.hpp
/// @author {authors}
/// @brief 
/// @date 2023-10-05
/// 
/// Copyright (c) 2023
/// 

#ifndef __COMMON__H__
#define __COMMON__H__

// TODO Select header of mcu
#include "ch32v30x.h"

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define UNUSED(x)   ((void)x)

#endif  //!__COMMON__H__