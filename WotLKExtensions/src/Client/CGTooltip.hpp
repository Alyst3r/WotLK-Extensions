#pragma once

#include <Data/DBItemCache.hpp>
#include <Data/Structs.hpp>
#include <GameObjects/CGItem.hpp>
#include <GameObjects/CGPlayer.hpp>

#include <cstdint>

class CGTooltip
{
public:
    static void ApplyPatches();

    static int32_t __fastcall SetItemEx(CGTooltip* thisTooltip, int32_t unused, int32_t itemID, int64_t* a4, int64_t* guid, int32_t a6, int32_t a7, int32_t a8, int32_t a9, uint64_t a10, int32_t a11, int32_t a12, int32_t a13, int32_t a14, int32_t a15, int32_t a16, int32_t a17);
    static int32_t __fastcall SetSpellEx(CGTooltip* thisTooltip, int32_t unused, int32_t spellId, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, uint32_t* a9, int32_t a10, int32_t a11, int32_t a12, int32_t a13, int32_t a14, int32_t a15, int32_t a16);

    static void AddLine(CGTooltip* thisTooltip, char* str1, char* str2, uint32_t* color1, uint32_t* color2, int32_t a6);
    static void AddEmbeddedItemBlock(CGTooltip* thisTooltip, SpellRow* spellRow);
    static void AddTalentLearnText(CGTooltip* thisTooltip, uint32_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9, int32_t a10);
    static int32_t AddTalentPrereqs(CGTooltip* thisTooltip, uint32_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6);
    static int32_t ClearTooltip(CGTooltip* thisTooltip);
    static int32_t GetDurationString(char* buffer, int32_t length, uint64_t cooldown, char* string, int32_t a5, int32_t a6, int32_t a7);
    static void CalculateSize(CGTooltip* thisTooltip);
    static int32_t SetDummyItemTooltip(CGTooltip* thisTooltip);
    
    static int32_t sub_81A2C0(CGTooltip* thisTooltip, int32_t* a2, int32_t a3, int32_t a4);

    static void AddCastTimeLine(CGTooltip* thisTooltip, SpellRow* spellRow, CGUnit* unit, int32_t a4, int32_t a5, int32_t a6);
    static int32_t AddCooldownLine(CGTooltip* thisTooltip, int32_t cooldown);
    static void AddDrainAllPowerLine(CGTooltip* thisTooltip, SpellRow* spellRow);
    static void AddPowerAndRangeLines(CGTooltip* thisTooltip, char* powerLine, CGUnit* unit, SpellRow* spellRow, bool displayRange);
    static void AddReagentsLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, int32_t a2, int32_t a3);
    static void AddRequiredFactionLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, int32_t a3);
    static void AddRequiredItemLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, int32_t a4, int32_t a5);
    static void AddRequiredLevelLine(CGTooltip* thisTooltip, CGUnit* unit, SpellRow* spellRow, bool a4);
    static void AddRequiredShapeshiftFormLine(CGTooltip* thisTooltip, CGUnit* unit, SpellRow* spellRow, int32_t a4);
    static int32_t AddSpecialActionLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, bool a4);
    static void AddSpellDescriptionLine(CGTooltip* thisTooltip, SpellRow* spellRow, int32_t a3, int32_t a4);
    static void AddSpellIDLine(CGTooltip* thisTooltip, SpellRow* spellRow);
    static void AddTalentRankLine(CGTooltip* thisTooltip, int32_t a2, int32_t a3);
    static void AddTalentNextRankLine(CGTooltip* thisTooltip);
    static void AddTotemsLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, int32_t a4, int32_t a5);
    static void AddTradeSkillLine(CGTooltip* thisTooltip, CGPlayer* activePlayer, SpellRow* spellRow, int32_t spellId);

    static void AppendPowerCostLine(CGTooltip* thisTooltip, char* buffer, CGUnit* unit, SpellRow* spellRow);
    static void AppendRuneCostLine(CGTooltip* thisTooltip, char* buffer, SpellRow* spellRow);

    static bool IsCreateItemSpell(SpellRow* spellRow);
    static bool IsTradespell(SpellRow* spellRow);

    static void AddItemAreaAndMapLines(CGTooltip* thisTooltip, DBItemCache* itemCache);
    static void AddItemBondingLine(CGTooltip* thisTooltip, CGItem* item, DBItemCache* itemCache, int64_t* a4);
    static void AddItemConjuredLine(CGTooltip* thisTooltip, DBItemCache* itemCache);
    static bool AddItemGemPropertyLine(CGTooltip* thisTooltip, int32_t gemProperties, int32_t a2);
    static void AddItemIDLine(CGTooltip* thisTooltip, int32_t itemID);
    static void AddItemLimitLines(CGTooltip* thisTooltip, DBItemCache* itemCache);
    static void AddItemNameAndQualityLines(CGTooltip* thisTooltip, int32_t itemID, int32_t a3, int32_t a4, int32_t a5, DBItemCache* itemCache, bool destroyed);
    static int32_t AddItemPetitionLines(CGTooltip* thisTooltip, CGItem* item, DBItemCache* itemCache, int64_t* guid);
    static void AddItemStartQuestLine(CGTooltip* thisTooltip, DBItemCache* itemCache);

    static void AppendItemSuffix(CGTooltip* thisTooltip, CGItem* item, int32_t* a2);

private:
    void* m_vTable;
    int32_t padding[207];
    WoWGUID guid1;
    int32_t padding2[30];
    WoWGUID guid2;
    int32_t padding3[258];

    CGTooltip() = delete;
    ~CGTooltip() = delete;
};

class CSimpleFrame
{
public:
    static int32_t Hide(void* thisFrame);
    static int32_t Show(void* thisFrame);

private:
    CSimpleFrame() = delete;
    ~CSimpleFrame() = delete;
};
