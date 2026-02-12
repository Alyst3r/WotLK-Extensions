#pragma once

#include <Data/Math.hpp>

#include <cstdint>
#include <vector>

struct ZoneLightData
{
    int32_t m_mapID = -1;
    int32_t m_lightID = -1;
    std::vector<C2Vector> m_pointData;
    float m_minX = FLT_MAX;
    float m_minY = FLT_MAX;
    float m_maxX = FLT_MIN;
    float m_maxY = FLT_MIN;

    static void ApplyZoneLightsExtensions();
    static void FillZoneLightData();
    static void FindAndAddZoneLightEx(C3Vector* vec);
};
