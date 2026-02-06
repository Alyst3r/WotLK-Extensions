#include <Client/SFile.hpp>

bool SFile::OpenFileEx(HANDLE handle, const char* filename, uint32_t flags, HANDLE* fileBlock)
{
    return reinterpret_cast<bool (__stdcall*)(HANDLE, const char*, uint32_t, HANDLE*)>(0x424B50)(handle, filename, flags, fileBlock);
}

bool SFile::ReadFile(HANDLE handle /*likely a handle*/, void* data, uint32_t bytesToRead, uint32_t* bytesRead, uint32_t* overlap /*just set to 0*/, uint32_t unk)
{
    return reinterpret_cast<bool (__stdcall*)(HANDLE, void*, uint32_t, uint32_t*, uint32_t*, uint32_t)>(0x422530)(handle, data, bytesToRead, bytesRead, overlap, unk);
}

void SFile::CloseFile(HANDLE handle)
{
    reinterpret_cast<void(__stdcall*)(HANDLE)>(0x422910)(handle);
}
