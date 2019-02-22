#include "pch.h"


HANDLE GetProcessHandle(PEPROCESS Process)
{
	HANDLE ProcessHandle = NULL;
	ObOpenObjectByPointer(
		Process,
		0,
		NULL,
		PROCESS_ALL_ACCESS,
		*PsProcessType,
		KernelMode,
		&ProcessHandle
	);
	return ProcessHandle;
}