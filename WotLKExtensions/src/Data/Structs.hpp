#pragma once

#include <cstdint>

// cdbc
struct LFGRolesRow
{
    int32_t m_classID = -1;
    int32_t m_roles = - 1;
};

struct ZoneLightRow
{
    int32_t m_ID = -1;
    char* m_name = nullptr;
    int32_t m_mapID = -1;
    int32_t m_lightID = -1;
};

struct ZoneLightPointRow
{
    int32_t m_ID = -1;
    int32_t m_zoneLightID = -1;
    float m_positionX = 0.f;
    float m_positionY = 0.f;
    int32_t m_pointOrder = -1;
};

// dbc
struct ChrClassesRow
{
    int32_t m_ID;
    int32_t padding0x04[13];
};

struct MapRow
{
    int32_t m_ID;
    char* m_directory;
    int32_t m_instanceType;
    int32_t m_flags;
    int32_t m_PVP;
    char* m_mapName_lang;
    int32_t m_areaTableID;
    char* m_mapDescription0_lang;
    char* m_mapDescription1_lang;
    int32_t m_loadingScreenID;
    float m_minimapIconScale;
    int32_t m_corpseMapID;
    float m_corpseX;
    float m_corpseY;
    int32_t m_timeOfDayOverride;
    int32_t m_expansionID;
    int32_t m_raidOffset;
    int32_t m_maxPlayers;
    int32_t m_parentMapID;
};

struct PowerDisplayRow
{
    int32_t m_ID;
    int32_t m_actualType;
    char* m_globalStringBaseTag;
    uint8_t m_red;
    uint8_t m_green;
    uint8_t m_blue;
};

struct SkillLineAbilityRow
{
    int32_t m_ID;
    int32_t m_skillLine;
    int32_t m_spell;
    int32_t m_raceMask;
    int32_t m_classMask;
    int32_t m_excludeRace;
    int32_t m_excludeClass;
    int32_t m_minSkillLineRank;
    int32_t m_supercededBySpell;
    int32_t m_acquireMethod;
    int32_t m_trivialSkillLineRankHigh;
    int32_t m_trivialSkillLineRankLow;
    int32_t m_characterPoints[2];
    int32_t m_numSkillUps;
};

struct SkillLineRow
{
    int32_t m_ID;
    int32_t m_categoryID;
    int32_t m_skillCostsID;
    char* m_displayName_lang;
    char* m_description_lang;
    int32_t m_spellIconID;
    char* m_alternateVerb_lang;
    int32_t m_canLink;
};

struct SpellRow
{
    int32_t m_ID;
    int32_t m_category;
    int32_t m_dispelType;
    int32_t m_mechanic;
    int32_t m_attributes;
    int32_t m_attributesEx;
    int32_t m_attributesExB;
    int32_t m_attributesExC;
    int32_t m_attributesExD;
    int32_t m_attributesExE;
    int32_t m_attributesExF;
    int32_t m_attributesExG;
    int32_t m_shapeshiftMask[2];
    int32_t m_shapeshiftExclude[2];
    int32_t m_targets;
    int32_t m_targetCreatureType;
    int32_t m_requiresSpellFocus;
    int32_t m_facingCasterFlags;
    int32_t m_casterAuraState;
    int32_t m_targetAuraState;
    int32_t m_excludeCasterAuraState;
    int32_t m_excludeTargetAuraState;
    int32_t m_casterAuraSpell;
    int32_t m_targetAuraSpell;
    int32_t m_excludeCasterAuraSpell;
    int32_t m_excludeTargetAuraSpell;
    int32_t m_castingTimeIndex;
    int32_t m_recoveryTime;
    int32_t m_categoryRecoveryTime;
    int32_t m_interruptFlags;
    int32_t m_auraInterruptFlags;
    int32_t m_channelInterruptFlags;
    int32_t m_procTypeMask;
    int32_t m_procChance;
    int32_t m_procCharges;
    int32_t m_maxLevel;
    int32_t m_baseLevel;
    int32_t m_spellLevel;
    int32_t m_durationIndex;
    int32_t m_powerType;
    int32_t m_manaCost;
    int32_t m_manaCostPerLevel;
    int32_t m_manaPerSecond;
    int32_t m_manaPerSecondPerLevel;
    int32_t m_rangeIndex;
    float m_speed;
    int32_t m_modalNextSpell;
    int32_t m_cumulativeAura;
    int32_t m_totem[2];
    int32_t m_reagent[8];
    int32_t m_reagentCount[8];
    int32_t m_equippedItemClass;
    int32_t m_equippedItemSubclass;
    int32_t m_equippedItemInvTypes;
    int32_t m_effect[3];
    int32_t m_effectDieSides[3];
    float m_effectRealPointsPerLevel[3];
    int32_t m_effectBasePoints[3];
    int32_t m_effectMechanic[3];
    int32_t m_implicitTargetA[3];
    int32_t m_implicitTargetB[3];
    int32_t m_effectRadiusIndex[3];
    int32_t m_effectAura[3];
    int32_t m_effectAuraPeriod[3];
    float m_effectAmplitude[3];
    int32_t m_effectChainTargets[3];
    int32_t m_effectItemType[3];
    int32_t m_effectMiscValue[3];
    int32_t m_effectMiscValueB[3];
    int32_t m_effectTriggerSpell[3];
    float m_effectPointsPerCombo[3];
    int32_t m_effectSpellClassMaskA[3];
    int32_t m_effectSpellClassMaskB[3];
    int32_t m_effectSpellClassMaskC[3];
    int32_t m_spellVisualID[2];
    int32_t m_spellIconID;
    int32_t m_activeIconID;
    int32_t m_spellPriority;
    char* m_name_lang;
    char* m_nameSubtext_lang;
    char* m_description_lang;
    char* m_auraDescription_lang;
    int32_t m_manaCostPct;
    int32_t m_startRecoveryCategory;
    int32_t m_startRecoveryTime;
    int32_t m_maxTargetLevel;
    int32_t m_spellClassSet;
    int32_t m_spellClassMask[3];
    int32_t m_maxTargets;
    int32_t m_defenseType;
    int32_t m_preventionType;
    int32_t m_stanceBarOrder;
    float m_effectChainAmplitude[3];
    int32_t m_minFactionID;
    int32_t m_minReputation;
    int32_t m_requiredAuraVision;
    int32_t m_requiredTotemCategoryID[2];
    int32_t m_requiredAreasID;
    int32_t m_schoolMask;
    int32_t m_runeCostID;
    int32_t m_spellMissileID;
    int32_t m_powerDisplayID;
    float m_effectBonusCoefficient[3];
    int32_t m_descriptionVariablesID;
    int32_t m_difficulty;
};

struct SpellRuneCostRow
{
    int32_t m_ID;
    int32_t m_blood;
    int32_t m_unholy;
    int32_t m_frost;
    int32_t m_runicPower;
};
