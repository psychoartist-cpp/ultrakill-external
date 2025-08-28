#include "Utilities.h"

std::string utilities::StringifyUintptr(uintptr_t value)
{
	
	std::stringstream ss;
	ss << std::hex << value;
	
	return ss.str();
}

std::string utilities::ConvertWstring(const std::wstring& value)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(value);
}
