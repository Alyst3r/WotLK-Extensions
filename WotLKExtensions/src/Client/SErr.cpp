#include <Client/SErr.hpp>

#include <cstdarg>
#include <cstdio>

void SErr::PrepareAppFatal(uint32_t code, const char* error, ...)
{
    char buffer[2048] = { 0 };
    va_list args;

    va_start(args, error);
    vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, error, args);
    va_end(args);

    // original SErr::PrepareAppFatal
    reinterpret_cast<void (_cdecl*)(uint32_t, const char*, ...)>(0x772A80)(code, "%s", buffer);
}
