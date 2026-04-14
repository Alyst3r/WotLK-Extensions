#pragma once

#include <Data/Structs.hpp>
#include <GameObjects/CGUnit.hpp>

struct lua_State;

class Spell
{
public:
    static void ApplyPatches();

    static int32_t GetCastTime(SpellRow* spell, int32_t a2, int32_t a3, int32_t a4);
    static int32_t GetDefaultMinRange(SpellRow* spell, float* minRange);
    static int32_t GetDescription(SpellRow* spell, char* buffer, int32_t length, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9);
    static int32_t GetMinMaxRange(CGUnit* unit, SpellRow* spell, float* minRange, float* maxRange, int32_t index, float a6);
    static int32_t GetPowerCost(SpellRow* spell, CGUnit* unit);
    static int32_t GetPowerCostPerSecond(SpellRow* spell, CGUnit* unit);
    static bool IsModifiedStat(SpellRow* spell, int32_t stat);
    static int32_t ModifySpellValueInt(SpellRow* spellRow, int32_t* a2, int32_t value);
    static int32_t sub_7FEF60(int32_t* a1, SpellRow* spellRow, int32_t value);
    static bool UsableInShapeshiftForm(SpellRow* spell, int32_t shapeshift);
    static bool UsesDefaultMinRange(SpellRow* spell);
    static bool UsesMeleeRange(SpellRow* spell);

private:
    Spell() = delete;
    ~Spell() = delete;
};
