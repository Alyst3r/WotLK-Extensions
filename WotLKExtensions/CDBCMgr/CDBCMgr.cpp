#include "CDBCMgr.h"
#include "CDBCDefs/LFGRoles.h"
#include "CDBCDefs/ZoneLight.h"
#include "CDBCDefs/ZoneLightPoint.h"

CDBCMgr GlobalCDBCMap;

void CDBCMgr::Load()
{
	if (useLFGRolesDBC)
		LFGRoles().LoadDB();

	if (useZoneLightDBCs)
	{
		ZoneLight().LoadDB();
		ZoneLightPoint().LoadDB();
	}
}

void CDBCMgr::addCDBC(std::string cdbcName)
{
	allCDBCs[cdbcName] = CDBC();
	cdbcIndexRanges[cdbcName] = { 0, 0 };
}

void __declspec(naked) RegisterDBCEx()
{
	CDBCMgr::Load();

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
