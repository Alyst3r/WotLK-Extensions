#include <CDBCMgr/CDBCDefs/LFGRoles.hpp>
#include <Client/CustomLua.hpp>
#include <Client/ClientServices.hpp>
#include <Data/DBCAddresses.hpp>
#include <GameObjects/CGPlayer.hpp>
#include <Misc/DataContainer.hpp>
#include <Misc/Util.hpp>

#include <PatchConfig.hpp>
#include <SharedDefines.hpp>

bool CGPlayer::IsDeadOrGhost(CGPlayer* thisPlayer)
{
    return reinterpret_cast<bool (__thiscall*)(CGPlayer*)>(0x6DAC10)(thisPlayer);
}

void CGPlayer::ApplyPatches()
{
#if CHARCREATIONRACE_FIX
    CharacterCreationRaceCrashfix();
#endif

#if COMBOPOINT_FIX
    Util::SetByteAtAddress((void*)0x611707, 0xEB);
#endif

#if CLASSLFDROLES_PATCH || LFGROLES_DBC
    LFDClassRoleExtension();
#endif
}

void CGPlayer::CharacterCreationRaceCrashfix()
{
    std::vector<uint32_t> patchedAddresses = { 0x4E157D, 0x4E16A3, 0x4E15B5, 0x4E20EE, 0x4E222A, 0x4E2127, 0x4E1E94, 0x4E1C3A };

    uint32_t* raceNameTablePtr = DataContainer::GetInstance().GetRaceTablePtr();
    uint32_t* memoryTablePtr = DataContainer::GetInstance().GetMemoryTablePtr();

    for (uint8_t i = 0; i < patchedAddresses.size(); i++)
        Util::OverwriteUInt32AtAddress(patchedAddresses[i], reinterpret_cast<uint32_t>(memoryTablePtr));

    Util::OverwriteUInt32AtAddress(0x4CDA43, reinterpret_cast<uint32_t>(raceNameTablePtr));

    // copy existing pointer table from wow.exe and fill the remaining slots with pointer to dummy
    memcpy(raceNameTablePtr, reinterpret_cast<const void*>(0xB24180), 0x30);

    for (uint8_t i = 22; i < 32; i++)
        raceNameTablePtr[i] = (uint32_t)&dummy;

    // I have a hunch this one is needed too
    Util::SetByteAtAddress(reinterpret_cast<void*>(0x4E0F86), 0x40);
}

void CGPlayer::LFDClassRoleExtension()
{
#if CLASSLFDROLES_PATCH && (!CUSTOM_DBC || !LFGROLES_DBC)
    uint32_t tablePtr = reinterpret_cast<uint32_t>(DataContainer::GetInstance().GetClassRoleMaskTablePtr());

    std::vector<uint32_t> patchedAddresses = { 0x552948, 0x553B7D, 0x553B94, 0x553DE7, 0x554922 };

    for (uint8_t i = 0; i < patchedAddresses.size(); i++)
        Util::OverwriteUInt32AtAddress(patchedAddresses[i], tablePtr);
#else
    Util::OverwriteUInt32AtAddress(0x553E90, (uint32_t)&CheckLFGRoles - 0x553E94);
    Util::OverwriteUInt32AtAddress(0x55736D, (uint32_t)&CheckLFGRoles - 0x557371);
    Util::OverwriteUInt32AtAddress(0x4E0B12, (uint32_t)&GetClassRoles - 0x4E0B16);
    // Lua_GetAvailableRoles pointer, we want direct address not offset in this case 
    Util::OverwriteUInt32AtAddress(0xACD7FC, (uint32_t)&CustomLua::GetAvailableRoles);
    // Lua_SetLFGRole pointer, ditto
    Util::OverwriteUInt32AtAddress(0xACD72C, (uint32_t)&CustomLua::SetLFGRole);
#endif
}

uint32_t CGPlayer::CheckLFGRoles(uint32_t roles)
{
    uint32_t classId = ClientServices::GetCharacterClass();
    LFGRolesRow cdbcRoles;

    if (classId > g_chrClassesDB->m_maxIndex || classId < g_chrClassesDB->m_minIndex) // ChrClasses.dbc max/min indices
        classId = 0;

    DataContainer::GetInstance().GetLFGRolesRow(cdbcRoles, classId);

    return roles & cdbcRoles.m_roles;
}

uint32_t CGPlayer::GetClassRoles(uint32_t classId)
{
    LFGRolesRow cdbcRoles;

    DataContainer::GetInstance().GetLFGRolesRow(cdbcRoles, classId);

    return cdbcRoles.m_roles;
}
