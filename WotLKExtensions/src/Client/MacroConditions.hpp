#pragma once

#include <cstdint>

class MacroConditions
{
public:
    static void Apply();

    static int32_t __fastcall Evaluate(MacroConditions* thisConditions, int32_t unused, uint32_t* a2);

private:
    uint32_t m_padding0;
    uint32_t m_padding1;
    uint32_t m_padding2;
    uint32_t m_padding3;
    uint32_t m_padding4;
    char* m_padding5;
    char* m_padding6;
    char* m_padding7;
    uint32_t m_padding8;
    uint32_t m_padding9;
    uint32_t m_padding10;

    MacroConditions() = delete;
    ~MacroConditions() = delete;
};
