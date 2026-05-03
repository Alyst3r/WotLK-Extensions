#include <Client/CFormula.hpp>
#include <Client/CGReputationInfo.hpp>
#include <Client/CGTooltip.hpp>
#include <Client/ClientServices.hpp>
#include <Client/CVar.hpp>
#include <Client/DBClient.hpp>
#include <Client/FrameScript.hpp>
#include <Client/Spell.hpp>
#include <Client/SStr.hpp>
#include <Data/DBCAddresses.hpp>
#include <Data/DBNameCache.hpp>
#include <Data/DBPetitionCache.hpp>
#include <Data/Enums.hpp>
#include <Data/MiscAddresses.hpp>
#include <GameObjects/CGBag.hpp>
#include <GameObjects/CGPetInfo.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Logger.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>

void CGTooltip::ApplyPatches()
{
#if SPELLDESCRIPTIONEXT_PATCH
    std::vector<const char*>& data = sDC.GetSpellVariableData();

    CFormula::FillSpellVariableData();
    Util::OverwriteUInt32AtAddress(0x576B63, reinterpret_cast<uint32_t>(data.data()));
    Util::OverwriteUInt32AtAddress(0x576B7C, data.size());
    Util::OverwriteUInt32AtAddress(0x578E8B, reinterpret_cast<uint32_t>(&CFormula::GetVariableValueEx) - 0x578E8F);
#endif

    std::vector<uint32_t> setSpellAddresses =
    {
        0x61DDB7, 0x625590, 0x62572F, 0x6258BC,
        0x625B20, 0x625C9A, 0x62643A, 0x6264C7,
        0x626687, 0x626F0C, 0x626F4A, 0x62DC3D,
        0x62DCC5, 0x62E9FD, 0x62EA9F, 0x62EC90,
        0x630F95, 0x630FC4, 0x63136D
    };

    for (size_t i = 0; i < setSpellAddresses.size(); i++)
        Util::OverwriteUInt32AtAddress(setSpellAddresses[i] - 4, reinterpret_cast<uint32_t>(&SetSpellEx) - setSpellAddresses[i]);

    std::vector<uint32_t> setItemAddresses =
    {
        0x626708, /*TODO: remove later*/0x62C412/*/TODO*/, 0x62DBC1, 0x62E1C8,
        0x62E376, 0x62E4BE, 0x62E649, 0x62E767,
        0x62E8D4, 0x62EA72, 0x62EC56, 0x62ED52,
        0x62EE50, 0x62EFCC, 0x62F1C1, 0x62F3FB,
        0x62F6C7, 0x62F98C, 0x62FBE0, 0x62FCB1,
        0x62FEF7, 0x630092, 0x630190, 0x63023B,
        0x63035B, 0x630495, 0x630600, 0x630780,
        0x6307D2, 0x630930, 0x630982, 0x630A74,
        0x630B70, 0x630C5D, 0x630EBD, 0x630EFB,
        0x6312B5, 0x6312E5, 0x631915, 0x6319C4,
        0x631B11
    };

    for (size_t j = 0; j < setItemAddresses.size(); j++)
        Util::OverwriteUInt32AtAddress(setItemAddresses[j] - 4, reinterpret_cast<uint32_t>(&SetItemEx) - setItemAddresses[j]);
}

int32_t __fastcall CGTooltip::SetItemEx(CGTooltip* thisTooltip, int32_t unused, int32_t itemID, int64_t* a4, int64_t* guid, int32_t a6, int32_t a7, int32_t a8, int32_t a9, uint64_t a10, int32_t a11, int32_t a12, int32_t a13, int32_t a14, int32_t a15, int32_t a16, int32_t a17)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*, int32_t, int64_t*, int64_t*, int32_t, int32_t, int32_t, int32_t, uint64_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x6277F0)(thisTooltip, itemID, a4, guid, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17);

    CGPlayer* player = reinterpret_cast<CGPlayer*>(ClientServices::GetObjectPtr(ClientServices::GetActivePlayer(), TYPEMASK_PLAYER));
    CGPlayer* player2 = nullptr;

    if (!player)
    {
        CSimpleFrame::Hide(thisTooltip);

        return 0;
    }

    if (a10)
        player2 = reinterpret_cast<CGPlayer*>(ClientServices::GetObjectPtr(a10, TYPEMASK_PLAYER));

    if (!a9)
    {
        ClearTooltip(thisTooltip);

        thisTooltip->guid1 = *guid;
        thisTooltip->padding2[6] = itemID;
        thisTooltip->padding2[27] = a6;
        thisTooltip->padding2[28] = a11;
        thisTooltip->padding2[29] = a7;
        thisTooltip->guid2 = a10;
        thisTooltip->padding3[62] = a8;
        thisTooltip->padding3[63] = a13;
        thisTooltip->padding3[64] = a15;
        thisTooltip->padding3[65] = a17;
    }

    DBItemCache* itemCache = DBItemCache::GetInfoBlockByID(g_itemDBCache, itemID, a4, reinterpret_cast<void (__cdecl*)(CGTooltip*, bool)>(0x626650), thisTooltip, 1);

    if (!itemCache)
        return SetDummyItemTooltip(thisTooltip);

    bool isBag = itemCache->m_inventoryType == INVTYPE_BAG;
    CGItem* item = reinterpret_cast<CGItem*>(ClientServices::GetObjectPtr(*guid, TYPEMASK_ITEM));
    bool isWrapped = (item && (item->m_itemData->m_flags & ITEM_FIELD_FLAG_WRAPPED)) || (thisTooltip->padding3[62] && thisTooltip->padding3[55]);
    a8 = 0;

    if (!isWrapped)
        AppendItemSuffix(thisTooltip, item, &a8);

    bool destroyed = AddItemGemPropertyLine(thisTooltip, itemCache->m_gemProperties, a7);

    AddItemNameAndQualityLines(thisTooltip, itemID, a8, a6, a9, itemCache, destroyed);
    
    if (!AddItemPetitionLines(thisTooltip, item, itemCache, guid))
        return 0;

    if (!a6 && !a11)
    {
        AddItemAreaAndMapLines(thisTooltip, itemCache);
        AddItemConjuredLine(thisTooltip, itemCache);
        AddItemBondingLine(thisTooltip, item, itemCache, a4);
        AddItemLimitLines(thisTooltip, itemCache);
        AddItemStartQuestLine(thisTooltip, itemCache);
    }

    if (!a16)
    {

    }

    //
#if TOOLTIPID_PATCH
    AddItemIDLine(thisTooltip, itemID);
#endif
    if (thisTooltip->padding3[75])
        sub_81A2C0(thisTooltip, &thisTooltip->padding3[75], 0, 0);

    CSimpleFrame::Show(thisTooltip);
    CalculateSize(thisTooltip);

    return 1;
}

