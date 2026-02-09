#pragma once

#include <PatchConfig.hpp>
#include <Misc/Util.hpp>

static uint32_t dummy = 0;

static std::unordered_map<char*, void*> luaFuncts;

typedef uint64_t WoWGUID;

// enums
enum CustomOpcodes
{
    NUM_ORIGINAL_MSG_TYPES                      = 1311,
    SMSG_UPDATE_CUSTOM_COMBAT_RATING            = NUM_ORIGINAL_MSG_TYPES,
    CMSG_TELEPORT_GRAVEYARD_REQUEST             = 1312,
    NUM_CUSTOM_MSG_TYPES
};

enum FrameXMLEvent : uint32_t
{
    EVENT_LFG_ROLE_UPDATE                       = 506,
};

enum PlayerFlags
{
    PLAYER_FLAGS_GHOST							= 0x10,
};

enum TypeMask
{
    TYPEMASK_OBJECT								= 0x0001,
    TYPEMASK_ITEM								= 0x0002,
    TYPEMASK_CONTAINER							= 0x0004,
    TYPEMASK_UNIT								= 0x0008,
    TYPEMASK_PLAYER								= 0x0010,
    TYPEMASK_GAMEOBJECT							= 0x0020,
    TYPEMASK_DYNAMICOBJECT						= 0x0040,
    TYPEMASK_CORPSE								= 0x0080,
};

// structures
struct C2Vector
{
    float x;
    float y;
};

struct C3Vector
{
    float x;
    float y;
    float z;
};

struct CMovement
{
    uint32_t padding0x00[4];
    C3Vector position;
    float padding0x1C;
    float orientation;
    float pitch;
    uint32_t padding28[7];
    uint32_t movementFlags;
    uint32_t movementFlags2;
    uint32_t padding0x4C[63];
};

struct UnitBytes0
{
    uint8_t unitRace;
    uint8_t unitClass;
    uint8_t unitGender;
    uint8_t unitPowerType;
};

struct UnitFields
{
    uint32_t padding0x00[17];
    UnitBytes0 bytes0;
    uint32_t padding0x48[30];
    uint32_t level;
    uint32_t padding0xC4[93];
};

struct CGUnit
{
    uint32_t padding0x00[52];
    UnitFields* unitFields;
    uint32_t padding0xD4;
    CMovement* movementInfo;
    uint32_t padding0x34[971];
};

struct PlayerFields
{
    WoWGUID playerDuelArbiter;
    uint32_t playerFlags;
    uint32_t padding0x0C[1175];
};

struct CGPlayer
{
    CGUnit unitData;
    PlayerFields* playerData;
    uint32_t padding0x1008[1024];
};

struct ChrClassesRow
{
    uint32_t m_ID;
    uint32_t padding0x04[13];
};

struct CustomNetClient
{
    void* handler[NUM_CUSTOM_MSG_TYPES - SMSG_UPDATE_CUSTOM_COMBAT_RATING];
    void* handlerParam[NUM_CUSTOM_MSG_TYPES - SMSG_UPDATE_CUSTOM_COMBAT_RATING];
};

struct MapRow
{
    uint32_t m_ID;
    char* m_Directory;
    uint32_t padding0x08[17];
};

