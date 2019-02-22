#pragma once
#include <windows.h>
#include <psapi.h>
#include <TlHelp32.h>
#include <map>
#include <ctime>
#include <string>
#include <iostream>
#include <tchar.h>
#include <vector>
namespace utils
{
	/// <summary>根据进程名获取进程ID</summary>
	DWORD getProcessIdByProcessName(const wchar_t * processName);
	void writeConfig(const wchar_t * filePath, const wchar_t * key, const wchar_t * value);
	int createRandom(int min, int max);
};

