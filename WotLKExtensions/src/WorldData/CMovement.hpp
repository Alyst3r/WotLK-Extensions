#pragma once

#include <Data/Math.hpp>

#include <cstdint>

struct CMovement
{
    uint32_t padding0x00[4];
    C3Vector m_position;
    float padding0x1C;
    float m_orientation;
    float m_pitch;
    uint32_t padding28[7];
    uint32_t m_movementFlags;
    uint32_t m_movementFlags2;
    uint32_t padding0x4C[63];
};
