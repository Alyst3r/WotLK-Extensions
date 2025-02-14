#include "Main.h"

void Main::OnAttach()
{
	Init();
	
	// Apply patches
	Misc::ApplyPatches();
	Player::ApplyPatches();
}

void Main::Init()
{
	if (useCustomDBCs)
		CustomDBCMgr::Load();

	if (outOfBoundLuaFunctions)
	{
		// From AwesomeWotLK, invalid function pointer hack
		*reinterpret_cast<uint32_t*>(0xD415B8) = 1;
		*reinterpret_cast<uint32_t*>(0xD415BC) = 0x7FFFFFFF;
	}
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
