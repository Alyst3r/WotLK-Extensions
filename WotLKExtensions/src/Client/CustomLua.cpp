#include <CDBCMgr/CDBCDefs/LFGRoles.hpp>
#include <Client/CDataStore.hpp>
#include <Client/CGChat.hpp>
#include <Client/ClientServices.hpp>
#include <Client/CNetClient.hpp>
#include <Client/CustomLua.hpp>
#include <Client/CVar.hpp>
#include <Client/DBClient.hpp>
#include <Client/FrameScript.hpp>
#include <Client/SpellParser.hpp>
#include <Client/SStr.hpp>
#include <Data/DBCAddresses.hpp>
#include <Data/Enums.hpp>
#include <Data/MiscAddresses.hpp>
#include <GameObjects/CGUnit.hpp>
#include <GameObjects/CGPlayer.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>
#include <WorldData/CWorld.hpp>

#include <PatchConfig.hpp>

void CustomLua::Apply()
{
    Util::OverwriteUInt32AtAddress(0x52AB17, (uint32_t)&LoadScriptFunctionsCustom - 0x52AB1B);

    RegisterFunctions();
}

int CustomLua::LoadScriptFunctionsCustom()
{
    auto& luaFunctionMap = DataContainer::GetInstance().GetLuaFunctionMap();

    for (auto& it : luaFunctionMap)
    {
        const char* name = it.first;
        void* ptr = it.second;

        FrameScript::RegisterFunction(name, ptr);
    }

    return FrameScript::LoadFunctions();
}

int CustomLua::GetShapeshiftFormID(lua_State* L)
{
    WoWGUID activePlayer = ClientServices::GetActivePlayer();

    if (activePlayer)
    {
        CGUnit* activeObjectPtr = reinterpret_cast<CGUnit*>(ClientServices::GetObjectPtr(activePlayer, TYPEMASK_UNIT));
        FrameScript::PushNumber(L, static_cast<double>(CGUnit::GetShapeshiftFormID(activeObjectPtr)));

        return 1;
    }

    FrameScript::PushNumber(L, 0);

    return 1;
}

int CustomLua::GetSpellDescription(lua_State* L)
{
    if (FrameScript::IsNumber(L, 1))
    {
        uint32_t spellId = static_cast<uint32_t>(FrameScript::GetNumber(L, 1));
        SpellRow row{};
        char desc[1024] = { 0 };

        if (DBClient::GetLocalizedRow(g_spellDB, spellId, &row))
        {
            SpellParser::ParseText(&row, desc, 1024, 0, 0, 0, 0, 1, 0);
            FrameScript::PushString(L, desc);

            return 1;
        }
    }

    FrameScript::PushNil(L);

    return 1;
}

int CustomLua::GetSpellNameById(lua_State* L)
{
    if (FrameScript::IsNumber(L, 1))
    {
        uint32_t spellId = static_cast<uint32_t>(FrameScript::GetNumber(L, 1));
        SpellRow row{};

        if (DBClient::GetLocalizedRow(g_spellDB, spellId, &row))
        {
            FrameScript::PushString(L, row.m_name_lang);
            FrameScript::PushString(L, row.m_nameSubtext_lang);

            return 2;
        }
    }

    FrameScript::PushNil(L);
    FrameScript::PushNil(L);

    return 2;
}

int CustomLua::FindSpellActionBarSlots(lua_State* L)
{
    uint32_t spellID = static_cast<uint32_t>(FrameScript::GetNumber(L, 1));
    uint8_t count = 0;

    for (uint8_t i = 0; i < 144; i++)
    {
        if (g_actionBarSpellIDArray[i] == spellID)
        {
            FrameScript::PushNumber(L, i);

            count++;
        }
    }

    if (!count)
    {
        FrameScript::PushNil(L);

        return 1;
    }
    else
        return count;
}

int CustomLua::ReplaceActionBarSpell(lua_State* L)
{
    uint32_t oldSpellID = FrameScript::GetNumber(L, 1);
    uint32_t newSpellID = FrameScript::GetNumber(L, 2);

    for (uint8_t i = 0; i < 144; i++)
    {
        if (g_actionBarSpellIDArray[i] == oldSpellID)
        {
            g_actionBarSpellIDArray[i] = newSpellID;

            CNetClient::Packet_MSG_SET_ACTION_BUTTON(i, true, false);

            for (uint8_t j = i + 72; j < 144; j += 12)
            {
                if (!g_actionButtonsArray[j])
                {
                    g_actionBarSpellIDArray[i] = newSpellID;
                    g_actionButtonsArray[j] = 1;

                    CNetClient::Packet_MSG_SET_ACTION_BUTTON(j, true, false);
                }
            }
        }
    }

    return 0;
}

