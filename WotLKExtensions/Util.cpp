#include "Util.h"

void Util::SetByteAtAddress(void* address, uint8_t byte)
{
	DWORD flOldProtect;
	VirtualProtect(address, 0x1, PAGE_EXECUTE_READWRITE, &flOldProtect);
	memset(address, byte, 0x1);
	VirtualProtect(address, 0x1, flOldProtect, &flOldProtect);
}

void Util::OverwriteBytesAtAddress(void* address, uint8_t byte, size_t numRepeats)
{
	DWORD flOldProtect;
	VirtualProtect(address, numRepeats, PAGE_EXECUTE_READWRITE, &flOldProtect);
	memset(address, byte, numRepeats);
	VirtualProtect(address, numRepeats, flOldProtect, &flOldProtect);
}

void Util::OverwriteBytesAtAddress(uint32_t address, uint8_t byteArray[], size_t arraySize)
{
	void* vAddress = (void*)address;
	for (size_t i = 0; i < arraySize; i++)
		SetByteAtAddress((void*)(address + i), byteArray[i]);
}

void Util::OverwriteUInt32AtAddress(uint32_t address, uint32_t newVal)
{
	DWORD flOldProtect;
	void* vAddress = (void*)address;
	VirtualProtect(vAddress, sizeof(uint32_t), PAGE_EXECUTE_READWRITE, &flOldProtect);
	*(uint32_t*)address = newVal;
	VirtualProtect(vAddress, sizeof(uint32_t), flOldProtect, &flOldProtect);
}
