#pragma once

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <codecvt>

namespace utilities {
	// Convert uintptr to string
	// 0xDEADC0DE -> "0xDEADC0DE" (duh?)
	std::string StringifyUintptr(uintptr_t value);

	// Convert std::wstring to std::string
	std::string ConvertWstring(const std::wstring& value);
}