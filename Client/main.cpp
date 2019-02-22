// Client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

VOID MainThreadMessage(MSG *msg);// 主线程消息处理
VOID HotKeyMessage(WPARAM KeyId);// 按键消息处理
VOID WorkThread();// 工作线程
VOID CloseCurrentTheProcess(); //结束进程
VOID windowInitialize();// 窗口初始化 

bool g_workThreadSwitch = true;

Memory<Driver> mem;


int main()
{
	mem.camouflageCurrentProcess(utils::getProcessIdByProcessName(L"explorer.exe"));

	mem.protectTheCurrentProcess();

	windowInitialize();

	RegisterHotKey(NULL, VK_INSERT, NULL, VK_INSERT);
	RegisterHotKey(NULL, VK_END, NULL, VK_END);
	RegisterHotKey(NULL, (MOD_ALT+VK_DELETE), MOD_ALT, VK_DELETE);

	CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)WorkThread,NULL,0,NULL);

	MSG msg = { 0 };//消息指针
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//等待信号
		DispatchMessage(&msg);//处理信号
		MainThreadMessage(&msg);//线程消息处理
	}
}
/// <summary>主线程消息响应函数</summary>
VOID MainThreadMessage(MSG *msg)
{
	switch (msg->message)
	{
	case WM_HOTKEY: // 热键消息
		HotKeyMessage(msg->wParam);
		break;
	default:
		break;
	}
}
/// <summary>热键响应函数</summary>
VOID HotKeyMessage(WPARAM KeyId)
{
	switch (KeyId)
	{
	case VK_INSERT:
		printf("VK_F1\n");
		break;
	case VK_END:
		g_workThreadSwitch = !g_workThreadSwitch;
		break;
	case (VK_DELETE + MOD_ALT):
		CloseCurrentTheProcess();
		break;
	default:
		break;
	}
}
/// <summary>工作线程</summary>
VOID WorkThread()
{
	while (true)
	{
		if (g_workThreadSwitch)
		{

		}
		else {
			Sleep(100);
		}
	}
}
/// <summary>关闭当前进程</summary>
VOID CloseCurrentTheProcess()
{
	mem.stop(); //停止驱动

	mem.unload();//卸载驱动

	ExitProcess(0);
}

/// <summary>初始化控制台窗口</summary>
VOID windowInitialize()
{
	RECT rect;
	int cx, cy;
	int width, height;
	cx = GetSystemMetrics(SM_CXFULLSCREEN);
	cy = GetSystemMetrics(SM_CYFULLSCREEN);
	HWND g_self_window_handle = GetConsoleWindow();
	_tsetlocale(LC_ALL, L"chs");
	GetWindowRect(g_self_window_handle, &rect);
	width = (rect.right - rect.left);
	height = (rect.bottom - rect.top);

	MoveWindow(g_self_window_handle, cx - 400, cy - 800, 400, 800, TRUE);

	EnableMenuItem(GetSystemMenu(g_self_window_handle, FALSE), SC_CLOSE, MF_GRAYED);

	SetConsoleTitle(L"管理员: 命令提示符");
}