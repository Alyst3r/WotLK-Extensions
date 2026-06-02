// Portions of this file based on nampower (https://gitea.com/avitasia/nampower)
// Copyright (c) 2017-2023, namreeb (legal@namreeb.org)
// BSD 2-Clause License

#pragma once
#include <Windows.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
    FileIOResult m_result;
    std::string m_content;
};

class CustomFileIO
{
public:
    static bool IsValidFilename(const char* name);
    static bool ValidateLuaFilename(const char* filename);
    static bool ResolveValidatedPath(const char* baseDir, const char* filename, bool forceTxtExtension, std::string& outPath);

    static std::string GetCustomDataDir();

    static FileIOResult WriteFileToDirectory(const char* baseDir, bool forceTxtExtension, const char* filename, char mode, const char* content);
    static void ReadFileFromDirectory(const char* baseDir, bool forceTxtExtension, const char* filename, bool returnNilIfMissing, FileReadResult& file);

    static std::wstring Utf8ToWide(const std::string& utf8);
    static std::string WideToUtf8(const std::wstring& wide);

private:
    CustomFileIO() = delete;
    ~CustomFileIO() = delete;

    static bool EnsureDirectoryExists(const char* baseDir);
    static std::string BuildPath(const char* baseDir, const char* filename, bool forceTxtExtension);
    static bool TryGetFullPath(const std::string& inputPath, std::string& outFullPath);
};

