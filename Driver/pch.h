#pragma once
#include "native.h"
#include "driver.h"

#define dprintf(Format, ...) DbgPrint("Fantasy: " Format "\n", __VA_ARGS__)



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

}TARGET_PROCESS_INFO_STRUCT, *PTARGET_PROCESS_INFO_STRUCT;

extern TARGET_PROCESS_INFO_STRUCT g_TargetProcessInfo;
extern NTKERNELAPI ULONG NtBuildNumber;//系统版本号
extern HANDLE g_currentProcessId;


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

/// <summary>根据进程ID获取进程名称</summary>
PCHAR GetProcessNameByProcessId(
	HANDLE hProcessId
);

/// <summary>根据进程ID伪装当前进程</summary>
BOOLEAN CamouflageCurrentProcess(HANDLE TargetProcessId);


HANDLE GetProcessHandle(PEPROCESS Process);

HANDLE GetThreadHandle(PETHREAD Thread);