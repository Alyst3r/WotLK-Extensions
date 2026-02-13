#pragma once

#include <cstdint>

struct DBClient
{
    void* m_vtable = nullptr;
    bool m_isLoaded = false;
    int m_numRows = 0;
    int m_maxIndex = 0xFFFFFFFF;
    int m_minIndex = 0xFFFFFFF;
    char* m_stringTable = nullptr;
    void* m_vtable2 = nullptr;
    int* m_firstRow = nullptr;
    int* m_Rows = nullptr;

    // this technically is not a part of DBClient iirc but who cares
    static double GetGameTableValue(uint32_t tableID, uint32_t classID, uint32_t combatRating);
    static int32_t GetLocalizedRow(void* thisDBC, uint32_t rowIndex, void* row);
    static void* GetRow(void* vtable2, uint32_t rowIndex);
};

