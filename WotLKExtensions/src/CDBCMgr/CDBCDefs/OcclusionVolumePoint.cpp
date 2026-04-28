#include <CDBCMgr/CDBCDefs/OcclusionVolumePoint.hpp>

OcclusionVolumePoint::OcclusionVolumePoint() : CDBC(sizeof(OcclusionVolumePointRow) / 4, sizeof(OcclusionVolumePointRow))
{
}

OcclusionVolumePoint& OcclusionVolumePoint::GetInstance()
{
    static OcclusionVolumePoint instance;

    return instance;
}

void OcclusionVolumePoint::LoadDB()
{
    CDBC::LoadDB("OcclusionVolumePoint.cdbc", reinterpret_cast<std::vector<char>*>(&m_rows));
    SetMinMaxIndices();
}

void OcclusionVolumePoint::ReloadDB()
{
    UnloadDB();
    LoadDB();
}

void OcclusionVolumePoint::UnloadDB()
{
    CDBC::UnloadDB();

    m_rows.clear();
}

void OcclusionVolumePoint::GetRow(OcclusionVolumePointRow& row, int32_t index)
{
    if (index >= m_minIndex && index <= m_maxIndex)
        for (auto& it : m_rows)
            if (it.m_ID == index)
                row = it;
}

void OcclusionVolumePoint::ReserveDataBlock()
{
    m_rows.resize(m_numRows);
}

void OcclusionVolumePoint::SetMinMaxIndices()
{
    for (auto& it : m_rows)
    {
        if (it.m_ID < m_minIndex)
            m_minIndex = it.m_ID;

        if (it.m_ID > m_maxIndex)
            m_maxIndex = it.m_ID;
    }
}
