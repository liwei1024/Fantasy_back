#include "pch.h"

HANDLE g_currentProcessId = NULL;

NTSTATUS DispatchDeviceControl(
	IN PDEVICE_OBJECT DeviceObject,
	IN PIRP Irp
)
{
	UNREFERENCED_PARAMETER(DeviceObject);
	NTSTATUS Status = STATUS_SUCCESS;
	PIO_STACK_LOCATION Stack;
	PREAD_VIRTUAL_MEMORY_STRUCT rvms;
	PWRITE_VIRTUAL_MEMORY_STRUCT wvms;
	ULONG IoControlCode;

	//�õ���ǰ��ջ
	Stack = IoGetCurrentIrpStackLocation(Irp);
	dprintf("Test");
	if (Stack) {
		IoControlCode = Stack->Parameters.DeviceIoControl.IoControlCode;
		if (IoControlCode == PROTECT_THE_CURRENT_PROCESS)
		{
			Status = ProtectTheCurrentProcess();
			Irp->IoStatus.Information = 0;
		}
		else if (IoControlCode == UNPROTECT_THE_CURRENT_PROCESS)
		{
			UnprotectTheCurrentProcess();
			Status = STATUS_SUCCESS;
			Irp->IoStatus.Information = 0;
		}
		else if (IoControlCode == SET_TARGET_PROCESS_NAME)
		{
			/*if (Irp->AssociatedIrp.SystemBuffer)
			{
				memcpy(&g_targetProcessName, Irp->AssociatedIrp.SystemBuffer, sizeof(g_targetProcessName));
			}*/
			Status = STATUS_SUCCESS;
			Irp->IoStatus.Information = 0;
		}
		else if (IoControlCode == GET_TARGET_PROCESS_STATUS)
		{
			*(ULONG*)Irp->AssociatedIrp.SystemBuffer = (ULONG)g_TargetProcessInfo.ProcessStatus;
			Status = STATUS_SUCCESS;
			Irp->IoStatus.Information = sizeof(ULONG);
		}
		else if(g_TargetProcessInfo.ProcessStatus == TRUE)
		{
			switch (IoControlCode)
			{
			case READ_VIRTUAL_MEMORY:
				{
					rvms = (PREAD_VIRTUAL_MEMORY_STRUCT)Irp->AssociatedIrp.SystemBuffer;
					if (rvms)
					{
						Status = ReadVirtualMemory(rvms);
					}
					Irp->IoStatus.Information = sizeof(READ_VIRTUAL_MEMORY_STRUCT);
				}
				break;
			case WRITE_VIRTUAL_MEMORY:
				{
					wvms = (PWRITE_VIRTUAL_MEMORY_STRUCT)Irp->AssociatedIrp.SystemBuffer;
					if (wvms)
					{
						Status = WriteVirtualMemory(wvms);
					}
					Irp->IoStatus.Information = sizeof(WRITE_VIRTUAL_MEMORY_STRUCT);
				}
				break;
			default:
				break;
			}
		}
		
	}
	else {
		Status = STATUS_NOT_SUPPORTED;
	}
	Irp->IoStatus.Status = Status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return Status;
}