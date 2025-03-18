#pragma optimize("", off)
#include "../CDBC.h"
#include "../CDBCMgr.h"

struct ZoneLightPointRow
{
	int32_t ID;
	int32_t zoneLightID;
	float positionX;
	float positionY;
	int32_t pointOrder;
};

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
			GlobalCDBCMap.addRow(this->fileName, row->ID, *row);
			++row;
		}
	};
};
#pragma optimize("", on)
