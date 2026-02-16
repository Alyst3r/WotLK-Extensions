#pragma once

#include <any>
#include <functional>
#include <limits>
#include <string>
#include <unordered_map>

class CDBCMgr
{
public:
    static void Load();
    static void PatchAddress();

private:
    CDBCMgr() = delete;
    ~CDBCMgr() = delete;
};
