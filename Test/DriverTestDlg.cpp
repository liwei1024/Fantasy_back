// DriverTest.cpp: 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "DriverTestDlg.h"
#include "afxdialogex.h"
#include "TestDlg.h"

extern CTestDlg* dlgTest;
// DriverTest 对话框

IMPLEMENT_DYNAMIC(DriverTestDlg, CDialogEx)

DriverTestDlg::DriverTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DRIVER_TEST, pParent)
{

}

DriverTestDlg::~DriverTestDlg()
{
}

void DriverTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT3, Path);
}


BEGIN_MESSAGE_MAP(DriverTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &DriverTestDlg::Install)
	ON_BN_CLICKED(IDC_BUTTON3, &DriverTestDlg::Start)
	ON_BN_CLICKED(IDC_BUTTON4, &DriverTestDlg::Stop)
	ON_BN_CLICKED(IDC_BUTTON5, &DriverTestDlg::Unload)
	ON_BN_CLICKED(IDC_BUTTON6, &DriverTestDlg::Select)
END_MESSAGE_MAP()


// DriverTest 消息处理程序


void DriverTestDlg::Install()
{
	// TODO: 在此添加控件通知处理程序代码
}


void DriverTestDlg::Start()
{
	// TODO: 在此添加控件通知处理程序代码
}


void DriverTestDlg::Stop()
{
	// TODO: 在此添加控件通知处理程序代码
}


void DriverTestDlg::Unload()
{
	// TODO: 在此添加控件通知处理程序代码
}


void DriverTestDlg::Select()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filePath = _T("");
	//打开驱动文件，获取文件路径名
	LPCTSTR filter = _T("SYS(*.sys)|*.sys|BMP(*.bmp)|*.bmp|ALLSUPORTFILE(*.*)|*.*||");
	CFileDialog dlgFileOpenImg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	//打开图像
	if (dlgFileOpenImg.DoModal() == IDOK)
	{
		//读取文件文件名
		filePath = dlgFileOpenImg.GetPathName();
		Path.SetWindowTextW(filePath);
	}
	dlgTest->UpdateData(FALSE);
	dlgTest->ToConsoleLog(filePath);// dlgTest;
}
