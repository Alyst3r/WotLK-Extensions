#pragma once

#include <CDBCMgr/CDBC.hpp>
#include <Data/Structs.hpp>

#include <cstdint>

class ZoneLight : public CDBC
{
public:
    static ZoneLight& GetInstance();

    void LoadDB();
    void ReloadDB();
    void UnloadDB();

    void GetRow(ZoneLightRow& row, int32_t index);

protected:
    ZoneLight();
    virtual ~ZoneLight() = default;

private:
    std::vector<ZoneLightRow> m_rows;

    void ReserveDataBlock() override;
    void SetMinMaxIndices() override;
};
