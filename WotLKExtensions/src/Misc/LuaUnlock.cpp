#include "LuaUnlock.hpp"
#include <PatchConfig.hpp>
#include <Misc/Util.hpp>
#include <Misc/Logger.hpp>

void LuaUnlock::ApplyPatches()
{
	// Unlock Lua engine for use in WotLK
	// This is done by patching the game's code to bypass the checks that disable Lua functionality
	// The specific addresses and values to patch would depend on the version of the game and may require reverse engineering to determine

#if LUAUNLOCK_PATCH

	uint8_t targetOverrideBytes[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };

	//"Patching 0x00524FD8 (jnz -> je for TargetNearestUnit)";
	Util::SetByteAtAddress(reinterpret_cast<void*>(0x00524FD8), 0x84);

	//"Patching 0x00524C6F (NOP for CGGameUI__Target)";
	Util::OverwriteBytesAtAddress(0x00524C6F, targetOverrideBytes, sizeof(targetOverrideBytes));
	
	//"Patching 0x005191D7 (ja -> jz for CanPerformAction)";
	Util::SetByteAtAddress(reinterpret_cast<void*>(0x005191D7), 0x72);
#endif
}