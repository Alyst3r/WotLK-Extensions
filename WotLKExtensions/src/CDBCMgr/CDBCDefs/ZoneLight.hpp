#pragma optimize("", off)
#include <CDBCMgr/CDBC.hpp>
#include <CDBCMgr/CDBCMgr.hpp>

#include <SharedDefines.hpp>

class ZoneLight : public CDBC
{
public:
    const char* fileName = "ZoneLight";
    ZoneLight() : CDBC()
    {
        this->numColumns = sizeof(ZoneLightRow) / 4;
        this->rowSize = sizeof(ZoneLightRow);
    }

    ZoneLight* LoadDB()
    {
        GlobalCDBCMap.addCDBC(this->fileName);
        CDBC::LoadDB(this->fileName);
        ZoneLight::setupStringsAndTable();
        GlobalCDBCMap.setIndexRange(this->fileName, this->minIndex, this->maxIndex);
        return this;
    };

    void ZoneLight::setupStringsAndTable()
    {
        ZoneLightRow* row = (ZoneLightRow*)this->rows;
        uintptr_t stringTable = (uintptr_t)this->stringTable;
        for (uint32_t i = 0; i < this->numRows; i++)
        {
            row->m_name = (char*)(stringTable + (uintptr_t)row->m_name);
            GlobalCDBCMap.addRow(this->fileName, row->m_ID, *row);
            ++row;
        }
    };
};
#pragma optimize("", on)
