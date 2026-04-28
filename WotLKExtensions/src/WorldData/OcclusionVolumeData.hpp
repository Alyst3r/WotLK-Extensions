#pragma once

#include <Data/Math.hpp>

#include <cstdint>
#include <vector>

struct OcclusionVolumeData
{
    int32_t m_mapID = -1;
    int32_t m_flags = -1;
    C3Vector m_min = { FLT_MAX, FLT_MAX, FLT_MAX };
    C3Vector m_max = { FLT_MIN, FLT_MIN, FLT_MIN };
    void* m_pointData;
    size_t m_pointCount = 0;

    static void ApplyOcclusionVolumeExtensions();
    static void FillOcclusionVolumeData();
};
