#include <Client/CFormula.hpp>
#include <Client/ClientServices.hpp>
#include <Data/Enums.hpp>
#include <GameObjects/CGPlayer.hpp>
#include <Misc/DataContainer.hpp>

#include <vector>

int32_t CFormula::GetVariableValue(void* thisVar, int32_t spellVariable, int32_t a3, SpellRow* spell, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9)
{
    return reinterpret_cast<int32_t (__thiscall*)(void*, int32_t, int32_t, SpellRow*, int32_t, int32_t, int32_t, int32_t, int32_t)>(0x5782D0)(thisVar, spellVariable, a3, spell, a5, a6, a7, a8, a9);
}

int32_t __fastcall CFormula::GetVariableValueEx(void* thisVar, int32_t unused, int32_t spellVariable, int32_t a3, SpellRow* spell, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9)
{
    int32_t result = 0;

    if (spellVariable < SPELLVARIABLE_hp)
        result = GetVariableValue(thisVar, spellVariable, a3, spell, a5, a6, a7, a8, a9);
    else
    {
        float value = 0.f;
        CGPlayer* activePlayer = reinterpret_cast<CGPlayer*>(ClientServices::GetObjectPtr(ClientServices::GetActivePlayer(), TYPEMASK_PLAYER));

        if (activePlayer)
        {
            switch (spellVariable)
            {
                case SPELLVARIABLE_hp:
                    value = static_cast<float>(activePlayer->m_unitFields->m_currHealth);
                    break;
                case SPELLVARIABLE_HP:
                    value = static_cast<float>(activePlayer->m_unitFields->m_maxHealth);
                    break;
                case SPELLVARIABLE_ppl1:
                    value = spell->m_effectRealPointsPerLevel[0];
                    break;
                case SPELLVARIABLE_ppl2:
                    value = spell->m_effectRealPointsPerLevel[1];
                    break;
                case SPELLVARIABLE_ppl3:
                    value = spell->m_effectRealPointsPerLevel[2];
                    break;
                case SPELLVARIABLE_PPL1:
                    value = spell->m_effectRealPointsPerLevel[1] * static_cast<float>(activePlayer->m_unitFields->m_level);
                    break;
                case SPELLVARIABLE_PPL2:
                    value = spell->m_effectRealPointsPerLevel[1] * static_cast<float>(activePlayer->m_unitFields->m_level);
                    break;
                case SPELLVARIABLE_PPL3:
                    value = spell->m_effectRealPointsPerLevel[2] * static_cast<float>(activePlayer->m_unitFields->m_level);
                    break;
                case SPELLVARIABLE_power1:
                case SPELLVARIABLE_power2:
                case SPELLVARIABLE_power3:
                case SPELLVARIABLE_power4:
                case SPELLVARIABLE_power5:
                case SPELLVARIABLE_power6:
                case SPELLVARIABLE_power7:
                    value = activePlayer->m_unitFields->m_currPowers[spellVariable - SPELLVARIABLE_power1];
                    break;
                case SPELLVARIABLE_POWER1:
                case SPELLVARIABLE_POWER2:
                case SPELLVARIABLE_POWER3:
                case SPELLVARIABLE_POWER4:
                case SPELLVARIABLE_POWER5:
                case SPELLVARIABLE_POWER6:
                case SPELLVARIABLE_POWER7:
                    value = activePlayer->m_unitFields->m_maxPowers[spellVariable - SPELLVARIABLE_POWER1];
                    break;
                case SPELLVARIABLE_bpct:
                    value = activePlayer->m_playerData->m_blockPct;
                    break;
                case SPELLVARIABLE_dpct:
                    value = activePlayer->m_playerData->m_dodgePct;
                    break;
                case SPELLVARIABLE_ppct:
                    value = activePlayer->m_playerData->m_parryPct;
                    break;
                case SPELLVARIABLE_petsp:
                    value = static_cast<float>(activePlayer->m_playerData->m_petSpellPower);
                    break;
                default:
                    *reinterpret_cast<uint32_t*>(thisVar) = 1;
                    break;
            }
        }

        result = a3;
        uint32_t* offset = reinterpret_cast<uint32_t*>(a3 + 128);
        --*offset;
        *reinterpret_cast<float*>(a3 + 4 * *offset) = value;
    }

    return result;
}

void CFormula::FillSpellVariableData()
{
    const char* tooltipSpellVariablesExtensions[] =
    {
        "hp", "HP", "ppl1", "ppl2", "ppl3", "PPL1", "PPL2", "PPL3",
        "power1", "power2", "power3", "power4", "power5", "power6", "power7",
        "POWER1", "POWER2", "POWER3", "POWER4", "POWER5", "POWER6", "POWER7",
        "bpct", "dpct", "ppct", "petsp"
    };

    size_t newSize = sizeof(uint32_t) * (SPELLVARIABLE_END - 21);
    std::vector<const char*>& data = DataContainer::GetInstance().GetSpellVariableData();

    data.resize(newSize);
    memcpy(data.data(), reinterpret_cast<const void*>(0xACE8F8), sizeof(const char*) * 140);

    for (size_t i = 0; i < sizeof(tooltipSpellVariablesExtensions) / sizeof(tooltipSpellVariablesExtensions[0]); i++)
        data[i + 140] = tooltipSpellVariablesExtensions[i];
}
