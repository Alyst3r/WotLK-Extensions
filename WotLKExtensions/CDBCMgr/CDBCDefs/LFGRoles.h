#pragma optimize("", off)
#include "../CDBC.h"
#include "../CDBCMgr.h"

struct LFGRolesRow
{
	uint32_t ClassID;
	uint32_t Roles;
};

class LFGRoles : public CDBC {
public:
	const char* fileName = "DBFilesClient\\LFGRoles.cdbc";

	LFGRoles(): CDBC()
	{
		this->numColumns = sizeof(LFGRolesRow) / 4;
		this->rowSize = sizeof(LFGRolesRow);
	}

	LFGRoles* LoadDB()
	{
		GlobalCDBCMap.addCDBC("LFGRoles");
		CDBC::LoadDB(this->fileName);
		LFGRoles::setupTable();
		return this;
	};

	void LFGRoles::setupTable() {
		LFGRolesRow* row = static_cast<LFGRolesRow*>(this->rows);

		for (uint32_t i = 0; i < this->numRows; i++)
		{
			GlobalCDBCMap.addRow("LFGRoles", row->ClassID, *row);
			++row;
		}
	};
};
#pragma optimize("", on)
