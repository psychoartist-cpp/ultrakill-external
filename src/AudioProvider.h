#pragma once

#include "Logger.h"
#include <fstream>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

bool PlayAsyncSound(const wchar_t* path);

