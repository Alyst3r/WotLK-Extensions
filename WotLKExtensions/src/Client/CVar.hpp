#pragma once

#include <cstdint>

class CVar
{
public:
    static void Set(void* cVar, int32_t value, bool a3, bool a4, bool a5, bool a6);

private:
    CVar() = delete;
    ~CVar() = delete;
};
