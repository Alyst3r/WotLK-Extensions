#include "CDBC.h"
#include "../Logger.h"

void CDBC::LoadDB(const char* filename)
{
    char name[512];

    CustomDBC dbcData = { 0 };
    uint32_t Buffer = 0;
    void* FileBlock = 0;
    int val = 0;

    SStr::Printf(name, 512, "DBFilesClient\\%s.cdbc", filename);
    LOG_DEBUG << name;
    if (allCDBCs.find(filename) != allCDBCs.end())
        return;

    if (!SFile::OpenFileEx(0, name, 0x20000, &FileBlock))
        SErr::PrepareAppFatal(0x85100079, "Unable to open %s", name);

    if (!SFile::ReadFile(FileBlock, &Buffer, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read signature from %s", name);

    if (Buffer != 0x43424457) // WDBC but little endian so technically CBDW
        SErr::PrepareAppFatal(0x85100079, "Invalid signature 0x%x from %s", Buffer, name);

    if (!SFile::ReadFile(FileBlock, &dbcData.numRows, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read record count from %s", name);

    if (!dbcData.numRows)
    {
        SFile::CloseFile(FileBlock);
        return;
    }

    if (!SFile::ReadFile(FileBlock, &val, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read column count from %s", name);

    if (val != this->numColumns)
        SErr::PrepareAppFatal(0x85100079, "%s has wrong number of columns (found %i, expected %i)", name, val, this->numColumns);

    if (!SFile::ReadFile(FileBlock, &val, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read row size from %s", name);

    if (val != this->rowSize)
        SErr::PrepareAppFatal(0x85100079, "%s has wrong row size (found %i, expected %i)", name, val, this->rowSize);

    if (!SFile::ReadFile(FileBlock, &val, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read string size from %s", name);

    dbcData.rows = malloc(dbcData.numRows * this->rowSize); //SMem::Alloc(this->numRows * this->rowSize, name, -2, 0);

    if (!SFile::ReadFile(FileBlock, dbcData.rows, dbcData.numRows * this->rowSize, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read row data from %s", name);

    dbcData.stringTable = malloc(val);//SMem::Alloc(len, filename, -2, 0);

    if (!SFile::ReadFile(FileBlock, dbcData.stringTable, val, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100086, "%s: Cannot read string table", name);

    dbcData.minIndex = *(uintptr_t*)dbcData.rows;
    dbcData.maxIndex = *((uintptr_t*)dbcData.rows + ((dbcData.numRows - 1) * this->numColumns));

    SFile::CloseFile(FileBlock);
    allCDBCs.insert(std::make_pair(filename, dbcData));
}

void CDBC::UnloadDB(const char* filename)
{
    if (allCDBCs.find(filename) != allCDBCs.end())
        allCDBCs.erase(filename);
};

int32_t CDBC::GetMinIndex(const char* filename)
{
    auto dbc = allCDBCs.find(filename);

    if (dbc != allCDBCs.end())
        return dbc->second.minIndex;

    return -1;
}

int32_t CDBC::GetMaxIndex(const char* filename)
{
    auto dbc = allCDBCs.find(filename);

    if (dbc != allCDBCs.end())
        return dbc->second.maxIndex;

    return -1;
}

uint32_t CDBC::GetNumRows(const char* filename)
{
    auto dbc = allCDBCs.find(filename);

    if (dbc != allCDBCs.end())
        return dbc->second.numRows;

    return 0;
}
