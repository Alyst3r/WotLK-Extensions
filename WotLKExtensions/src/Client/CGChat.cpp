#include <Client/CGChat.hpp>

bool CGChat::AddChatMessage(char* msg, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t* a5, uint32_t a6, char* a7, uint64_t a8, uint32_t a9, uint64_t a10, uint32_t a11, uint32_t a12, uint32_t* a13)
{
    return reinterpret_cast<bool (__cdecl*)(char*, uint32_t, uint32_t, uint32_t, uint32_t*, uint32_t, char*, uint64_t, uint32_t, uint64_t, uint32_t, uint32_t, uint32_t*)>(0x509DD0)(msg, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
}
