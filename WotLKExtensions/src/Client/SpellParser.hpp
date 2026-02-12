#pragma once

#include <Data/Structs.hpp>

#include <cstdint>

class SpellParser
{
public:
    static void ParseText(SpellRow* spell, char* dest, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

private:
    SpellParser() = delete;
    ~SpellParser() = delete;
};
