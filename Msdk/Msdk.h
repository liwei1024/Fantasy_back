#pragma once
#ifndef __MSDK_H__
#define __MSDK_H__
#include <windows.h>
#include "stdio.h"
#include <windows.h>
#include <malloc.h>
#include <string.h>
#include <tchar.h>

#include "../VMProtectSDK.h"

typedef HANDLE(WINAPI*M_OPEN_VIDPID)(int, int);
typedef int (WINAPI*M_RELEASEALLKEY)(HANDLE);
typedef int (WINAPI*M_KEYSTATE2)(HANDLE, int);
typedef int (WINAPI*M_KEYDOWN2)(HANDLE, int);
typedef int (WINAPI*M_KEYUP2)(HANDLE, int);
typedef int (WINAPI*M_LEFTCLICK)(HANDLE, int);
typedef int (WINAPI*M_MOVETO2)(HANDLE, int, int);
typedef int (WINAPI*M_MOVETO3)(HANDLE, int, int);
typedef int (WINAPI*M_GETCURMOUSEPOS2)(int*, int*);
typedef int (WINAPI*M_CLOSE)(HANDLE);
typedef int (WINAPI*M_RESOLUTIONUSED)(HANDLE, int, int);

class Msdk
{
public:
	HANDLE msdk_handle = NULL;

	Msdk();
	virtual ~Msdk();

	M_OPEN_VIDPID M_Open_VidPid;
	M_RELEASEALLKEY M_ReleaseAllKey;
	M_KEYSTATE2 M_KeyState2;
	M_KEYDOWN2 M_KeyDown2;
	M_KEYUP2 M_KeyUp2;
	M_LEFTCLICK M_LeftClick;
	M_MOVETO2 M_MoveTo2;
	M_MOVETO3 M_MoveTo3;
	M_GETCURMOUSEPOS2 M_GetCurrMousePos2;
	M_CLOSE M_Close;
	M_RESOLUTIONUSED M_ResolutionUsed;

	void Init();
	void openHandle();
	void closeHandle();
	void upAllKey();
	int getKeyState(int keyCode);
	void keyDown(int keyCode, int s = 100);
	void keyUp(int keyCode);
	void doKeyPress(int keyCode, int s = 100);
	void mouseClick(int s = 100);
	void mouseDoubleClick(int s = 0);
	void moveMousePos(int x, int y);
	void setMousePos(int x, int y);
	void getMousePos(int * x, int * y);
};
#endif // !__MSDK_H__