int32_t __fastcall CGTooltip::SetSpellEx(CGTooltip* thisTooltip, int32_t unused, int32_t spellId, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, uint32_t* a9, int32_t a10, int32_t a11, int32_t a12, int32_t a13, int32_t a14, int32_t a15, int32_t a16)
{
    bool displayRange = true;
    bool unc = false;
    CGPlayer* activePlayer = reinterpret_cast<CGPlayer*>(ClientServices::GetObjectPtr(ClientServices::GetActivePlayer(), TYPEMASK_PLAYER));
    CGUnit* unit = nullptr;
    char powerCostLine[128] = { 0 };
    int32_t result = 0;
    int32_t talentPrereq = 1;
    SpellRow spellRow{};

    if (!a11)
    {
        ClearTooltip(thisTooltip);

        thisTooltip->padding2[7] = spellId;
        *thisTooltip->padding3 = 0;
    }

    if (!activePlayer)
    {
        CSimpleFrame::Hide(thisTooltip);

        return 0;
    }

    if (!DBClient::GetLocalizedRow(g_spellDB, spellId, &spellRow))
    {
        if (!a11)
            CSimpleFrame::Hide(thisTooltip);

        return 0;
    }

    if (a7)
        unit = reinterpret_cast<CGUnit*>(ClientServices::GetObjectPtr(*reinterpret_cast<uint64_t*>(0xC24220), TYPEMASK_UNIT));
    else if (a5)
        unit = reinterpret_cast<CGUnit*>(ClientServices::GetObjectPtr(CGPetInfo::GetPet(0), TYPEMASK_UNIT));
    else
        unit = activePlayer;

    if (a9 && a11)
        AddTalentNextRankLine(thisTooltip);
    else if (IsTradespell(&spellRow))
        AddTradeSkillLine(thisTooltip, activePlayer, &spellRow, spellId);
    else
        AddLine(thisTooltip, spellRow.m_name_lang, (a3 || a6) ? spellRow.m_nameSubtext_lang : nullptr, &sTextWhite, &sTextGrey, 0);

    if (a9 && !a11)
    {
        AddTalentRankLine(thisTooltip, a14, a15);

        if (a14 < 0)
            talentPrereq = AddTalentPrereqs(thisTooltip, a9, a10, a7, a5, a12);
    }

    if (!a3)
        AppendPowerCostLine(thisTooltip, powerCostLine, unit, &spellRow);

    if (a3 || (spellRow.m_attributes & (SPELL_ATTR0_ON_NEXT_SWING | SPELL_ATTR0_ON_NEXT_SWING_2)) || (spellRow.m_attributesExC & SPELL_ATTR3_DONT_DISPLAY_RANGE))
        displayRange = false;

    AddPowerAndRangeLines(thisTooltip, powerCostLine, unit, &spellRow, displayRange);

    if (!a4 || !IsTradespell(&spellRow))
    {
        if (spellRow.m_effect[0] == SPELL_EFFECT_TRADE_SKILL || (spellRow.m_attributes & SPELL_ATTR0_PASSIVE))
            unc = true;
        else if (spellRow.m_effect[0] != SPELL_EFFECT_ATTACK)
            AddCastTimeLine(thisTooltip, &spellRow, unit, a3, a5, a7);
    }

    AddTotemsLine(thisTooltip, activePlayer, &spellRow, a3, a5);
    AddRequiredItemLine(thisTooltip, activePlayer, &spellRow, a3, a5);
    AddRequiredShapeshiftFormLine(thisTooltip, unit, &spellRow, a3);
    AddRequiredFactionLine(thisTooltip, activePlayer, &spellRow, a3);
    AddRequiredLevelLine(thisTooltip, unit, &spellRow, unc);
    AddReagentsLine(thisTooltip, activePlayer, &spellRow, a5, a3);

    result = AddCooldownLine(thisTooltip, a4);

    if (!a3)
    {
        result = !result ? AddSpecialActionLine(thisTooltip, activePlayer, &spellRow, unc) : 1;

        AddDrainAllPowerLine(thisTooltip, &spellRow);
        AddSpellDescriptionLine(thisTooltip, &spellRow, a5, a7);

        if (a9 && !a7 && a16)
            AddTalentLearnText(thisTooltip, a9, a10, talentPrereq, a14, a15, 0, a8, a5, a12);

        AddEmbeddedItemBlock(thisTooltip, &spellRow);
    }

#if TOOLTIPID_PATCH
    AddSpellIDLine(thisTooltip, &spellRow);
#endif

    if (thisTooltip->padding3[77])
        sub_81A2C0(thisTooltip, &thisTooltip->padding3[77], 0, 0);

    CSimpleFrame::Show(thisTooltip);
    CalculateSize(thisTooltip);

    return result;
}

void CGTooltip::AddLine(CGTooltip* thisTooltip, char* str1, char* str2, uint32_t* color1, uint32_t* color2, int32_t a6)
{
    reinterpret_cast<void (__thiscall*)(CGTooltip*, char*, char*, uint32_t*, uint32_t*, int32_t)>(0x61FEC0)(thisTooltip, str1, str2, color1, color2, a6);
}

void CGTooltip::AddEmbeddedItemBlock(CGTooltip* thisTooltip, SpellRow* spellRow)
{
    if (!IsCreateItemSpell(spellRow))
        return;

    int32_t itemID = 0;

    for (int32_t i = 0; i < 3; i++)
    {
        if (spellRow->m_effectItemType[i])
        {
            itemID = spellRow->m_effectItemType[i];

            break;
        }
    }

    if (itemID)
    {
        reinterpret_cast<int (__thiscall*)(void*)>(0x50F590)(&thisTooltip->padding3[8]);

        int64_t dummy = 0;
        int64_t guid = 0;

        SetItemEx(thisTooltip, 0, itemID, &dummy, &guid, 0, 0, 0, 1, 0i64, 0, 0, 0, 0, 0, 0, 1);
    }
}

void CGTooltip::AddTalentLearnText(CGTooltip* thisTooltip, uint32_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9, int32_t a10)
{
    reinterpret_cast<void(__thiscall*)(CGTooltip*, uint32_t*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x622800)(thisTooltip, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

int32_t CGTooltip::AddTalentPrereqs(CGTooltip* thisTooltip, uint32_t* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*, uint32_t*, int32_t, int32_t, int32_t, int32_t)>(0x6224F0)(thisTooltip, a2, a3, a4, a5, a6);
}

int32_t CGTooltip::ClearTooltip(CGTooltip* thisTooltip)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*)>(0x61C620)(thisTooltip);
}

int32_t CGTooltip::GetDurationString(char* buffer, int32_t length, uint64_t cooldown, char* string, int32_t a5, int32_t a6, int32_t a7)
{
    return reinterpret_cast<int32_t (__cdecl*)(char*, int32_t, uint64_t, char*, int32_t, int32_t, int32_t)>(0x61A9E0)(buffer, length, cooldown, string, a5, a6, a7);
}

void CGTooltip::CalculateSize(CGTooltip* thisTooltip)
{
    reinterpret_cast<void (__thiscall*)(CGTooltip*)>(0x61CAF0)(thisTooltip);
}

int32_t CGTooltip::SetDummyItemTooltip(CGTooltip* thisTooltip)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*)>(0x623760)(thisTooltip);
}

int32_t CGTooltip::sub_81A2C0(CGTooltip* thisTooltip, int32_t* a2, int32_t a3, int32_t a4)
{
    return reinterpret_cast<int(__thiscall*)(CGTooltip*, int32_t*, int32_t, int32_t)>(0x81A2C0)(thisTooltip, a2, a3, a4);
}

