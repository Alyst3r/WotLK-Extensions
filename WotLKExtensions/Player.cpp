#include "Player.h"
#include "CustomLua.h"
#include "CDBCMgr/CDBCDefs/LFGRoles.h"

void Player::ApplyPatches()
{
	if (characterCreationRaceFix)
		CharacterCreationRaceCrashfix();

	if (comboPointFix)
		Util::SetByteAtAddress((void*)0x611707, 0xEB);

	if (classLFDRoles || useLFGRolesDBC)
		LFDClassRoleExtension();
}

void Player::CharacterCreationRaceCrashfix()
{
	std::vector<uint32_t> patchedAddresses = { 0x4E157D, 0x4E16A3, 0x4E15B5, 0x4E20EE, 0x4E222A, 0x4E2127, 0x4E1E94, 0x4E1C3A };

	for (uint8_t i = 0; i < patchedAddresses.size(); i++)
		Util::OverwriteUInt32AtAddress(patchedAddresses[i], (uint32_t)&memoryTable);

	Util::OverwriteUInt32AtAddress(0x4CDA43, (uint32_t)&raceNameTable);

	// copy existing pointer table from wow.exe and fill the remaining slots with pointer to dummy
	memcpy(&raceNameTable, (const void*)0xB24180, 0x30);

	for (uint8_t i = 22; i < 32; i++)
		raceNameTable[i] = (uint32_t)&dummy;

	// I have a hunch this one is needed too
	Util::SetByteAtAddress((void*)0x4E0F86, 0x40);
}

void Player::LFDClassRoleExtension()
{
	if (classLFDRoles && !useLFGRolesDBC)
	{
		std::vector<uint32_t> patchedAddresses = { 0x552948, 0x553B7D, 0x553B94, 0x553DE7, 0x554922 };

		for (uint8_t i = 0; i < patchedAddresses.size(); i++)
			Util::OverwriteUInt32AtAddress(patchedAddresses[i], (uint32_t)&classRoleMask);
	}
	else
	{
		Util::OverwriteUInt32AtAddress(0x553E90, (uint32_t)&CheckLFGRoles - 0x553E94);
		Util::OverwriteUInt32AtAddress(0x55736D, (uint32_t)&CheckLFGRoles - 0x557371);
		Util::OverwriteUInt32AtAddress(0x4E0B12, (uint32_t)&GetClassRoles - 0x4E0B16);
		// Lua_GetAvailableRoles pointer, we want direct address not offset in this case 
		Util::OverwriteUInt32AtAddress(0xACD7FC, (uint32_t)&CustomLua::GetAvailableRoles);
		// Lua_SetLFGRole pointer, ditto
		Util::OverwriteUInt32AtAddress(0xACD72C, (uint32_t)&CustomLua::SetLFGRole);
	}
}

uint32_t Player::CheckLFGRoles(uint32_t roles)
{
	uint32_t classId = sub_6B1080();

	if (classId > *(uint32_t*)0xAD3410 || classId < *(uint32_t*)0xAD3414) // ChrClasses.dbc max/min indices
		classId = 0;

	LFGRolesRow* cdbcRoles = GlobalCDBCMap.getRow<LFGRolesRow>("LFGRoles", classId);

	return roles & cdbcRoles->Roles;
}

uint32_t Player::GetClassRoles(uint32_t classId)
{
	LFGRolesRow* cdbcRoles = GlobalCDBCMap.getRow<LFGRolesRow>("LFGRoles", classId);

	return cdbcRoles->Roles;
}
