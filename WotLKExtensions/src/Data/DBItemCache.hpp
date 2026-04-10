#pragma once

#include <Client/CGTooltip.hpp>

#include <cstdint>

struct DBItemCache
{
    int32_t padding[125];
    char* m_name;

    static DBItemCache* GetInfoBlockByID(DBItemCache* thisCache, int32_t itemID, int64_t* guid, void* a4, CGTooltip* tooltip, int32_t a6);
};
