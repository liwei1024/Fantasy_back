#include "pch.h"

KCE_TARGET_PROCESS_INFO_STRUCT g_TargetProcessInfo;

/// <summary>(创建/结束)进程处理</summary>
VOID ProcessNotify(
	_Inout_  PEPROCESS              Process,
	_In_     HANDLE                 ProcessId,
	_In_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo
)
{
	if (NULL != CreateInfo)
	{
		//if (wcsstr(CreateInfo->ImageFileName->Buffer, L"dnf.exe"))YoudaoDict.exe
		if (wcsstr(CreateInfo->ImageFileName->Buffer, L"YoudaoDict.exe"))
		{
			g_TargetProcessInfo.ProcessStatus = TRUE;
			g_TargetProcessInfo.ProcessId = ProcessId;
			g_TargetProcessInfo.Process = Process;
		}
	}
	else {
		if (ProcessId == g_currentProcessId) {
			UnprotectTheCurrentProcess();
		}

		if (ProcessId == g_TargetProcessInfo.ProcessId)
		{
			g_TargetProcessInfo.ProcessHandle = NULL;
			g_TargetProcessInfo.MainThreadHandle = NULL;
			g_TargetProcessInfo.ProcessStatus = FALSE;
		}
	}
}

/// <summary>创建虚拟设备</summary>
NTSTATUS CreateDevice(
	IN PDRIVER_OBJECT DriverObject
)
{
	PDEVICE_OBJECT DeviceObject;
	UNICODE_STRING DeviceName;
	UNICODE_STRING SymbolicLinkName;
	NTSTATUS Status = STATUS_SUCCESS;

	RtlInitUnicodeString(&DeviceName, DEVICE_NAME);
	Status = IoCreateDevice(DriverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DeviceObject);
	if (!NT_SUCCESS(Status))return Status;

	RtlInitUnicodeString(&SymbolicLinkName, SYMBOLIC_LINK_NAME);
	Status = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);
	if (!NT_SUCCESS(Status)) {
		IoDeleteDevice(DeviceObject);
		return Status;
	}

	DeviceObject->Flags &= (~DO_DEVICE_INITIALIZING);

	return Status;
}

/// <summary>占坑用 请无视</summary>
NTSTATUS DefaultDispatchFunction(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

/// <summary>卸载驱动</summary>
VOID DriverUnload(
	IN PDRIVER_OBJECT DriverObject
)
{
	UNICODE_STRING SymbolicLinkName;

	PsSetCreateProcessNotifyRoutineEx(ProcessNotify, TRUE);

	UnprotectTheCurrentProcess();

	RtlInitUnicodeString(&SymbolicLinkName, SYMBOLIC_LINK_NAME);
	IoDeleteSymbolicLink(&SymbolicLinkName);

	IoDeleteDevice(DriverObject->DeviceObject);
}

/// <summary>驱动入口</summary>
NTSTATUS DriverEntry(
	IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath
)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS Status = STATUS_SUCCESS;

	Status = PsSetCreateProcessNotifyRoutineEx(ProcessNotify, FALSE);// 创建进程监视回调

	if (NT_SUCCESS(Status)) {
		for (size_t i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
			DriverObject->MajorFunction[i] = DefaultDispatchFunction;

		DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchDeviceControl;
		DriverObject->DriverUnload = DriverUnload;
		DriverObject->Flags |= DO_BUFFERED_IO;

		Status = CreateDevice(DriverObject);
	}

	//dprintf("id->:%d",PsGetCurrentProcessId());

	return Status;
}