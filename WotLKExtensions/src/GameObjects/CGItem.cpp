#include <GameObjects/CGItem.hpp>

char* CGItem::BuildItemName(char* buffer, int32_t size, int32_t itemID, int32_t a4)
{
    return reinterpret_cast<char* (__cdecl*)(char*, int32_t, int32_t, int32_t)>(0x706D70)(buffer, size, itemID, a4);
}

int32_t CGItem::sub_61DC90(void* thisObject)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*)>(0x61DC90)(thisObject);
}

int32_t CGItem::sub_707390(void* thisObject, int32_t a2)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*, int32_t)>(0x707390)(thisObject, a2);
}

bool CGItem::sub_708520(CGItem* thisItem)
{
    return reinterpret_cast<bool (__thiscall*)(CGItem*)>(0x708520)(thisItem);
}
