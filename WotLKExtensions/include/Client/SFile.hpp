#pragma once

#include <Windows.h>
#include <cstdint>

class SFile
{
public:
	static bool OpenFileEx(HANDLE, const char*, uint32_t, HANDLE*);
	static bool ReadFile(HANDLE handle /*likely a handle*/, void* data, uint32_t bytesToRead, uint32_t* bytesRead, uint32_t* overlap /*just set to 0*/, uint32_t unk);
	static void CloseFile(HANDLE handle);

private:
	SFile() = delete;
	~SFile() = delete;
};
