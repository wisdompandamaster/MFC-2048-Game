#pragma once


// StartDlg 对话框

class StartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StartDlg)

public:
	StartDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~StartDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();      //新游戏  按钮
	afx_msg void OnPaint();                 //绘图函数
	afx_msg void OnBnClickedButton3();      //退出游戏  按钮
};
