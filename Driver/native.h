#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
#include <ntstrsafe.h>

NTKERNELAPI NTSTATUS  MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	CONST VOID * SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);

NTKERNELAPI HANDLE PsGetProcessInheritedFromUniqueProcessId(
	IN PEPROCESS Process
);

NTKERNELAPI PCHAR PsGetProcessImageFileName(
	PEPROCESS Process
);

NTKERNELAPI NTSTATUS PsReferenceProcessFilePointer(
	IN PEPROCESS Process,
	OUT PVOID *pFilePointer
);

NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(
	__in PEPROCESS Process
);