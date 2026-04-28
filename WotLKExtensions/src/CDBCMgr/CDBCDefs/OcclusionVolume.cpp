#include <CDBCMgr/CDBCDefs/OcclusionVolume.hpp>

OcclusionVolume::OcclusionVolume() : CDBC(sizeof(OcclusionVolumeRow) / 4, sizeof(OcclusionVolumeRow))
{
}

OcclusionVolume& OcclusionVolume::GetInstance()
{
    static OcclusionVolume instance;

    return instance;
}

void OcclusionVolume::LoadDB()
{
    CDBC::LoadDB("OcclusionVolume.cdbc", reinterpret_cast<std::vector<char>*>(&m_rows));
    SetMinMaxIndices();
}

void OcclusionVolume::ReloadDB()
{
    UnloadDB();
    LoadDB();
}

void OcclusionVolume::UnloadDB()
{
    CDBC::UnloadDB();

    m_rows.clear();
}

void OcclusionVolume::GetRow(OcclusionVolumeRow& row, int32_t index)
{
    if (index >= m_minIndex && index <= m_maxIndex)
        for (auto& it : m_rows)
            if (it.m_ID == index)
                row = it;
}

void OcclusionVolume::ReserveDataBlock()
{
    m_rows.resize(m_numRows);
}

void OcclusionVolume::SetMinMaxIndices()
{
    for (auto& it : m_rows)
    {
        if (it.m_ID < m_minIndex)
            m_minIndex = it.m_ID;

        if (it.m_ID > m_maxIndex)
            m_maxIndex = it.m_ID;
    }
}
