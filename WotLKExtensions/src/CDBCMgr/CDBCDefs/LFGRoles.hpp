#pragma once

#include <CDBCMgr/CDBC.hpp>
#include <Data/Structs.hpp>

#include <cstdint>

class LFGRoles : public CDBC
{
public:
    static LFGRoles& GetInstance();

    void LoadDB();
    void ReloadDB();
    void UnloadDB();
    
    void GetRow(LFGRolesRow& row, int32_t index);

protected:
    LFGRoles();
    virtual ~LFGRoles() = default;

protected:
    std::vector<LFGRolesRow> m_rows;

    void ReserveDataBlock() override;
    void SetMinMaxIndices() override; 
};
