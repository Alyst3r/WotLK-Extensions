#pragma once

#include <cstdint>

#include <SharedDefines.hpp>

class CGTooltip;

struct DBNameCache
{
    char m_name[48];
    WoWGUID m_guid;
    uint32_t m_race;
    uint32_t m_sex;
    char m_unk;
    uint32_t m_class;

    static DBNameCache* GetRecord(DBNameCache* thisCache, int64_t a2, int32_t a3, void* a4, CGTooltip* a5, int32_t a6);
};
