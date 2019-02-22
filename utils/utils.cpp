#include "utils.h"


/// <summary>根据进程名获取进程ID</summary>
DWORD utils::getProcessIdByProcessName(const wchar_t * processName)
{
	//bool result = false;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		//printf(VMProtectDecryptStringA("CreateToolhelp32Snapshot Error!\n"));
		return 0;
	}
	BOOL bResult = Process32First(hProcessSnap, &pe32);
	while (bResult)
	{
		if (wcscmp(processName, pe32.szExeFile) == 0) {
			return pe32.th32ProcessID;
			break;
		}
		bResult = Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	return 0;
}

void utils::writeConfig(const wchar_t * filePath, const wchar_t * key, const wchar_t *value)
{
	wchar_t *lpPath = new wchar_t[MAX_PATH];

	wcscpy_s(lpPath, MAX_PATH, L"C:\\IniFileName.ini");

	WritePrivateProfileString(L"LiMing", L"Sex", L"Man", lpPath);
	WritePrivateProfileString(L"LiMing", L"Age", L"20", lpPath);

	WritePrivateProfileString(L"Fangfang", L"Sex", L"Woman", lpPath);
	WritePrivateProfileString(L"Fangfang", L"Age", L"21", lpPath);


}

wchar_t * readConfig(const wchar_t * filePath, wchar_t * key)
{
	//GetPrivateProfileInt();
	wchar_t buffer[255] = { 0 };
	GetPrivateProfileString(L"Fangfang", L"Sex", L"", buffer, 255, filePath);
	return buffer;
	//GetPrivateProfileInt(L"Driver", key,"",);
}

int utils::createRandom(int min, int max)
{
	int Random = 0;
	if (max > min) {
		srand((unsigned)time(NULL));
		Random = (rand() % (min - max + 1) + max);
	}
	else {
		srand((unsigned)time(NULL));
		Random = (rand() % (max - min + 1) + min);
	}
	return Random;
}