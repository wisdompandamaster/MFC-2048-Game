#pragma once


// NewUser 对话框

class NewUser : public CDialogEx
{
	DECLARE_DYNAMIC(NewUser)

public:
	NewUser(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~NewUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();                   //OK按钮
	CMFC2048Dlg* c = (CMFC2048Dlg*)AfxGetApp();     //获得CMFC2048Dlg的类指针   
	afx_msg void OnBnClickedCancel();               //Cancel按钮
};
