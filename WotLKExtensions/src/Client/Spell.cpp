#include <Client/Spell.hpp>

#include <string>

void Spell::ApplyPatches()
{
}

int32_t Spell::GetCastTime(SpellRow* spell, int32_t a2, int32_t a3, int32_t a4)
{
    return reinterpret_cast<int32_t (__cdecl*)(SpellRow*, int32_t, int32_t, int32_t)>(0x7FF180)(spell, a2, a3, a4);
}

int32_t Spell::GetDefaultMinRange(SpellRow* spell, float* minRange)
{
    return reinterpret_cast<int32_t (__cdecl*)(SpellRow*, float*)>(0x7FF400)(spell, minRange);
}

int32_t Spell::GetDescription(SpellRow* spell, char* buffer, int32_t length, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9)
{
    return reinterpret_cast<int32_t (__cdecl*)(SpellRow*, char*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x57ABC0)(spell, buffer, length, a4, a5, a6, a7, a8, a9);
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

int32_t Spell::ModifySpellValueInt(SpellRow* spellRow, int32_t* a2, int32_t value)
{
    return reinterpret_cast<int32_t (__cdecl*)(SpellRow*, int32_t*, int32_t)>(0x7FDB50)(spellRow, a2, value);
}

int32_t Spell::sub_7FEF60(int32_t* a1, SpellRow* spellRow, int32_t value)
{
    return reinterpret_cast<int32_t (__cdecl*)(int32_t*, SpellRow*, int32_t)>(0x7FEF60)(a1, spellRow, value);
}

bool Spell::UsableInShapeshiftForm(SpellRow* spell, int32_t shapeshift)
{
    return reinterpret_cast<bool (__cdecl*)(SpellRow*, int32_t)>(0x7FE850)(spell, shapeshift);
}

bool Spell::UsesDefaultMinRange(SpellRow* spell)
{
    return reinterpret_cast<bool (__cdecl*)(SpellRow*)>(0x7FF3C0)(spell);
}

bool Spell::UsesMeleeRange(SpellRow* spell)
{
    return reinterpret_cast<bool (__cdecl*)(SpellRow*)>(0x7FF380)(spell);
}
