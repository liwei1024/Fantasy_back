#include "DriverControl.h"



DriverControl::DriverControl()
{
	
}


DriverControl::~DriverControl()
{
}

BOOL DriverControl::insert()
{
	wchar_t ServicesName[MAX_PATH] = { 0 };

	::lstrcpy(ServicesName, driverFilePath);
	::PathStripPathW(ServicesName);                   // 过滤掉文件目录，获取文件名

	schSCManager = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);//打开服务管理器
	
	schService = ::CreateService(
		schSCManager, 
		ServicesName,
		ServicesName,
		SERVICE_ALL_ACCESS, 
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START, 
		SERVICE_ERROR_NORMAL,
		driverFilePath, 
		NULL,
		NULL, 
		NULL, 
		NULL, NULL
	);

	/*SERVICE_STATUS sStatus;
	QueryServiceStatus(schService, &sStatus);*/

	if (!schService)
	{
		wsprintfW(returnMessage, L"CreateService Failure  Error Code - <%d>", ::GetLastError());
		::CloseServiceHandle(schSCManager);
		return FALSE;
	}

	schService = OpenService(schSCManager, ServicesName, SERVICE_ALL_ACCESS);
	if (!schService)
	{
		wsprintfW(returnMessage, L"OpenService Failure  Error Code - <%d>", ::GetLastError());
		//::CloseServiceHandle(schSCManager);
		return FALSE;
	}
	wsprintfW(returnMessage, L"%s", L"安装成功");
	return TRUE;
}

BOOL DriverControl::start()
{
	if (!::StartService(schService, 0, NULL))
	{
		wsprintfW(returnMessage, L"StartService Failure  Error Code - <%d>", ::GetLastError());
		//::CloseServiceHandle(schService);
		//::CloseServiceHandle(schSCManager);
		return FALSE;
	}
	wsprintfW(returnMessage, L"%s", L"启动成功");
	return TRUE;
}

BOOL DriverControl::stop()
{
	if (!::ControlService(schService, SERVICE_CONTROL_STOP, &ss))
	{
		wsprintfW(returnMessage, L"StopService Failure  Error Code - <%d>", ::GetLastError());
		//::CloseServiceHandle(schService);
		//::CloseServiceHandle(schSCManager);
		return FALSE;
	}
	wsprintfW(returnMessage, L"%s", L"停止成功");
	return TRUE;
}

BOOL DriverControl::unload()
{
	BOOL result = ::DeleteService(schService);
	if (!result)
	{
		wsprintfW(returnMessage, L"DeleteService Failure  Error Code - <%d>", ::GetLastError());
	}
	else {
		wsprintfW(returnMessage, L"%s", L"卸载成功");
	}
	::CloseServiceHandle(schService);
	//::CloseServiceHandle(schSCManager);
	return result;
}

BOOL DriverControl::control(DWORD IoControlCode,
	PVOID InBuffer, DWORD InBufferSize, PVOID OutBuffer, DWORD OutBufferSize)
{
	HANDLE hDevice = INVALID_HANDLE_VALUE;
	DWORD Junk = 0;
	DWORD errorCode = 0;

	hDevice = CreateFileW(symboliLinkName, 0, FILE_SHARE_READ |
		FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		wsprintfW(returnMessage, L"CreateFile Failure  Error Code - <%d>", ::GetLastError());
		return FALSE;
	}

	if (!DeviceIoControl(hDevice, IoControlCode, InBuffer,
		InBufferSize, OutBuffer, OutBufferSize, &Junk, NULL))
	{
		errorCode = GetLastError();
		if (errorCode != 299)
		{
			wsprintfW(returnMessage, L"DeviceIoControl Failure  Error Code - <%d>", ::GetLastError());
		}
		CloseHandle(hDevice);
		return FALSE;
	}
	CloseHandle(hDevice);
	return TRUE;
}

wchar_t* DriverControl::getMessage()
{
	return returnMessage;
}