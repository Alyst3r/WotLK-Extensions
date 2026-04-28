#pragma once

#include <Data/Math.hpp>

#include <cstdint>
#include <vector>

struct ZoneLightData
{
    int32_t m_mapID = -1;
    int32_t m_lightID = -1;
    std::vector<C2Vector> m_pointData;
    C2Vector m_min = { FLT_MAX };
    C2Vector m_max = { FLT_MIN };

    static void ApplyZoneLightsExtensions();
    static void FillZoneLightData();
    static void FindAndAddZoneLightEx(C3Vector* vec);
};
