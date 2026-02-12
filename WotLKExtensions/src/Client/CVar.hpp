#pragma once

class CVar
{
public:
    static void Set(void* cVar, int value, bool a3, bool a4, bool a5, bool a6);

private:
    CVar() = delete;
    ~CVar() = delete;
};
