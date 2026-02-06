#pragma optimize("", off)
#include <CDBCMgr/CDBC.hpp>
#include <CDBCMgr/CDBCMgr.hpp>

struct ZoneLightRow
{
    int32_t ID;
    char* name;
    int32_t mapID;
    int32_t lightID;
};

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
            row->name = (char*)(stringTable + (uintptr_t)row->name);
            GlobalCDBCMap.addRow(this->fileName, row->ID, *row);
            ++row;
        }
    };
};
#pragma optimize("", on)
