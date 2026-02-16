#include <CDBCMgr/CDBC.hpp>
#include <Client/SErr.hpp>
#include <Client/SFile.hpp>
#include <Client/SMem.hpp>
#include <Client/SStr.hpp>

#include <string>

CDBC::CDBC(int32_t numColumns, int32_t rowSize) : m_numColumns(numColumns), m_rowSize(rowSize)
{
}

void CDBC::LoadDB(const char* name, std::vector<char>* data)
{
    uint32_t buffer = 0;
    void* file = nullptr;
    std::string path = "DBFilesClient\\" + std::string(name);
    const char* filepath = path.c_str();

    if (m_isLoaded)
        return;

    if (!SFile::OpenFileEx(nullptr, filepath, 0x20000, &file))
        SErr::PrepareAppFatal(0x85100079, "Unable to open %s", filepath);

    if (!SFile::ReadFile(file, &buffer, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read signature from %s", filepath);

    if (buffer != 0x43424457) // WDBC but little endian so technically CBDW
        SErr::PrepareAppFatal(0x85100079, "Invalid signature 0x%x from %s", buffer, filepath);

    if (!SFile::ReadFile(file, &m_numRows, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read record count from %s", filepath);

    if (!m_numRows)
    {
        SFile::CloseFile(file);

        return;
    }

    if (!SFile::ReadFile(file, &buffer, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read column count from %s", filepath);

    if (buffer != m_numColumns)
        SErr::PrepareAppFatal(0x85100079, "%s has wrong number of columns (found %i, expected %i)", filepath, buffer, m_numColumns);

    if (!SFile::ReadFile(file, &buffer, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read row size from %s", filepath);

    if (buffer != m_rowSize)
        SErr::PrepareAppFatal(0x85100079, "%s has wrong row size (found %i, expected %i)", filepath, buffer, m_rowSize);

    if (!SFile::ReadFile(file, &buffer, 4, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read string size from %s", filepath);

    ReserveDataBlock();
    m_stringTable.resize(buffer);

    if (!SFile::ReadFile(file, data->data(), m_numRows * m_rowSize, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100079, "Unable to read row data from %s", filepath);

    if (!SFile::ReadFile(file, m_stringTable.data(), buffer, 0, 0, 0))
        SErr::PrepareAppFatal(0x85100086, "%s: Cannot read string table", filepath);

    m_isLoaded = true;

    SetMinMaxIndices();
    SFile::CloseFile(file);
}

void CDBC::UnloadDB()
{
    m_isLoaded = false;
    m_numRows = 0;
    m_maxIndex = 0xFFFFFFFF;
    m_minIndex = 0x7FFFFFFF;
    m_stringTable.clear();
}

int32_t CDBC::GetMinIndex() const
{
    return m_minIndex;
}

int32_t CDBC::GetMaxIndex() const
{
    return m_maxIndex;
}
