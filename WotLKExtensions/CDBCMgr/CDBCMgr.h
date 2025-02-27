#pragma once

#include <functional>
#include <unordered_map>
#include <string>
#include <any>

class CDBCMgr
{
    using CDBC = std::unordered_map<int, std::any>;
public:
    std::unordered_map<std::string, CDBC> allCDBCs;
    static void CDBCMgr::Load();
    void addCDBC(std::string cdbcName);
    //these stay in .h because haha template
    template <typename T>
    void addRow(std::string cdbcName, int rowIndex, T row) { allCDBCs[cdbcName][rowIndex] = row; }
    template <typename T>
    T* getRow(std::string cdbcName, int rowIndex)
    {
        auto it = allCDBCs.find(cdbcName);
        if (it != allCDBCs.end()) {
            auto objIt = it->second.find(rowIndex);
            if (objIt != it->second.end())
                return std::any_cast<T>(&objIt->second);
        }
        return nullptr;
    }

    static void PatchAddress();
};

extern CDBCMgr GlobalCDBCMap;
