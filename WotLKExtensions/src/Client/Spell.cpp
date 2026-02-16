#include <Client/Spell.hpp>

int Spell::GetPowerCost(SpellRow* spell, CGUnit* unit)
{
    return reinterpret_cast<int (__cdecl*)(SpellRow*, CGUnit*)>(0x8012F0)(spell, unit);
}

int Spell::GetPowerCostPerSecond(SpellRow* spell, CGUnit* unit)
{
    return reinterpret_cast<int (__cdecl*)(SpellRow*, CGUnit*)>(0x7FF100)(spell, unit);
}

bool Spell::IsModifiedStat(SpellRow* spell, int32_t stat)
{
    return reinterpret_cast <bool (__cdecl*)(SpellRow*, int32_t)>(0x800770)(spell, stat);
}

bool Spell::UsesMeleeRange(SpellRow* spell)
{
    return reinterpret_cast<bool (__cdecl*)(SpellRow*)>(0x7FF380)(spell);
}