void CGTooltip::AddCastTimeLine(CGTooltip* thisTooltip, SpellRow* spellRow, CGUnit* unit, int32_t a4, int32_t a5, int32_t a6)
{
    bool skip = false;
    char bufferLeft[128] = { 0 };
    char bufferRight[128] = { 0 };
    int32_t categoryRecoveryTime = spellRow->m_categoryRecoveryTime;
    int32_t recoveryTime = spellRow->m_recoveryTime;

    Spell::ModifySpellValueInt(spellRow, &recoveryTime, 11);
    Spell::sub_7FEF60(&categoryRecoveryTime, spellRow, 0);

    if (recoveryTime <= categoryRecoveryTime)
        recoveryTime = categoryRecoveryTime;

    int32_t castTime = Spell::GetCastTime(spellRow, a5, a6, 1);

#if SPELLATTRIBUTESEXTENDED_DBC
    SpellAttributesExtendedRow spellAttributesExtendedRow{};

    sDC.GetSpellAttributesExtendedRow(spellAttributesExtendedRow, spellRow->m_ID);

    bool treatAsInstant = castTime <= 250 ? spellAttributesExtendedRow.HasCustomAttribute0(SPELL_ATTR0_CU_LOW_CASTTIME_TREAT_AS_INSTANT) : spellAttributesExtendedRow.HasCustomAttribute0(SPELL_ATTR0_CU_TREAT_AS_INSTANT);

    if (treatAsInstant)
        castTime = 0;
#endif

    if (castTime > 0)
    {
        SStr::Printf(bufferLeft, 128, FrameScript::GetText(castTime < 60000 ? "SPELL_CAST_TIME_SEC" : "SPELL_CAST_TIME_MIN", -1, 0), static_cast<float>(castTime) / (castTime < 60000 ? 1000.f : 60000.f));

        skip = true;
    }

    if ((spellRow->m_attributesEx & (SPELL_ATTR1_CHANNELED_1 | SPELL_ATTR1_CHANNELED_2)) && !skip)
    {
        SStr::Printf(bufferLeft, 128, FrameScript::GetText("SPELL_CAST_CHANNELED", -1, 0));

        skip = true;
    }

    if (castTime <= 0 && !skip)
    {
        SStr::Printf(bufferLeft, 128, FrameScript::GetText("SPELL_CAST_TIME_INSTANT", -1, 0));

        skip = true;
    }

    if (!skip)
    {
        if (spellRow->m_attributes & (SPELL_ATTR0_ON_NEXT_SWING | SPELL_ATTR0_ON_NEXT_SWING_2))
            SStr::Printf(bufferLeft, 128, FrameScript::GetText("SPELL_ON_NEXT_SWING", -1, 0));
        else if (spellRow->m_attributes & SPELL_ATTR0_REQ_AMMO)
            SStr::Printf(bufferLeft, 128, FrameScript::GetText("SPELL_ON_NEXT_RANGED", -1, 0));
        else
        {
            if (!spellRow->m_powerType && Spell::GetPowerCost(spellRow, unit) > 0)
                SStr::Printf(bufferLeft, 128, FrameScript::GetText("SPELL_CAST_TIME_INSTANT", -1, 0));
            else
                SStr::Printf(bufferLeft, 128, FrameScript::GetText("SPELL_CAST_TIME_INSTANT_NO_MANA", -1, 0));
        }
    }

    if (recoveryTime > 0 && !(spellRow->m_attributesExF & SPELL_ATTR6_DONT_DISPLAY_COOLDOWN))
        SStr::Printf(bufferRight, 128, FrameScript::GetText(recoveryTime < 60000 ? "SPELL_RECAST_TIME_SEC" : "SPELL_RECAST_TIME_MIN", -1, 0), static_cast<float>(recoveryTime) / (recoveryTime < 60000 ? 1000.f : 60000.f));

    AddLine(thisTooltip, bufferLeft, bufferRight, &sTextWhite, &sTextWhite, 0);
}

int32_t CGTooltip::AddCooldownLine(CGTooltip* thisTooltip, int32_t cooldown)
{
    int32_t result = 0;

    if (cooldown)
    {
        char buffer[128] = { 0 };

        GetDurationString(buffer, 128, cooldown, "ITEM_COOLDOWN_TIME", 0, 1, 0);
        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);

        result = 1;
    }

    return result;
}

void CGTooltip::AddDrainAllPowerLine(CGTooltip* thisTooltip, SpellRow* spellRow)
{
    bool hide = false;
#if SPELLATTRIBUTESEXTENDED_DBC
    SpellAttributesExtendedRow spellAttributesExtendedRow{};

    sDC.GetSpellAttributesExtendedRow(spellAttributesExtendedRow, spellRow->m_ID);

    hide = spellAttributesExtendedRow.HasCustomAttribute0(SPELL_ATTR0_CU_DO_NOT_DISPLAY_POWER_COST);
#endif

    if ((spellRow->m_attributesEx & SPELL_ATTR1_DRAIN_ALL_POWER) && !hide)
    {
        char buffer[128] = { 0 };
        char* powerCostStr = "SPELL_USE_ALL_HEALTH";
        char* powerCostStrTable[] = { "SPELL_USE_ALL_MANA", "SPELL_USE_ALL_RAGE", "SPELL_USE_ALL_FOCUS", "SPELL_USE_ALL_ENERGY", "SPELL_USE_ALL_HAPPINESS", "SPELL_USE_ALL_RUNE", /*"SPELL_USE_ALL_RUNIC_POWER"*/nullptr };

        PowerDisplayRow* powerDisplayRow = nullptr;

        if (DBClient::IsValidIndex(g_powerDisplayDB, spellRow->m_powerDisplayID))
            powerDisplayRow = reinterpret_cast<PowerDisplayRow*>(DBClient::GetRow(&g_powerDisplayDB->m_vtable2, spellRow->m_powerDisplayID));

        if (powerDisplayRow)
            SStr::Printf(buffer, 128, FrameScript::GetText("SPELL_USE_ALL_POWER_DISPLAY", -1, 0), FrameScript::GetText(powerDisplayRow->m_globalStringBaseTag, -1, 0));
        else
        {
            if (spellRow->m_powerType > -1 && spellRow->m_powerType <= 6)
                powerCostStr = powerCostStrTable[spellRow->m_powerType];

            SStr::Printf(buffer, 128, FrameScript::GetText(powerCostStr, -1, 0));
        }

        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);
    }
}

