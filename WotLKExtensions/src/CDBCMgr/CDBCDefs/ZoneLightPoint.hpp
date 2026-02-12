#pragma optimize("", off)
#include <CDBCMgr/CDBC.hpp>
#include <CDBCMgr/CDBCMgr.hpp>
#include <Data/Structs.hpp>

#include <cstdint>

class ZoneLightPoint : public CDBC
{
public:
    const char* fileName = "ZoneLightPoint";
    ZoneLightPoint() : CDBC()
    {
        this->numColumns = sizeof(ZoneLightPointRow) / 4;
        this->rowSize = sizeof(ZoneLightPointRow);
    }

    ZoneLightPoint* LoadDB()
    {
        GlobalCDBCMap.addCDBC(this->fileName);
        CDBC::LoadDB(this->fileName);
        ZoneLightPoint::setupTable();
        GlobalCDBCMap.setIndexRange(this->fileName, this->minIndex, this->maxIndex);
        return this;
    }

    void ZoneLightPoint::setupTable()
    {
        ZoneLightPointRow* row = (ZoneLightPointRow*)this->rows;
        for (uint32_t i = 0; i < this->numRows; i++)
        {
            GlobalCDBCMap.addRow(this->fileName, row->m_ID, *row);
            ++row;
        }
    };
};
#pragma optimize("", on)
