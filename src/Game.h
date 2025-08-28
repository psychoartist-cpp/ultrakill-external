#pragma once

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <windows.h>
#include <intsafe.h>
#include <TlHelp32.h>

#include <string>
#include <iostream>
#include <fstream>
#include <string_view>
#include <format>
#include <vector>
#include <codecvt>
#include <expected>
#include <exception>
#include <optional>

#include "Logger.h"
#include "Utilities.h"

#define INVALID_MODULE_ADDRESS 0xDEADC0DE

class InvalidProcessError : public std::exception {
private:
	std::wstring_view procName;
	const char* message;
public:
	InvalidProcessError(const std::wstring_view& procName, const char* message) :
		procName(procName), message(message) { }

	const char* what() const noexcept override {
		return message;
	}

	std::wstring_view name() const noexcept {
		return procName;
	}
};

class Game
{
private:
	// Process name
	std::wstring_view m_procName;
	// Process pid
	DWORD m_pid = 0;
	// Handle to the process, make sure it has full access
	HANDLE m_hProc = INVALID_HANDLE_VALUE;
public:


	// Can throw InvalidProcessError
	Game(std::wstring_view procName);
	~Game();

	// Get a module's base address
	// Handled with strings to handle at process level
	std::expected<uintptr_t, std::string_view> GetModuleBase(const std::wstring& moduleName) const;

	// Writes value to memory
	template<typename T>
	bool WriteMemory(uintptr_t addy, T value) {
		SIZE_T bytesWritten;
		BOOL writeResult = WriteProcessMemory(
			m_hProc,
			reinterpret_cast<LPVOID>(addy),
			reinterpret_cast<LPCVOID>(&value),
			sizeof(T),
			&bytesWritten
		);

		if (!writeResult || bytesWritten != sizeof(T)) {
			logging::Error("Failed to write memory!");
			return false;
		}
		return true;
	}
	// Reads memory at address
	template<typename T>
	std::optional<T> ReadMemory(uintptr_t addy) {
		size_t bytesRead;
		T value;

		BOOL readResult = ReadProcessMemory(
			m_hProc, (LPCVOID)addy, &value, sizeof(T), &bytesRead
		);
		if (!readResult) {
			logging::Error("Failed to read memory!");
			return std::nullopt;
		}
		else return value;
	}

};

