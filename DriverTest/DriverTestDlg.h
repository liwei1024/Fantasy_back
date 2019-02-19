
// DriverTestDlg.h: 头文件
//

#pragma once


// CDriverTestDlg 对话框
class CDriverTestDlg : public CDialogEx
{
// 构造
public:
	CDriverTestDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRIVERTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void DriverInstall();
	afx_msg void DriverStart();
	afx_msg void DriverStop();
	afx_msg void DriverUnload();
	afx_msg void SelectDriverFilePath();
	CEdit DriverFilePath;
	CEdit OutputMessage;
	afx_msg void ProtectTheCurrentProcess();
	afx_msg void UnprotectTheCurrentProcess();
	CEdit edit_log;
	afx_msg void OnEnChangeEdit3();
	void showLog(CString log);
};
