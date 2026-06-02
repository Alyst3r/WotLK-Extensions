#include <Client/CGlueMgr.hpp>
#include <Client/CustomLua.hpp>
#include <Client/FrameScript.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

void CGlueMgr::ApplyPatches()
{
    Util::OverwriteUInt32AtAddress(0x4DA71D, reinterpret_cast<uint32_t>(&LoadScriptFunctionsCustom) - 0x4DA721);
    Util::OverwriteUInt32AtAddress(0x4DA758, reinterpret_cast<uint32_t>(&RegisterEventEx) - 0x4DA75C);

    InitializeEvents();
    RegisterFunctions();
}

int32_t CGlueMgr::LoadScriptFunctionsCustom()
{
    auto& luaFunctionMap = sDC.GetGlueLuaFunctionMap();

    for (auto& it : luaFunctionMap)
        FrameScript::RegisterFunction(it.first, it.second);

    return LoadFunctions();
}

void CGlueMgr::AddToFunctionMap(const char* name, void* ptr)
{
    sDC.AddGlueLuaFunction(name, ptr);
}

void CGlueMgr::InitializeEvents()
{
    sDC.RegisterCustomGlueEvent("GLUE_TEST");
}

void CGlueMgr::RegisterFunctions()
{
    AddToFunctionMap("FlashGameWindow", &CustomLua::FlashGameWindow);
}

void __cdecl CGlueMgr::RegisterEventEx(const char** list, size_t count)
{
    sDC.SetupGlueEventVector(list, count);

    FrameScript::RegisterEvent(sDC.GetGlueEventVector().data(), sDC.GetGlueEventVector().size());
}

int32_t CGlueMgr::LoadFunctions()
{
    return reinterpret_cast<int32_t (__cdecl*)()>(0x60A120)();
}
