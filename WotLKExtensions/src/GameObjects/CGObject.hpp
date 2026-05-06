#pragma once

#include <cstdint>

#include <SharedDefines.hpp>

struct ObjectFields
{
    WoWGUID m_guid;
    int32_t m_type;
    int32_t m_entry;
    float m_scale;
    int32_t m_padding0x10;
};

struct CGObject
{
    void* m_vtable;
    int32_t m_padding0x04;
    ObjectFields* m_objectData;
    int32_t m_padding0x0C[49];
};
