#include <Data/DBItemCache.hpp>

DBItemCache* DBItemCache::GetInfoBlockByID(DBItemCache* thisCache, int32_t itemID, int64_t* guid, void* a4, CGTooltip* tooltip, int32_t a6)
{
    return reinterpret_cast<DBItemCache* (__thiscall*)(DBItemCache*, int32_t, int64_t*, void*, CGTooltip*, int32_t)>(0x67CA30)(thisCache, itemID, guid, a4, tooltip, a6);
}
