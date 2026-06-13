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
    int32_t m_padding0x0C[2];
    int32_t m_typeID;
    int32_t m_padding0x18[39];
    void* m_model;
    int32_t m_padding0xB8[6];
};
