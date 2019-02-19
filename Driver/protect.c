#include "pch.h"

#define PROCESS_TERMINATE                  (0x0001)  
#define PROCESS_CREATE_THREAD              (0x0002)  
#define PROCESS_SET_SESSIONID              (0x0004)  
#define PROCESS_VM_OPERATION               (0x0008)  
#define PROCESS_VM_READ                    (0x0010)  
#define PROCESS_VM_WRITE                   (0x0020)  
#define PROCESS_DUP_HANDLE                 (0x0040)  
#define PROCESS_CREATE_PROCESS             (0x0080)  
#define PROCESS_SET_QUOTA                  (0x0100)  
#define PROCESS_SET_INFORMATION            (0x0200)  
#define PROCESS_QUERY_INFORMATION          (0x0400)  
#define PROCESS_SUSPEND_RESUME             (0x0800)  
#define PROCESS_QUERY_LIMITED_INFORMATION  (0x1000)  
#define PROCESS_SET_LIMITED_INFORMATION    (0x2000) 

PVOID g_RegistrationHandle = NULL;

OB_PREOP_CALLBACK_STATUS ProcessPreCallback(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInformation)
{
	if (RegistrationContext == NULL)
	{
		return OB_PREOP_SUCCESS;
	}
	HANDLE pid = PsGetProcessId((PEPROCESS)OperationInformation->Object);
	if (OperationInformation->ObjectType == *PsProcessType && pid == (HANDLE)RegistrationContext)
	{
		if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
		{
			ACCESS_MASK DesiredAccess = OperationInformation->Parameters->CreateHandleInformation.DesiredAccess;

			DesiredAccess = DesiredAccess & (PROCESS_TERMINATE | PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_SUSPEND_RESUME | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE);
			if (DesiredAccess) {
				OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~DesiredAccess;// DesiredAccess;
			}
		}
		else if (OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
		{
			ACCESS_MASK DesiredAccess = OperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess;

			DesiredAccess = DesiredAccess & (PROCESS_TERMINATE | PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_SUSPEND_RESUME | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE);
			if (DesiredAccess) {
				OperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess &= ~DesiredAccess;// DesiredAccess;
			}

		}
	}
	return OB_PREOP_SUCCESS;
}

VOID ProcessPostCallback(PVOID RegistrationContext, POB_POST_OPERATION_INFORMATION OperationInformation)
{
	UNREFERENCED_PARAMETER(RegistrationContext);
	UNREFERENCED_PARAMETER(OperationInformation);
	//dprintf("ProcessPostCallback");
}

OB_PREOP_CALLBACK_STATUS ThreadPreCallback(PVOID RegistrationContext, POB_PRE_OPERATION_INFORMATION OperationInformation)
{
	ACCESS_MASK DesiredAccess;
	if (RegistrationContext == NULL)
		return OB_PREOP_SUCCESS;
	if (PsGetCurrentProcessId() == (HANDLE)RegistrationContext)
		return OB_PREOP_SUCCESS;
	if (OperationInformation->ObjectType == *PsThreadType)
	{
		if ((HANDLE)RegistrationContext == PsGetThreadProcessId((PETHREAD)OperationInformation->Object))
		{
			if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE)
			{
				DesiredAccess = OperationInformation->Parameters->CreateHandleInformation.DesiredAccess;

				DesiredAccess = DesiredAccess & (THREAD_SET_LIMITED_INFORMATION | THREAD_QUERY_LIMITED_INFORMATION);
				if (DesiredAccess) {
					OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~DesiredAccess;
				}
			}
			else if (OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
			{
				DesiredAccess = OperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess;

				DesiredAccess = DesiredAccess & (THREAD_SET_LIMITED_INFORMATION | THREAD_QUERY_LIMITED_INFORMATION);
				if (DesiredAccess) {
					OperationInformation->Parameters->DuplicateHandleInformation.DesiredAccess &= ~DesiredAccess;
				}
			}
		}
	}
	return OB_PREOP_SUCCESS;
}

VOID ThreadPostCallback(PVOID RegistrationContext, POB_POST_OPERATION_INFORMATION OperationInformation)
{
	UNREFERENCED_PARAMETER(RegistrationContext);
	UNREFERENCED_PARAMETER(OperationInformation);
	//dprintf("ThreadPostCallback");
}

NTSTATUS ProtectTheCurrentProcess()
{
	NTSTATUS Status = STATUS_SUCCESS;
	OB_CALLBACK_REGISTRATION obReg;
	OB_OPERATION_REGISTRATION opReg[2];

	if (g_RegistrationHandle == NULL) {
		memset(&opReg, 0, sizeof(opReg)); //初始化结构体变量

		opReg[0].ObjectType = PsProcessType;
		opReg[0].Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
		opReg[0].PreOperation = ProcessPreCallback;
		opReg[0].PostOperation = ProcessPostCallback;

		opReg[1].ObjectType = PsThreadType;
		opReg[1].Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
		opReg[1].PreOperation = ThreadPreCallback;
		opReg[1].PostOperation = ThreadPostCallback;

		memset(&obReg, 0, sizeof(obReg));//初始化结构体变量

		obReg.Version = OB_FLT_REGISTRATION_VERSION;//ObGetFilterVersion();
		obReg.OperationRegistrationCount = (sizeof(opReg) / sizeof(OB_OPERATION_REGISTRATION));
		obReg.RegistrationContext = (PVOID)PsGetCurrentProcessId();
		RtlInitUnicodeString(&obReg.Altitude, L"401900");
		obReg.OperationRegistration = opReg;

		Status = ObRegisterCallbacks(&obReg, &g_RegistrationHandle); //在这里注册回调函数
	}

	return Status;
}

VOID UnprotectTheCurrentProcess()
{
	if (g_RegistrationHandle != NULL) {
		ObUnRegisterCallbacks(g_RegistrationHandle);
		g_RegistrationHandle = NULL;
	}
	
}