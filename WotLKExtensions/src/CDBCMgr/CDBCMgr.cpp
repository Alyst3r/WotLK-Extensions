#include <CDBCMgr/CDBCMgr.hpp>
#include <CDBCMgr/CDBCDefs/LFGRoles.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLight.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLightPoint.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>

CDBCMgr GlobalCDBCMap;

void CDBCMgr::Load()
{
#if LFGROLES_DBC
    LFGRoles().LoadDB();
#endif

#if ZONELIGHT_DBC
    ZoneLight().LoadDB();
    ZoneLightPoint().LoadDB();
#endif
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
