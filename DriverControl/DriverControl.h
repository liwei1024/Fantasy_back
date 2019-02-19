#pragma once
#include <windows.h>
#include <stdio.h>

class DriverControl
{
public:
	DriverControl();
	~DriverControl();
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_STATUS ss;
	wchar_t returnMessage[255] = { 0 };

	BOOL insert(LPCTSTR driverPath);
	BOOL start();
	BOOL stop();
	BOOL unload();
	BOOL control(LPCWSTR SymbolicLinkName, DWORD IoControlCode, PVOID InBuffer, DWORD InBufferSize, PVOID OutBuffer, DWORD OutBufferSize);
	wchar_t *getMessage();
};

