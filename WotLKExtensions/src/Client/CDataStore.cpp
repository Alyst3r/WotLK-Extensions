#include <Client/CDataStore.hpp>

void CDataStore::GenPacket(CDataStore* thisPacket)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*)>(0x401050)(thisPacket);
}

void CDataStore::GetCString(CDataStore* thisPacket, char* cString, int32_t size)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, char*, int32_t)>(0x47B480)(thisPacket, cString, size);
}

void CDataStore::GetInt8(CDataStore* thisPacket, int8_t* var)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, int8_t*)>(0x47B340)(thisPacket, var);
}

void CDataStore::GetInt16(CDataStore* thisPacket, int16_t* var)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, int16_t*)>(0x47B380)(thisPacket, var);
}

void CDataStore::GetInt32(CDataStore* thisPacket, int32_t* var)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, int32_t*)>(0x47B3C0)(thisPacket, var);
}

void CDataStore::GetInt64(CDataStore* thisPacket, int64_t* var)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, int64_t*)>(0x47B400)(thisPacket, var);
}

void CDataStore::PutCString(CDataStore* thisPacket, const char* cString)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, const char*)>(0x47B300)(thisPacket, cString);
}

void CDataStore::PutInt8(CDataStore* thisPacket, int8_t value)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, int8_t)>(0x47AFE0)(thisPacket, value);
}

void CDataStore::PutInt16(CDataStore* thisPacket, int16_t value)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, int16_t)>(0x47AFE0)(thisPacket, value);
}

void CDataStore::PutInt32(CDataStore* thisPacket, int32_t value)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, int32_t)>(0x47B0A0)(thisPacket, value);
}

void CDataStore::PutInt64(CDataStore* thisPacket, int64_t value)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*, int64_t)>(0x47B100)(thisPacket, value);
}

void CDataStore::Release(CDataStore* thisPacket)
{
    reinterpret_cast<void (__thiscall*)(CDataStore*)>(0x403880)(thisPacket);
}

bool CDataStore::IsRead(CDataStore* thisPacket)
{
    return reinterpret_cast<bool (__thiscall*)(CDataStore*)>(0x4010D0)(thisPacket);
}