void CGTooltip::AddPowerAndRangeLines(CGTooltip* thisTooltip, char* powerLine, CGUnit* unit, SpellRow* spellRow, bool displayRange)
{
    if (!displayRange)
        AddLine(thisTooltip, powerLine, nullptr, &sTextWhite, &sTextWhite, 0);
    else
    {
        char buffer[128] = { 0 };
        char format[32] = { 0 };

        if (Spell::UsesMeleeRange(spellRow) && !Spell::IsModifiedStat(spellRow, 5))
        {
            SStr::Printf(buffer, 128, FrameScript::GetText("MELEE_RANGE", -1, 0));
            AddLine(thisTooltip, powerLine, buffer, &sTextWhite, &sTextWhite, 0);

            return;
        }

        float minRange0 = 0.f;
        float maxRange0 = 0.f;
        float minRange1 = 0.f;
        float maxRange1 = 0.f;

        Spell::GetMinMaxRange(unit, spellRow, &minRange0, &maxRange0, 0, 0.f);
        Spell::GetMinMaxRange(unit, spellRow, &minRange1, &maxRange1, 1, 0.f);

        if (Spell::UsesDefaultMinRange(spellRow))
        {
            Spell::GetDefaultMinRange(spellRow, &minRange0);
            Spell::GetDefaultMinRange(spellRow, &minRange1);
        }

        if ((minRange0 == minRange1) && (maxRange0 == maxRange1))
        {
            if (maxRange0 > 0.f)
            {
                if (maxRange0 < 50000.f)
                {
                    if (minRange0 <= 0.f)
                        SStr::Printf(format, 32, "%d", static_cast<int32_t>(maxRange0));
                    else
                        SStr::Printf(format, 32, "%d-%d", static_cast<int32_t>(minRange0), static_cast<int32_t>(maxRange0));

                    SStr::Printf(buffer, 128, FrameScript::GetText("SPELL_RANGE", -1, 0), format);
                }
                else
                    SStr::Printf(buffer, 128, FrameScript::GetText("SPELL_RANGE_UNLIMITED", -1, 0));
            }

            AddLine(thisTooltip, !*powerLine ? buffer : powerLine, !*powerLine ? nullptr : buffer, &sTextWhite, &sTextWhite, 0);

            return;
        }

        if (maxRange0 > 0.f)
        {
            if (maxRange0 < 50000.f)
            {
                if (minRange0 <= 0.f)
                    SStr::Printf(format, 32, "%d", static_cast<int32_t>(maxRange0));
                else
                    SStr::Printf(format, 32, "%d-%d", static_cast<int32_t>(minRange0), static_cast<int32_t>(maxRange0));

                // TODO: figure out why does it shit itself with those varargs
                // SStr::Printf(buffer, 128, FrameScript::GetText("SPELL_RANGE_DUAL", -1, 0), FrameScript::GetText("ENEMY", -1, 0), format);
                // direct address call somehow works without any hiccups
                reinterpret_cast<int32_t(__cdecl*)(char*, uint32_t, char*, ...)>(0x76F070)(buffer, 128, FrameScript::GetText("SPELL_RANGE_DUAL", -1, 0), FrameScript::GetText("ENEMY", -1, 0), format);
            }
            else
                SStr::Printf(buffer, 128, FrameScript::GetText("SPELL_RANGE_UNLIMITED", -1, 0));
        }

        AddLine(thisTooltip, !*powerLine ? buffer : " ", !*powerLine ? nullptr : buffer, &sTextWhite, &sTextWhite, 0);

        if (maxRange1 > 0.f)
        {
            if (maxRange1 < 50000.f)
            {
                if (minRange1 <= 0.f)
                    SStr::Printf(format, 32, "%d", static_cast<int32_t>(maxRange1));
                else
                    SStr::Printf(format, 32, "%d-%d", static_cast<int32_t>(minRange1), static_cast<int32_t>(maxRange1));

                // ditto
                // SStr::Printf(buffer, 128, FrameScript::GetText("SPELL_RANGE_DUAL", -1, 0), FrameScript::GetText("FRIENDLY", -1, 0), format);
                reinterpret_cast<int32_t(__cdecl*)(char*, uint32_t, char*, ...)>(0x76F070)(buffer, 128, FrameScript::GetText("SPELL_RANGE_DUAL", -1, 0), FrameScript::GetText("FRIENDLY", -1, 0), format);
            }
            else
                SStr::Printf(buffer, 128, FrameScript::GetText("SPELL_RANGE_UNLIMITED", -1, 0));
        }

        AddLine(thisTooltip, !*powerLine ? buffer : powerLine, !*powerLine ? nullptr : buffer, &sTextWhite, &sTextWhite, 0);
    }
}

void CGTooltip::AddReagentsLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, int32_t a4, int32_t a5)
{
    if (!a4 && reinterpret_cast<bool (__cdecl*)(CGPlayer*, SpellRow*)>(0x800D60)(player, spellRow));
    {
        bool isFirst = true;
        bool smth = true;
        char buffer[4096] = { 0 };
        char format[128] = { 0 };

        for (int32_t i = 0; i < 8; i++)
        {
            int32_t reagentID = spellRow->m_reagent[i];

            if (reagentID <= 0)
                continue;

            int64_t guid = spellRow->m_ID & 0x1FE0000000000000;
            DBItemCache* infoBlock = DBItemCache::GetInfoBlockByID(g_itemDBCache, reagentID, &guid, reinterpret_cast<void (__cdecl*)(CGTooltip*, bool)>(0x61DD60), thisTooltip, 1);

            if (!infoBlock)
            {
                (*thisTooltip->padding3)++;

                continue;
            }

            if (isFirst)
            {
                isFirst = false;

                SStr::Copy(buffer, FrameScript::GetText("SPELL_REAGENTS", -1, 0), 4096);
            }
            else
                SStr::Append(buffer, ", ", 4096);

            char* name = infoBlock->m_name;

            if (spellRow->m_reagentCount[i] <= 1)
                SStr::Copy(format, name, 128);
            else
                SStr::Printf(format, 128, "%s (%d)", name, spellRow->m_reagentCount[i]);

            bool result = CGBag::GetItemTypeCount(reinterpret_cast<CGBag*>(&player->m_padding0x100C[569]), spellRow->m_reagent[i], 0) >= spellRow->m_reagentCount[i];

            if (!result)
            {
                SStr::Append(buffer, sStringRed, 4096);

                smth = false;
            }
            SStr::Append(buffer, format, 4096);

            if (!result)
                SStr::Append(buffer, "|r", 4096);
        }

        if (!isFirst && (!smth || !a5))
            AddLine(thisTooltip, buffer, 0, &sTextWhite, &sTextWhite, 1);
    }
}

void CGTooltip::AddRequiredFactionLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, int32_t a3)
{
    if (spellRow->m_minFactionID)
    {
        int32_t factionStanding = CGReputationInfo::GetFactionStanding(spellRow->m_minFactionID);
        bool meetsRequirement = factionStanding >= (reinterpret_cast<int32_t*>(0xA2D2FC))[spellRow->m_minFactionID];

        if (factionStanding < (reinterpret_cast<int32_t*>(0xA2D2FC))[spellRow->m_minFactionID] || !a3)
        {
            char buffer[128] = { 0 };
            char format[128] = { 0 };

            FactionRow* factionRow = nullptr;

            if (DBClient::IsValidIndex(g_factionDB, spellRow->m_minFactionID))
                factionRow = reinterpret_cast<FactionRow*>(DBClient::GetRow(&g_factionDB->m_vtable2, spellRow->m_minFactionID));

            SStr::Printf(format, 128, "FACTION_STANDING_LABEL%d", spellRow->m_minReputation + 1);
            SStr::Printf(buffer, 128, FrameScript::GetText("ITEM_REQ_REPUTATION", -1, 0), factionRow ? factionRow->m_name_lang : "UNKNOWN", CGUnit::GetFrameScriptText(player, format, -1));
            AddLine(thisTooltip, buffer, nullptr, meetsRequirement ? &sTextWhite : &sTextRed, meetsRequirement ? &sTextWhite : &sTextRed, 0);
        }
    }
}

