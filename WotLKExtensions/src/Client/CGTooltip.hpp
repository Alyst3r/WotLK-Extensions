#pragma once

#include <cstdint>

class CGTooltip
{
public:
    static void ApplyPatches();

    static int32_t __fastcall SetSpellEx(CGTooltip* thisTooltip, int32_t unused, int32_t spellId, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, uint32_t* a9, int32_t a10, int32_t a11, int32_t a12, int32_t a13, int32_t a14, int32_t a15, int32_t a16);

    static void AddLine(CGTooltip* thisTooltip, char* str1, char* str2, uint32_t color1, uint32_t color2, int32_t a6);
    static int32_t AddTalentPrereqs(CGTooltip* thisTooltip, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6);
    static int32_t ClearTooltip(CGTooltip* thisTooltip);

private:
    CGTooltip() = delete;
    ~CGTooltip() = delete;
};

class CSimpleFrame
{
public:
    static int32_t Hide(void* thisFrame);

private:
    CSimpleFrame() = delete;
    ~CSimpleFrame() = delete;
};
