// ChallengeDialog.cpp: 实现文件
//

#include "pch.h"
#include "MFC2048.h"
#include "MFC2048Dlg.h"
#include "ChallengeDialog.h"
#include "afxdialogex.h"


// ChallengeDialog 对话框

IMPLEMENT_DYNAMIC(ChallengeDialog, CDialogEx)

ChallengeDialog::ChallengeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHALLENGE, pParent)
{

}

ChallengeDialog::~ChallengeDialog()
{
}

void ChallengeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChallengeDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChallengeDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// ChallengeDialog 消息处理程序

CString ChallengeDialog::name=0;                //初始化name

void ChallengeDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(name); //获取编辑框中输入的姓名
	CDialogEx::OnOK();

}
