#include <CDBCMgr/CDBCDefs/LFGRoles.hpp>

LFGRoles::LFGRoles() : CDBC(sizeof(LFGRolesRow) / 4, sizeof(LFGRolesRow))
{
}

LFGRoles& LFGRoles::GetInstance()
{
    static LFGRoles instance;

    return instance;
}

void LFGRoles::LoadDB()
{
    CDBC::LoadDB("LFGRoles.cdbc", reinterpret_cast<std::vector<char>*>(&m_rows));
    SetMinMaxIndices();
}

void LFGRoles::ReloadDB()
{
    UnloadDB();
    LoadDB();
}

void LFGRoles::UnloadDB()
{
    CDBC::UnloadDB();

    m_rows.clear();
}

void LFGRoles::GetRow(LFGRolesRow& row, int32_t index)
{
    if (index >= m_minIndex && index <= m_maxIndex)
        for (auto& it : m_rows)
            if (it.m_classID == index)
                row = it;
}

void LFGRoles::ReserveDataBlock()
{
    m_rows.resize(m_numRows);
}

void LFGRoles::SetMinMaxIndices()
{
    for (auto& it : m_rows)
    {
        if (it.m_classID < m_minIndex)
            m_minIndex = it.m_classID;

        if (it.m_classID > m_maxIndex)
            m_maxIndex = it.m_classID;
    }
}
