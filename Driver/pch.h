#pragma once
#include "native.h"
#include "driver.h"

#define dprintf(Format, ...) DbgPrint("Fantasy: " Format "\n", __VA_ARGS__)

extern HANDLE g_currentProcessId;

typedef struct _TARGET_PROCESS_INFO
{
	PEPROCESS Process;
	HANDLE ProcessId;
	HANDLE ProcessHandle;
	PVOID ProcessBaseAddress;

	HANDLE MainThreadId;
	PETHREAD MainThread;
	HANDLE MainThreadHandle;

	BOOLEAN ProcessStatus;

}KCE_TARGET_PROCESS_INFO_STRUCT, *PKCE_TARGET_PROCESS_INFO_STRUCT;

extern KCE_TARGET_PROCESS_INFO_STRUCT g_TargetProcessInfo;

/// dispatch
NTSTATUS DispatchDeviceControl(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
);

/// <summary>读虚拟内存</summary>
NTSTATUS ReadVirtualMemory(
	PREAD_VIRTUAL_MEMORY_STRUCT rvms
);
/// <summary>写虚拟内存</summary>
NTSTATUS WriteVirtualMemory(
	PWRITE_VIRTUAL_MEMORY_STRUCT wvms
);

/// <summary>保护当前进程</summary>
NTSTATUS ProtectTheCurrentProcess();
/// <summary>解除当前进程保护</summary>
VOID UnprotectTheCurrentProcess();