void CGTooltip::AddRequiredItemLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, int32_t a4, int32_t a5)
{
    if ((spellRow->m_targets & 0x10) || (spellRow->m_equippedItemClass & 0x80000000) || !spellRow->m_equippedItemSubclass)
        return;

    bool isFirst = true;
    bool meetsRequirements = true;
    bool useItemClassMask = false;
    char buffer[512] = { 0 };
    char format[512] = { 0 };
    int32_t requirementFlags = -1;

    for (int32_t i = 0; i < g_itemSubClassMaskDB->m_numRows; i++)
    {
        ItemSubClassMaskRow* itemSubClassMaskRow = reinterpret_cast<ItemSubClassMaskRow*>(DBClient::GetRow(g_itemSubClassMaskDB, i));

        if (itemSubClassMaskRow && spellRow->m_equippedItemClass == itemSubClassMaskRow->m_classID && spellRow->m_equippedItemSubclass == itemSubClassMaskRow->m_mask)
        {
            SStr::Copy(format, itemSubClassMaskRow->m_name_lang, 512);

            useItemClassMask = true;

            break;
        }
    }

    if (spellRow->m_attributesExC & SPELL_ATTR3_MAIN_HAND)
        requirementFlags = 0x8000;
    else if (spellRow->m_attributesExC & SPELL_ATTR3_REQ_OFFHAND)
        requirementFlags = 0x10000;

    if (!CGUnit::EquippedItemMeetsSpellRequirements(player, spellRow, requirementFlags) || (((spellRow->m_attributesExC & (SPELL_ATTR3_REQ_OFFHAND | SPELL_ATTR3_MAIN_HAND)) == 0x1000400) && !CGUnit::EquippedItemMeetsSpellRequirements(player, spellRow, 0x10000)))
        meetsRequirements = false;

    for (int32_t j = 0; j < g_itemSubClassDB->m_numRows; j++)
    {
        ItemSubClassRow* itemSubClassRow = reinterpret_cast<ItemSubClassRow*>(DBClient::GetRow(g_itemSubClassDB, j));

        if (itemSubClassRow)
        {
            if (spellRow->m_equippedItemClass == itemSubClassRow->m_classID && (spellRow->m_equippedItemSubclass & (1 << itemSubClassRow->m_subClassID)) && !useItemClassMask)
            {
                if (isFirst)
                    isFirst = false;
                else
                    SStr::Append(format, ", ", 512);

                SStr::Append(format, (itemSubClassRow->m_verboseName_lang && *itemSubClassRow->m_verboseName_lang) ? itemSubClassRow->m_verboseName_lang : itemSubClassRow->m_displayName_lang, 512);
            }
        }
    }

    if (a5)
        meetsRequirements = true;

    if (*format && (!meetsRequirements && !a4))
    {
        char* equipped = (!meetsRequirements && a4) ? "SPELL_EQUIPPED_ITEM_NOSPACE" : "SPELL_EQUIPPED_ITEM";

        SStr::Printf(buffer, 512, FrameScript::GetText(equipped, -1, 0), format);
        AddLine(thisTooltip, buffer, nullptr, meetsRequirements ? &sTextWhite : &sTextRed, meetsRequirements ? &sTextWhite : &sTextRed, 1);
    }
}

void CGTooltip::AddRequiredLevelLine(CGTooltip* thisTooltip, CGUnit* unit, SpellRow* spellRow, bool a4)
{
    if (a4 && unit && unit->GetLevel() < spellRow->m_baseLevel)
    {
        char buffer[128] = { 0 };

        SStr::Printf(buffer, 128, FrameScript::GetText("ITEM_MIN_LEVEL", -1, 0), spellRow->m_baseLevel);
        AddLine(thisTooltip, buffer, nullptr, &sTextRed, &sTextRed, 0);
    }
}

void CGTooltip::AddRequiredShapeshiftFormLine(CGTooltip* thisTooltip, CGUnit* unit, SpellRow* spellRow, int32_t a4)
{
    if (!spellRow->m_shapeshiftMask[0] && !spellRow->m_shapeshiftMask[1])
        return;

    bool isUsable = false;
    bool isFirst = true;
    bool needsShapeshift = !(spellRow->m_attributesExB & SPELL_ATTR2_NOT_NEED_SHAPESHIFT);
    char format[512] = { 0 };
    char* form = a4 ? "SPELL_REQUIRED_FORM_NOSPACE" : "SPELL_REQUIRED_FORM";

    if (needsShapeshift)
    {
        int32_t numRows = g_spellShapeshiftFormDB->m_numRows > 64 ? 64 : g_spellShapeshiftFormDB->m_numRows;

        if (!numRows)
            return;

        for (int32_t i = 0; i < numRows; i++)
        {
            if (Spell::UsableInShapeshiftForm(spellRow, i))
            {
                SpellShapeshiftFormRow* shapeshiftRow = reinterpret_cast<SpellShapeshiftFormRow*>(DBClient::GetRow(&g_spellShapeshiftFormDB->m_vtable2, i + 1));

                if (!shapeshiftRow || !shapeshiftRow->m_name_lang || !*shapeshiftRow->m_name_lang)
                    continue;

                if (isFirst)
                {
                    SStr::Copy(format, shapeshiftRow->m_name_lang, 512);

                    isFirst = false;
                }
                else
                {
                    SStr::Append(format, ", ", 512);
                    SStr::Append(format, shapeshiftRow->m_name_lang, 512);
                }
            }
        }
    }

    int32_t shapeshiftForm = CGUnit::GetShapeshiftFormID(unit);

    if (!unit || Spell::UsableInShapeshiftForm(spellRow, shapeshiftForm - 1) || !needsShapeshift && !CGUnit::IsShapeshifted(unit) || CGUnit::HasAuraMatchingSpellClass(unit, SPELL_AURA_MOD_IGNORE_SHAPESHIFT, spellRow))
        isUsable = true;

    if (isFirst)
        return;

    if (!isUsable || !a4)
    {
        char buffer[512] = { 0 };
        
        SStr::Printf(buffer, 512, FrameScript::GetText(form, -1, 0), format);
        AddLine(thisTooltip, buffer, nullptr, isUsable ? &sTextWhite : &sTextRed, isUsable ? &sTextWhite : &sTextRed, 0);
    }
}

int32_t CGTooltip::AddSpecialActionLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, bool a4)
{
    char buffer[128] = { 0 };
    char* string = nullptr;
    float amount = 0.f;
    int32_t effect = spellRow->m_effect[0];
    int32_t result = 0;

    switch (effect)
    {
        case SPELL_EFFECT_DODGE:
            amount = player->m_playerData->m_dodgePct;
            string = "CHANCE_TO_DODGE";
            break;
        case SPELL_EFFECT_PARRY:
            amount = player->m_playerData->m_parryPct;
            string = "CHANCE_TO_PARRY";
            break;
        case SPELL_EFFECT_BLOCK:
            amount = player->m_playerData->m_blockPct;
            string = "CHANCE_TO_BLOCK";
            break;
        case SPELL_EFFECT_ATTACK:
            amount = player->m_playerData->m_critPct;
            string = "CHANCE_TO_CRIT";
            break;
        default:
            break;
    }

    if ((effect == SPELL_EFFECT_ATTACK || (a4 && (effect == SPELL_EFFECT_DODGE || effect == SPELL_EFFECT_PARRY || effect == SPELL_EFFECT_BLOCK))) && string)
    {
        SStr::Printf(buffer, 128, FrameScript::GetText(string, -1, 0), amount);
        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);

        result = 1;
    }

    return result;
}

void CGTooltip::AddSpellDescriptionLine(CGTooltip* thisTooltip, SpellRow* spellRow, int32_t a3, int32_t a4)
{
    if (spellRow->m_description_lang && *spellRow->m_description_lang)
    {
        char spellDescription[2048] = { 0 };

        Spell::GetDescription(spellRow, spellDescription, 2048, a3, a4, 0, 0, 1, 0);
        AddLine(thisTooltip, spellDescription, nullptr, &sTextYellow, &sTextYellow, 1);
    }
}

void CGTooltip::AddSpellIDLine(CGTooltip* thisTooltip, SpellRow* spellRow)
{
    char buffer[32] = { 0 };

    SStr::Printf(buffer, 32, "%d", spellRow->m_ID);
    AddLine(thisTooltip, "Spell ID:", buffer, &sTextGrey, &sTextGrey, 0);
}

void CGTooltip::AddTalentRankLine(CGTooltip* thisTooltip, int32_t a2, int32_t a3)
{
    if (a3 >= 0)
    {
        char buffer[128] = { 0 };

        SStr::Printf(buffer, 128, FrameScript::GetText("TOOLTIP_TALENT_RANK", -1, 0), a2 + 1, a3 + 1);
        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);
    }
}

void CGTooltip::AddTalentNextRankLine(CGTooltip* thisTooltip)
{
    char buffer[128] = { 0 };

    SStr::Printf(buffer, 128, "\n%s", FrameScript::GetText("TOOLTIP_TALENT_NEXT_RANK", -1, 0));
    CGTooltip::AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);
}

