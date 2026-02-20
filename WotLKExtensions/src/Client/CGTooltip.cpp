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
}

void CGTooltip::AddLine(void* thisTooltip, char* str1, char* str2, uint32_t color1, uint32_t color2, int32_t a6)
{
    reinterpret_cast<void (__thiscall*)(void*, char*, char*, uint32_t, uint32_t, int32_t)>(0)(thisTooltip, str1, str2, color1, color2, a6);
}

int32_t CGTooltip::AddTalentPrereqs(void* thisTooltip, int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x6224F0)(thisTooltip, a2, a3, a4, a5, a6);
}

int32_t CGTooltip::ClearTooltip(void* thisTooltip)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*)>(0x61C620)(thisTooltip);
}

int32_t CSimpleFrame::Hide(void* thisFrame)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*)>(0x48F620)(thisFrame);
}
