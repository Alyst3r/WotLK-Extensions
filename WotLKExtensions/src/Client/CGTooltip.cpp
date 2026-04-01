#include <Client/CFormula.hpp>
#include <Client/CGTooltip.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>

void CGTooltip::ApplyPatches()
{
#if SPELLDESCRIPTIONEXT_PATCH
    std::vector<const char*>& data = DataContainer::GetInstance().GetSpellVariableData();

    CFormula::FillSpellVariableData();
    Util::OverwriteUInt32AtAddress(0x576B63, reinterpret_cast<uint32_t>(data.data()));
    Util::OverwriteUInt32AtAddress(0x576B7C, data.size());
    Util::OverwriteUInt32AtAddress(0x578E8B, reinterpret_cast<uint32_t>(&CFormula::GetVariableValueEx) - 0x578E8F);
#endif

    std::vector<uint32_t> setSpellAddresses =
    {
        0x61DDB7, 0x625590, 0x62572F, 0x6258BC,
        0x625B20, 0x625C9A, 0x62643A, 0x6264C7,
        0x626687, 0x626F0C, 0x626F4A, 0x62DC3D,
        0x62DCC5, 0x62E9FD, 0x62EA9F, 0x62EC90,
        0x630F95, 0x630FC4, 0x63136D
    };

    for (size_t i = 0; i < setSpellAddresses.size(); i++)
        Util::OverwriteUInt32AtAddress(setSpellAddresses[i] - 4, reinterpret_cast<uint32_t>(&SetSpellEx) - setSpellAddresses[i]);
}

int32_t __fastcall CGTooltip::SetSpellEx(CGTooltip* thisTooltip, int32_t unused, int32_t spellId, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, uint32_t* a9, int32_t a10, int32_t a11, int32_t a12, int32_t a13, int32_t a14, int32_t a15, int32_t a16)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, uint32_t*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x6238A0)(thisTooltip, spellId, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
}

void CGTooltip::AddLine(CGTooltip* thisTooltip, char* str1, char* str2, uint32_t color1, uint32_t color2, int32_t a6)
{
    reinterpret_cast<void (__thiscall*)(CGTooltip*, char*, char*, uint32_t, uint32_t, int32_t)>(0x61FEC0)(thisTooltip, str1, str2, color1, color2, a6);
}

int32_t CGTooltip::AddTalentPrereqs(CGTooltip* thisTooltip, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x6224F0)(thisTooltip, a2, a3, a4, a5, a6);
}

int32_t CGTooltip::ClearTooltip(CGTooltip* thisTooltip)
{
    return reinterpret_cast<int32_t (__thiscall*)(CGTooltip*)>(0x61C620)(thisTooltip);
}

int32_t CSimpleFrame::Hide(void* thisFrame)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*)>(0x48F620)(thisFrame);
}
