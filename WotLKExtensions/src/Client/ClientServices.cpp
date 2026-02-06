#include <Client/ClientServices.hpp>

uint8_t ClientServices::GetCharacterClass()
{
	return reinterpret_cast<uint8_t (__cdecl*)()>(0x6B1080)();
}

void ClientServices::InitializePlayer()
{
	reinterpret_cast<void (__cdecl*)()>(0x6E83B0)();
}

void ClientServices::SendPacket(CDataStore* packet)
{
	reinterpret_cast<void (__cdecl*)(CDataStore*)>(0x6B0B50)(packet);
}
