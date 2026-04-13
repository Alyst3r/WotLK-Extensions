#pragma once

#include <cstdint>

class CGBag
{
public:
    static int32_t GetItemTypeCount(CGBag* thisBag, int32_t itemID, int32_t a3);
    static bool GetTotemCategory(int32_t totemCategory, int32_t a2);
    static int32_t FindItemOfType(CGBag* thisBag, int32_t itemID, int32_t a3);

private:
    CGBag() = delete;
    ~CGBag() = delete;
};
