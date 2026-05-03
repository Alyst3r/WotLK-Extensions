#include <Data/DBPetitionCache.hpp>

DBPetitionCache* DBPetitionCache::GetInfoBlockByID(DBPetitionCache* thisCache, int32_t id, int64_t* guid, void* a4, CGTooltip* tooltip, int32_t a6)
{
    return reinterpret_cast<DBPetitionCache* (__thiscall*)(DBPetitionCache*, int32_t, int64_t*, void*, CGTooltip*, int32_t)>(0x67EF70)(thisCache, id, guid, a4, tooltip, a6);
}
