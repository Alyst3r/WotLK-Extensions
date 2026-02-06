#pragma once

#include <SharedDefines.hpp>

static CustomNetClient customData = { 0 };

class CustomPacket
{
public:
    static void Apply();
private:
    static void SetCustomHandlers();

    static void InitializePlayerEx();
    static void __fastcall ProcessMessageEx(void* _this, uint32_t unused, uint32_t a2, CDataStore* a3, uint32_t a4);
    static void __fastcall SetMessageHandlerEx(void* _this, uint32_t unused, uint32_t opcode, void* function, void* param);

    static void Packet_SMSG_UPDATE_CUSTOM_COMBAT_RATING(void* handlerParam, uint32_t opcode, uint32_t a2, CDataStore* a3);
};
