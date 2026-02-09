#pragma once

#include <cstdint>

struct lua_State;

class FrameScript
{
public:
    static void DisplayError(lua_State* L, char* fmt, ...);
    static bool GetBoolean(lua_State* L, int32_t index);
    static double GetNumber(lua_State* L, int32_t index);
    static bool GetParam(lua_State* L, int32_t index, bool p);
    static char* GetString(lua_State* L, int32_t index, bool p);
    static int32_t GetTop(lua_State* L, int32_t p);
    static int32_t IsNumber(lua_State* L, int32_t index);
    static char* IsString(lua_State* L, int32_t index);
    static int32_t LoadFunctions();
    static int32_t PushBoolean(lua_State* L, bool state);
    static int32_t PushNil(lua_State* L);
    static int32_t PushNumber(lua_State* L, double value);
    static int32_t PushString(lua_State* L, const char* str);
    static int32_t RegisterFunction(const char* name, void* ptr);
    static int32_t SetTop(lua_State* L, int32_t p);
    static int32_t SignalEvent(uint32_t event, char* fmt, ...);

private:
    FrameScript() = delete;
    ~FrameScript() = delete;
};
