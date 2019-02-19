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