#include <WorldData/CWorld.hpp>

void CWorld::LoadMap(const char* directory, C3Vector* pos, uint32_t mapID)
{
    reinterpret_cast<void (__cdecl*)(const char*, C3Vector*, uint32_t)>(0x781430)(directory, pos, mapID);
}

void CWorld::UnloadMap()
{
    reinterpret_cast<void (__cdecl*)()>(0x783180)();
}

