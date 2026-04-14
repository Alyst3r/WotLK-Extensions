#include <GameObjects/CGUnit.hpp>

int32_t CGUnit::EquippedItemMeetsSpellRequirements(CGUnit* thisUnit, SpellRow* spellRow, int32_t requirementFlags)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGUnit*, SpellRow*, int32_t)>(0x6DE230)(thisUnit, spellRow, requirementFlags);
}

char* CGUnit::GetFrameScriptText(CGUnit* thisUnit, const char* format, int32_t a3)
{
    return reinterpret_cast<char* (__thiscall*)(CGUnit*, const char*, int32_t)>(0x7225E0)(thisUnit, format, a3);
}

uint32_t CGUnit::GetShapeshiftFormID(CGUnit* thisUnit)
{
    return reinterpret_cast<uint32_t (__thiscall*)(CGUnit*)>(0x71AF70)(thisUnit);
}

bool CGUnit::HasAuraMatchingSpellClass(CGUnit* thisUnit, int32_t aura, SpellRow* spell)
{
    return reinterpret_cast<bool (__thiscall*)(CGUnit*, int32_t, SpellRow*)>(0x7283A0)(thisUnit, aura, spell);
}

bool CGUnit::IsShapeshifted(CGUnit* thisUnit)
{
    return reinterpret_cast<bool (__thiscall*)(CGUnit*)>(0x721CA0)(thisUnit);
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

uint32_t CGUnit::GetLevel() const
{
    return m_unitFields->m_level;
}
