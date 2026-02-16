#pragma once

#include <Data/Structs.hpp>
#include <GameObjects/CGUnit.hpp>

class Spell
{
public:
    static int GetDefaultMinRange(SpellRow* spell, float* minRange);
    static int GetMinMaxRange(CGUnit* unit, SpellRow* spell, float* , float* , int32_t index, float a6);
    static int GetPowerCost(SpellRow* spell, CGUnit* unit);
    static int GetPowerCostPerSecond(SpellRow* spell, CGUnit* unit);
    static bool IsModifiedStat(SpellRow* spell, int32_t stat);
    static bool UsesDefaultMinRange(SpellRow* spell);
    static bool UsesMeleeRange(SpellRow* spell);

private:
    Spell() = delete;
    ~Spell() = delete;
};
