#pragma once

#include <Windows.h>
#include <functional>

class Functions
{
public:
	static void SetByteAtAddress(void* address, uint8_t byte);
	static void OverwriteBytesAtAddress(void* address, uint8_t byte, size_t numRepeats);
};
