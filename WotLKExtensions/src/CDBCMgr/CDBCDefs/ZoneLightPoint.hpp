#pragma once

#include <CDBCMgr/CDBC.hpp>
#include <Data/Structs.hpp>

#include <cstdint>

class ZoneLightPoint : public CDBC
{
public:
    static ZoneLightPoint& GetInstance();

    void LoadDB();
    void ReloadDB();
    void UnloadDB();

    void GetRow(ZoneLightPointRow& row, int32_t index);

protected:
    ZoneLightPoint();
    virtual ~ZoneLightPoint() = default;

private:
    std::vector<ZoneLightPointRow> m_rows;

    void ReserveDataBlock() override;
    void SetMinMaxIndices() override;
};
