// StartDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFC2048.h"
#include "StartDlg.h"
#include "afxdialogex.h"
#include "framework.h"
#include "MFC2048Dlg.h"
#include "NewUser.h"


// StartDlg 对话框

IMPLEMENT_DYNAMIC(StartDlg, CDialogEx)

StartDlg::StartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

StartDlg::~StartDlg()
{
}

void StartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
}


BEGIN_MESSAGE_MAP(StartDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &StartDlg::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON3, &StartDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// StartDlg 消息处理程序


void StartDlg::OnBnClickedButton1()     
{ 
	NewUser a;                         //显示输入用户名的对话框
	a.DoModal();
}


void StartDlg::OnPaint()
{
	CPaintDC dc(this);  
	CRect start_rc(188, 100, 500, 200);

	CFont font_start;                                   //创建开始界面的字体
	font_start.CreateFont(80, 40, 0, 0, 0, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
    DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));

	CFont* pOldFont = dc.SelectObject(&font_start);      //选定字体 画2048
	SetTextColor(dc, RGB(95, 160, 220));                 
	SetBkMode(dc, TRANSPARENT);
	dc.DrawTextW(_T("2048"), start_rc, DT_SINGLELINE);
}


void StartDlg::OnBnClickedButton3()     
{
	exit(0);                           //退出程序
	 
}
