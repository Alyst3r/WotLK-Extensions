#pragma once

#include <cstdint>

// cdbc
struct LFGRolesRow
{
    uint32_t m_classID;
    uint32_t m_roles;
};

struct ZoneLightRow
{
    int32_t m_ID;
    char* m_name;
    int32_t m_mapID;
    int32_t m_lightID;
};

struct ZoneLightPointRow
{
    int32_t m_ID;
    int32_t m_zoneLightID;
    float m_positionX;
    float m_positionY;
    int32_t m_pointOrder;
};

// dbc
struct ChrClassesRow
{
    int32_t m_ID;
    uint32_t padding0x04[13];
};

struct MapRow
{
    uint32_t m_ID;
    char* m_Directory;
    uint32_t padding0x08[17];
};

struct SkillLineAbilityRow
{
    int32_t m_ID;
    uint32_t m_skillLine;
    uint32_t m_spell;
    uint32_t m_raceMask;
    uint32_t m_classMask;
    uint32_t m_excludeRace;
    uint32_t m_excludeClass;
    uint32_t m_minSkillLineRank;
    uint32_t m_supercededBySpell;
    uint32_t m_acquireMethod;
    uint32_t m_trivialSkillLineRankHigh;
    uint32_t m_trivialSkillLineRankLow;
    uint32_t m_characterPoints[2];
    uint32_t m_numSkillUps;
};

struct SkillLineRow
{
    int32_t m_ID;
    uint32_t m_categoryID;
    uint32_t m_skillCostsID;
    char* m_displayName_lang;
    char* m_description_lang;
    uint32_t m_spellIconID;
    char* m_alternateVerb_lang;
    uint32_t m_canLink;
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

struct SpellRuneCostRow
{
    uint32_t m_ID;
    int32_t m_blood;
    int32_t m_unholy;
    int32_t m_frost;
    int32_t m_runicPower;
};
