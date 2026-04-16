#pragma once

#include <cstdint>

class CVar
{
public:
    static void Apply();

    static int32_t RegisterGlueCVarsCustom();

    static int32_t Register(const char* name, const char* description, uint32_t size, const char* defaultVal, void* callback, uint32_t flags, bool a7, int32_t a8, bool a9);
    static void Set(CVar* cVar, int32_t value, bool a3, bool a4, bool a5, bool a6);

private:
    CVar() = delete;
    ~CVar() = delete;

    static void FillCustomGlueCVarVector();

    static void AddToGlueCVarVector(const char* name, const char* description, uint32_t size, const char* defaultVal, void* callback, uint32_t flags, bool a7, int32_t a8, bool a9);
};
