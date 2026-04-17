#include <Client/FrameScript.hpp>
#include <Client/MacroConditions.hpp>
#include <Misc/Logger.hpp>
#include <Misc/Util.hpp>

#include <SharedDefines.hpp>

#include <Windows.h>

void MacroConditions::Apply()
{
    Util::OverwriteUInt32AtAddress(0x5F0F9D, reinterpret_cast<uint32_t>(&Evaluate) - 0x5F0FA1);
}

int32_t __fastcall MacroConditions::Evaluate(MacroConditions* thisConditions, int32_t unused, uint32_t* a2)
{
    return reinterpret_cast<int32_t (__thiscall*)(MacroConditions*, uint32_t*)>(0x5EF5C0)(thisConditions, a2);
}
