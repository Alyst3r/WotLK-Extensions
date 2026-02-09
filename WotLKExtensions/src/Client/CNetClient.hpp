#pragma once

#include <cstdint>

struct CDataStore;

class CNetClient
{
public:
    static int ProcessMessage(void* thisMessage, uint32_t a2, CDataStore* dataStore, uint32_t a4);
    static void SetMessageHandler(void* thisMessage, uint32_t opcode, void* handler, void* param);

private:
    CNetClient() = delete;
    ~CNetClient() = delete;
};
