#include <Client/SStr.hpp>

#include <cstdarg>
#include <cstdio>

int SStr::Printf(char* buf, uint32_t length, char* fmt, ...)
{
    char buffer[2048] = { 0 };
    va_list args;

    va_start(args, fmt);
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, fmt, args);
    va_end(args);

    // original SStr::Printf
    return reinterpret_cast<int(__cdecl*)(char*, uint32_t, char*, ...)>(0x76F070)(buf, length, "%s", buffer);
}
