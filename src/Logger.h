#pragma once

#include <string>
#include <iostream>
#include <map>
#include <chrono>
#include <ctime>

namespace logging {

	enum class LoggerPrefix : char {
		Success = '+',
		Fail = '-'
	};

	const std::string_view redColor    = "\033[31m";
	const std::string_view clearColor  = "\033[0m";
	const std::string_view greenColor  = "\033[32m";
	const std::string_view yellowColor = "\033[33m";
	const std::string_view cyanColor   = "\033[36m";

	void OutputRaw(LoggerPrefix prefix, const std::string_view color, const std::string& message);
	void Info(const std::string& message);
	void Debug(const std::string& message);
	void Success(const std::string& message);
	void Error(const std::string& message);
	void Critical(const std::string& message);
	void Warn(const std::string& message);
}