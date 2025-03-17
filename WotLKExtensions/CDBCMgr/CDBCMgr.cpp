#include "CDBCMgr.h"
#include "CDBCDefs/LFGRoles.h"
#include "../Logger.h"

CDBCMgr GlobalCDBCMap;

void CDBCMgr::Load()
{
	LFGRoles().LoadDB();
}

void __declspec(naked) RegisterDBCEx()
{
	CDBCMgr::Load();

	CDBCMgr::Test();

	__asm
	{
		mov ecx, 0x6337D0;
		call ecx;
		ret;
	}
}

void CDBCMgr::PatchAddress()
{
	Util::OverwriteUInt32AtAddress(0x634E30, (uint32_t)&RegisterDBCEx - 0x634E34);
}

void CDBCMgr::Test()
{
	const char* filename = "LFGRoles";
	auto dbc = allCDBCs.find(filename);

	LOG_DEBUG << allCDBCs.size();

	if (dbc == allCDBCs.end())
	{
		LOG_DEBUG << "Not found.";
		return;
	}

	LOG_DEBUG << filename;
	LOG_DEBUG << "rows: " << dbc->second.rows;
	LOG_DEBUG << "numRows: " << dbc->second.numRows;
	LOG_DEBUG << "minIndex: " << dbc->second.minIndex;
	LOG_DEBUG << "maxIndex: " << dbc->second.maxIndex;
	LOG_DEBUG << "stringTable: " << dbc->second.stringTable;
}
