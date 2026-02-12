#pragma once

#include <cstdint>

struct CDataStore;

class CNetClient
{
public:
    static void Apply();

    // original packet wrappers
    static void Packet_MSG_SET_ACTION_BUTTON(uint32_t slotID, bool p1, bool p2);

private:
    CNetClient() = delete;
    ~CNetClient() = delete;

    static int ProcessMessage(void* thisMessage, uint32_t a2, CDataStore* dataStore, uint32_t a4);
    static void SetMessageHandler(void* thisMessage, uint32_t opcode, void* handler, void* param);

    static void SetCustomHandlers();

    static void InitializePlayerEx();
    static void __fastcall ProcessMessageEx(void* _this, uint32_t unused, uint32_t a2, CDataStore* a3, uint32_t a4);
    static void __fastcall SetMessageHandlerEx(void* _this, uint32_t unused, uint32_t opcode, void* function, void* param);

    // custom packets
    static void Packet_SMSG_UPDATE_CUSTOM_COMBAT_RATING(void* handlerParam, uint32_t opcode, uint32_t a2, CDataStore* a3);
};
