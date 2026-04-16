#pragma once

#include <SharedDefines.hpp>

class CGlueMgr
{
public:
    static void Apply();

    static int32_t LoadScriptFunctionsCustom();

private:
    CGlueMgr() = delete;
    ~CGlueMgr() = delete;

    static void AddToFunctionMap(const char* name, void* ptr);
    static void RegisterFunctions();

    static int32_t LoadFunctions();
};