struct SpellRow
{
    int32_t m_ID;
    uint32_t m_category;
    uint32_t m_dispelType;
    uint32_t m_mechanic;
    uint32_t m_attributes;
    uint32_t m_attributesEx;
    uint32_t m_attributesExB;
    uint32_t m_attributesExC;
    uint32_t m_attributesExD;
    uint32_t m_attributesExE;
    uint32_t m_attributesExF;
    uint32_t m_attributesExG;
    uint32_t m_shapeshiftMask[2];
    uint32_t m_shapeshiftExclude[2];
    uint32_t m_targets;
    uint32_t m_targetCreatureType;
    uint32_t m_requiresSpellFocus;
    uint32_t m_facingCasterFlags;
    uint32_t m_casterAuraState;
    uint32_t m_targetAuraState;
    uint32_t m_excludeCasterAuraState;
    uint32_t m_excludeTargetAuraState;
    uint32_t m_casterAuraSpell;
    uint32_t m_targetAuraSpell;
    uint32_t m_excludeCasterAuraSpell;
    uint32_t m_excludeTargetAuraSpell;
    uint32_t m_castingTimeIndex;
    uint32_t m_recoveryTime;
    uint32_t m_categoryRecoveryTime;
    uint32_t m_interruptFlags;
    uint32_t m_auraInterruptFlags;
    uint32_t m_channelInterruptFlags;
    uint32_t m_procTypeMask;
    uint32_t m_procChance;
    uint32_t m_procCharges;
    uint32_t m_maxLevel;
    uint32_t m_baseLevel;
    uint32_t m_spellLevel;
    uint32_t m_durationIndex;
    uint32_t m_powerType;
    uint32_t m_manaCost;
    uint32_t m_manaCostPerLevel;
    uint32_t m_manaPerSecond;
    uint32_t m_manaPerSecondPerLevel;
    uint32_t m_rangeIndex;
    float m_speed;
    uint32_t m_modalNextSpell;
    uint32_t m_cumulativeAura;
    uint32_t m_totem0[2];
    uint32_t m_reagent[8];
    uint32_t m_reagentCount[8];
    uint32_t m_equippedItemClass;
    uint32_t m_equippedItemSubclass;
    uint32_t m_equippedItemInvTypes;
    uint32_t m_effect[3];
    uint32_t m_effectDieSides[3];
    float m_effectRealPointsPerLevel[3];
    uint32_t m_effectBasePoints[3];
    uint32_t m_effectMechanic[3];
    uint32_t m_implicitTargetA[3];
    uint32_t m_implicitTargetB[3];
    uint32_t m_effectRadiusIndex[3];
    uint32_t m_effectAura[3];
    uint32_t m_effectAuraPeriod[3];
    float m_effectAmplitude[3];
    uint32_t m_effectChainTargets[3];
    uint32_t m_effectItemType[3];
    uint32_t m_effectMiscValue[3];
    uint32_t m_effectMiscValueB[3];
    uint32_t m_effectTriggerSpell[3];
    float m_effectPointsPerCombo[3];
    uint32_t m_effectSpellClassMaskA[3];
    uint32_t m_effectSpellClassMaskB[3];
    uint32_t m_effectSpellClassMaskC[3];
    uint32_t m_spellVisualID[2];
    uint32_t m_spellIconID;
    uint32_t m_activeIconID;
    uint32_t m_spellPriority;
    char* m_name_lang;
    char* m_nameSubtext_lang;
    char* m_description_lang;
    char* m_auraDescription_lang;
    uint32_t m_manaCostPct;
    uint32_t m_startRecoveryCategory;
    uint32_t m_startRecoveryTime;
    uint32_t m_maxTargetLevel;
    uint32_t m_spellClassSet;
    uint32_t m_spellClassMask[3];
    uint32_t m_maxTargets;
    uint32_t m_defenseType;
    uint32_t m_preventionType;
    uint32_t m_stanceBarOrder;
    float m_effectChainAmplitude[3];
    uint32_t m_minFactionID;
    uint32_t m_minReputation;
    uint32_t m_requiredAuraVision;
    uint32_t m_requiredTotemCategoryID[2];
    uint32_t m_requiredAreasID;
    uint32_t m_schoolMask;
    uint32_t m_runeCostID;
    uint32_t m_spellMissileID;
    uint32_t m_powerDisplayID;
    float m_effectBonusCoefficient[3];
    uint32_t m_descriptionVariablesID;
    uint32_t m_difficulty;
};

// Aleist3r: afaik it's not a full structure but I don't need the rest defined
struct WoWTime
{
    int32_t minute;
    int32_t hour;
    int32_t weekDay;
    int32_t monthDay;
    int32_t month;
    int32_t year;
    int32_t flags;
};

struct ZoneLightData
{
    int32_t mapID;
    int32_t lightID;
    void* pointData;
    int32_t pointNum;
    float minX;
    float minY;
    float maxX;
    float maxY;
};

// Client functions
namespace CGChat
{
    CLIENT_FUNCTION(AddChatMessage, 0x509DD0, __cdecl, bool, (char*, uint32_t, uint32_t, uint32_t, uint32_t*, uint32_t, char*, uint64_t, uint32_t, uint64_t, uint32_t, uint32_t, uint32_t*))
}

namespace CGPlayer_C
{
    CLIENT_FUNCTION(IsDeadOrGhost, 0x6DAC10, __thiscall, bool, (CGPlayer*))
}

namespace CGUnit_C
{
    CLIENT_FUNCTION(GetShapeshiftFormId, 0x71AF70, __thiscall, uint32_t, (CGUnit*))
}

namespace ClientPacket
{
    CLIENT_FUNCTION(MSG_SET_ACTION_BUTTON, 0x5AA390, __cdecl, void, (uint32_t, bool, bool))
}

namespace ClntObjMgr
{
    CLIENT_FUNCTION(GetActivePlayer, 0x4D3790, __cdecl, WoWGUID, ())
    CLIENT_FUNCTION(ObjectPtr, 0x4D4DB0, __cdecl, void*, (WoWGUID, uint32_t))
}

namespace CVar
{
    CLIENT_FUNCTION(sub_766940, 0x766940, __thiscall, void, (void*, int, char, char, char, char))
    CLIENT_FUNCTION(SetCvar, 0x76C9C0, __thiscall, void, (void* cvar, const char* value, bool setDirty, bool, bool, bool forceUpdate))
    CLIENT_FUNCTION(LookupCvar, 0x767460, __cdecl, void*, (const char* name))
}

namespace DNInfo
{
    CLIENT_FUNCTION(AddZoneLight, 0x7ED150, __thiscall, void, (void*, int32_t, float))
    CLIENT_FUNCTION(GetDNInfoPtr, 0x7ECEF0, __stdcall, void*, ())
}

namespace NTempest
{
    CLIENT_FUNCTION(DistanceSquaredFromEdge, 0x7F9C90, __cdecl, bool, (int32_t, void*, C2Vector*, float*))
}

namespace SpellParser
{
    CLIENT_FUNCTION(ParseText, 0x57ABC0, __cdecl, void, (void*, void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))
}

namespace World
{
    CLIENT_FUNCTION(LoadMap, 0x781430, __cdecl, void, (char*, C3Vector*, uint32_t))
    CLIENT_FUNCTION(UnloadMap, 0x783180, __cdecl, void, ())
    CLIENT_FUNCTION(Pos3Dto2D, 0x4F6D20, __fastcall, int, (void* This, void* edx, C3Vector* pos3d, C3Vector* pos2d, uint32_t* flags))
}
