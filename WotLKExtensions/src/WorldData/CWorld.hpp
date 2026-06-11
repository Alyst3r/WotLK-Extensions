#pragma once

#include <Data/Math.hpp>
#include <WorldData/CGWorldFrame.hpp>

class CWorld
{
public:
    static void LoadMap(const char* directory, C3Vector* pos, uint32_t mapID);
    static void UnloadMap();

private:
    CWorld() = delete;
    ~CWorld() = delete;
};
