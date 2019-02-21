
// TestDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include "DriverTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlg 对话框


CTestDlg* dlgTest;
CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, ConsoleLog);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::DriverTest)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	dlgTest = this;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestDlg::DriverTest()
{
	// TODO: 在此添加控件通知处理程序代码
	DriverTestDlg dlgDriverTest;
	dlgDriverTest.DoModal();
	//dlgDriverTest->DoModal();
}

void CTestDlg::ToConsoleLog(CString log)
{
	UpdateData(TRUE);
	static int ipos = 0;
	CTime time = CTime::GetCurrentTime();
	CString sTime = time.Format(_T("%Y-%m-%d %H:%M:%S  "));
	log = sTime + log + L"\r\n";
	ConsoleLog.SetSel(-1, -1, FALSE);   //nstart = -1表示取消所有选择

	int iTextLen = ConsoleLog.GetWindowTextLength();
	ConsoleLog.SetSel(iTextLen, iTextLen, FALSE);
	ConsoleLog.SetFocus();       //移动光标到最后
	ConsoleLog.ReplaceSel(log);     //这个函数还是在光标的位置书写

	ConsoleLog.LineScroll(ConsoleLog.GetLineCount());   //可用于水平滚动所有行最后一个字符,这只是设置edit进行滚动
}