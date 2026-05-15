#include <CDBCMgr/CDBCMgr.hpp>
#include <CDBCMgr/CDBCDefs/LFGRoles.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLight.hpp>
#include <CDBCMgr/CDBCDefs/ZoneLightPoint.hpp>
#include <Client/DBClient.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>
#include <WorldData/OcclusionVolumeData.hpp>
#include <WorldData/ZoneLightData.hpp>

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

    if (sDC.GetShouldFillZoneLightData())
        ZoneLightData::FillZoneLightData();
#endif
}

void CDBCMgr::Unload()
{
#if LFGROLES_DBC
    sDC.UnloadLFGRolesDB();
#endif

#if SPELLATTRIBUTESEXTENDED_DBC
    sDC.UnloadSpellAttributesExtendedDB();
#endif

#if OCCLUSIONVOLUME_DBC
    sDC.ClearOcclusionVolume();
    sDC.UnloadOcclusionVolumePointDB();
    sDC.UnloadOcclusionVolumeDB();
#endif

#if ZONELIGHT_DBC
    sDC.SetShouldFillZoneLightData(true);
    sDC.ClearZoneLight();
    sDC.UnloadZoneLightPointDB();
    sDC.UnloadZoneLightDB();
#endif
}

void CDBCMgr::Register()
{
    DBClient::RegisterBaseEx();
    Load();
}

void CDBCMgr::PatchAddress()
{
    Util::OverwriteUInt32AtAddress(0x634E30, reinterpret_cast<uint32_t>(&Register) - 0x634E34);
}
