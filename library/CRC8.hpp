///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
/// @file CRC8.hpp
/// @author {authors}
/// @brief 
/// @date 2023-10-09
/// 
/// Copyright (c) 2023
/// 

#ifndef __CRC8__H__
#define __CRC8__H__

#include "Common.h"

namespace ch32v_lib
{
    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief CRC8 Class
    /// 
    /// This class provides functionality for CRC-8 (Cyclic Redundancy Check) calculations.
    ///
    class CRC8
    {
    public:
        void Init(u8 polynomial);
        u8 Calculate(const u8 *data, u32 length);
        bool Check(const u8 *data, u32 length, u8 expected);

    private:
        u8 _polynomial;
        u8 _crcTable[256];
        void InitTable();
    };
}

#endif //!__CRC8__H__