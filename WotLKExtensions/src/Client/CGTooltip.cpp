#include <Client/CFormula.hpp>
#include <Client/CGTooltip.hpp>
#include <Client/ClientServices.hpp>
#include <Client/DBClient.hpp>
#include <Client/FrameScript.hpp>
#include <Client/Spell.hpp>
#include <Client/SStr.hpp>
#include <Data/DBCAddresses.hpp>
#include <Data/DBItemCache.hpp>
#include <Data/Enums.hpp>
#include <GameObjects/CGBag.hpp>
#include <GameObjects/CGPetInfo.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Logger.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>

void CGTooltip::ApplyPatches()
{
#if SPELLDESCRIPTIONEXT_PATCH
    std::vector<const char*>& data = DataContainer::GetInstance().GetSpellVariableData();

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
}

int32_t __fastcall CGTooltip::SetItemEx(CGTooltip* thisTooltip, int32_t unused, int32_t itemID, int32_t* a4, int64_t* guid, int32_t a6, int32_t a7, int32_t a8, int32_t a9, uint64_t a10, int32_t a11, int32_t a12, int32_t a13, int32_t a14, int32_t a15, int32_t a16, int32_t a17)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*, int32_t, int32_t*, int64_t*, int32_t, int32_t, int32_t, int32_t, uint64_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x6277F0)(thisTooltip, itemID, a4, guid, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17);
}

int32_t __fastcall CGTooltip::SetSpellEx(CGTooltip* thisTooltip, int32_t unused, int32_t spellId, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, uint32_t* a9, int32_t a10, int32_t a11, int32_t a12, int32_t a13, int32_t a14, int32_t a15, int32_t a16)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x6238A0)(thisTooltip, spellId, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);

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

        thisTooltip->padding[217] = spellId;
        thisTooltip->padding[242] = 0;
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
    AddRequiredItemLine(thisTooltip, &spellRow);

    // TODO

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

    if (thisTooltip->padding[319])
        sub_81A2C0(thisTooltip, &thisTooltip->padding[319], 0, 0);

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
        reinterpret_cast<int(__thiscall*)(void*)>(0x50F590)(&thisTooltip->padding[250]);

        int32_t dummy = 0;
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
    if (spellRow->m_attributesEx & SPELL_ATTR1_DRAIN_ALL_POWER)
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

                // TODO: figure out why it does shit itself with those varargs
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
            DBItemCache* infoBlock = DBItemCache::GetInfoBlockByID(reinterpret_cast<DBItemCache*>(0xC5D828), reagentID, &guid, reinterpret_cast<void (__cdecl*)(CGTooltip*, bool)>(0x61DD60), thisTooltip, 1);

            if (!infoBlock)
            {
                thisTooltip->padding[242]++;

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

void CGTooltip::AddRequiredItemLine(CGTooltip* thisTooltip, SpellRow* spellRow)
{
    if (!(spellRow->m_targets & 0x10) && !(spellRow->m_equippedItemClass & 0x80000000) && spellRow->m_equippedItemSubclass)
    {

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

    if (effect == SPELL_EFFECT_ATTACK || (a4 && (effect == SPELL_EFFECT_DODGE || effect == SPELL_EFFECT_PARRY || effect == SPELL_EFFECT_BLOCK)))
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
        DBItemCache* infoBlock = DBItemCache::GetInfoBlockByID(reinterpret_cast<DBItemCache*>(0xC5D828), totemID, &guid, reinterpret_cast<void(__cdecl*)(CGTooltip*, bool)>(0x61DD60), thisTooltip, 1);

        if (!infoBlock)
        {
            thisTooltip->padding[242]++;

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

        bool result = CGBag::GetTotemCategory(totemCategory, 0);

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

int32_t CSimpleFrame::Hide(void* thisFrame)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*)>(0x48F620)(thisFrame);
}

int32_t CSimpleFrame::Show(void* thisTooltip)
{
    return reinterpret_cast<int(__thiscall*)(void*)>(0x48F660)(thisTooltip);
}
