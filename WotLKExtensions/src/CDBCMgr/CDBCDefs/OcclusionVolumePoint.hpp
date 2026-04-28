#pragma once

#include <CDBCMgr/CDBC.hpp>
#include <Data/Structs.hpp>

#include <cstdint>

class OcclusionVolumePoint : public CDBC
{
public:
    static OcclusionVolumePoint& GetInstance();

    void LoadDB();
    void ReloadDB();
    void UnloadDB();

    void GetRow(OcclusionVolumePointRow& row, int32_t index);

protected:
    OcclusionVolumePoint();
    virtual ~OcclusionVolumePoint() = default;

private:
    std::vector<OcclusionVolumePointRow> m_rows;

    void ReserveDataBlock() override;
    void SetMinMaxIndices() override;
};
