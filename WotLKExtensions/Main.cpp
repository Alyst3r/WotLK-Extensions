#include "Main.h"
#include "Misc.h"

void Main::OnAttach()
{
	// From AwesomeWotLK, invalid function pointer hack
	*reinterpret_cast<uint32_t*>(0xD415B8) = 1;
	*reinterpret_cast<uint32_t*>(0xD415BC) = 0x7FFFFFFF;

	// Apply patches
	Misc::ApplyPatches();
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
