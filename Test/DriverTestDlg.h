#pragma once


// DriverTest 对话框

class DriverTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DriverTestDlg)

public:
	DriverTestDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DriverTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRIVER_TEST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void Install();
	afx_msg void Start();
	afx_msg void Stop();
	afx_msg void Unload();
	afx_msg void Select();
	CEdit Path;
};
