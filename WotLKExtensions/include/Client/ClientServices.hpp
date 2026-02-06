#pragma once

#include <cstdint>

struct CDataStore;

class ClientServices
{
public:
    static uint8_t GetCharacterClass();
    static void InitializePlayer();
    static void SendPacket(CDataStore* packet);

private:
    ClientServices() = delete;
    ~ClientServices() = delete;
};
