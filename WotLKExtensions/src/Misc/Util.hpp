#pragma once

#include <Misc/Macros.hpp>

#include <Windows.h>
#include <functional>

class Util
{
public:
    static void SetByteAtAddress(void* address, uint8_t byte);
    static void OverwriteBytesAtAddress(uint32_t address, uint8_t byteArray[], size_t arraySize);
    static void OverwriteBytesAtAddress(void* address, uint8_t byte, size_t numRepeats);
    static void OverwriteUInt32AtAddress(uint32_t address, uint32_t newVal);

    static void PercToScreenPos(float x, float y, float* resX, float* resY);
};
