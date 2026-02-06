#pragma once

#include <filesystem>
#include <fstream>
#include <string>

std::string relProjectPath(std::string const& pathIn);

class Logger
{
public:
    Logger();

    template <typename T>
    Logger& operator<<(T const& obj)
    {
        m_file << obj;
        m_file.flush();

        return *this;
    }

private:
    std::ofstream m_file;
};

Logger& log(const char* chr, const char* file, size_t line);

#define LOG_DEBUG log("DEBUG", __FILE__, __LINE__)
#define LOG_ERROR log("ERROR", __FILE__, __LINE__)
#define LOG_INFO log("INFO", __FILE__, __LINE__)
#define LOG_WARN log("WARN", __FILE__, __LINE__)
