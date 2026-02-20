#pragma once

#include <Data/Structs.hpp>
#include <GameObjects/CGUnit.hpp>

struct lua_State;

class Spell
{
public:
    static void ApplyPatches();

    static int32_t GetDefaultMinRange(SpellRow* spell, float* minRange);
    static int32_t GetMinMaxRange(CGUnit* unit, SpellRow* spell, float* minRange, float* maxRange, int32_t index, float a6);
    static int32_t GetPowerCost(SpellRow* spell, CGUnit* unit);
    static int32_t GetPowerCostPerSecond(SpellRow* spell, CGUnit* unit);
    static bool IsModifiedStat(SpellRow* spell, int32_t stat);
    static bool UsesDefaultMinRange(SpellRow* spell);
    static bool UsesMeleeRange(SpellRow* spell);

private:
    Spell() = delete;
    ~Spell() = delete;
};
