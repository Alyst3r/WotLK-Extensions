#pragma once

#include <CDBCMgr/CDBC.hpp>
#include <Data/Structs.hpp>

#include <cstdint>

class OcclusionVolume : public CDBC
{
public:
    static OcclusionVolume& GetInstance();

    void LoadDB();
    void ReloadDB();
    void UnloadDB();

    void GetRow(OcclusionVolumeRow& row, int32_t index);

protected:
    OcclusionVolume();
    virtual ~OcclusionVolume() = default;

private:
    std::vector<OcclusionVolumeRow> m_rows;

    void ReserveDataBlock() override;
    void SetMinMaxIndices() override;
};
