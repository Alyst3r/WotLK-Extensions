#pragma once

#include <GameObjects/CGUnit.hpp>
#include <SharedDefines.hpp>

struct PlayerFields
{
    WoWGUID m_playerDuelArbiter;
    uint32_t m_playerFlags;
    uint32_t m_padding0x0C[1175];
};

struct CGPlayer : CGUnit
{
    PlayerFields* m_playerData;
    uint32_t m_padding0x1008[1024];

    static bool IsDeadOrGhost(CGPlayer* thisPlayer);

    // custom functions
    static void ApplyPatches();

    static void CharacterCreationRaceCrashfix();
    static void LFDClassRoleExtension();

    static uint32_t CheckLFGRoles(uint32_t roles);
    static uint32_t GetClassRoles(uint32_t classId);
};

struct CGPlayerCustomFields
{
    int32_t m_combatRating[7] = { 0 };
};
