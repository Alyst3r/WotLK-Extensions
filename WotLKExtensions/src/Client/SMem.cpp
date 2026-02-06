#include <Client/SMem.hpp>

void* SMem::Alloc(uint32_t size, const char* filepath, uint32_t flags /*most likely*/, uint32_t smth)
{
	return reinterpret_cast<void* (__stdcall*)(uint32_t, const char*, uint32_t, uint32_t)>(0x76E540)(size, filepath, flags, smth);
}

bool SMem::Free(void* memory, const char* func /*dunno*/, uint32_t flags /*most likely*/, uint32_t smth)
{
	return reinterpret_cast<bool (__stdcall*)(void*, const char*, uint32_t, uint32_t)>(0x76E5A0)(memory, func, flags, smth);
}
