#pragma once

#include <SharedDefines.hpp>

class CGlueMgr
{
public:
    static void ApplyPatches();

    static int32_t LoadScriptFunctionsCustom();

private:
    CGlueMgr() = delete;
    ~CGlueMgr() = delete;

    static void AddToFunctionMap(const char* name, void* ptr);
    static void InitializeEvents();
    static void RegisterFunctions();
    static void __cdecl RegisterEventEx(const char** list, size_t count);

    static int32_t LoadFunctions();
};
