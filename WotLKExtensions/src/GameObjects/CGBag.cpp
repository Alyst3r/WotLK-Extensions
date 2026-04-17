#include <GameObjects/CGBag.hpp>

int32_t CGBag::GetItemTypeCount(CGBag* thisBag, int32_t itemID, int32_t a3)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGBag*, int32_t, int32_t)>(0x754D00)(thisBag, itemID, a3);
}

bool CGBag::FindTotemOfCategory(int32_t totemCategory, int32_t a2)
{
    return reinterpret_cast<bool (__stdcall*)(int32_t, int32_t)>(0x7548F0)(totemCategory, 0);
}

int32_t CGBag::FindItemOfType(CGBag* thisBag, int32_t itemID, int32_t a3)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGBag*, int32_t, int32_t)>(0x754A20)(thisBag, itemID, a3);
}
