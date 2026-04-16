#include <Client/CGlueMgr.hpp>
#include <Client/CustomLua.hpp>
#include <Client/FrameScript.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

void CGlueMgr::Apply()
{
    Util::OverwriteUInt32AtAddress(0x4DA71D, reinterpret_cast<uint32_t>(&LoadScriptFunctionsCustom) - 0x4DA721);

    RegisterFunctions();
}

int32_t CGlueMgr::LoadScriptFunctionsCustom()
{
    auto& luaFunctionMap = DataContainer::GetInstance().GetGlueLuaFunctionMap();

    for (auto& it : luaFunctionMap)
        FrameScript::RegisterFunction(it.first, it.second);

    return LoadFunctions();
}

void CGlueMgr::AddToFunctionMap(const char* name, void* ptr)
{
    DataContainer::GetInstance().AddGlueLuaFunction(name, ptr);
}

void CGlueMgr::RegisterFunctions()
{
    AddToFunctionMap("FlashGameWindow", &CustomLua::FlashGameWindow);
}

int32_t CGlueMgr::LoadFunctions()
{
    return reinterpret_cast<int32_t(__cdecl*)()>(0x60A120)();
}
