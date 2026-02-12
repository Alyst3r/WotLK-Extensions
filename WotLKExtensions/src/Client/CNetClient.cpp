#include <Client/CDataStore.hpp>
#include <Client/ClientServices.hpp>
#include <Client/CNetClient.hpp>
#include <GameObjects/CGPlayer.hpp>
#include <Misc/Util.hpp>
#include <SharedDefines.hpp>

int CNetClient::ProcessMessage(void* thisMessage, uint32_t a2, CDataStore* dataStore, uint32_t a4)
{
    return reinterpret_cast<int (__thiscall*)(void*, uint32_t, CDataStore*, uint32_t)>(0x631FE0)(thisMessage, a2, dataStore, a4);
}

void CNetClient::SetMessageHandler(void* thisMessage, uint32_t opcode, void* handler, void* param)
{
    reinterpret_cast<void (__thiscall*)(void*, uint32_t, void*, void*)>(0x631FA0)(thisMessage, opcode, handler, param);
}

void CNetClient::Packet_MSG_SET_ACTION_BUTTON(uint32_t slotID, bool p1, bool p2)
{
    reinterpret_cast<void (__cdecl*)(uint32_t, bool, bool)>(0x5AA390)(slotID, p1, p2);
}

void CNetClient::Apply()
{
    Util::OverwriteUInt32AtAddress(0x6E8EE2, (uint32_t)&InitializePlayerEx - 0x6E8EE6);
    //
    Util::OverwriteUInt32AtAddress(0x6324CA, (uint32_t)&ProcessMessageEx - 0x6324CE);
    Util::OverwriteUInt32AtAddress(0x714AFC, (uint32_t)&ProcessMessageEx - 0x714B00);
    Util::OverwriteUInt32AtAddress(0x716A79, (uint32_t)&ProcessMessageEx - 0x716A7D);
    //
    Util::OverwriteUInt32AtAddress(0x6B0B9E, (uint32_t)&SetMessageHandlerEx - 0x6B0BA2);
}

void CNetClient::SetCustomHandlers()
{
    SetMessageHandlerEx(nullptr, 0, SMSG_UPDATE_CUSTOM_COMBAT_RATING, &Packet_SMSG_UPDATE_CUSTOM_COMBAT_RATING, 0);
}

void CNetClient::InitializePlayerEx()
{
    ClientServices::InitializePlayer();
    SetCustomHandlers();
}

void __fastcall CNetClient::ProcessMessageEx(void* _this, uint32_t unused, uint32_t a2, CDataStore* a3, uint32_t a4)
{
    int16_t opcode = 0;
    CDataStore::GetInt16(a3, &opcode);

    if (opcode < NUM_ORIGINAL_MSG_TYPES)
    {
        a3->m_read -= 2;
        CNetClient::ProcessMessage(_this, a2, a3, a4);
    }
    else
    {
        ++*(uint32_t*)0xC5D638;
        uint32_t num = opcode - NUM_ORIGINAL_MSG_TYPES;
        if (opcode < NUM_CUSTOM_MSG_TYPES && customData.handler[num])
            // I've got cancer writing this, function typedefs are ugly as sin
            ((void(*)(void*, uint32_t, uint32_t, CDataStore*))customData.handler[num])(customData.handlerParam[num], opcode, a2, a3);
        else
            CDataStore::IsRead(a3);
    }
}

void __fastcall CNetClient::SetMessageHandlerEx(void* _this, uint32_t unused, uint32_t opcode, void* handler, void* param)
{
    if (opcode < NUM_ORIGINAL_MSG_TYPES)
        CNetClient::SetMessageHandler(_this, opcode, handler, param);
    else
    {
        uint32_t num = opcode - NUM_ORIGINAL_MSG_TYPES;

        customData.handler[num] = handler;
        customData.handlerParam[num] = param;
    }
}

void CNetClient::Packet_SMSG_UPDATE_CUSTOM_COMBAT_RATING(void* handlerParam, uint32_t opcode, uint32_t a2, CDataStore* a3)
{
    int8_t ratingID = 0;
    int32_t ratingAmount = 0;
    CDataStore::GetInt8(a3, &ratingID);
    CDataStore::GetInt32(a3, &ratingAmount);

    if (ratingID > -1 && ratingID < 7)
    {
        if (ratingAmount > -1)
            CustomFields::SetCustomCombatRating(ratingID, ratingAmount);
        else
            CustomFields::SetCustomCombatRating(ratingID, 0);
    }
}
