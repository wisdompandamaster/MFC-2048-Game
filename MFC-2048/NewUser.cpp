// NewUser.cpp: 实现文件
//

#include "pch.h"
#include "MFC2048.h"
#include "MFC2048Dlg.h"
#include "NewUser.h"
#include "afxdialogex.h"


// NewUser 对话框

IMPLEMENT_DYNAMIC(NewUser, CDialogEx)

NewUser::NewUser(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

NewUser::~NewUser()
{
}

void NewUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewUser, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewUser::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &NewUser::OnBnClickedCancel)
END_MESSAGE_MAP()


// NewUser 消息处理程序


void NewUser::OnBnClickedOk()
{
	 
	CString name;
	GetDlgItem(IDC_EDIT1)->GetWindowText(name);      //将编辑框中输入的用户名传给name
		CMFC2048Dlg::i++;
		CMFC2048Dlg::tname = CT2A(name.GetBuffer());   //转化为string类型

		CMFC2048Dlg c2048;                             //显示主界面
		c2048.DoModal();
		 
	CDialogEx::OnOK();
}


void NewUser::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
