#pragma once

#include <SharedDefines.hpp>

struct lua_State;
class Main;

class CustomLua {
public:
    static int32_t LoadScriptFunctionsCustom();

    static int32_t GetAvailableRoles(lua_State* L);
    static int32_t SetLFGRole(lua_State* L);
private:
    static void AddToFunctionMap(const char* name, void* ptr);
    static void Apply();
    static void RegisterFunctions();

    static int32_t FindSpellActionBarSlots(lua_State* L);
    static int32_t ReplaceActionBarSpell(lua_State* L);
    static int32_t SetSpellInActionBarSlot(lua_State* L);

    static int32_t ReloadMap(lua_State* L);
    static int32_t ToggleDisplayNormals(lua_State* L);
    static int32_t ToggleGroundEffects(lua_State* L);
    static int32_t ToggleLiquids(lua_State* L);
    static int32_t ToggleM2(lua_State* L);
    static int32_t ToggleTerrain(lua_State* L);
    static int32_t ToggleTerrainCulling(lua_State* L);
    static int32_t ToggleWireframeMode(lua_State* L);
    static int32_t ToggleWMO(lua_State* L);

    static int32_t FlashGameWindow(lua_State* L);

    static int32_t GetShapeshiftFormID(lua_State* L);
    static int32_t GetSpellDescription(lua_State* L);
    static int32_t GetSpellNameById(lua_State* L);

    static int32_t GetCustomCombatRating(lua_State* L);
    static int32_t GetCustomCombatRatingBonus(lua_State* L);

    static int32_t ConvertCoordsToScreenSpace(lua_State* L);

    static int32_t PortGraveyard(lua_State* L);

    friend class Main;
};
