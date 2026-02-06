#pragma once

#include <SharedDefines.hpp>

namespace CustomFields
{
    inline int32_t combatRating[7] = { 0 };

    inline int32_t GetCustomCombatRating(int8_t index) { return combatRating[index]; }
    inline void SetCustomCombatRating(int8_t index, int32_t newValue) { combatRating[index] = newValue; }
}

class Player
{
public:
    static void ApplyPatches();
private:
    static inline uint32_t memoryTable[64] = { 0 };
    static inline uint32_t raceNameTable[32] = { 0 };
    // Just for clarity's sake, class role masks go as followed
    // ID0, War, Pal, Hun, Rog, Pri, DK, Sha, Mag, Warl, ID10, Dru
    // bitmasks: 1 - leader, 2 - tank, 4 - healer, 8 - dps
    // so for example warrior is: leader + tank + dps -> 0x01 + 0x02 + 0x08 = 0x0B
    static inline uint8_t classRoleMask[32] = {
        0x00, 0x0B, 0x0F, 0x09, 0x09, 0x0D, 0x0B, 0x0D,	0x09, 0x09, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    static void CharacterCreationRaceCrashfix();
    static void LFDClassRoleExtension();

    static uint32_t CheckLFGRoles(uint32_t roles);
    static uint32_t GetClassRoles(uint32_t classId);
};
