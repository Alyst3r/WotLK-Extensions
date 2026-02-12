#include <GameObjects/CGUnit.hpp>

uint32_t CGUnit::GetShapeshiftFormID(CGUnit* thisUnit)
{
    return reinterpret_cast<uint32_t (__thiscall*)(CGUnit*)>(0x71AF70)(thisUnit);
}
