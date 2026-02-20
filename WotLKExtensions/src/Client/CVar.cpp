#include <Client/CVar.hpp>

void CVar::Set(void* cVar, int32_t value, bool a3, bool a4, bool a5, bool a6)
{
    reinterpret_cast<void (__thiscall*)(void*, int32_t, bool, bool, bool, bool)>(0x766940)(cVar, value, a3, a4, a5, a6);
}
