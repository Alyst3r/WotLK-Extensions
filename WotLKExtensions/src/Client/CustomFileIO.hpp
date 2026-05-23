// Portions of this file based on nampower (https://gitea.com/avitasia/nampower)
// Copyright (c) 2017-2023, namreeb (legal@namreeb.org)
// BSD 2-Clause License

#pragma once
#include <windows.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

enum class FileIOResult : uint32_t
{
    Success = 0,
    DirectoryCreateFailed,
    InvalidPath,
    InvalidMode,
    TempFileOpenFailed,
    TempFileWriteFailed,
    TempFileRenameFailed,
    FileOpenFailed,
    FileWriteFailed,
    InvalidFilename,
    FileNotFound,
    FileReadFailed,
};

struct FileReadResult
{
    FileIOResult Result;
    std::string Content;
};

bool IsValidFilename(const char* name);
bool ValidateLuaFilename(const char* filename);
std::string GetCustomDataDir();
FileIOResult WriteFileToDirectory(const char* baseDir, bool forceTxtExtension,
    const char* filename, char mode, const char* content);

FileReadResult* ReadFileFromDirectory(const char* baseDir, bool forceTxtExtension,
    const char* filename, bool returnNilIfMissing, std::string& outContent);

std::wstring Utf8ToWide(const std::string& utf8);

std::string WideToUtf8(const std::wstring& wide);


bool ResolveValidatedPath(const char* baseDir, const char* filename, bool forceTxtExtension,
    std::string& outPath);