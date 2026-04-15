#pragma once

#include <Data/Math.hpp>

#include <cstdint>

class CMissile
{
public:
    static void ApplyPatches();

private:
    int32_t padding0x00[7];
    int32_t m_spellID;
    int32_t m_padding0x20;
    float m_speed;
    float m_baseSpeed;
    int32_t m_padding0x2C[102];

    CMissile() = delete;
    ~CMissile() = delete;

    static void __fastcall FireMissilesEx(CMissile* thisMissile, int32_t unused, C3Vector* launchPos);
    static C3Vector* GetImpactDestination(CMissile* thisMissile, C3Vector* dest);
};
