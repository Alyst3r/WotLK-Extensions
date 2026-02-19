#pragma once

#include <GameObjects/CGObject.hpp>
#include <WorldData/CMovement.hpp>

struct UnitBytes0
{
    uint8_t m_unitRace;
    uint8_t m_unitClass;
    uint8_t m_unitGender;
    uint8_t m_unitPowerType;
};

struct UnitFields
{
    uint32_t m_padding0x00[17];
    UnitBytes0 m_bytes0;
    uint32_t m_currHealth;
    uint32_t m_currPowers[7];
    uint32_t m_maxHealth;
    uint32_t m_maxPowers[7];
    uint32_t m_padding0x88[14];
    uint32_t m_level;
    uint32_t m_padding0xC4[93];
};

struct CGUnit : CGObject
{
    UnitFields* m_unitFields;
    uint32_t m_padding0xD4;
    CMovement* m_movementInfo;
    uint32_t m_padding0x34[971];

    static uint32_t GetShapeshiftFormID(CGUnit* thisUnit);
};
