#include "Logger.h"

#include <fstream>
#include <ctime>
#include <iomanip>
#include <windows.h>
#include <filesystem>

static std::filesystem::path dirname = std::filesystem::path(__FILE__).parent_path();

std::string relProjectPath(std::string const& pathIn)
{
	return std::filesystem::relative(pathIn, dirname).string();
}

namespace {
	Logger logger;
}

Logger::Logger()
{
#if LOG_LEVEL > 0
	m_file.open("log",std::ios::out);
#endif
}

static bool isFirst = true;
Logger& log(const char* type, const char* file, size_t line)
{
#if LOG_LEVEL > 0
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::string filename = relProjectPath(file);

	if (isFirst)
		isFirst = false;
	else
		logger << "\n";

	logger
	<< "["
	<< type
	<< "]["
	<< std::put_time(&tm, "%H:%M:%S")
	<< "]["
	<< relProjectPath(file)
	<< ":"
	<< line
	<< "] ";
#endif
	return logger;
}
