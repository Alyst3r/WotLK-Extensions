#pragma once

#include <Data/Math.hpp>

#include <cstdint>

struct CMovement
{
    uint32_t padding0x00[4];
    C3Vector position;
    float padding0x1C;
    float orientation;
    float pitch;
    uint32_t padding28[7];
    uint32_t movementFlags;
    uint32_t movementFlags2;
    uint32_t padding0x4C[63];
};
