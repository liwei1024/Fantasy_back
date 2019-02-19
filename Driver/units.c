#include "pch.h"

PCHAR GetProcessNameByProcessId(
	HANDLE hProcessId
)
{
	NTSTATUS		status = STATUS_UNSUCCESSFUL;
	PEPROCESS		ProcessObj = NULL;
	PCHAR			pProcessName = NULL;

	status = PsLookupProcessByProcessId(hProcessId, &ProcessObj);
	if (NT_SUCCESS(status))
	{
		pProcessName = PsGetProcessImageFileName(ProcessObj);
		ObfDereferenceObject(ProcessObj);
	}

	return pProcessName;
}