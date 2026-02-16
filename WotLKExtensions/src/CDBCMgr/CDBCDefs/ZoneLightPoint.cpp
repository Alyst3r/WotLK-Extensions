#include <CDBCMgr/CDBCDefs/ZoneLightPoint.hpp>

ZoneLightPoint::ZoneLightPoint() : CDBC(sizeof(ZoneLightPointRow) / 4, sizeof(ZoneLightPointRow))
{
}

ZoneLightPoint& ZoneLightPoint::GetInstance()
{
    static ZoneLightPoint instance;

    return instance;
}

void ZoneLightPoint::LoadDB()
{
    CDBC::LoadDB("ZoneLightPoint.cdbc", reinterpret_cast<std::vector<char>*>(&m_rows));
    SetMinMaxIndices();
}

void ZoneLightPoint::ReloadDB()
{
    UnloadDB();
    LoadDB();
}

void ZoneLightPoint::UnloadDB()
{
    CDBC::UnloadDB();

    m_rows.clear();
}

void ZoneLightPoint::GetRow(ZoneLightPointRow& row, int32_t index)
{
    if (index >= m_minIndex && index <= m_maxIndex)
        for (auto& it : m_rows)
            if (it.m_ID == index)
                row = it;
}

void ZoneLightPoint::ReserveDataBlock()
{
    m_rows.resize(m_numRows);
}

void ZoneLightPoint::SetMinMaxIndices()
{
    for (auto& it : m_rows)
    {
        if (it.m_ID < m_minIndex)
            m_minIndex = it.m_ID;

        if (it.m_ID > m_maxIndex)
            m_maxIndex = it.m_ID;
    }
}
