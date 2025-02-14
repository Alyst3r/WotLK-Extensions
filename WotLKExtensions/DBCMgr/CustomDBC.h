#pragma once

#include "../SharedDefines.h"
#include <string>

class CustomDBC
{
public:
    CustomDBC()
    {
        isLoaded = false;
        numRows = 0;
        minIndex = 0;
        maxIndex = 0;
        rows = 0;
    }
    void* stringTable = 0;
    uint32_t numColumns = 0;
    uint32_t rowSize = 0;
    void* rows;
    uint32_t numRows;

    CustomDBC* LoadDB(const char* filename);
    void UnloadDB();
    void GetMinMaxIndices();
    virtual ~CustomDBC() = default;
private:
    bool isLoaded;
    uint32_t minIndex;
    uint32_t maxIndex;
};
