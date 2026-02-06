#include <Misc/Logger.hpp>

#include <chrono>
#include <iomanip>
#include <sstream>

static std::filesystem::path dirname = std::filesystem::path(__FILE__).parent_path();

Logger logger;

Logger::Logger()
{
    if (!std::filesystem::exists("DLL_Logs"))
        std::filesystem::create_directory("DLL_Logs");

    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    std::string build;

#ifndef NDEBUG
    build = "_debug";
#else
    build = "_release";
#endif

    localtime_s(&tm, &t);

    std::ostringstream oss;
    oss << "Logs/" << std::put_time(&tm, "%Y_%m_%d_%H_%M_%S") << build << ".txt";

    m_file.open(oss.str(), std::ios::out);
}

static bool isFirst = true;
Logger& log(const char* type, const char* file, size_t line)
{
    auto t = std::time(nullptr);
    std::tm tm{};

    localtime_s(&tm, &t);

    if (isFirst)
        isFirst = false;
    else
        logger << "\n";

#ifndef NDEBUG
    logger << "[" << type << "][" << std::put_time(&tm, "%H:%M:%S") << "][" << relProjectPath(file) << ":" << line << "] ";
#else
    logger << "[" << type << "][" << std::put_time(&tm, "%H:%M:%S") << "] ";
#endif

    return logger;
}

std::string relProjectPath(std::string const& pathIn)
{
    return std::filesystem::relative(pathIn, dirname).string();
}
