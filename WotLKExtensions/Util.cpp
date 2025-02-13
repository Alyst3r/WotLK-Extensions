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
	void* vAddress = reinterpret_cast<void*>(address);
	DWORD flOldProtect;
	VirtualProtect(vAddress, sizeof(byteArray), PAGE_EXECUTE_READWRITE, &flOldProtect);
	for (size_t i = 0; i < sizeof(byteArray); i++)
		SetByteAtAddress(reinterpret_cast<void*>(address + i), byteArray[i]);
	VirtualProtect(vAddress, sizeof(byteArray), flOldProtect, &flOldProtect);
}

void Util::OverwriteUInt32AtAddress(uint32_t address, uint32_t newVal)
{
	DWORD flOldProtect;
	void* vAddress = reinterpret_cast<void*>(address);
	VirtualProtect(vAddress, sizeof(uint32_t), PAGE_EXECUTE_READWRITE, &flOldProtect);
	*reinterpret_cast<uint32_t*>(address) = newVal;
	VirtualProtect(vAddress, sizeof(uint32_t), flOldProtect, &flOldProtect);
}
