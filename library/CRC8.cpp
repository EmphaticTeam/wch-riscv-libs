///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
/// @file CRC8.cpp
/// @author {authors}
/// @brief
/// @date 2023-10-09
///
/// Copyright (c) 2023
///

#include "CRC8.hpp"

namespace ch32v_lib
{
    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief CRC8 Class
    ///
    /// This class provides functionality for CRC-8 (Cyclic Redundancy Check) calculations.
    ///
    /// @param[polynomial] The polynomial used for CRC calculation.
    ///
    void CRC8::Init(u8 polynomial)
    {
        _polynomial = polynomial;
        InitTable();
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Calculate CRC8
    ///
    /// Calculates the CRC-8 checksum for the given data with the specified length.
    ///
    /// @param[data] Pointer to the input data buffer.
    /// @param[length] Length of the input data.
    /// @return u8 The calculated CRC-8 checksum.
    ///
    u8 CRC8::Calculate(const u8 *data, u32 length)
    {
        u8 crc = 0;
        for (u32 i = 0; i < length; ++i)
            crc = _crcTable[(crc ^ data[i]) & 0xFF];
        return crc;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Check CRC8
    ///
    /// Checks if the calculated CRC-8 checksum for the given data matches the expected value.
    ///
    /// @param[data] Pointer to the input data buffer.
    /// @param[length] Length of the input data.
    /// @param[expected] The expected CRC-8 checksum value.
    /// @return true if the calculated CRC-8 matches the expected value, false otherwise.
    ///
    bool CRC8::Check(const u8 *data, u32 length, u8 expected)
    {
        u8 crc = 0;
        for (u32 i = 0; i < length; ++i)
            crc = _crcTable[(crc ^ data[i]) & 0xFF];

        return expected == crc;
    }

    ///=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=///
    /// @brief Initialize CRC8 Lookup Table
    ///
    /// Initializes the CRC-8 lookup table based on the provided polynomial.
    ///
    void CRC8::InitTable()
    {
        for (int i = 0; i < 256; ++i)
        {
            u8 crc = i;
            for (int j = 0; j < 8; ++j)
            {
                if (crc & 0x80)
                    crc = (crc << 1) ^ _polynomial;
                else
                    crc <<= 1;
            }
            _crcTable[i] = crc;
        }
    }
}
