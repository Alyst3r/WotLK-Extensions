#include <CDBCMgr/CDBCMgr.hpp>
#include <CDBCMgr/CDBCDefs/LFGRoles.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLight.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLightPoint.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>

void CDBCMgr::Load()
{
    DataContainer& dc = DataContainer::GetInstance();

#if LFGROLES_DBC
    dc.LoadLFGRolesDB();
#endif

#if ZONELIGHT_DBC
    dc.LoadZoneLightDB();
    dc.LoadZoneLightPointDB();
#endif
}

static void __declspec(naked) RegisterDBCEx()
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
