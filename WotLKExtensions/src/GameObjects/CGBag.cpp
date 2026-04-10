#include <GameObjects/CGBag.hpp>

int32_t CGBag::GetItemTypeCount(CGBag* thisBag, int32_t itemID, int32_t a3)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGBag*, int32_t, int32_t)>(0x754D00)(thisBag, itemID, a3);
}
