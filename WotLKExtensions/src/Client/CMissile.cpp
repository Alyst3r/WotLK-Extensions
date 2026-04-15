#include <Client/CMissile.hpp>
#include <Client/DBClient.hpp>
#include <Data/DBCAddresses.hpp>
#include <Data/Enums.hpp>
#include <Data/Structs.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>

void CMissile::ApplyPatches()
{
    std::vector<uint32_t> fireMissilesAddresses =
    {
        0x702AAF, 0x702AFC, 0x7033E0, 0x72E1D4, 0x80282A
    };

    for (size_t i = 0; i < fireMissilesAddresses.size(); i++)
        Util::OverwriteUInt32AtAddress(fireMissilesAddresses[i] - 4, reinterpret_cast<uint32_t>(&FireMissilesEx) - fireMissilesAddresses[i]);
}

// credits to hater
void __fastcall CMissile::FireMissilesEx(CMissile* thisMissile, int32_t unused, C3Vector* launchPos)
{
#if SPELLATTRIBUTESEXTENDED_DBC
    if (thisMissile && launchPos)
    {
        int32_t spellID = thisMissile->m_spellID;
        SpellRow spellRow{};
        SpellAttributesExtendedRow spellAttributesExtendedRow{};

        if (spellID && DBClient::GetLocalizedRow(g_spellDB, spellID, &spellRow))
        {
            DataContainer::GetInstance().GetSpellAttributesExtendedRow(spellAttributesExtendedRow, spellID);

            if (spellID == spellAttributesExtendedRow.m_ID && spellAttributesExtendedRow.HasCustomAttribute0(SPELL_ATTR0_CU_MISSILE_SPEED_IS_DELAY_IN_SEC))
            {
                float delaySeconds = thisMissile->m_speed;

                if (delaySeconds > 0.0001f)
                {
                    C3Vector impactPos{};

                    if (GetImpactDestination(thisMissile, &impactPos));
                    {
                        float dx = impactPos.m_x - launchPos->m_x;
                        float dy = impactPos.m_y - launchPos->m_y;
                        float dz = impactPos.m_z - launchPos->m_z;
                        float distance = std::sqrt(dx * dx + dy * dy + dz * dz);

                        if (distance > 0.0001f)
                        {
                            float convertedSpeed = distance / delaySeconds;

                            thisMissile->m_speed = convertedSpeed;
                            thisMissile->m_baseSpeed = convertedSpeed;
                        }
                    }
                }
            }
        }
    }
#endif

    reinterpret_cast<void (__thiscall*)(CMissile*, C3Vector*)>(0x7022D0)(thisMissile, launchPos);
}

C3Vector* CMissile::GetImpactDestination(CMissile* thisMissile, C3Vector* dest)
{
    return reinterpret_cast<C3Vector* (__thiscall*)(CMissile*, C3Vector*)>(0x6FF320)(thisMissile, dest);
}