void CGTooltip::AddTotemsLine(CGTooltip* thisTooltip, CGPlayer* player, SpellRow* spellRow, int32_t a4, int32_t a5)
{
    if (a5)
        return;

    bool isFirst = true;
    bool smth = true;
    char buffer[4096] = { 0 };
    char format[128] = { 0 };

    for (int32_t i = 0; i < 2; i++)
    {
        int32_t totemID = spellRow->m_totem[i];

        if (!totemID)
            continue;

        int64_t guid = spellRow->m_ID & 0x1FE0000000000000;
        DBItemCache* infoBlock = DBItemCache::GetInfoBlockByID(g_itemDBCache, totemID, &guid, reinterpret_cast<void (__cdecl*)(CGTooltip*, bool)>(0x61DD60), thisTooltip, 1);

        if (!infoBlock)
        {
            (*thisTooltip->padding3)++;

            continue;
        }

        if (isFirst)
        {
            isFirst = false;

            SStr::Copy(buffer, FrameScript::GetText("SPELL_TOTEMS", -1, 0), 4096);
        }
        else
            SStr::Append(buffer, ", ", 4096);

        int32_t temp = CGBag::FindItemOfType(reinterpret_cast<CGBag*>(&player->m_padding0x100C[569]), spellRow->m_totem[i], 0);

        if (!temp)
        {
            SStr::Append(buffer, sStringRed, 4096);

            smth = false;
        }

        SStr::Append(buffer, infoBlock->m_name, 4096);

        if (!temp)
            SStr::Append(buffer, "|r", 4096);
    }

    for (int32_t j = 0; j < 2; j++)
    {
        int32_t totemCategory = spellRow->m_requiredTotemCategoryID[j];

        if (!DBClient::IsValidIndex(g_totemCategoryDB, totemCategory))
            continue;
        
        TotemCategoryRow* totemCategoryRow = reinterpret_cast<TotemCategoryRow*>(DBClient::GetRow(&g_totemCategoryDB->m_vtable2, totemCategory));

        if (!totemCategoryRow)
            continue;

        if (isFirst)
        {
            isFirst = false;

            SStr::Copy(buffer, FrameScript::GetText("SPELL_TOTEMS", -1, 0), 4096);
        }
        else
            SStr::Append(buffer, ", ", 4096);

        bool result = CGBag::FindTotemOfCategory(totemCategory, 0);

        if (!result)
        {
            SStr::Append(buffer, sStringRed, 4096);

            smth = false;
        }

        SStr::Append(buffer, totemCategoryRow->m_nameLang, 4096);

        if (!result)
            SStr::Append(buffer, "|r", 4096);
    }

    if (!isFirst || (!smth || !a4))
        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);
}

void CGTooltip::AddTradeSkillLine(CGTooltip* thisTooltip, CGPlayer* activePlayer, SpellRow* spellRow, int32_t spellId)
{
    SkillLineAbilityRow* skillLineAbilityRow = ClientServices::SpellTableLookupAbility(activePlayer->GetRace(), activePlayer->GetClass(), spellId);

    if (skillLineAbilityRow)
    {
        int32_t skillLine = skillLineAbilityRow->m_skillLine;

        if (DBClient::IsValidIndex(g_skillLineDB, skillLine))
        {
            SkillLineRow* skillLineRow = reinterpret_cast<SkillLineRow*>(DBClient::GetRow(&g_skillLineDB->m_vtable2, skillLine));

            if (skillLineRow)
            {
                char buffer[128] = { 0 };

                SStr::Printf(buffer, 128, "%s: %s", skillLineRow->m_displayName_lang, spellRow->m_name_lang);
                CGTooltip::AddLine(thisTooltip, buffer, nullptr, &sTextYellow, &sTextYellow, 0);
            }
        }
    }
}

void CGTooltip::AppendPowerCostLine(CGTooltip* thisTooltip, char* buffer, CGUnit* unit, SpellRow* spellRow)
{
    bool hide = false;
#if SPELLATTRIBUTESEXTENDED_DBC
    SpellAttributesExtendedRow spellAttributesExtendedRow{};

    sDC.GetSpellAttributesExtendedRow(spellAttributesExtendedRow, spellRow->m_ID);

    hide = spellAttributesExtendedRow.HasCustomAttribute0(SPELL_ATTR0_CU_DO_NOT_DISPLAY_POWER_COST);
#endif

    if (hide)
        return;

    char* powerCostStr = "HEALTH_COST";
    char* powerCostStrTable[] = { "MANA_COST", "RAGE_COST", "FOCUS_COST", "ENERGY_COST", "HAPPINESS_COST", "RUNE_COST", "RUNIC_POWER_COST" };
    int32_t powerCost = Spell::GetPowerCost(spellRow, unit) / ClientServices::GetPowerDivisor(spellRow->m_powerType);
    int32_t powerCostPerSecond = Spell::GetPowerCostPerSecond(spellRow, unit) / ClientServices::GetPowerDivisor(spellRow->m_powerType);
    PowerDisplayRow* powerDisplayRow = nullptr;

    if (DBClient::IsValidIndex(g_powerDisplayDB, spellRow->m_powerDisplayID))
        powerDisplayRow = reinterpret_cast<PowerDisplayRow*>(DBClient::GetRow(&g_powerDisplayDB->m_vtable2, spellRow->m_powerDisplayID));

    if (spellRow->m_powerType > -1 && spellRow->m_powerType <= 6)
        powerCostStr = powerCostStrTable[spellRow->m_powerType];

    if (spellRow->m_powerType == 5)
        AppendRuneCostLine(thisTooltip, buffer, spellRow);
    else
    {
        char format[128] = { 0 };

        if (powerCost > 0 && powerCostPerSecond <= 0)
        {
            if (powerDisplayRow)
            {
                SStr::Copy(format, FrameScript::GetText(powerDisplayRow->m_globalStringBaseTag, 0, -1), 128);
                SStr::Printf(buffer, 128, FrameScript::GetText("POWER_DISPLAY_COST", -1, 0), powerCost, format);
            }
            else
            {
                SStr::Copy(format, FrameScript::GetText(powerCostStr, -1, 0), 128);
                SStr::Printf(buffer, 128, format, powerCost);
            }

            return;
        }
        else if (powerCost <= 0 && powerCostPerSecond <= 0)
            return;

        if (powerDisplayRow)
        {
            SStr::Copy(format, FrameScript::GetText(powerDisplayRow->m_globalStringBaseTag, 0, -1), 128);
            SStr::Printf(buffer, 128, FrameScript::GetText("POWER_DISPLAY_COST_PER_TIME", -1, 0), powerCost, format, powerCostPerSecond);
        }
        else
        {
            SStr::Printf(format, 128, "%s_PER_TIME", powerCostStr);
            SStr::Printf(buffer, 128, FrameScript::GetText(format, -1, 0), powerCost, powerCostPerSecond);
        }
    }
}