int CustomLua::SetSpellInActionBarSlot(lua_State* L)
{
    uint32_t spellID = static_cast<uint32_t>(FrameScript::GetNumber(L, 1));
    uint8_t slotID = static_cast<uint8_t>(FrameScript::GetNumber(L, 2));

    if (slotID < 144)
    {
        if (!g_actionButtonsArray[slotID])
            g_actionButtonsArray[slotID] = 1;

        g_actionBarSpellIDArray[slotID] = spellID;

        CNetClient::Packet_MSG_SET_ACTION_BUTTON(slotID, true, false);
    }

    return 0;
}

int CustomLua::ReloadMap(lua_State* L)
{
    uint64_t activePlayer = ClientServices::GetActivePlayer();

    if (activePlayer)
    {
        MapRow* row = nullptr;
        int32_t mapId = *g_currentMapID;
        CGUnit* activeObjectPtr = reinterpret_cast<CGUnit*>(ClientServices::GetObjectPtr(activePlayer, TYPEMASK_UNIT));
        CMovement* moveInfo = activeObjectPtr->m_movementInfo;

        if (mapId > -1)
        {
            row = reinterpret_cast<MapRow*>(DBClient::GetRow(&g_mapDB->m_vtable2, mapId));

            if (row)
            {
                char buffer[512];

                CWorld::UnloadMap();
                CWorld::LoadMap(row->m_directory, &moveInfo->position, mapId);
                SStr::Printf(buffer, 512, "Map ID: %d (Directory: \"%s\", x: %f, y: %f, z: %f) reloaded.", mapId, row->m_directory, moveInfo->position.x, moveInfo->position.y, moveInfo->position.z);
                CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
            }
        }
    }

    return 0;
}

int CustomLua::ToggleDisplayNormals(lua_State* L)
{
    char buffer[512];
    bool areNormalsDisplayed = renderFlags4 & 0x40;

    if (areNormalsDisplayed)
    {
        renderFlags4 &= ~0x40;

        SStr::Printf(buffer, 512, "Normal display turned off.");
    }
    else
    {
        renderFlags4 |= 0x40;

        SStr::Printf(buffer, 512, "Normal display turned on.");
    }

    CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}

int CustomLua::ToggleGroundEffects(lua_State* L)
{
    char buffer[512];
    bool areGroundEffectsDisplayed = renderFlags3 & 0x10;

    if (areGroundEffectsDisplayed)
    {
        renderFlags3 &= ~0x10;

        SStr::Printf(buffer, 512, "Ground clutter hidden.");
    }
    else
    {
        renderFlags3 |= 0x10;

        SStr::Printf(buffer, 512, "Ground clutter shown.");
    }

    CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}

int CustomLua::ToggleLiquids(lua_State* L)
{
    char buffer[512];
    bool areLiquidsShowing = renderFlags4 & 0x03;

    if (areLiquidsShowing)
    {
        renderFlags4 &= ~0x03;

        SStr::Printf(buffer, 512, "Liquids hidden.");
    }
    else
    {
        renderFlags4 |= 0x03;

        SStr::Printf(buffer, 512, "Liquids shown.");
    }

    CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}

int CustomLua::ToggleM2(lua_State* L)
{
    char buffer[512];
    bool areM2Displayed = renderFlags1 & 0x01;

    if (areM2Displayed)
    {
        renderFlags1 &= ~0x01;

        SStr::Printf(buffer, 512, "Client-side M2s hidden.");
    }
    else
    {
        renderFlags1 |= 0x01;

        SStr::Printf(buffer, 512, "Client-side M2s shown.");
    }

    CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}

int CustomLua::ToggleTerrain(lua_State* L)
{
    char buffer[512];
    bool isTerrainShown = renderFlags1 & 0x02;

    if (isTerrainShown)
    {
        renderFlags1 &= ~0x02;

        SStr::Printf(buffer, 512, "Terrain hidden.");
    }
    else
    {
        renderFlags1 |= 0x02;

        SStr::Printf(buffer, 512, "Terrain shown.");
    }

    CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}

int CustomLua::ToggleTerrainCulling(lua_State* L)
{
    char buffer[512];
    bool isTerrainCullingOn = renderFlags1 & 0x32;

    if (isTerrainCullingOn)
    {
        renderFlags1 &= ~0x32;

        SStr::Printf(buffer, 512, "Terrain culling disabled.");
    }
    else
    {
        renderFlags1 |= 0x32;

        SStr::Printf(buffer, 512, "Terrain culling enabled.");
    }

    CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}

