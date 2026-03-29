#pragma once

#include <Windows.h>

class CMap
{
public:
    static void Apply();

    static bool __cdecl SafeOpenEx(const char* filename, HANDLE* a2);

private:
    CMap() = delete;
    ~CMap() = delete;
};
