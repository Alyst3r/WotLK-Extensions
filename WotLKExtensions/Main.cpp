#include "Main.h"

void Main::OnAttach()
{
	Init();
	
	// Apply patches
	Misc::ApplyPatches();
	Player::ApplyPatches();
	WorldDataExtensions::ApplyPatches();

	// Custom dbc loader
	if (useCustomDBCFiles)
		CDBCMgr::PatchAddress();
}

void Main::Init()
{
	Misc::SetYearOffsetMultiplier();

	if (customPackets)
		CustomPacket::Apply();

	if (outOfBoundLuaFunctions || useCustomDBCFiles || customPackets)
	{
		// From AwesomeWotLK, invalid function pointer hack
		*(uint32_t*)0xD415B8 = 1;
		*(uint32_t*)0xD415BC = 0x7FFFFFFF;
	}

	if (outOfBoundLuaFunctions || customPackets)
		CustomLua::Apply();
}

extern "C"
{
	__declspec(dllexport) void WotLKExtensionsDummy() {}
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
