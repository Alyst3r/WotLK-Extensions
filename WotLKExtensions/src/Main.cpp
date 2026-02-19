#include <Main.hpp>

void Main::OnAttach()
{
    Init();
    
    // this one is non-optional, it's WoWTime fix I guess
    // and don't let me get started how retarded original idea behind packing like this is
    WoWTime::ApplyWoWTimePatches();

    // Apply patches
    Misc::ApplyPatches();
    CGPlayer::ApplyPatches();
    CGTooltip::ApplyPatches();
    
#if CUSTOM_DBC && ZONELIGHT_DBC
    ZoneLightData::ApplyZoneLightsExtensions();
#endif

    // Custom dbc loader
#if CUSTOM_DBC
    CDBCMgr::PatchAddress();
#endif
}

void Main::Init()
{
    // just to create singleton early to let everything else access already initialized instance
    DataContainer& dc = DataContainer::GetInstance();

    dc.SetYearOffsetMultiplier();

#if CUSTOMPACKETS_PATCH
    CNetClient::Apply();
#endif

#if OOBLUAFUNCTIONS_PATCH || CUSTOM_DBC || CUSTOMPACKETS_PATCH
    // From AwesomeWotLK, invalid function pointer hack
    *reinterpret_cast<uint32_t*>(0xD415B8) = 1;
    *reinterpret_cast<uint32_t*>(0xD415BC) = 0x7FFFFFFF;
#endif

#if OOBLUAFUNCTIONS_PATCH || CUSTOMPACKETS_PATCH
    CustomLua::Apply();
#endif
}

bool __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
        CreateThread(nullptr, 0, [](LPVOID) -> DWORD
        {
            Main::OnAttach();
            return 0;
        }, nullptr, 0, nullptr);
    }
    return true;
}
