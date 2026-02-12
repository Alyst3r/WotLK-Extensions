#pragma once

#include <cstdint>

class CGChat
{
public:
    static bool AddChatMessage(char* msg, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t* a5, uint32_t a6, char* a7, uint64_t a8, uint32_t a9, uint64_t a10, uint32_t a11, uint32_t a12, uint32_t* a13);

private:
    CGChat() = delete;
    ~CGChat() = delete;
};
