
// DriverTestDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "DriverTest.h"
#include "DriverTestDlg.h"
#include "afxdialogex.h"
#include "../Driver/driver.h"
#include "winioctl.h"
#include "../DriverControl/DriverControl.h"
#pragma comment(lib,"DriverControl.lib")

DriverControl drictl;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDriverTestDlg 对话框



CDriverTestDlg::CDriverTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRIVERTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDriverTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, DriverFilePath);
	DDX_Control(pDX, IDC_EDIT2, OutputMessage);
	DDX_Control(pDX, IDC_EDIT3, edit_log);
	DDX_Control(pDX, IDC_EDIT4, targetProcessId);
}

BEGIN_MESSAGE_MAP(CDriverTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDriverTestDlg::DriverInstall)
	ON_BN_CLICKED(IDC_BUTTON2, &CDriverTestDlg::DriverStart)
	ON_BN_CLICKED(IDC_BUTTON3, &CDriverTestDlg::DriverStop)
	ON_BN_CLICKED(IDC_BUTTON4, &CDriverTestDlg::DriverUnload)
	ON_BN_CLICKED(IDC_BUTTON5, &CDriverTestDlg::SelectDriverFilePath)
	ON_BN_CLICKED(IDC_BUTTON7, &CDriverTestDlg::ProtectTheCurrentProcess)
	ON_BN_CLICKED(IDC_BUTTON6, &CDriverTestDlg::UnprotectTheCurrentProcess)
	ON_EN_CHANGE(IDC_EDIT3, &CDriverTestDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON8, &CDriverTestDlg::CamouflageCurrentProcess)
END_MESSAGE_MAP()


// CDriverTestDlg 消息处理程序

BOOL CDriverTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDriverTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDriverTestDlg::OnPaint()
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
HCURSOR CDriverTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDriverTestDlg::DriverInstall()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	DriverFilePath.GetWindowTextW(str);
	//OutputDebugString(str);
	drictl.insert(str);
	showLog(drictl.getMessage());
}


void CDriverTestDlg::DriverStart()
{
	// TODO: 在此添加控件通知处理程序代码
	drictl.start();
	showLog(drictl.getMessage());
}


void CDriverTestDlg::DriverStop()
{
	// TODO: 在此添加控件通知处理程序代码
	drictl.stop();
	showLog(drictl.getMessage());
}


void CDriverTestDlg::DriverUnload()
{
	// TODO: 在此添加控件通知处理程序代码
	drictl.unload();
	showLog(drictl.getMessage());
}


void CDriverTestDlg::SelectDriverFilePath()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString m_strFilePath = _T("");

	//打开图像文件，获取文件路径名
	LPCTSTR szFilter = _T("SYS(*.sys)|*.sys|BMP(*.bmp)|*.bmp|ALLSUPORTFILE(*.*)|*.*||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取文件文件名
		m_strFilePath = dlgFileOpenImg.GetPathName();
		OutputDebugString(m_strFilePath);
		DriverFilePath.SetWindowTextW(m_strFilePath);
	}
}


void CDriverTestDlg::ProtectTheCurrentProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!drictl.control(L"\\\\.\\" SYMBOLIC_LINK_SHORT_NAME, PROTECT_THE_CURRENT_PROCESS, 0, 0, 0, 0)) {
		showLog(drictl.getMessage());
	}
	else {
		showLog(L"保护进程");
	}
}


void CDriverTestDlg::UnprotectTheCurrentProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!drictl.control(L"\\\\.\\" SYMBOLIC_LINK_SHORT_NAME, UNPROTECT_THE_CURRENT_PROCESS, 0, 0, 0, 0)) {
		showLog(drictl.getMessage());
	}
	else {
		showLog(L"解除保护");
	}
}


void CDriverTestDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CDriverTestDlg::showLog(CString m_str)
{
	static int ipos = 0;
	CTime time = CTime::GetCurrentTime();
	CString sTime = time.Format(_T("%H:%M:%S  "));
	m_str = sTime + m_str + L"\r\n";
	//m_EditLog.LineScroll(m_EditLog.GetLineCount());   //永远滑动到最下面
	edit_log.SetSel(-1, -1, FALSE);   //nstart = -1表示取消所有选择


	int iTextLen = edit_log.GetWindowTextLength();
	edit_log.SetSel(iTextLen, iTextLen, FALSE);
	edit_log.SetFocus();       //移动光标到最后
	edit_log.ReplaceSel(m_str);     //这个函数还是在光标的位置书写

	edit_log.LineScroll(edit_log.GetLineCount());   //可用于水平滚动所有行最后一个字符,这只是设置edit进行滚动

	
}

void CDriverTestDlg::CamouflageCurrentProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	targetProcessId.GetWindowTextW(str);
	ULONG targetProcessId = (ULONG)_wtoi(str);
	if (!drictl.control(L"\\\\.\\" SYMBOLIC_LINK_SHORT_NAME, CAMOUFLAGE_CURRENT_PROCESS,&targetProcessId, sizeof(targetProcessId), 0, 0)) {
		showLog(drictl.getMessage());
	}
	else {
		showLog(L"伪装进程");
	}
}
