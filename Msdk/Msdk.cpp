#include "Msdk.h"


#ifndef __UTILS_H__
#include "../utils/utils.h"
#pragma comment(lib,"utils.lib")
#endif

#ifndef __MEMORY_LOADER_H__
#include "../memory_loader/memory_loader.h"
#pragma comment(lib,"memory_loader.lib")
#endif // !__MEMORY_LOADER_H__


Msdk::Msdk() {
	Init();
}

Msdk::~Msdk() {
	closeHandle();
}

void Msdk::Init()
{
	FILE *fp;
	unsigned char *data = NULL;
	size_t size;
	HMEMORYMODULE module = NULL;
	LPCSTR path = VMProtectDecryptStringA("./dll/msdk.dat");
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
	{
		printf(VMProtectDecryptStringA("���ļ�ʧ��\n"));
		return;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	data = (unsigned char *)malloc(size);
	fseek(fp, 0, SEEK_SET);
	fread(data, 1, size, fp);
	fclose(fp);

	module = MemoryLoadLibrary(data);
	if (module == NULL)
	{
		printf(VMProtectDecryptStringA("��ȡģ��ʧ��\n"));
		return;
	}
	M_Open_VidPid = (M_OPEN_VIDPID)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_Open_VidPid"));
	M_ReleaseAllKey = (M_RELEASEALLKEY)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_ReleaseAllKey"));
	M_KeyState2 = (M_KEYSTATE2)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_KeyState2"));
	M_KeyDown2 = (M_KEYDOWN2)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_KeyDown2"));
	M_KeyUp2 = (M_KEYUP2)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_KeyUp2"));
	M_LeftClick = (M_LEFTCLICK)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_LeftClick"));
	M_MoveTo2 = (M_MOVETO2)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_MoveTo2"));
	M_MoveTo3 = (M_MOVETO3)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_MoveTo3"));
	M_GetCurrMousePos2 = (M_GETCURMOUSEPOS2)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_GetCurrMousePos2"));
	M_Close = (M_CLOSE)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_Close"));
	M_ResolutionUsed = (M_RESOLUTIONUSED)MemoryGetProcAddress(module, VMProtectDecryptStringA("M_ResolutionUsed"));

	openHandle();
}


void Msdk::openHandle()
{
	if (msdk_handle == NULL)
	{
		msdk_handle = M_Open_VidPid(0xc110, 0xc107);
		if (msdk_handle == INVALID_HANDLE_VALUE) {
			printf(VMProtectDecryptStringA("msdk ��ʧ��\n"));
		}

		M_ResolutionUsed(msdk_handle, 1920, 1080);
	}
}

void Msdk::closeHandle()
{
	if (msdk_handle != NULL)
	{
		M_Close(msdk_handle);
		msdk_handle = NULL;
	}

}

void Msdk::upAllKey()
{
	M_ReleaseAllKey(msdk_handle);
}

int Msdk::getKeyState(int keyCode)
{
	int keyState = M_KeyState2(msdk_handle, keyCode);
	return keyState;
}

void Msdk::keyDown(int keyCode, int s)
{
	if (getKeyState(keyCode) == 0)
	{
		M_KeyDown2(msdk_handle, keyCode);
		Sleep(s);
	}
}
void Msdk::keyUp(int keyCode)
{
	if (getKeyState(keyCode) == 1)
	{
		M_KeyUp2(msdk_handle, keyCode);
		Sleep(100 + utils::createRandom(1, 10));
	}
}
void Msdk::doKeyPress(int keyCode, int s)
{
	keyDown(keyCode, s + utils::createRandom(1, 10));
	keyUp(keyCode);
}
void Msdk::mouseClick(int s)
{
	M_LeftClick(msdk_handle, 1);
	Sleep(s);
}
void Msdk::mouseDoubleClick(int s)
{
	mouseClick();
	Sleep(s + utils::createRandom(0, 10));
	mouseClick();
}
void Msdk::moveMousePos(int x, int y)
{
	M_MoveTo2(msdk_handle, x, y);
}
void Msdk::setMousePos(int x, int y)
{
	M_MoveTo3(msdk_handle, x, y);
}
void Msdk::getMousePos(int *x, int *y)
{
	M_GetCurrMousePos2(x, y);
}