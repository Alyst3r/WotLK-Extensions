#pragma once

#include <cstdint>

class CGTooltip
{
public:
    static void ApplyPatches();

    static void AddLine(void* thisTooltip, char* str1, char* str2, uint32_t color1, uint32_t color2, int32_t a6);
    static int AddTalentPrereqs(void* thisTooltip, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6);
    static int ClearTooltip(void* thisTooltip);

private:
    CGTooltip() = delete;
    ~CGTooltip() = delete;
};

class CSimpleFrame
{
public:
    static int Hide(void* thisFrame);

private:
    CSimpleFrame() = delete;
    ~CSimpleFrame() = delete;
};