void CGTooltip::AppendRuneCostLine(CGTooltip* thisTooltip, char* buffer, SpellRow* spellRow)
{
    if (DBClient::IsValidIndex(g_spellRuneCostDB, spellRow->m_runeCostID))
    {
        SpellRuneCostRow* row = reinterpret_cast<SpellRuneCostRow*>(DBClient::GetRow(&g_spellRuneCostDB->m_vtable2, spellRow->m_runeCostID));

        if (row)
        {
            char* runeCostString[] = { "RUNE_COST_BLOOD", "RUNE_COST_UNHOLY", "RUNE_COST_FROST" };
            int32_t runeCostTable[] = { row->m_blood, row->m_unholy, row->m_frost };

            char format[128] = { 0 };

            for (int32_t i = 0; i < 3; i++)
            {
                if (runeCostTable[i])
                {
                    SStr::Printf(format, 128, FrameScript::GetText(runeCostString[i], -1, 0), runeCostTable[i]);
                    SStr::Append(buffer, format, 0x7FFFFFFF);
            
                    for (int32_t j = i + 1; j < 3; j++)
                    {
                        if (runeCostTable[j])
                        {
                            SStr::Append(buffer, " ", 0x7FFFFFFF);

                            break;
                        }
                    }
                }
            }

#if TOOLTIPDKRUNEEXT_PATCH
// Aleist3r: something I originally implemented for Duskhaven
// runic power column in dbc should, in fact, be int32_t but if I remember correctly
// it is defined as unsigned in the core; if you modify it to allow signed
// this addition will show consumed runic power amount if you set refunded value to negative in dbc
            if (row->m_runicPower < 0)
            {
                bool hasRuneCost = false;

                for (int32_t i = 0; i < 3; i++)
                {
                    if (runeCostTable[i] > 0)
                    {
                        hasRuneCost = true;

                        break;
                    }
                }

                if (hasRuneCost)
                    SStr::Append(buffer, " ", 0x7FFFFFFF);

                SStr::Printf(format, 128, FrameScript::GetText("RUNIC_POWER_COST", -1, 0), -row->m_runicPower / 10);
                SStr::Append(buffer, format, 0x7FFFFFFF);
            }
#endif
        }
    }
}

bool CGTooltip::IsCreateItemSpell(SpellRow* spellRow)
{
    bool result = false;

    if (spellRow->m_attributes & SPELL_ATTR0_TRADESPELL)
    {
        for (int32_t i = 0; i < 3; i++)
        {
            int32_t spellEffect = spellRow->m_effect[i];

            if (spellEffect == SPELL_EFFECT_CREATE_ITEM || spellEffect == SPELL_EFFECT_CREATE_RANDOM_ITEM || spellEffect == SPELL_EFFECT_CREATE_ITEM_2)
            {
                result = true;

                break;
            }
        }
    }

    return result;
}

bool CGTooltip::IsTradespell(SpellRow* spellRow)
{
    bool result = false;

    if (spellRow->m_attributes & SPELL_ATTR0_TRADESPELL)
        result = true;

    return result;
}

void CGTooltip::AddItemAreaAndMapLines(CGTooltip* thisTooltip, DBItemCache* itemCache)
{
    int32_t area = itemCache->m_area;
    int16_t map = static_cast<int16_t>(itemCache->m_map);

    if (area)
    {
        AreaTableRow* row = reinterpret_cast<AreaTableRow*>(DBClient::GetRow(&g_areaTableDB->m_vtable2, area));

        if (row)
            AddLine(thisTooltip, row->m_areaNameLang, nullptr, &sTextWhite, &sTextWhite, 0);
    }

#if ITEMTOOLTIPMAPLINE_FIX
    if (map > -1)
#else
    if (map)
#endif
    {
        MapRow* row = reinterpret_cast<MapRow*>(DBClient::GetRow(&g_mapDB->m_vtable2, map));

        if (row)
            AddLine(thisTooltip, row->m_mapName_lang, nullptr, &sTextWhite, &sTextWhite, 0);
    }
}

void CGTooltip::AddItemBondingLine(CGTooltip* thisTooltip, CGItem* item, DBItemCache* itemCache, int64_t* a4)
{
    bool isAccountBound = (itemCache->m_flagsAndFactions[0] & 0x8000000) != 0;
    bool skip = false;
    char buffer[4096] = { 0 };
    int32_t bonding = itemCache->m_bonding;

    if (item && CGItem::sub_708520(item))
    {
        if (bonding == 4)
        {
            skip = true;

            SStr::Copy(buffer, FrameScript::GetText("ITEM_BIND_QUEST", -1, 0), 4096);
        }
        else if (itemCache->m_class != ITEM_CLASS_MONEY)
        {
            skip = true;

            SStr::Copy(buffer, isAccountBound ? FrameScript::GetText("ITEM_ACCOUNTBOUND", -1, 0) : FrameScript::GetText("ITEM_SOULBOUND", -1, 0), 4096);
        }
    }

    if (!bonding)
    {
        if (!*buffer)
            return;

        skip = true;
    }

    if (!skip && ((itemCache->m_class != ITEM_CLASS_MONEY) || (*a4 == *reinterpret_cast<int64_t*>(0xBFA8D8))))
    {
        if (isAccountBound)
            SStr::Copy(buffer, FrameScript::GetText("ITEM_ACCOUNTBOUND", -1, 0), 4096);
        else
        {
            switch (bonding)
            {
                case 1:
                    SStr::Copy(buffer, FrameScript::GetText("ITEM_BIND_ON_PICKUP", -1, 0), 4096);
                    break;
                case 2:
                    SStr::Copy(buffer, FrameScript::GetText("ITEM_BIND_ON_EQUIP", -1, 0), 4096);
                    break;
                case 3:
                    SStr::Copy(buffer, FrameScript::GetText("ITEM_BIND_ON_USE", -1, 0), 4096);
                    break;
                case 4:
                    SStr::Copy(buffer, FrameScript::GetText("ITEM_BIND_QUEST", -1, 0), 4096);
                    break;
                default:
                    return;
            }
        }
    }

    if (*buffer)
        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);
}

void CGTooltip::AddItemConjuredLine(CGTooltip* thisTooltip, DBItemCache* itemCache)
{
    if (!(itemCache->m_flagsAndFactions[0] & 2))
        return;

    AddLine(thisTooltip, FrameScript::GetText("ITEM_CONJURED", -1, 0), nullptr, &sTextWhite, &sTextWhite, 0);
}

bool CGTooltip::AddItemGemPropertyLine(CGTooltip* thisTooltip, int32_t gemProperties, int32_t a3)
{
    bool result = false;

    if (a3)
    {
        if (gemProperties)
        {
            AddLine(thisTooltip, FrameScript::GetText("DESTROY_GEM", -1, 0), nullptr, &sTextRed, &sTextRed, 0);

            result = true;
        }
        else
            AddLine(thisTooltip, FrameScript::GetText("CURRENTLY_EQUIPPED", -1, 0), nullptr, &sTextGrey, &sTextGrey, 0);
    }

    return result;
}

void CGTooltip::AddItemIDLine(CGTooltip* thisTooltip, int32_t itemID)
{
    char buffer[32] = { 0 };

    SStr::Printf(buffer, 32, "%d", itemID);
    AddLine(thisTooltip, "Item ID:", buffer, &sTextGrey, &sTextGrey, 0);
}

void CGTooltip::AddItemLimitLines(CGTooltip* thisTooltip, DBItemCache* itemCache)
{
    if (itemCache->m_class == ITEM_CLASS_MONEY)
        return;

    if (itemCache->m_flagsAndFactions[0] & 0x80000)
        AddLine(thisTooltip, FrameScript::GetText("ITEM_UNIQUE_EQUIPPABLE", -1, 0), nullptr, &sTextWhite, &sTextWhite, 0);
    else
    {
        char buffer[4096] = { 0 };
        char format[4096] = { 0 };
        int32_t itemLimitCategory = itemCache->m_itemLimitCategory;
        int32_t maxCount = itemCache->m_maxCount;
        ItemLimitCategoryRow* row = reinterpret_cast<ItemLimitCategoryRow*>(DBClient::GetRow(&g_itemLimitCategoryDB->m_vtable2, itemLimitCategory));

        if (maxCount <= 0)
            if (row)
                SStr::Printf(buffer, 4096, (row->m_flags & 1) ? FrameScript::GetText("ITEM_LIMIT_CATEGORY_MULTIPLE", -1, 0) : FrameScript::GetText("ITEM_LIMIT_CATEGORY", -1, 0), row->m_name_lang, row->m_quantity);
        else
        {
            if (maxCount == 1)
                SStr::Printf(buffer, 4096, FrameScript::GetText("ITEM_UNIQUE", -1, 0));
            else
                SStr::Printf(buffer, 4096, FrameScript::GetText("ITEM_UNIQUE_MULTIPLE", -1, 0), maxCount);
        }

        if (*buffer)
            AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);
    }
}

