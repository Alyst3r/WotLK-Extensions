#pragma once

#include <cstdint>

class SErr
{
public:
    static void PrepareAppFatal(uint32_t code, const char* error, ...);

private:
    SErr() = delete;
    ~SErr() = delete;
};
