// Portions of this file based on nampower (https://gitea.com/avitasia/nampower)
// Copyright (c) 2017-2023, namreeb (legal@namreeb.org)
// BSD 2-Clause License

#include "CustomFileIO.hpp"

bool CustomFileIO::IsValidFilename(const char* name)
{
    return name && name[0] != '\0' && std::strpbrk(name, "<>:\"/\\|?*") == nullptr;
}

bool CustomFileIO::ValidateLuaFilename(const char* filename)
{
    if (!IsValidFilename(filename))
        return false;

    return true;
}

std::wstring CustomFileIO::Utf8ToWide(const std::string& utf8)
{
    if (utf8.empty())
        return {};

    const int len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), nullptr, 0);

    if (len <= 0)
        return {};

    std::wstring wide(len, L'\0');

    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), static_cast<int>(utf8.size()), &wide[0], len);

    return wide;
}

std::string CustomFileIO::WideToUtf8(const std::wstring& wide)
{
    if (wide.empty())
        return {};

    const int len = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), static_cast<int>(wide.size()), nullptr, 0, nullptr, nullptr);

    if (len <= 0)
        return {};

    std::string utf8(len, '\0');

    WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), static_cast<int>(wide.size()), &utf8[0], len, nullptr, nullptr);

    return utf8;
}

bool CustomFileIO::EnsureDirectoryExists(const char* baseDir)
{
    if (CreateDirectoryW(Utf8ToWide(baseDir).c_str(), nullptr))
        return true;

    const DWORD errorCode = GetLastError();

    return errorCode == ERROR_ALREADY_EXISTS;
}

bool CustomFileIO::TryGetFullPath(const std::string& inputPath, std::string& outFullPath)
{
    const std::wstring wideInput = Utf8ToWide(inputPath);
    wchar_t buffer[MAX_PATH] = {};
    const DWORD result = GetFullPathNameW(wideInput.c_str(), MAX_PATH, buffer, nullptr);

    if (result == 0 || result >= MAX_PATH)
        return false;

    outFullPath = WideToUtf8(std::wstring(buffer, result));

    return true;
}

std::string CustomFileIO::BuildPath(const char* baseDir, const char* filename, bool forceTxtExtension)
{
    std::string fileNameStr(filename);
    std::string fullPath(baseDir);

    if (forceTxtExtension)
        fileNameStr += ".txt";

    fullPath += "\\";
    fullPath += fileNameStr;

    return fullPath;
}

bool CustomFileIO::ResolveValidatedPath(const char* baseDir, const char* filename, bool forceTxtExtension, std::string& outPath)
{
    if (!filename || !*filename)
        return false;

    std::string baseFullPath;

    if (!TryGetFullPath(baseDir, baseFullPath))
        return false;

    std::string candidatePath = BuildPath(baseDir, filename, forceTxtExtension);
    std::string candidateFullPath;

    if (!TryGetFullPath(candidatePath, candidateFullPath))
        return false;

    std::string basePrefix = baseFullPath;

    if (!basePrefix.empty() && basePrefix.back() != '\\' && basePrefix.back() != '/')
        basePrefix += "\\";

    if (candidateFullPath.size() <= basePrefix.size())
        return false;

    if (_strnicmp(candidateFullPath.c_str(), basePrefix.c_str(), basePrefix.size()) != 0)
        return false;

    outPath = candidateFullPath;

    return true;
}

// Creates the "CustomData" directory in the same location as the executable if not found, and returns its path.
std::string CustomFileIO::GetCustomDataDir()
{
    char path[MAX_PATH];
    GetModuleFileNameA(nullptr, path, MAX_PATH);

    std::string dir(path);

    dir = dir.substr(0, dir.find_last_of("\\/"));
    dir += "\\CustomData";

    CreateDirectoryA(dir.c_str(), nullptr);

    return dir;
}

FileIOResult CustomFileIO::WriteFileToDirectory(const char* baseDir, bool forceTxtExtension, const char* filename, char mode, const char* content)
{
    if (!EnsureDirectoryExists(baseDir))
        return FileIOResult::DirectoryCreateFailed;

    std::string fullPath;

    if (!ResolveValidatedPath(baseDir, filename, forceTxtExtension, fullPath))
        return FileIOResult::InvalidPath;

    std::ios::openmode openMode = std::ios::out;
    if (mode == 'w')
        openMode |= std::ios::trunc;
    else if (mode == 'a')
        openMode |= std::ios::app;
    else if (mode == 'b')
        openMode |= std::ios::binary;
    else
        return FileIOResult::InvalidMode;

    if (mode == 'w' || mode == 'b')
    {
        const std::wstring wideFull = Utf8ToWide(fullPath);
        const std::wstring wideTemp = wideFull + L".tmp";

        {
            std::ofstream out(wideTemp, openMode);

            if (!out)
                return FileIOResult::TempFileOpenFailed;

            out << content;

            if (!out)
            {
                DeleteFileW(wideTemp.c_str());

                return FileIOResult::TempFileWriteFailed;
            }
        }

        if (!MoveFileExW(wideTemp.c_str(), wideFull.c_str(), MOVEFILE_REPLACE_EXISTING))
        {
            DeleteFileW(wideTemp.c_str());

            return FileIOResult::TempFileRenameFailed;
        }
    }
    else
    {
        std::ofstream out(Utf8ToWide(fullPath), openMode);

        if (!out)
            return FileIOResult::FileOpenFailed;

        out << content;

        if (!out)
            return FileIOResult::FileWriteFailed;
    }

    return FileIOResult::Success;
}


void CustomFileIO::ReadFileFromDirectory(const char* baseDir, bool forceTxtExtension, const char* filename, bool returnNilIfMissing, FileReadResult& file)
{
    std::string fullPath;

    if (!ResolveValidatedPath(baseDir, filename, forceTxtExtension, fullPath))
    {
        file.m_result = FileIOResult::InvalidPath;

        return;
    }

    const std::wstring widePath = Utf8ToWide(fullPath);
    const DWORD attributes = GetFileAttributesW(widePath.c_str());

    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
        const DWORD err = GetLastError();

        if (returnNilIfMissing && (err == ERROR_FILE_NOT_FOUND || err == ERROR_PATH_NOT_FOUND))
        {
            file.m_result = FileIOResult::FileNotFound;

            return;
        }
            
        file.m_result = FileIOResult::FileOpenFailed;

        return;
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        file.m_result = FileIOResult::FileOpenFailed;

        return;
    }

    std::ifstream in(widePath);

    if (!in)
    {
        file.m_result = FileIOResult::FileOpenFailed;

        return;
    }

    std::ostringstream buf;
    buf << in.rdbuf();

    file.m_result = FileIOResult::Success;
    file.m_content = buf.str();
}
