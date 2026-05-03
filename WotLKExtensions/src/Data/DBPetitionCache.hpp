#pragma once

#include <cstdint>

class CGTooltip;

struct DBPetitionCache
{
    int32_t m_padding0x00[2];
    int64_t m_creatorGuid;
    int32_t m_padding0x10[1260];

    static DBPetitionCache* GetInfoBlockByID(DBPetitionCache* thisCache, int32_t ID, int64_t* guid, void* a4, CGTooltip* tooltip, int32_t a6);
};
