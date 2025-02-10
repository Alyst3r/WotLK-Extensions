#include "Misc.h"

void Misc::ApplyPatches()
{
	if (noAmmoPatch)
	{
		Functions::SetByteAtAddress(reinterpret_cast<void*>(0x809540), 0xE9);
		Functions::SetByteAtAddress(reinterpret_cast<void*>(0x809541), 0xBA);
		Functions::OverwriteBytesAtAddress(reinterpret_cast<void*>(0x809542), 0x00, 3);
	}
}
