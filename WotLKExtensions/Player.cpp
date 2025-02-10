#include "Player.h"

void Player::ApplyPatches()
{
	if (characterCreationRaceFix)
		CharacterCreationRaceCrashfix();

	if (comboPointFix)
		Util::SetByteAtAddress(reinterpret_cast<void*>(0x611707), 0xEB);

	if (classLFDRoles)
		LFDClassRoleEx();

	if (unlimitedRaceClassCombo)
		UnimitedRaceClassPairs();
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

	// I have a hunch this one is needed too
	Util::SetByteAtAddress(reinterpret_cast<void*>(0x4E0F86), 0x40);
}

void Player::LFDClassRoleExtension()
{
	std::vector<uint32_t> patchedAddresses = { 0x552948, 0x553B7D, 0x553B94, 0x553DE7, 0x554922 };

	for (uint8_t i = 0; i < patchedAddresses.size(); i++)
		Util::OverwriteUInt32AtAddress(patchedAddresses[i], reinterpret_cast<uint32_t>(&classRoleMask));
}

// you know what, fuck it, a bunch of asm patches in one function
// since there's not enough space to just patch in values
// should probably just move that function to dll in the future but cba to do this currently
static void __declspec(naked) sub_4E0F50Patch()
{
	__asm
	{
		push ebp;
		mov ebp, esp;
		sub esp, 0x400;
		push 0x4E0F56;
		ret;

		mov ecx, [ecx];
		mov[ebp + esi * 4 - 0x410], ecx;
		push 0x4E0F8F;
		ret;

		xor eax, eax;
		mov eax, [ebp + esi * 4 - 0x410];
		push 0x4E0FA4;
		ret;

		mov ecx, 0x414DB0;
		call ecx;
		mov eax, [ebp + esi * 4 - 0x410];
		push 0x4E0FC4;
		ret;
	}
}

void Player::UnimitedRaceClassPairs()
{
	//
	Util::SetByteAtAddress(reinterpret_cast<void*>(0x4E0F50), 0xE9);
	Util::OverwriteUInt32AtAddress(0x4E0F51, reinterpret_cast<uint32_t>(&sub_4E0F50Patch) - 0x4E0F55);
	//
	Util::SetByteAtAddress(reinterpret_cast<void*>(0x4E0F89), 0xE9);
	Util::OverwriteUInt32AtAddress(0x4E0F8A, reinterpret_cast<uint32_t>(&sub_4E0F50Patch) + 0x0E - 0x4E0F8E);
	//
	Util::SetByteAtAddress(reinterpret_cast<void*>(0x4E0F9E), 0xE9);
	Util::OverwriteUInt32AtAddress(0x4E0F9F, reinterpret_cast<uint32_t>(&sub_4E0F50Patch) + 0x1D - 0x4E0FA3);
	//
	Util::SetByteAtAddress(reinterpret_cast<void*>(0x4E0FBB), 0xE9);
	Util::OverwriteUInt32AtAddress(0x4E0FBC, reinterpret_cast<uint32_t>(&sub_4E0F50Patch) + 0x2C - 0x4E0FC0);
}
