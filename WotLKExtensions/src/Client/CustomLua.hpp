#pragma once

#include <SharedDefines.hpp>

struct lua_State;
class Main;

class CustomLua {
public:
    static int LoadScriptFunctionsCustom();

    static int GetAvailableRoles(lua_State* L);
    static int SetLFGRole(lua_State* L);
private:
    static void AddToFunctionMap(char* name, void* ptr);
    static void Apply();
    static void RegisterFunctions();

    static int FindSpellActionBarSlots(lua_State* L);
    static int ReplaceActionBarSpell(lua_State* L);
    static int SetSpellInActionBarSlot(lua_State* L);

    static int ReloadMap(lua_State* L);
    static int ToggleDisplayNormals(lua_State* L);
    static int ToggleGroundEffects(lua_State* L);
    static int ToggleLiquids(lua_State* L);
    static int ToggleM2(lua_State* L);
    static int ToggleTerrain(lua_State* L);
    static int ToggleTerrainCulling(lua_State* L);
    static int ToggleWireframeMode(lua_State* L);
    static int ToggleWMO(lua_State* L);

    static int FlashGameWindow(lua_State* L);

    static int GetShapeshiftFormID(lua_State* L);
    static int GetSpellDescription(lua_State* L);
    static int GetSpellNameById(lua_State* L);

    static int GetCustomCombatRating(lua_State* L);
    static int GetCustomCombatRatingBonus(lua_State* L);

    static int ConvertCoordsToScreenSpace(lua_State* L);

    static int PortGraveyard(lua_State* L);

    friend class Main;
};
