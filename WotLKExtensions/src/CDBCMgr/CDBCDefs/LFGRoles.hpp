#pragma optimize("", off)
#include <CDBCMgr/CDBC.hpp>
#include <CDBCMgr/CDBCMgr.hpp>

#include <SharedDefines.hpp>

class LFGRoles : public CDBC
{
public:
    const char* fileName = "LFGRoles";

    LFGRoles(): CDBC()
    {
        this->numColumns = sizeof(LFGRolesRow) / 4;
        this->rowSize = sizeof(LFGRolesRow);
    }

    LFGRoles* LoadDB()
    {
        GlobalCDBCMap.addCDBC(this->fileName);
        CDBC::LoadDB(this->fileName);
        LFGRoles::setupTable();
        GlobalCDBCMap.setIndexRange(this->fileName, this->minIndex, this->maxIndex);
        return this;
    };

    void LFGRoles::setupTable()
    {
        LFGRolesRow* row = (LFGRolesRow*)this->rows;

        for (uint32_t i = 0; i < this->numRows; i++)
        {
            GlobalCDBCMap.addRow(this->fileName, row->m_classID, *row);
            ++row;
        }
    };
};
#pragma optimize("", on)
