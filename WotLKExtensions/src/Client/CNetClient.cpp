#include <Client/CNetClient.hpp>

int CNetClient::ProcessMessage(void* thisMessage, uint32_t a2, CDataStore* dataStore, uint32_t a4)
{
    return reinterpret_cast<int (__thiscall*)(void*, uint32_t, CDataStore*, uint32_t)>(0x631FE0)(thisMessage, a2, dataStore, a4);
}

void CNetClient::SetMessageHandler(void* thisMessage, uint32_t opcode, void* handler, void* param)
{
    reinterpret_cast<void (__thiscall*)(void*, uint32_t, void*, void*)>(0x631FA0)(thisMessage, opcode, handler, param);
}