int CustomLua::ToggleWireframeMode(lua_State* L)
{
    char buffer[512];
    bool isWireframeModeOn = renderFlags4 & 0x20;

    if (isWireframeModeOn)
    {
        renderFlags4 &= ~0x20;

        SStr::Printf(buffer, 512, "Wireframe mode off.");
    }
    else
    {
        renderFlags4 |= 0x20;

        SStr::Printf(buffer, 512, "Wireframe mode on.");
    }

    CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}

int CustomLua::ToggleWMO(lua_State* L)
{
    char buffer[512];
    bool areWMOsDisplayed = renderFlags2 & 0x01;

    if (areWMOsDisplayed)
    {
        renderFlags2 &= ~0x01;

        SStr::Printf(buffer, 512, "WMOs hidden.");
    }
    else
    {
        renderFlags2 |= 0x01;

        SStr::Printf(buffer, 512, "WMOs shown.");
    }

    CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return 0;
}

int CustomLua::FlashGameWindow(lua_State* L)
{
    HWND activeWindow = *g_window;

    if (activeWindow && GetForegroundWindow() != activeWindow) {
        FLASHWINFO flashInfo{};

        flashInfo.cbSize = sizeof(flashInfo);
        flashInfo.hwnd = activeWindow;
        flashInfo.dwFlags = FLASHW_TIMERNOFG | FLASHW_TRAY;
        flashInfo.uCount = -1;
        flashInfo.dwTimeout = 500;

        FlashWindowEx(&flashInfo);
    }

    return 0;
}

int CustomLua::GetCustomCombatRating(lua_State* L)
{
    uint8_t cr = 0;
    float value = 0;

    if (!FrameScript::IsNumber(L, 1))
        FrameScript::DisplayError(L, "Usage: GetCustomCombatRating(ratingIndex)");

    cr = FrameScript::GetNumber(L, 1) - 1;

    if (cr < 25 || cr >= 32)
        FrameScript::DisplayError(L, "ratingIndex is in the range %d .. %d", 26, 32);

    CGUnit* activeObjectPtr = reinterpret_cast<CGUnit*>(ClientServices::GetObjectPtr(ClientServices::GetActivePlayer(), TYPEMASK_PLAYER));

    if (activeObjectPtr)
        value = DataContainer::GetInstance().GetCustomCombatRating(cr - 25);

    FrameScript::PushNumber(L, value);

    return 1;
}

int CustomLua::GetCustomCombatRatingBonus(lua_State* L)
{
    uint32_t cr = 0;
    float value = 0.f;
    float gtCombatRating = 0.f;
    float gtOctClasCombatRatingScalar = 0.f;

    if (!FrameScript::IsNumber(L, 1))
        FrameScript::DisplayError(L, "Usage: GetCustomCombatRating(ratingIndex)");

    cr = FrameScript::GetNumber(L, 1) - 1;

    if (cr < 25 || cr >= 32)
        FrameScript::DisplayError(L, "ratingIndex is in the range %d .. %d", 26, 32);

    CGUnit* activeObjectPtr = reinterpret_cast<CGUnit*>(ClientServices::GetObjectPtr(ClientServices::GetActivePlayer(), TYPEMASK_PLAYER));

    if (activeObjectPtr)
    {
        gtCombatRating = DBClient::GetGameTableValue(1, activeObjectPtr->m_unitFields->m_level, cr);
        gtOctClasCombatRatingScalar = DBClient::GetGameTableValue(1, activeObjectPtr->m_unitFields->m_bytes0.m_unitClass, cr);

        if (gtCombatRating && gtOctClasCombatRatingScalar)
            value = gtOctClasCombatRatingScalar * DataContainer::GetInstance().GetCustomCombatRating(cr - 25) / gtCombatRating;
    }

    FrameScript::PushNumber(L, value);

    return 1;
}

int CustomLua::GetAvailableRoles(lua_State* L)
{
    ChrClassesRow* row = reinterpret_cast<ChrClassesRow*>(DBClient::GetRow(&g_chrClassesDB->m_vtable2, ClientServices::GetCharacterClass()));
    uint32_t classId = 0;
    LFGRolesRow cdbcRole;

    if (row)
        classId = row->m_ID;

    DataContainer::GetInstance().GetLFGRolesRow(cdbcRole, classId);//GlobalCDBCMap.getRow<LFGRolesRow>("LFGRoles", classId);

    FrameScript::PushBoolean(L, cdbcRole.m_roles & 2);
    FrameScript::PushBoolean(L, cdbcRole.m_roles & 4);
    FrameScript::PushBoolean(L, cdbcRole.m_roles & 8);

    return 3;
}

