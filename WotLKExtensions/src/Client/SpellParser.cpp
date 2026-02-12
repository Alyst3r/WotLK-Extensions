#include <Client/SpellParser.hpp>

void SpellParser::ParseText(SpellRow* spell, char* dest, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6, uint32_t a7, uint32_t a8, uint32_t a9)
{
    reinterpret_cast<void (__cdecl*)(SpellRow*, char*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)>(0x57ABC0)(spell, dest, a3, a4, a5, a6, a7, a8, a9);
}
