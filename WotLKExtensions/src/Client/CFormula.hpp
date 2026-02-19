#pragma once

#include <Data/Structs.hpp>

#include <cstdint>

class CFormula
{
public:
    static int32_t GetVariableValue(void* thisVar, int32_t spellVariable, int32_t a3, SpellRow* spell, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9);
    static int32_t __fastcall GetVariableValueEx(void* thisVar, int32_t unused, int32_t spellVariable, int32_t a3, SpellRow* spell, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9);

    static void FillSpellVariableData();

private:
    CFormula() = delete;
    ~CFormula() = delete;
};
