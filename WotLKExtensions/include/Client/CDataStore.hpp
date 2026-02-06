#pragma once

#include <cstdint>

struct CDataStore;

struct CDataStore_vTable
{
    void (__thiscall* InternalInitialize)(CDataStore*, uint8_t*, uint32_t, uint32_t);
    void (__thiscall* InternalDestroy)(CDataStore*, uint8_t*, uint32_t, uint32_t);
    int (__thiscall* InternalFetchRead)(CDataStore*, uint32_t, uint32_t, uint8_t*, uint32_t, uint32_t);
    int (__thiscall* InternalFetchWrite)(CDataStore*, uint32_t, uint32_t, uint8_t*, uint32_t, uint32_t);
    void (__thiscall* Destructor)(CDataStore*);
    void (__thiscall* Reset)(CDataStore*);
    bool (__thiscall* IsRead)(CDataStore*);
    void (__thiscall* Finalize)(CDataStore*);
    void (__thiscall* GetBufferParams)(CDataStore*, const void**, uint32_t*, uint32_t*);
    void (__thiscall* DetachBuffer)(CDataStore*, void**, uint32_t*, uint32_t*);
};

struct CDataStore
{
    CDataStore_vTable* vTable;
    int8_t* m_buffer;
    int32_t m_base;
    int32_t m_alloc;
    int32_t m_size;
    int32_t m_read;

    static void GenPacket(CDataStore* thisPacket);
    static void GetCString(CDataStore* thisPacket, char* cString, int32_t size);
    static void GetInt8(CDataStore* thisPacket, int8_t* var);
    static void GetInt16(CDataStore* thisPacket, int16_t* var);
    static void GetInt32(CDataStore* thisPacket, int32_t* var);
    static void GetInt64(CDataStore* thisPacket, int64_t* var);
    static void PutCString(CDataStore* thisPacket, const char* cString);
    static void PutInt8(CDataStore* thisPacket, int8_t value);
    static void PutInt16(CDataStore* thisPacket, int16_t value);
    static void PutInt32(CDataStore* thisPacket, int32_t value);
    static void PutInt64(CDataStore* thisPacket, int64_t value);
    static void Release(CDataStore* thisPacket);

    // vtable entries
    static bool IsRead(CDataStore* thisPacket);
};
