#pragma once
#include <SharedDefines.hpp>

#include <vector>

class CDBC
{
public:
    CDBC(int32_t numColumns, int32_t rowSize);
    virtual ~CDBC() = default;

    void LoadDB(const char* name, std::vector<char>* data);
    void UnloadDB();

    virtual int32_t GetMinIndex() const;
    virtual int32_t GetMaxIndex() const;

protected:
    bool m_isLoaded = false;
    int32_t m_numColumns;
    int32_t m_numRows = 0;
    int32_t m_rowSize;
    int32_t m_maxIndex = 0xFFFFFFFF;
    int32_t m_minIndex = 0x7FFFFFFF;
    std::vector<char> m_stringTable;

    virtual void ReserveDataBlock() = 0;
    virtual void SetMinMaxIndices() = 0;
};
