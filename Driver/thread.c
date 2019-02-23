#include "pch.h"

//#pragma alloc_text(PAGE, GetThreadHandle)

HANDLE GetThreadHandle(PETHREAD Thread)
{
	HANDLE ThreadHandle = NULL;
	ObOpenObjectByPointer(
		Thread,
		0,
		NULL,
		THREAD_ALL_ACCESS,
		*PsThreadType,
		KernelMode,
		&ThreadHandle
	);
	return ThreadHandle;
}