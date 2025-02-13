#include "Misc.h"

void Misc::ApplyPatches()
{
	if (noAmmoPatch)
	{
		uint8_t byteArray[] = { 0xE9, 0xBA, 0x00, 0x00, 0x00 };
		Util::OverwriteBytesAtAddress(0x809540, byteArray, sizeof(byteArray));
	}
}
