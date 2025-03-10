#include "CustomPacket.h"
#include "Player.h"

void CustomPacket::Apply()
{
	Util::OverwriteUInt32AtAddress(0x6E8EE2, (uint32_t)&InitializePlayerEx - 0x6E8EE6);
	//
	Util::OverwriteUInt32AtAddress(0x6324CA, (uint32_t)&ProcessMessageEx - 0x6324CE);
	Util::OverwriteUInt32AtAddress(0x714AFC, (uint32_t)&ProcessMessageEx - 0x714B00);
	Util::OverwriteUInt32AtAddress(0x716A79, (uint32_t)&ProcessMessageEx - 0x716A7D);
	//
	Util::OverwriteUInt32AtAddress(0x6B0B9E, (uint32_t)&SetMessageHandlerEx - 0x6B0BA2);
}

void CustomPacket::SetCustomHandlers()
{
	SetMessageHandlerEx(nullptr, 0, SMSG_UPDATE_CUSTOM_COMBAT_RATING, &Packet_SMSG_UPDATE_CUSTOM_COMBAT_RATING, 0);
}

void CustomPacket::InitializePlayerEx()
{
	ClientServices::InitializePlayer();
	SetCustomHandlers();
}

void __fastcall CustomPacket::ProcessMessageEx(void* _this, uint32_t unused, uint32_t a2, CDataStore* a3, uint32_t a4)
{
	int16_t opcode = 0;
	CDataStore_C::GetInt16(a3, &opcode);

	if (opcode < SMSG_UPDATE_CUSTOM_COMBAT_RATING)
	{
		a3->m_read -= 2;
		CNetClient::ProcessMessage(_this, a2, a3, a4);
	}
	else
	{
		++*(uint32_t*)0xC5D638;
		uint32_t num = NUM_CUSTOM_MSG_TYPES - opcode - 1;
		if (opcode < NUM_CUSTOM_MSG_TYPES && customData.handler[num])
			// I've got cancer writing this, function typedefs are ugly as sin
			((void(*)(void*, uint32_t, uint32_t, CDataStore*))customData.handler[num])(customData.handlerParam[num], opcode, a2, a3);
		else
			// Yes I know this throws C4229, I'll let you guess why
			((void(*__thiscall)(CDataStore*))a3->vTable->IsRead)(a3);
	}
}

void __fastcall CustomPacket::SetMessageHandlerEx(void* _this, uint32_t unused, uint32_t opcode, void* handler, void* param)
{
	if (opcode < SMSG_UPDATE_CUSTOM_COMBAT_RATING)
		CNetClient::SetMessageHandler(_this, opcode, handler, param);
	else
	{
		uint32_t num = opcode - SMSG_UPDATE_CUSTOM_COMBAT_RATING;
		
		customData.handler[num] = handler;
		customData.handlerParam[num] = param;
	}
}

void CustomPacket::Packet_SMSG_UPDATE_CUSTOM_COMBAT_RATING(void* handlerParam, uint32_t opcode, uint32_t a2, CDataStore* a3)
{
	int8_t ratingID = 0;
	int32_t ratingAmount = 0;
	CDataStore_C::GetInt8(a3, &ratingID);
	CDataStore_C::GetInt32(a3, &ratingAmount);

	if (ratingID > -1 && ratingID < 7)
	{
		if (ratingAmount > -1)
			CustomFields::SetCustomCombatRating(ratingID, ratingAmount);
		else
			CustomFields::SetCustomCombatRating(ratingID, 0);
	}
}
