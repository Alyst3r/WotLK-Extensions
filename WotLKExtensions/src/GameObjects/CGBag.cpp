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

/// NOTE: itemObj, is currently typed as uint32_t*, but as far as I can see, it should either be the CGObject*, or CGItem*
/// The reason it's currently uint32_t* is because the original function signature is __thiscall int32_t FindItemSlot(CGBag* thisBag, CGObject* itemObj)
int32_t CGBag::FindItemSlot(CGBag* thisBag, uint32_t* itemObj)
{
    return reinterpret_cast<int32_t(__thiscall*)(CGBag*, uint32_t*)>(0x754040)(thisBag, itemObj);
}

int32_t CGBag::GetNumFreeInvSlots(CGBag* thisBag)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGBag*)>(0x754470)(thisBag);
}