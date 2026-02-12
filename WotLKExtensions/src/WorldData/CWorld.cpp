#include <WorldData/CWorld.hpp>

void CWorld::LoadMap(const char* directory, C3Vector* pos, uint32_t mapID)
{
    reinterpret_cast<void (__cdecl*)(const char*, C3Vector*, uint32_t)>(0x781430)(directory, pos, mapID);
}

void CWorld::UnloadMap()
{
    reinterpret_cast<void (__cdecl*)()>(0x783180)();
}

int CWorld::Pos3Dto2D(void* thisWorld, C3Vector* pos3d, C3Vector* pos2d, uint32_t* flags)
{
    return reinterpret_cast<int (__thiscall*)(void*, C3Vector*, C3Vector*, uint32_t*)>(0x4F6D20)(thisWorld, pos3d, pos2d, flags);
}
