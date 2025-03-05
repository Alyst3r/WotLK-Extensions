#include "Misc.h"

void Misc::ApplyPatches()
{
	if (noAmmoPatch)
	{
		uint8_t byteArray[] = { 0xE9, 0xBA, 0x00, 0x00, 0x00 };
		Util::OverwriteBytesAtAddress(0x809540, byteArray, sizeof(byteArray));
	}

	if (extendedItemMods)
	{
		// Code needs to be un-commented when you decide to add some custom mods
		// ofc can replace "ITEM_MOD_TEST" with your own
		//const char* customItemModStrings[1] = {
		//	"ITEM_MOD_TEST"
		//};

		memcpy(&itemModTable, (const void*)0xAD6640, 0xC4);
		Util::OverwriteUInt32AtAddress(0x5DC1EB, (uint32_t)&itemModTable);
		Util::OverwriteUInt32AtAddress(0x629211, (uint32_t)&itemModTable);
		Util::OverwriteUInt32AtAddress(0x6292E6, (uint32_t)&itemModTable);
		Util::OverwriteUInt32AtAddress(0x62BC60, (uint32_t)&itemModTable);
		Util::OverwriteUInt32AtAddress(0x62BE67, (uint32_t)&itemModTable);
		//
		Util::OverwriteUInt32AtAddress(0x62BD82, (uint32_t)&itemModTable[45]);
		// when you read code in ida, this table is kinda dumb but what can you do about it
		memcpy(&itemModTableVal, (const void*)0xA25F78, 0x94);
		Util::OverwriteUInt32AtAddress(0x62BC43, (uint32_t)&itemModTableVal);
		Util::SetByteAtAddress((void*)0x62BC4E, (uint8_t)(sizeof(itemModTableVal)/4));
		Util::OverwriteUInt32AtAddress(0x62BC59, (uint32_t)&itemModTableVal);
		Util::OverwriteUInt32AtAddress(0x62BE4A, (uint32_t)&itemModTableVal);
		Util::SetByteAtAddress((void*)0x62BE55, (uint8_t)(sizeof(itemModTableVal) / 4));
		Util::OverwriteUInt32AtAddress(0x62BE60, (uint32_t)&itemModTableVal);

		//for (uint32_t i = 0; i < sizeof(customItemModStrings) / 4; i++)
		//	itemModTable[i + 49] = (uint32_t)customItemModStrings[i];
		//
		//for (uint32_t j = 37; j < sizeof(itemModTableVal) / 4; j++)
		//	itemModTableVal[j] = j + 12;
	}
}
