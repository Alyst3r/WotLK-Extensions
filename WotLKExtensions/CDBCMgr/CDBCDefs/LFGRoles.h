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
	const char* fileName = "LFGRoles";

	LFGRoles(): CDBC()
	{
		this->numColumns = sizeof(LFGRolesRow) / 4;
		this->rowSize = sizeof(LFGRolesRow);
	}

	LFGRoles* LoadDB()
	{
		CDBC::LoadDB(this->fileName);
		return this;
	};

	void* GetRow(const char* filename, int32_t index) override
	{
		if (index >= GetMinIndex(filename) && index <= GetMaxIndex(filename))
		{
			auto it = allCDBCs.find(filename);

			if (it != allCDBCs.end())
			{
				uint32_t* ptr = (uint32_t*)it->second.rows;

				for (uint32_t i = 0; i < GetNumRows(filename); i++)
				{
					if (*ptr == index)
						return (void*)ptr;

					ptr += sizeof(LFGRolesRow) / 4;
				}
			}
		}

		return nullptr;
	}
};
#pragma optimize("", on)
