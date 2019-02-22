#pragma once
#include "../Driver/driver.h"
#include "../DriverControl/DriverControl.h"
#pragma comment(lib,"DriverControl.lib")

class Driver :public  DriverControl
{
public:
	HANDLE DriverHandle = NULL;

	Driver() :DriverControl()
	{
		driverFilePath = L"C:\\Users\\lw\\source\\repos\\Fantasy\\x64\\Release\\Driver.sys";

		symboliLinkName = L"\\\\.\\" SYMBOLIC_LINK_SHORT_NAME;

		//printf("%ws\n", L"123132");
		if (!insert()) {
			printf("%ws\n", getMessage());
		}
		if (!start()) {
			printf("%ws\n", getMessage());
		}
	}

	virtual ~Driver()
	{
		stop();
		unload();
	}

	BOOL readVirtualMemory(ULONG Address, PVOID Response, SIZE_T Size)
	{
		READ_VIRTUAL_MEMORY_STRUCT rvms;
		rvms.Response = Response;
		rvms.Address = Address;
		rvms.Size = Size;
		return control(READ_VIRTUAL_MEMORY, &rvms, sizeof(rvms), &rvms, sizeof(rvms));
	}

	BOOL writeVirtualMemory(ULONG Address, PVOID Value, SIZE_T Size)
	{
		WRITE_VIRTUAL_MEMORY_STRUCT wvms;
		BOOL result = TRUE;
		wvms.Address = Address;
		wvms.Value = Value;
		wvms.Size = Size;
		result = control(WRITE_VIRTUAL_MEMORY, &wvms, sizeof(wvms), &wvms, sizeof(wvms));
		return result;
	}

	BOOL protectTheCurrentProcess()
	{
		return control(PROTECT_THE_CURRENT_PROCESS, 0, 0, 0, 0);
	}

	BOOL unprotectTheCurrentProcess()
	{
		return control(UNPROTECT_THE_CURRENT_PROCESS, 0, 0, 0, 0);
	}

	BOOL camouflageCurrentProcess(ULONG targetProcessId)
	{
		return control(CAMOUFLAGE_CURRENT_PROCESS, &targetProcessId, sizeof(targetProcessId), 0, 0);
	}


private:

};

