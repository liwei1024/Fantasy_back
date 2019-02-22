#pragma once
#include <windows.h>
#include <stdio.h>
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

class DriverControl
{
public:
	DriverControl();
	~DriverControl();
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_STATUS ss;
	LPCWSTR symboliLinkName;
	LPCTSTR driverFilePath;

	wchar_t returnMessage[255] = { 0 };

	BOOL insert();
	BOOL start();
	BOOL stop();
	BOOL unload();
	BOOL control(DWORD IoControlCode, PVOID InBuffer, DWORD InBufferSize, PVOID OutBuffer, DWORD OutBufferSize);
	wchar_t *getMessage();
};