int CustomLua::SetLFGRole(lua_State* L)
{
    ChrClassesRow* row = reinterpret_cast<ChrClassesRow*>(DBClient::GetRow(&g_chrClassesDB->m_vtable2, ClientServices::GetCharacterClass()));
    LFGRolesRow cdbcRole;
    uint32_t roles = FrameScript::GetParam(L, 1, 0) != 0;
    uint32_t classId = 0;
    void* ptr = *reinterpret_cast<void**>(0xBD0A28);

    if (FrameScript::GetParam(L, 2, 0))
        roles |= 2;
    if (FrameScript::GetParam(L, 3, 0))
        roles |= 4;
    if (FrameScript::GetParam(L, 4, 0))
        roles |= 8;

    if (row)
        classId = row->m_ID;

    DataContainer::GetInstance().GetLFGRolesRow(cdbcRole, classId);

    CVar::Set(ptr, roles & cdbcRole.m_roles, 1, 0, 0, 1);
    FrameScript::SignalEvent(EVENT_LFG_ROLE_UPDATE, 0);

    return 0;
}

int CustomLua::ConvertCoordsToScreenSpace(lua_State* L)
{
    float ox = static_cast<float>(FrameScript::GetNumber(L, 1));
    float oy = static_cast<float>(FrameScript::GetNumber(L, 2));
    float oz = static_cast<float>(FrameScript::GetNumber(L, 3));
    void* worldFrame = *reinterpret_cast<void**>(0xB7436C);
    C3Vector pos3d = { ox, oy, oz };
    C3Vector pos2d = {};
    uint32_t flags = 0;
    int result = CWorld::Pos3Dto2D(worldFrame, &pos3d, &pos2d, &flags);
    float x = 0.f;
    float y = 0.f;

    Util::PercToScreenPos(pos2d.x, pos2d.y, &x, &y);
    FrameScript::PushNumber(L, x);
    FrameScript::PushNumber(L, y);
    FrameScript::PushNumber(L, pos2d.z);

    return 3;
}

int CustomLua::PortGraveyard(lua_State* L)
{
    CGPlayer* activeObjectPtr = reinterpret_cast<CGPlayer*>(ClientServices::GetObjectPtr(ClientServices::GetActivePlayer(), TYPEMASK_PLAYER));

    if (activeObjectPtr && (activeObjectPtr->m_playerData->m_flags & PLAYER_FLAGS_GHOST))
    {
        CDataStore pkt;

        CDataStore::GenPacket(&pkt);
        CDataStore::PutInt32(&pkt, CMSG_TELEPORT_GRAVEYARD_REQUEST);

        pkt.m_read = 0;

        ClientServices::SendPacket(&pkt);
        CDataStore::Release(&pkt);
    }

    return 0;
}

void CustomLua::AddToFunctionMap(const char* name, void* ptr)
{
    DataContainer::GetInstance().AddLuaFunction(name, ptr);
}

void CustomLua::RegisterFunctions()
{
#if OOBLUAFUNCTIONS_PATCH
    AddToFunctionMap("FlashGameWindow", &FlashGameWindow);
    AddToFunctionMap("GetShapeshiftFormID", &GetShapeshiftFormID);
    AddToFunctionMap("GetSpellDescription", &GetSpellDescription);
    AddToFunctionMap("GetSpellNameById", &GetSpellNameById);
    AddToFunctionMap("ConvertCoordsToScreenSpace", &ConvertCoordsToScreenSpace);
#endif

#if ACTIONBAR_LUA
    AddToFunctionMap("FindSpellActionBarSlots", &FindSpellActionBarSlots);
    AddToFunctionMap("ReplaceActionBarSpell", &ReplaceActionBarSpell);
    AddToFunctionMap("SetSpellInActionBarSlot", &SetSpellInActionBarSlot);
#endif
    
#if DEVHELPER_LUA
    AddToFunctionMap("ReloadMap", &ReloadMap);
    AddToFunctionMap("ToggleDisplayNormals", &ToggleDisplayNormals);
    AddToFunctionMap("ToggleGroundEffects", &ToggleGroundEffects);
    AddToFunctionMap("ToggleM2", &ToggleM2);
    AddToFunctionMap("ToggleLiquids", &ToggleLiquids);
    AddToFunctionMap("ToggleTerrain", &ToggleTerrain);
    AddToFunctionMap("ToggleTerrainCulling", &ToggleTerrainCulling);
    AddToFunctionMap("ToggleWireframeMode", &ToggleWireframeMode);
    AddToFunctionMap("ToggleWMO", &ToggleWMO);
#endif

#if CUSTOMPACKETS_PATCH
    AddToFunctionMap("GetCustomCombatRating", &GetCustomCombatRating);
    AddToFunctionMap("GetCustomCombatRatingBonus", &GetCustomCombatRatingBonus);
    AddToFunctionMap("PortGraveyard", &PortGraveyard);
#endif
}
