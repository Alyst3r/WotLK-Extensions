#pragma once

#include "Macros.h"

#include <Windows.h>
#include <functional>

class Util
{
public:
	static void SetByteAtAddress(void* address, uint8_t byte);
	static void OverwriteBytesAtAddress(uint32_t address, uint8_t byteArray[], size_t arraySize);
	static void OverwriteBytesAtAddress(void* address, uint8_t byte, size_t numRepeats);
	static void OverwriteUInt32AtAddress(uint32_t address, uint32_t newVal);
};
