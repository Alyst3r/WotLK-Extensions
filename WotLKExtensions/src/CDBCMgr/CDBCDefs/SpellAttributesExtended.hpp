#pragma once

#include <CDBCMgr/CDBC.hpp>
#include <Data/Structs.hpp>

#include <cstdint>

class SpellAttributesExtended : public CDBC
{
public:
    static SpellAttributesExtended& GetInstance();

    void LoadDB();
    void ReloadDB();
    void UnloadDB();

    void GetRow(SpellAttributesExtendedRow& row, int32_t index);

protected:
    SpellAttributesExtended();
    virtual ~SpellAttributesExtended() = default;

protected:
    std::vector<SpellAttributesExtendedRow> m_rows;

    void ReserveDataBlock() override;
    void SetMinMaxIndices() override;
};
