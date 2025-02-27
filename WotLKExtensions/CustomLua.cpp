#include "CustomLua.h"

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

	if (Spell_C::IsSpellKnown(spellID))
	{
		for (uint8_t i = 0; i < 144; i++)
		{
			if (actionBarSpellIDs[i] == spellID)
			{
				FrameScript::PushNumber(L, i);
				count++;
			}
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

	if (Spell_C::IsSpellKnown(oldSpellID) && Spell_C::IsSpellKnown(newSpellID))
	{
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
	}

	FrameScript::PushNil(L);
	return 1;
}

int CustomLua::SetSpellInActionBarSlot(lua_State* L)
{
	uint32_t spellID = FrameScript::GetNumber(L, 1);
	uint8_t slotID = FrameScript::GetNumber(L, 2);
	uintptr_t* actionBarSpellIDs = (uintptr_t*)0xC1E358;
	uintptr_t* actionButtons = (uintptr_t*)0xC1DED8;

	if (slotID < 144 && Spell_C::IsSpellKnown(spellID))
	{
		if (!actionButtons[slotID])
			actionButtons[slotID] = 1;

		actionBarSpellIDs[slotID] = spellID;
		ClientPacket::MSG_SET_ACTION_BUTTON(slotID, 1, 0);
	}

	FrameScript::PushNil(L);
	return 1;
}

int CustomLua::ReloadMap(lua_State* L)
{
	uint64_t activePlayer = ClntObjMgr::GetActivePlayer();

	if (activePlayer) {
		MapRow* row = 0;
		int32_t mapId = *(uint32_t*)0xBD088C;
		CGUnit* activeObjectPtr = (CGUnit*)ClntObjMgr::ObjectPtr(activePlayer, 0x08);
		CMovement* moveInfo = activeObjectPtr->movementInfo;

		if (mapId > -1) {
			row = (MapRow*)ClientDB::GetRow((void*)0xAD4178, mapId);

			if (row) {
				char buffer[512];

				World::UnloadMap();
				World::LoadMap(row->m_Directory, &moveInfo->position, mapId);

				SStr::Printf(buffer, 512, "Map ID: %d (Directory: \"%s\", x: %f, y: %f, z: %f) reloaded.", mapId, row->m_Directory, moveInfo->position.x, moveInfo->position.y, moveInfo->position.z);
				FrameScript::PushString(L, buffer);
				return 1;
			}
		}
	}

	FrameScript::PushNil(L);
	return 1;
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

	FrameScript::PushNil(L);
	return 1;
}

void CustomLua::AddToFunctionMap(char* name, void* ptr)
{
	luaFuncts.insert(std::make_pair(name, ptr));
}

void CustomLua::RegisterFunctions()
{
	AddToFunctionMap("GetShapeshiftFormID", &GetShapeshiftFormID);
	AddToFunctionMap("GetSpellDescription", &GetSpellDescription);
	AddToFunctionMap("FindSpellActionBarSlots", &FindSpellActionBarSlots);
	AddToFunctionMap("ReplaceActionBarSpell", &ReplaceActionBarSpell);
	AddToFunctionMap("SetSpellInActionBarSlot", &SetSpellInActionBarSlot);
	AddToFunctionMap("ReloadMap", &ReloadMap);
	AddToFunctionMap("FlashGameWindow", &FlashGameWindow);
}
