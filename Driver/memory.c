#include "pch.h"

NTSTATUS ReadVirtualMemory(
	PREAD_VIRTUAL_MEMORY_STRUCT rvms
)
{
	NTSTATUS Status = STATUS_SUCCESS;
	SIZE_T Bytes;
	if (g_TargetProcessInfo.ProcessStatus == TRUE)
	{
		Status = MmCopyVirtualMemory(g_TargetProcessInfo.Process, (CONST PVOID)rvms->Address, PsGetCurrentProcess(), rvms->Response, (SIZE_T)rvms->Size, KernelMode, &Bytes);
	}
	return Status;

}

NTSTATUS WriteVirtualMemory(
	PWRITE_VIRTUAL_MEMORY_STRUCT wvms
)
{
	NTSTATUS Status = STATUS_SUCCESS;
	SIZE_T Bytes;
	if (g_TargetProcessInfo.ProcessStatus == TRUE)
	{
		Status = MmCopyVirtualMemory(PsGetCurrentProcess(), wvms->Value, g_TargetProcessInfo.Process, (PVOID)wvms->Address, (SIZE_T)wvms->Size, KernelMode, &Bytes);
	}
	return Status;
}