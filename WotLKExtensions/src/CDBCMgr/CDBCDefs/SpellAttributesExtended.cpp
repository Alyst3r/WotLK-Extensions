#include <CDBCMgr/CDBCDefs/SpellAttributesExtended.hpp>

SpellAttributesExtended::SpellAttributesExtended() : CDBC(sizeof(SpellAttributesExtendedRow) / 4, sizeof(SpellAttributesExtendedRow))
{
}

SpellAttributesExtended& SpellAttributesExtended::GetInstance()
{
    static SpellAttributesExtended instance;

    return instance;
}

void SpellAttributesExtended::LoadDB()
{
    CDBC::LoadDB("SpellAttributesExtended.cdbc", reinterpret_cast<std::vector<char>*>(&m_rows));
    SetMinMaxIndices();
}

void SpellAttributesExtended::ReloadDB()
{
    UnloadDB();
    LoadDB();
}

void SpellAttributesExtended::UnloadDB()
{
    CDBC::UnloadDB();

    m_rows.clear();
}

void SpellAttributesExtended::GetRow(SpellAttributesExtendedRow& row, int32_t index)
{
    if (index >= m_minIndex && index <= m_maxIndex)
        for (auto& it : m_rows)
            if (it.m_ID == index)
                row = it;
}

void SpellAttributesExtended::ReserveDataBlock()
{
    m_rows.resize(m_numRows);
}

void SpellAttributesExtended::SetMinMaxIndices()
{
    for (auto& it : m_rows)
    {
        if (it.m_ID < m_minIndex)
            m_minIndex = it.m_ID;

        if (it.m_ID > m_maxIndex)
            m_maxIndex = it.m_ID;
    }
}
