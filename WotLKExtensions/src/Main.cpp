#include <Main.hpp>

void Main::OnAttach()
{
    Init();
    
    // Apply patches
    Misc::ApplyPatches();
    CGPlayer::ApplyPatches();
    WorldDataExtensions::ApplyPatches();

    // Custom dbc loader
#if CUSTOM_DBC
    CDBCMgr::PatchAddress();
#endif
}

void Main::Init()
{
    Misc::SetYearOffsetMultiplier();

#if CUSTOMPACKETS_PATCH
    CNetClient::Apply();
#endif

#if OOBLUAFUNCTIONS_PATCH || CUSTOM_DBC || CUSTOMPACKETS_PATCH
    // From AwesomeWotLK, invalid function pointer hack
    *(uint32_t*)0xD415B8 = 1;
    *(uint32_t*)0xD415BC = 0x7FFFFFFF;
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
