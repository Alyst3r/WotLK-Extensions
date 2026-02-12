#include <Client/FrameScript.hpp>

#include <cstdarg>
#include <cstdio>

void FrameScript::DisplayError(lua_State* L, char* fmt, ...)
{
    char buffer[2048] = { 0 };
    va_list args;

    va_start(args, fmt);
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, args);
    va_end(args);

    reinterpret_cast<void(_cdecl*)(lua_State*, char*, ...)>(0x84F280)(L, "%s", buffer);
}

bool FrameScript::GetBoolean(lua_State* L, int32_t index)
{
    return reinterpret_cast<bool (__cdecl*)(lua_State*, int32_t)>(0x84E0B0)(L, index);
}

double FrameScript::GetNumber(lua_State* L, int32_t index)
{
    return reinterpret_cast<double(__cdecl*)(lua_State*, int32_t)>(0x84E030)(L, index);
}

bool FrameScript::GetParam(lua_State* L, int32_t index, bool p)
{
    return reinterpret_cast<bool(__cdecl*)(lua_State*, int32_t, bool)>(0x815500)(L, index, p);
}

// or ToLString
char* FrameScript::GetString(lua_State* L, int32_t index, bool p)
{
    return reinterpret_cast<char* (__cdecl*)(lua_State*, int32_t, bool)>(0x84E0E0)(L, index, p);
}

char* FrameScript::GetText(const char* str, int32_t a2, int32_t a3)
{
    return reinterpret_cast<char* (__cdecl*)(const char*, int32_t, int32_t)>(0x819D40)(str, a2, a3);
}

int32_t FrameScript::GetTop(lua_State* L, int32_t p)
{
    return reinterpret_cast <int32_t(__cdecl*)(lua_State*, int32_t)>(0x84DBD0)(L, p);
}

int32_t FrameScript::IsNumber(lua_State* L, int32_t index)
{
    return reinterpret_cast<int32_t(__cdecl*)(lua_State*, int32_t)>(0x84DF20)(L, index);
}

char* FrameScript::IsString(lua_State* L, int32_t index)
{
    return reinterpret_cast<char* (__cdecl*)(lua_State*, int32_t)>(0x84DF60)(L, index);
}

int32_t FrameScript::LoadFunctions()
{
    return reinterpret_cast<int32_t(__cdecl*)()>(0x5120E0)();
}

int32_t FrameScript::PushBoolean(lua_State* L, bool state)
{
    return reinterpret_cast<int32_t(__cdecl*)(lua_State*, bool)>(0x84E4D0)(L, state);
}

int32_t FrameScript::PushNil(lua_State* L)
{
    return reinterpret_cast<int32_t(__cdecl*)(lua_State*)>(0x84E280)(L);
}

int32_t FrameScript::PushNumber(lua_State* L, double value)
{
    return reinterpret_cast<int32_t(__cdecl*)(lua_State*, double)>(0x84E2A0)(L, value);
}

int32_t FrameScript::PushString(lua_State* L, const char* str)
{
    return reinterpret_cast<int32_t(__cdecl*)(lua_State*, const char*)>(0x84E350)(L, str);
}

int32_t FrameScript::RegisterFunction(const char* name, void* ptr)
{
    return reinterpret_cast<int32_t(__cdecl*)(const char*, void*)>(0x817F90)(name, ptr);
}

int32_t FrameScript::SetTop(lua_State* L, int32_t p)
{
    return reinterpret_cast<int32_t(__cdecl*)(lua_State * L, int32_t)>(0x84DBF0)(L, p);
}

int32_t FrameScript::SignalEvent(uint32_t event, char* fmt, ...)
{
    char buffer[2048] = { 0 };
    va_list args;

    va_start(args, fmt);
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, args);
    va_end(args);

    return reinterpret_cast<int32_t(__cdecl*)(uint32_t, char*, ...)>(0x81B530)(event, "%s", buffer);
}
