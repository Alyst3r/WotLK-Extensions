#include "CustomLua.h"
#include "CDBCMgr/CDBCDefs/LFGRoles.h"

void CustomLua::Apply()
{
	Util::OverwriteUInt32AtAddress(0x52AB17, (uint32_t)&LoadScriptFunctionsCustom - 0x52AB1B);

	RegisterFunctions();
}

int CustomLua::LoadScriptFunctionsCustom()
{
	for (auto it = luaFuncts.begin(); it != luaFuncts.end(); it++)
	{
		char* funcName = it->first;
		void* funcPtr = it->second;
	
		FrameScript::RegisterFunction(funcName, funcPtr);
	}

	return FrameScript::LoadFunctions();
}

int CustomLua::GetShapeshiftFormID(lua_State* L)
{
	uint64_t activePlayer = ClntObjMgr::GetActivePlayer();

	if (activePlayer)
	{
		CGUnit* activeObjectPtr = (CGUnit*)ClntObjMgr::ObjectPtr(activePlayer, 0x08);
		FrameScript::PushNumber(L, CGUnit_C::GetShapeshiftFormId(activeObjectPtr));
		return 1;
	}

	FrameScript::PushNumber(L, 0);
	return 1;
}

int CustomLua::GetSpellDescription(lua_State* L)
{
	if (FrameScript::IsNumber(L, 1))
	{
		uint32_t spellId = (uint32_t)FrameScript::GetNumber(L, 1);
		SpellRow row;
		char desc[1024];

		if (ClientDB::GetLocalizedRow((void*)0xAD49D0, spellId, &row))
		{
			SpellParser::ParseText(&row, &desc, 1024, 0, 0, 0, 0, 1, 0);
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
		uint32_t spellId = (uint32_t)FrameScript::GetNumber(L, 1);
		SpellRow row;

		if (ClientDB::GetLocalizedRow((void*)0xAD49D0, spellId, &row))
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
	uint32_t spellID = FrameScript::GetNumber(L, 1);
	uintptr_t* actionBarSpellIDs = (uintptr_t*)0xC1E358;
	uint8_t count = 0;

	for (uint8_t i = 0; i < 144; i++)
	{
		if (actionBarSpellIDs[i] == spellID)
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
	uintptr_t* actionBarSpellIDs = (uintptr_t*)0xC1E358;
	uintptr_t* actionButtons = (uintptr_t*)0xC1DED8;

	for (uint8_t i = 0; i < 144; i++)
	{
		if (actionBarSpellIDs[i] == oldSpellID)
		{
			actionBarSpellIDs[i] = newSpellID;
			ClientPacket::MSG_SET_ACTION_BUTTON(i, 1, 0);

			for (uint8_t j = i + 72; j < 144; j += 12)
			{
				if (!actionButtons[j])
				{
					actionBarSpellIDs[i] = newSpellID;
					actionButtons[j] = 1;
					ClientPacket::MSG_SET_ACTION_BUTTON(j, 1, 0);
				}
			}
		}
	}

	return 0;
}

int CustomLua::SetSpellInActionBarSlot(lua_State* L)
{
	uint32_t spellID = FrameScript::GetNumber(L, 1);
	uint8_t slotID = FrameScript::GetNumber(L, 2);
	uintptr_t* actionBarSpellIDs = (uintptr_t*)0xC1E358;
	uintptr_t* actionButtons = (uintptr_t*)0xC1DED8;

	if (slotID < 144)
	{
		if (!actionButtons[slotID])
			actionButtons[slotID] = 1;

		actionBarSpellIDs[slotID] = spellID;
		ClientPacket::MSG_SET_ACTION_BUTTON(slotID, 1, 0);
	}

	return 0;
}

int CustomLua::ReloadMap(lua_State* L)
{
	uint64_t activePlayer = ClntObjMgr::GetActivePlayer();

	if (activePlayer)
	{
		MapRow* row = 0;
		int32_t mapId = *(uint32_t*)0xBD088C;
		CGUnit* activeObjectPtr = (CGUnit*)ClntObjMgr::ObjectPtr(activePlayer, 0x08);
		CMovement* moveInfo = activeObjectPtr->movementInfo;

		if (mapId > -1)
		{
			row = (MapRow*)ClientDB::GetRow((void*)0xAD4178, mapId);

			if (row)
			{
				char buffer[512];

				World::UnloadMap();
				World::LoadMap(row->m_Directory, &moveInfo->position, mapId);
				SStr::Printf(buffer, 512, "Map ID: %d (Directory: \"%s\", x: %f, y: %f, z: %f) reloaded.", mapId, row->m_Directory, moveInfo->position.x, moveInfo->position.y, moveInfo->position.z);
				CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			}
		}
	}

	return 0;
}

int CustomLua::ToggleDisplayNormals(lua_State* L)
{
	char buffer[512];
	uint8_t renderFlags = *(uint8_t*)0xCD774F;
	bool areNormalsDisplayed = renderFlags & 0x40;

	if (areNormalsDisplayed)
	{
		*(uint8_t*)0xCD774F = renderFlags - 0x40;
		SStr::Printf(buffer, 512, "Normal display turned off.");
	}
	else
	{
		*(uint8_t*)0xCD774F = renderFlags + 0x40;
		SStr::Printf(buffer, 512, "Normal display turned on.");
	}

	CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 0;
}

int CustomLua::ToggleGroundEffects(lua_State* L)
{
	char buffer[512];
	uint8_t renderFlags = *(uint8_t*)0xCD774E;
	bool areWMOsDisplayed = renderFlags & 0x10;

	if (areWMOsDisplayed)
	{
		*(uint8_t*)0xCD774E = renderFlags - 0x10;
		SStr::Printf(buffer, 512, "Ground clutter hidden.");
	}
	else
	{
		*(uint8_t*)0xCD774E = renderFlags + 0x10;
		SStr::Printf(buffer, 512, "Ground clutter shown.");
	}

	CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 0;
}

int CustomLua::ToggleLiquids(lua_State* L)
{
	char buffer[512];
	uint8_t renderFlags = *(uint8_t*)0xCD774F;
	bool isWireframeModeOn = renderFlags & 0x3;

	if (isWireframeModeOn)
	{
		*(uint8_t*)0xCD774F = renderFlags - 0x3;
		SStr::Printf(buffer, 512, "Liquids hidden.");
	}
	else
	{
		*(uint8_t*)0xCD774F = renderFlags + 0x3;
		SStr::Printf(buffer, 512, "Liquids shown.");
	}

	CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 0;
}

int CustomLua::ToggleM2(lua_State* L)
{
	char buffer[512];
	uint8_t renderFlags = *(uint8_t*)0xCD774C;
	bool areWMOsDisplayed = renderFlags & 0x1;

	if (areWMOsDisplayed)
	{
		*(uint8_t*)0xCD774C = renderFlags - 0x1;
		SStr::Printf(buffer, 512, "Client-side M2s hidden.");
	}
	else
	{
		*(uint8_t*)0xCD774C = renderFlags + 0x1;
		SStr::Printf(buffer, 512, "Client-side M2s shown.");
	}

	CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 0;
}

int CustomLua::ToggleTerrain(lua_State* L)
{
	char buffer[512];
	uint8_t renderFlags = *(uint8_t*)0xCD774C;
	bool areWMOsDisplayed = renderFlags & 0x2;

	if (areWMOsDisplayed)
	{
		*(uint8_t*)0xCD774C = renderFlags - 0x2;
		SStr::Printf(buffer, 512, "Terrain hidden.");
	}
	else
	{
		*(uint8_t*)0xCD774C = renderFlags + 0x2;
		SStr::Printf(buffer, 512, "Terrain shown.");
	}

	CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 0;
}

int CustomLua::ToggleTerrainCulling(lua_State* L)
{
	char buffer[512];
	uint8_t renderFlags = *(uint8_t*)0xCD774C;
	bool areWMOsDisplayed = renderFlags & 0x32;

	if (areWMOsDisplayed)
	{
		*(uint8_t*)0xCD774C = renderFlags - 0x32;
		SStr::Printf(buffer, 512, "Terrain culling disabled.");
	}
	else
	{
		*(uint8_t*)0xCD774C = renderFlags + 0x32;
		SStr::Printf(buffer, 512, "Terrain culling enabled.");
	}

	CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 0;
}

int CustomLua::ToggleWireframeMode(lua_State* L)
{
	char buffer[512];
	uint8_t renderFlags = *(uint8_t*)0xCD774F;
	bool isWireframeModeOn = renderFlags & 0x20;

	if (isWireframeModeOn)
	{
		*(uint8_t*)0xCD774F = renderFlags - 0x20;
		SStr::Printf(buffer, 512, "Wireframe mode off.");
	}
	else
	{
		*(uint8_t*)0xCD774F = renderFlags + 0x20;
		SStr::Printf(buffer, 512, "Wireframe mode on.");
	}

	CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 0;
}

int CustomLua::ToggleWMO(lua_State* L)
{
	char buffer[512];
	uint8_t renderFlags = *(uint8_t*)0xCD774D;
	bool areWMOsDisplayed = renderFlags & 0x1;

	if (areWMOsDisplayed)
	{
		*(uint8_t*)0xCD774D = renderFlags - 0x1;
		SStr::Printf(buffer, 512, "WMOs hidden.");
	}
	else
	{
		*(uint8_t*)0xCD774D = renderFlags + 0x1;
		SStr::Printf(buffer, 512, "WMOs shown.");
	}

	CGChat::AddChatMessage(buffer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return 0;
}

int CustomLua::FlashGameWindow(lua_State* L)
{
	HWND activeWindow = *(HWND*)0x00D41620;

	if (activeWindow && GetForegroundWindow() != activeWindow) {
		FLASHWINFO flashInfo;

		flashInfo.cbSize = sizeof(flashInfo);
		flashInfo.hwnd = activeWindow;
		flashInfo.dwFlags = FLASHW_TIMERNOFG | FLASHW_TRAY;
		flashInfo.uCount = -1;
		flashInfo.dwTimeout = 500;

		FlashWindowEx(&flashInfo);
	}

	return 0;
}

int CustomLua::GetAvailableRoles(lua_State* L)
{
	ChrClassesRow* row = (ChrClassesRow*)ClientDB::GetRow((void*)(0xAD341C), sub_6B1080());
	uint32_t classId = 0;
	LFGRolesRow* cdbcRole = 0;

	if (row)
		classId = row->m_ID;

	cdbcRole = GlobalCDBCMap.getRow<LFGRolesRow>("LFGRoles", classId);

	FrameScript::PushBoolean(L, cdbcRole->Roles & 2);
	FrameScript::PushBoolean(L, cdbcRole->Roles & 4);
	FrameScript::PushBoolean(L, cdbcRole->Roles & 8);
	return 3;
}

int CustomLua::SetLFGRole(lua_State* L)
{
	ChrClassesRow* row = (ChrClassesRow*)ClientDB::GetRow((void*)0xAD341C, sub_6B1080());
	LFGRolesRow* cdbcRole = 0;
	uint32_t roles = FrameScript::GetParam(L, 1, 0) != 0;
	uint32_t classId = 0;
	uintptr_t ptr = *(uintptr_t*)0xBD0A28;

	if (FrameScript::GetParam(L, 2, 0))
		roles |= 2;
	if (FrameScript::GetParam(L, 3, 0))
		roles |= 4;
	if (FrameScript::GetParam(L, 4, 0))
		roles |= 8;

	if (row)
		classId = row->m_ID;

	cdbcRole = GlobalCDBCMap.getRow<LFGRolesRow>("LFGRoles", classId);

	CVar::sub_766940((void*)ptr, roles & cdbcRole->Roles, 1, 0, 0, 1);
	FrameScript::SignalEvent(EVENT_LFG_ROLE_UPDATE, 0);
	return 0;
}

void CustomLua::AddToFunctionMap(char* name, void* ptr)
{
	luaFuncts.insert(std::make_pair(name, ptr));
}

void CustomLua::RegisterFunctions()
{
	AddToFunctionMap("FlashGameWindow", &FlashGameWindow);
	AddToFunctionMap("GetShapeshiftFormID", &GetShapeshiftFormID);
	AddToFunctionMap("GetSpellDescription", &GetSpellDescription);
	AddToFunctionMap("GetSpellNameById", &GetSpellNameById);

	if (customActionBarFunctions)
	{
		AddToFunctionMap("FindSpellActionBarSlots", &FindSpellActionBarSlots);
		AddToFunctionMap("ReplaceActionBarSpell", &ReplaceActionBarSpell);
		AddToFunctionMap("SetSpellInActionBarSlot", &SetSpellInActionBarSlot);
	}
	
	if (devHelperFunctions)
	{
		AddToFunctionMap("ReloadMap", &ReloadMap);
		AddToFunctionMap("ToggleDisplayNormals", &ToggleDisplayNormals);
		AddToFunctionMap("ToggleGroundEffects", &ToggleGroundEffects);
		AddToFunctionMap("ToggleM2", &ToggleM2);
		AddToFunctionMap("ToggleLiquids", &ToggleLiquids);
		AddToFunctionMap("ToggleTerrain", &ToggleTerrain);
		AddToFunctionMap("ToggleTerrainCulling", &ToggleTerrainCulling);
		AddToFunctionMap("ToggleWireframeMode", &ToggleWireframeMode);
		AddToFunctionMap("ToggleWMO", &ToggleWMO);
	}
}
