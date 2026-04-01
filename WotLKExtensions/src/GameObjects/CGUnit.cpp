#include <GameObjects/CGUnit.hpp>

uint32_t CGUnit::GetShapeshiftFormID(CGUnit* thisUnit)
{
    return reinterpret_cast<uint32_t (__thiscall*)(CGUnit*)>(0x71AF70)(thisUnit);
}

uint8_t CGUnit::GetClass() const
{
    return m_unitFields->m_bytes0.m_unitClass;
}

uint8_t CGUnit::GetGender() const
{
    return m_unitFields->m_bytes0.m_unitGender;
}

uint8_t CGUnit::GetPowerType() const
{
    return m_unitFields->m_bytes0.m_unitPowerType;
}

uint8_t CGUnit::GetRace() const
{
    return m_unitFields->m_bytes0.m_unitRace;
}
