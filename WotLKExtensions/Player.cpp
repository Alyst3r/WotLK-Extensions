#include "Player.h"

void Player::ApplyPatches()
{
	if (characterCreationRaceFix)
		CharacterCreationRaceCrashfix();
}

void Player::CharacterCreationRaceCrashfix()
{
	std::vector<uint32_t> patchedAddresses = { 0x4E157D, 0x4E16A3, 0x4E15B5, 0x4E20EE, 0x4E222A, 0x4E2127, 0x4E1E94, 0x4E1C3A };

	for (uint8_t i = 0; i < patchedAddresses.size(); i++)
		Util::OverwriteUInt32AtAddress(patchedAddresses[i], reinterpret_cast<uint32_t>(&memoryTable));

	Util::OverwriteUInt32AtAddress(0x4CDA43, reinterpret_cast<uint32_t>(&raceNameTable));

	// copy existing pointer table from wow.exe and fill the remaining slots with pointer to dummy
	memcpy(&raceNameTable, (const void*)0xB24180, 0x30);

	for (uint8_t i = 22; i < 32; i++)
		raceNameTable[i] = reinterpret_cast<uint32_t>(&dummy);
}
