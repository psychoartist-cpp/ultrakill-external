#include "Logger.h"

void logging::OutputRaw(LoggerPrefix prefix,const std::string_view color, const std::string& message)
{
	time_t now = time(0);
	struct tm* ltm = localtime(&now);
	char buffer[11];
	strftime(buffer, sizeof(buffer), "[%H:%M:%S]", ltm);

	char prefixChar = static_cast<char>(prefix);
	std::cout << color 
		<< buffer << " => " << "[" << prefixChar << "] " << message << clearColor << std::endl;
}

void logging::Info(const std::string& message)
{
	OutputRaw(LoggerPrefix::Success, cyanColor, message);
}

void logging::Debug(const std::string& message)
{
	OutputRaw(LoggerPrefix::Success, cyanColor, message);
}

void logging::Success(const std::string& message)
{
	OutputRaw(LoggerPrefix::Success, greenColor, message);
}

void logging::Error(const std::string& message)
{
	OutputRaw(LoggerPrefix::Fail, redColor, message);
}

void logging::Critical(const std::string& message)
{
	OutputRaw(LoggerPrefix::Fail, redColor, message);
}

void logging::Warn(const std::string& message)
{
	OutputRaw(LoggerPrefix::Fail, yellowColor, message);
}
