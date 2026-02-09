#pragma once

#include <cstdint>

class SStr
{
public:
    static int Printf(char* buf, uint32_t length, char* fmt, ...);

private:
    SStr() = delete;
    ~SStr() = delete;
};
