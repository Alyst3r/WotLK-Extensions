#pragma once

#include <cstdint>

class SStr
{
public:
    static int Printf(char* buf, uint32_t length, char* fmt, ...);
    static char* Append(char* dst, char* src, int32_t size);
    static char* Copy(char* dst, char* src, int32_t size);

private:
    SStr() = delete;
    ~SStr() = delete;
};
