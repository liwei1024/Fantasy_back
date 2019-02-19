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

/// <summary>�������ڴ�</summary>
NTSTATUS ReadVirtualMemory(
	PREAD_VIRTUAL_MEMORY_STRUCT rvms
);
/// <summary>д�����ڴ�</summary>
NTSTATUS WriteVirtualMemory(
	PWRITE_VIRTUAL_MEMORY_STRUCT wvms
);

/// <summary>������ǰ����</summary>
NTSTATUS ProtectTheCurrentProcess();
/// <summary>�����ǰ���̱���</summary>
VOID UnprotectTheCurrentProcess();