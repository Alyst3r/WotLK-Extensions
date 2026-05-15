#pragma once

#include <cstdint>
#include <string>

struct DBClient;

// Aleist3r: not typedefing other six functions since we don't call them anywhere for now
struct DBClient_vtable
{
    int32_t (__thiscall* Destructor)(DBClient*, char);
    void (__thiscall* Load)(DBClient*, const char*, int32_t);
};

struct DBClient
{
    DBClient_vtable* m_vtable = nullptr;
    bool m_isLoaded = false;
    int32_t m_numRows = 0;
    int32_t m_maxIndex = 0xFFFFFFFF;
    int32_t m_minIndex = 0x7FFFFFFF;
    char* m_stringTable = nullptr;
    void* m_vtable2 = nullptr;
    int32_t* m_firstRow = nullptr;
    int32_t* m_rows = nullptr;

    // this technically is not a part of DBClient iirc but who cares
    static double GetGameTableValue(uint32_t tableID, uint32_t classID, uint32_t combatRating);
    static int32_t GetLocalizedRow(DBClient* thisDBC, uint32_t rowIndex, void* row);
    static void* GetRow(void* vtable2, uint32_t rowIndex);
    static void* GetRow(DBClient* thisRow, uint32_t index, size_t rowSize);
    static bool IsValidIndex(DBClient* dbc, uint32_t rowIndex);

    static void RegisterBaseEx();

    static void LoadDBC(DBClient* thisDBC, const char* string, int32_t exitCode);
    static void ReloadAll();
    static bool ReloadByName(std::string& name);
};