void CGTooltip::AddItemNameAndQualityLines(CGTooltip* thisTooltip, int32_t itemID, int32_t a3, int32_t a4, int32_t a5, DBItemCache* itemCache, bool destroyed)
{
    char buffer[1024] = { 0 };
    char format[1024] = { 0 };

    CGItem::BuildItemName(buffer, 1024, itemID, a3);

    if (a5)
    {
        SStr::Copy(format, buffer, 1024);
        SStr::Printf(buffer, 1024, "/n%s", format);
    }

    if (a4)
    {
        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);

        return;
    }

    CVar* colorblindMode = CVar::Lookup("colorblindMode");
    uint32_t* color = destroyed ? &sTextGrey : sItemQualityColors[itemCache->m_quality];

    AddLine(thisTooltip, buffer, nullptr, color, color, 0);

    if (colorblindMode && colorblindMode->m_padding[12])
    {
        if (itemCache->m_flagsAndFactions[0] & 8)
        {
            AddLine(thisTooltip, FrameScript::GetText("ITEM_HEROIC_EPIC", -1, 0), nullptr, &sTextWhite, &sTextWhite, 0);

            return;
        }
        else
        {
            uint32_t quality = destroyed ? 0 : itemCache->m_quality;

            SStr::Printf(format, 1024, "ITEM_QUALITY%d_DESC", quality);
            AddLine(thisTooltip, FrameScript::GetText(format, -1, 0), nullptr, &sTextWhite, &sTextWhite, 0);
        }
    }
    else if (itemCache->m_flagsAndFactions[0] & 8)
        AddLine(thisTooltip, FrameScript::GetText("ITEM_HEROIC", -1, 0), nullptr, &sTextGreen, &sTextGreen, 0);
}

int32_t CGTooltip::AddItemPetitionLines(CGTooltip* thisTooltip, CGItem* item, DBItemCache* itemCache, int64_t* guid)
{
    if (!item)
        return 1;

    bool result = (CGItem::sub_707390(&item->m_vTable, 0) & 0x2000) != 0;

    if (!result)
        return 1;

    int32_t enchantID = item->m_itemData->m_enchantment[0].m_ID;

    DBPetitionCache* petitionCache = DBPetitionCache::GetInfoBlockByID(g_petitionDBCache, enchantID, guid, reinterpret_cast<void (__cdecl*)(CGTooltip*, bool)>(0x626650), thisTooltip, 1);

    if (!petitionCache)
        return 0;

    bool meetsRequirements = petitionCache->m_padding0x10[1259] != 0;
    char buffer[4096] = { 0 };

    SStr::Printf(buffer, 4096, meetsRequirements ? FrameScript::GetText("PETITION_TITLE", -1, 0) : FrameScript::GetText("GUILD_CHARTER_TITLE", -1, 0), petitionCache->m_padding0x10);
    AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 1);

    DBNameCache* nameCache = DBNameCache::GetRecord(g_nameDBCache, petitionCache->m_creatorGuid, petitionCache->m_creatorGuid, reinterpret_cast<void (__cdecl*)(CGTooltip*, bool)>(0x626650), thisTooltip, 1);

    if (nameCache)
    {
        SStr::Printf(buffer, 4096, meetsRequirements ? FrameScript::GetText("PETITION_CREATOR", -1, 0) : FrameScript::GetText("GUILD_CHARTER_CREATOR", -1, 0), nameCache->m_name);
        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);
    }

    int32_t count = CGItem::sub_61DC90(&item->m_vTable);

    if (count)
    {
        SStr::Printf(buffer, 4096, FrameScript::GetText("PETITION_NUM_SIGNATURES", count, 0), count);
        AddLine(thisTooltip, buffer, nullptr, &sTextWhite, &sTextWhite, 0);
    }

    if (itemCache->m_flagsAndFactions[0] & 0x2000)
        AddLine(thisTooltip, FrameScript::GetText("ITEM_SIGNABLE", -1, 0), nullptr, &sTextWhite, &sTextWhite, 0);

    return 1;
}

void CGTooltip::AddItemStartQuestLine(CGTooltip* thisTooltip, DBItemCache* itemCache)
{
    if (!itemCache->m_startQuestID)
        return;

    AddLine(thisTooltip, FrameScript::GetText("ITEM_STARTS_QUEST", -1, 0), nullptr, &sTextWhite, &sTextWhite, 0);
}

void CGTooltip::AppendItemSuffix(CGTooltip* thisTooltip, CGItem* item, int32_t* a3)
{
    int32_t property = thisTooltip->padding3[53];

    if (thisTooltip->padding3[62] && property)
    {
        *a3 = property;

        if (property <= 0)
        {
            ItemRandomSuffixRow* randomSuffixRow = reinterpret_cast<ItemRandomSuffixRow*>(DBClient::GetRow(&g_itemRandomSuffixDB->m_vtable2, -property));

            if (randomSuffixRow)
            {
                thisTooltip->padding3[16] = randomSuffixRow->m_enchantment[0] > 0 ? randomSuffixRow->m_enchantment[0] : 0;
                thisTooltip->padding3[17] = randomSuffixRow->m_enchantment[1] > 0 ? randomSuffixRow->m_enchantment[1] : 0;
                thisTooltip->padding3[18] = randomSuffixRow->m_enchantment[2] > 0 ? randomSuffixRow->m_enchantment[2] : 0;
                thisTooltip->padding3[19] = randomSuffixRow->m_enchantment[3] > 0 ? randomSuffixRow->m_enchantment[3] : 0;
                thisTooltip->padding3[20] = randomSuffixRow->m_enchantment[4] > 0 ? randomSuffixRow->m_enchantment[4] : 0;
            }
        }
        else
        {
            ItemRandomPropertiesRow* randomPropertiesRow = reinterpret_cast<ItemRandomPropertiesRow*>(DBClient::GetRow(&g_itemRandomPropertiesDB->m_vtable2, property));

            if (randomPropertiesRow)
            {
                thisTooltip->padding3[16] = randomPropertiesRow->m_enchantment[0] > 0 ? randomPropertiesRow->m_enchantment[0] : 0;
                thisTooltip->padding3[17] = randomPropertiesRow->m_enchantment[1] > 0 ? randomPropertiesRow->m_enchantment[1] : 0;
                thisTooltip->padding3[18] = randomPropertiesRow->m_enchantment[2] > 0 ? randomPropertiesRow->m_enchantment[2] : 0;
                thisTooltip->padding3[19] = randomPropertiesRow->m_enchantment[3] > 0 ? randomPropertiesRow->m_enchantment[3] : 0;
                thisTooltip->padding3[20] = randomPropertiesRow->m_enchantment[4] > 0 ? randomPropertiesRow->m_enchantment[4] : 0;
            }
        }
    }
    else if (item)
        *a3 = item->m_itemData->m_randomPropertySeed;
}

int32_t CSimpleFrame::Hide(void* thisFrame)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*)>(0x48F620)(thisFrame);
}

int32_t CSimpleFrame::Show(void* thisTooltip)
{
    return reinterpret_cast<int(__thiscall*)(void*)>(0x48F660)(thisTooltip);
}
