#pragma once

#include <Data/Structs.hpp>
#include <GameObjects/CGObject.hpp>

struct CPassenger
{
    uint32_t m_padding0x00[2];
    uint64_t m_transportGuid;
    C3Vector m_position;
    uint32_t m_padding0x1C;
    uint64_t m_compressedRotation;
    uint64_t m_guid2;
    uint32_t m_padding_0x2C;
};

struct CGGameObject : CGObject
{
    uint32_t m_padding0xD0[2];
    CPassenger m_passenger;
};
