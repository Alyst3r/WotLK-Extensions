#pragma once

#include <Data/Math.hpp>

class CWorld
{
public:
    static void LoadMap(const char* directory, C3Vector* pos, uint32_t mapID);
    static void UnloadMap();

    static int Pos3Dto2D(void* thisWorld, C3Vector* pos3d, C3Vector* pos2d, uint32_t* flags);

private:
    CWorld() = delete;
    ~CWorld() = delete;
};
