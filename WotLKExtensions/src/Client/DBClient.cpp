#include <Client/DBClient.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Logger.hpp>
#include <Misc/Util.hpp>

double DBClient::GetGameTableValue(uint32_t tableID, uint32_t classID, uint32_t combatRating)
{
    return reinterpret_cast<double (__cdecl*)(uint32_t, uint32_t, uint32_t)>(0x7F6990)(tableID, classID, combatRating);
}

int32_t DBClient::GetLocalizedRow(DBClient* thisDBC, uint32_t rowIndex, void* row)
{
    return reinterpret_cast<int (__thiscall*)(DBClient*, uint32_t, void*)>(0x4CFD20)(thisDBC, rowIndex, row);
}

void* DBClient::GetRow(void* vtable2, uint32_t rowIndex)
{
    return reinterpret_cast<void* (__thiscall*)(void*, uint32_t)>(0x65C290)(vtable2, rowIndex);
}

// Aleist3r: wrapper for some special case DBCs where index column is omitted
void* DBClient::GetRow(DBClient* thisRow, uint32_t index, size_t rowSize)
{
    if (index >= thisRow->m_numRows)
        return nullptr;

    return &thisRow->m_firstRow[index * rowSize / 4];
}

bool DBClient::IsValidIndex(DBClient* dbc, uint32_t rowIndex)
{
    if (rowIndex >= dbc->m_minIndex && rowIndex <= dbc->m_maxIndex)
        return true;

    return false;
}

void DBClient::RegisterBaseEx()
{
    std::vector<DBClientEntry>& data = sDC.GetDBCDataVector();

    for (size_t i = 0; i < data.size(); i++)
        LoadDBC(data[i].m_dbc, ".\\DBClient.cpp", data[i].m_exitCode);
}

void DBClient::LoadDBC(DBClient* thisDBC, const char* string, int32_t exitCode)
{
    thisDBC->m_vtable->Load(thisDBC, string, exitCode);
}

void DBClient::ReloadAll()
{
    std::vector<DBClientEntry>& data = sDC.GetDBCDataVector();

    for (size_t i = 0; i < data.size(); i++)
    {
        void* firstRow = data[i].m_dbc->m_firstRow;
        void* rows = data[i].m_dbc->m_rows;
        void* stringTable = data[i].m_dbc->m_stringTable;

        data[i].m_dbc->m_isLoaded = false;

        LoadDBC(data[i].m_dbc, ".\\DBClient.cpp", data[i].m_exitCode);
    }
}

bool DBClient::ReloadByName(std::string& name)
{
    bool result = false;
    std::vector<DBClientEntry>& data = sDC.GetDBCDataVector();

    Util::StringToLower(name);

    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].m_name == name)
        {
            result = true;
            data[i].m_dbc->m_isLoaded = false;

            LoadDBC(data[i].m_dbc, ".\\DBClient.cpp", data[i].m_exitCode);

            break;
        }
    }

    return result;
}
