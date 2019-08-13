#pragma once


// ChallengeDialog 对话框

class ChallengeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ChallengeDialog)

public:
	ChallengeDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChallengeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHALLENGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CMFC2048Dlg* c = (CMFC2048Dlg*)AfxGetApp();        //获取主界面指针；
	static CString name;                               //用于存储输入的姓名
};
