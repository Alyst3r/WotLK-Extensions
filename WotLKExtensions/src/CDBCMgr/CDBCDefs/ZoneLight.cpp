#include <CDBCMgr/CDBCDefs/ZoneLight.hpp>

ZoneLight::ZoneLight() : CDBC(sizeof(ZoneLightRow) / 4, sizeof(ZoneLightRow))
{
}

ZoneLight& ZoneLight::GetInstance()
{
    static ZoneLight instance;

    return instance;
}

void ZoneLight::LoadDB()
{
    CDBC::LoadDB("ZoneLight.cdbc", reinterpret_cast<std::vector<char>*>(&m_rows));
    SetMinMaxIndices();
}

void ZoneLight::ReloadDB()
{
    UnloadDB();
    LoadDB();
}

void ZoneLight::UnloadDB()
{
    CDBC::UnloadDB();

    m_rows.clear();
}

void ZoneLight::GetRow(ZoneLightRow& row, int32_t index)
{
    if (index >= m_minIndex && index <= m_maxIndex)
        for (auto& it : m_rows)
            if (it.m_ID == index)
                row = it;
}

void ZoneLight::ReserveDataBlock()
{
    m_rows.resize(m_numRows);
}

void ZoneLight::SetMinMaxIndices()
{
    for (auto& it : m_rows)
    {
        if (it.m_ID < m_minIndex)
            m_minIndex = it.m_ID;

        if (it.m_ID > m_maxIndex)
            m_maxIndex = it.m_ID;
    }
}
