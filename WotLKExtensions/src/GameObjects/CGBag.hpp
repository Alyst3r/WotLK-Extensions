#pragma once

#include <cstdint>

class CGBag
{
public:
    static int32_t GetItemTypeCount(CGBag* thisBag, int32_t itemID, int32_t a3);
    static int32_t FindItemOfType(CGBag* thisBag, int32_t itemID, int32_t a3);
    static int32_t FindItemSlot(CGBag* thisBag, int32_t itemID);
    static int32_t GetNumFreeInvSlots(CGBag* thisBag);
    static bool FindTotemOfCategory(int32_t totemCategory, int32_t a2);

private:
    CGBag() = delete;
    ~CGBag() = delete;
};
