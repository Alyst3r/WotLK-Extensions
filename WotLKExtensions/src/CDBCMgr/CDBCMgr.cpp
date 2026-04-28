#include <CDBCMgr/CDBCMgr.hpp>
#include <CDBCMgr/CDBCDefs/LFGRoles.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLight.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLightPoint.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>
#include <WorldData/OcclusionVolumeData.hpp>

#include <PatchConfig.hpp>

void CDBCMgr::Load()
{
#if LFGROLES_DBC
    sDC.LoadLFGRolesDB();
#endif

#if SPELLATTRIBUTESEXTENDED_DBC
    sDC.LoadSpellAttributesExtendedDB();
#endif

#if OCCLUSIONVOLUME_DBC
    sDC.LoadOcclusionVolumeDB();
    sDC.LoadOcclusionVolumePointDB();
    OcclusionVolumeData::FillOcclusionVolumeData();
    OcclusionVolumeData::ApplyOcclusionVolumeExtensions();
#endif

#if ZONELIGHT_DBC
    sDC.LoadZoneLightDB();
    sDC.LoadZoneLightPointDB();
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
    Util::OverwriteUInt32AtAddress(0x634E30, reinterpret_cast<uint32_t>(&RegisterDBCEx) - 0x634E34);
}
