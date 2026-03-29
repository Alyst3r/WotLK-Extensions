#pragma once

#include <Windows.h>
#include <cstdint>

class SFile
{
public:
    static bool OpenFile(const char* filename, HANDLE* fileBlock);
    static bool OpenFileEx(HANDLE handle, const char* filename, uint32_t flags, HANDLE* fileBlock);
    static bool ReadFile(HANDLE handle /*likely a handle*/, void* data, uint32_t bytesToRead, uint32_t* bytesRead, uint32_t* overlap /*just set to 0*/, uint32_t unk);
    static void CloseFile(HANDLE handle);

private:
    SFile() = delete;
    ~SFile() = delete;
};
