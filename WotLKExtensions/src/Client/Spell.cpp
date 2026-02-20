#include <Client/Spell.hpp>

#include <string>

void Spell::ApplyPatches()
{
}

int32_t Spell::GetDefaultMinRange(SpellRow* spell, float* minRange)
{
    return reinterpret_cast<int32_t (__cdecl*)(SpellRow*, float*)>(0x7FF400)(spell, minRange);
}

int32_t Spell::GetMinMaxRange(CGUnit* unit, SpellRow* spell, float* minRange, float* maxRange, int32_t index, float a6)
{
    return reinterpret_cast<int32_t (__cdecl*)(CGUnit*, SpellRow*, float*, float*, int32_t, float)>(0x7FF480)(unit, spell, minRange, maxRange, index, a6);
}

int32_t Spell::GetPowerCost(SpellRow* spell, CGUnit* unit)
{
    return reinterpret_cast<int32_t (__cdecl*)(SpellRow*, CGUnit*)>(0x8012F0)(spell, unit);
}

int32_t Spell::GetPowerCostPerSecond(SpellRow* spell, CGUnit* unit)
{
    return reinterpret_cast<int32_t (__cdecl*)(SpellRow*, CGUnit*)>(0x7FF100)(spell, unit);
}

bool Spell::IsModifiedStat(SpellRow* spell, int32_t stat)
{
    return reinterpret_cast <bool (__cdecl*)(SpellRow*, int32_t)>(0x800770)(spell, stat);
}

bool Spell::UsesDefaultMinRange(SpellRow* spell)
{
    return reinterpret_cast<bool (__cdecl*)(SpellRow*)>(0x7FF3C0)(spell);
}

bool Spell::UsesMeleeRange(SpellRow* spell)
{
    return reinterpret_cast<bool (__cdecl*)(SpellRow*)>(0x7FF380)(spell);
}
