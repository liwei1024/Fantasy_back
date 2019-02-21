// Client.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

VOID ThreadMessage(MSG *msg);// 线程消息处理
VOID HotKeyMessage(WPARAM KeyId);// 按键消息处理
bool g_switch = true;

void MainThread()
{
	while (g_switch)
	{

		Sleep(10);
	}
}


int main()
{
	RegisterHotKey(NULL, VK_F1, NULL, VK_F1);
	RegisterHotKey(NULL, VK_F2, NULL, VK_F2);
	RegisterHotKey(NULL, VK_F3, NULL, VK_F3);
	RegisterHotKey(NULL, VK_F4, NULL, VK_F4); 
	RegisterHotKey(NULL, VK_INSERT, NULL, VK_INSERT);
	RegisterHotKey(NULL, VK_END, NULL, VK_END);

	//RegisterWindowMessage(L"");

	MSG msg = { 0 };//消息指针
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//等待信号
		DispatchMessage(&msg);//处理信号
		ThreadMessage(&msg);//线程消息处理
	}
}


VOID ThreadMessage(MSG *msg)
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

VOID HotKeyMessage(WPARAM KeyId)
{
	switch (KeyId)
	{
	case VK_F1:
		printf("VK_F1\n");
		break;
	case VK_F2:
		printf("VK_F2\n");
		break;
	default:
		break;
	}
}