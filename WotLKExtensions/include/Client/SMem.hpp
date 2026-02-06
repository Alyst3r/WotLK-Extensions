#pragma once

#include <cstdint>

class SMem
{
public:
	static void* Alloc(uint32_t size, const char* filepath, uint32_t flags /*most likely*/, uint32_t smth);
	static bool Free(void* memory, const char* func /*dunno*/, uint32_t flags /*most likely*/, uint32_t smth);

private:
	SMem() = delete;
	~SMem() = delete;
};
