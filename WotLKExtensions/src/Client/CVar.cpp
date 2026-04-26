#include <Client/CVar.hpp>
#include <Data/Enums.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>

void CVar::Apply()
{
#if GLUEMGREXTENSION
    Util::OverwriteUInt32AtAddress(0x404147, reinterpret_cast<uint32_t>(&RegisterGlueCVarsCustom) - 0x40414B);

    FillCustomGlueCVarVector();
#endif
}

int32_t CVar::RegisterGlueCVarsCustom()
{
    auto& customCVars = sDC.GetGlueCVarVector();

    for (auto& it : customCVars)
        Register(it.m_name, it.m_description, it.m_size, it.m_defaultValue, it.m_callback, it.m_flags, it.m_a7, it.n_a8, it.m_a9);

    return reinterpret_cast <int32_t (__cdecl*)()>(0x401B60)();
}

int32_t CVar::Register(const char* name, const char* description, uint32_t size, const char* defaultVal, void* callback, uint32_t flags, bool a7, int32_t a8, bool a9)
{
    return reinterpret_cast<int32_t (__cdecl*)(const char*, const char*, uint32_t, const char*, void*, uint32_t, bool, int32_t, bool)>(0x767FC0)(name, description, size, defaultVal, callback, flags, a7, a8, a9);
}

void CVar::Set(CVar* cVar, int32_t value, bool a3, bool a4, bool a5, bool a6)
{
    reinterpret_cast<void (__thiscall*)(void*, int32_t, bool, bool, bool, bool)>(0x766940)(cVar, value, a3, a4, a5, a6);
}

void CVar::FillCustomGlueCVarVector()
{
}

void CVar::AddToGlueCVarVector(const char* name, const char* description, uint32_t size, const char* defaultVal, void* callback, uint32_t flags, bool a7, int32_t a8, bool a9)
{
    CustomCVar temp{ name, description, size, defaultVal, callback, flags, a8, a7, a9 };

    sDC.GetGlueCVarVector().push_back(temp);
}
