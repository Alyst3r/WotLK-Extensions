#include <Misc/LuaUnlock.hpp>
#include <Misc/Util.hpp>

void LuaUnlock::ApplyPatches()
{
    // Unlock Lua engine for use in WotLK
    // This is done by patching the game's code to bypass the checks that disable Lua functionality
    // The specific addresses and values to patch would depend on the version of the game and may require reverse engineering to determine

    uint8_t targetOverrideBytes[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
    uint8_t functionPatch[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 };

    // NOP for TargetNearestEnemy;
    Util::OverwriteBytesAtAddress(0x524FD7, targetOverrideBytes, sizeof(targetOverrideBytes));

    // jz -> jmp for CGGameUI::Target;
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x524C76), 0xEB);
    
    // CGGameUI::CheckPermissions() always returns 0
    Util::OverwriteBytesAtAddress(0x5191C0, functionPatch, sizeof(functionPatch));
}
