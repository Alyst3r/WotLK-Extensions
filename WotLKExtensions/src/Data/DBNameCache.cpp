#include <Data/DBNameCache.hpp>

DBNameCache* DBNameCache::GetRecord(DBNameCache* thisCache, int64_t a2, int32_t a3, void* a4, CGTooltip* a5, int32_t a6)
{
	return reinterpret_cast<DBNameCache* (__thiscall*)(DBNameCache*, int64_t, int32_t, void*, CGTooltip*, int32_t)>(0x67D770)(thisCache, a2, a3, a4, a5, a6);
}
