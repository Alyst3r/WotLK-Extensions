#pragma once

#include <SharedDefines.hpp>

#include <cstdint>

struct CDataStore;

class ClientServices
{
public:
    static WoWGUID GetActivePlayer();
    static uint8_t GetCharacterClass();
    static void* GetObjectPtr(WoWGUID objGUID, uint32_t typeMask);
    static void InitializePlayer();
    static void SendPacket(CDataStore* packet);

private:
    ClientServices() = delete;
    ~ClientServices() = delete;
};
