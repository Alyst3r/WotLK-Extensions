#pragma once

#include <cstdint>

struct CGObject
{
	void* m_vtable;
	int32_t m_padding0x04[51];
};
