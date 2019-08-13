
// MFC2048Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC2048.h"
#include "MFC2048Dlg.h"
#include "StartDlg.h"
#include "ChallengeDialog.h"
#include "afxdialogex.h"
#include<fstream>
#include<cstring>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_USER_PAINT 1001
#define WM_USER_MOVE  1002
//int CMFC2048Dlg::thread_m = 0;
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
public:
	//afx_msg void OnMenu32774();
	//DECLARE_MESSAGE_MAP()
//	afx_msg void OnMenu32774();
//	afx_msg void OnHelp32773();
//	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

/*BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_MENU_32774, &CAboutDlg::OnMenu32774)
END_MESSAGE_MAP()*/


// CMFC2048Dlg 对话框



CMFC2048Dlg::CMFC2048Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC2048_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC2048Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC2048Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HELP_ABOUT, &CMFC2048Dlg::OnHelpAbout)
	ON_COMMAND(ID_HELP_32772, &CMFC2048Dlg::OnHelp32772)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC2048Dlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON3, &CMFC2048Dlg::OnBnClickedButton3)
//	ON_STN_CLICKED(IDC_STATIC1, &CMFC2048Dlg::OnStnClickedStatic1)
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BUTTON2, &CMFC2048Dlg::OnBnClickedButton2)
ON_COMMAND(ID_MENU_32775, &CMFC2048Dlg::ChallengeMode)
END_MESSAGE_MAP()


// CMFC2048Dlg 消息处理程序

BOOL CMFC2048Dlg::OnInitDialog()
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
	//////////////////////////////////////////////////////////////////////////////以上为自动生成的代码
	




	LoadPlayers();                             //初始化 将文件内容读出到数组中
	rank_list();                               //将初始文件中的人员信息显示到排行榜中
	p->Zero();                                 //初始化游戏界面  产生两个随机位置的2或4方块
	p->SetRandCell_C();                        //在四个角上随机生成一个方块
	p->SetRandCell();                          //在非四个角上随机生成一个方块
	p->score = 0;                              //初始化分数为0
	p->step_num = 0;
	//chance = 0;
	s = 32;                                    //初始化出现道具条件为合成2*32=64方块时
	pr = 0;                                    //初始化道具数为0


	for (int i = 0; i < 4; i++)                //设定数字方块的大小和位置（坐标）
	{
		for (int j = 0; j < 4; j++)
		{
			rect[i][j].left = 28 + i * 100 ;
			rect[i][j].top = 28 + j * 100 ;
			rect[i][j].right = rect[i][j].left + 85;
			rect[i][j].bottom = rect[i][j].top + 85;
		}
	}
	



	//////////////////////////////////////////////////////////////////////////////以下为自动生成的代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}





void CMFC2048Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
///////////////////////////////////////////////////////////////////////////////////以上为自动生成的代码






int CMFC2048Dlg::i = 0;
string CMFC2048Dlg::tname = "name";
int CMFC2048Dlg::ChallengeStep = 0;
long CMFC2048Dlg::ChallengeScore = 0;           //初始化静态变量




void CMFC2048Dlg::OnPaint()                     //绘图函数
{
	//Invalidate(TRUE);
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
	else                                 //////////以下为绘图/////////
	{

		CPaintDC dc(this);
		CPen pen(PS_DASH, 15, RGB(180, 170, 160)), * mypen;
		mypen = dc.SelectObject(&pen);
		for (int i = 0; i < 5; i++)                      //画5条粗竖线
		{
			dc.MoveTo(20, 20 + i * 100);
			dc.LineTo(20 + 4 * 100, 20 + i * 100);
		}
		for (int i = 0; i < 5; i++)                      //画5条粗横线
		{
			dc.MoveTo(20 + i * 100, 20);
			dc.LineTo(20 + i * 100, 20 + 4 * 100);     
		}
		dc.SelectObject(mypen);                          //组成4*4 16个方格的棋盘背景


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (p->cell[i][j] == 0)                  //当[i][j]位置数字为0时，什么都不画
				{
					 
				}
				else
				{   

					TRACE("画数字方格\r\n");
					COLORREF colorref = MFC2048::GetBkColor(p->cell[i][j]);          //得到数字对应方格背景颜色的R G B 
					CBrush brush(RGB(GetRValue(colorref), GetGValue(colorref), GetBValue(colorref)));//创建画刷
					dc.FillRect(&rect[i][j], &brush);                                                //选定区域和画刷

			        CString str_cell;                          //数字转换成字符串
					str_cell.Format(L"%d", p->cell[i][j]);     

					COLORREF Tcolorref = MFC2048::GetTColor(p->cell[i][j]);      //得到数字对应的字体颜色的R G B
					SetTextColor(dc, RGB(GetRValue(Tcolorref), GetGValue(Tcolorref), GetBValue(Tcolorref))); //设定数字文本颜色
					SetBkMode(dc,TRANSPARENT);               //设定文本区域背景透明

					CFont font;                               //创建数字的字体 
					int x = MFC2048::GetFontSize(str_cell.GetLength());
					font.CreateFont(x,x*1/2,0, 0, 0,FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
					CFont* pOldFont = dc.SelectObject(&font);  //选定字体

					dc.DrawTextW(str_cell, rect[i][j], DT_CENTER|DT_VCENTER|DT_SINGLELINE);  //在文本区域中画出数字文本
				}
			}
		}
		GetBestScore();                          //得到最高分

		CString str_score,str_score2,str_score3,str_prop,str_cstep;            //将分数数字等转化为字符串
		str_score.Format(L"%d", p->score);
		str_score2.Format(L"%d", best_score);
		str_score3.Format(L"%d", p->step_num);
		str_prop.Format(L"%d", pr);
		str_cstep.Format(L"%d", ChallengeStep);

		CRect rc_score(460, 55, 960, 100);       //显示 分数数字 区域的坐标
		CRect rc_score2(460, 20, 660, 140);      //显示"Score"区域的坐标
		CRect rc_score3(460, 90, 960, 180);     //显示"Best Score"区域的坐标
		CRect rc_score4(460, 125, 660, 170);     //显示 最高分数字 区域的坐标
		CRect rc_score5(460,193,960,230);        //显示 步数 区域的坐标
		CRect rc_score6(460,160,960,220);           //显示 "Step" 区域
		CRect rc_score7(560, 160, 960, 220);
		CRect rc_score8(560, 193, 960, 230);
		CRect rc_prop(595, 250, 635, 400);
		 
		           
        CFont font_score,font_score2,font_score3;            //创建 分数数字 和 "Score" 的字体
		font_score2.CreateFont(38, 19, 0, 0, 0, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
		font_score.CreateFont(38, 19, 0, 0, 0, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
		font_score3.CreateFont(30, 15, 0, 0, 0, FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));

		CFont* pOldFont = dc.SelectObject(&font_score);      //选定字体
        SetTextColor(dc, RGB(0, 0, 0));                      //数字文本为黑色
		dc.DrawTextW(str_score, rc_score, DT_SINGLELINE);   //画 分数数字
		dc.DrawTextW(str_score2, rc_score4, DT_SINGLELINE);  //画 最高分数字
		dc.DrawTextW(str_score3, rc_score5, DT_SINGLELINE);   //画步数
		
		CFont* pOldFont2 = dc.SelectObject(&font_score2);    //选定另一种字体
		SetTextColor(dc, RGB(95, 160, 220));                  //字体颜色
		dc.DrawTextW(_T("Score"), rc_score2, DT_SINGLELINE);  //画 "Score"
		dc.DrawTextW(_T("Best Score"), rc_score3, DT_SINGLELINE);// 画"Best Score" 
		dc.DrawTextW(_T("Step"), rc_score6, DT_SINGLELINE);      //画"Step" 
		
		CFont* pOldFont3 = dc.SelectObject(&font_score3);
		SetTextColor(dc, RGB(95, 160, 220));
		dc.DrawTextW(str_prop, rc_prop, DT_SINGLELINE);

		if (ChallengeStep != 0)
		{
			CFont* pOldFont2 = dc.SelectObject(&font_score2);    //选定另一种字体
			SetTextColor(dc, RGB(190, 50, 50));
			dc.DrawTextW(_T("C-Step"), rc_score7, DT_SINGLELINE);      //画"C-Step"

			CFont* pOldFont = dc.SelectObject(&font_score);       
			SetTextColor(dc, RGB(0, 0, 0));                       
			dc.DrawTextW(str_cstep, rc_score8, DT_SINGLELINE);

			ChallengeCheck();
		}
		
		if (p->Isover())                                      //如果结束 显示对话框2
		{
			CDialogEx dlg(IDD_DIALOG2);
			dlg.DoModal();
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFC2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
///////////////////////////////////////////////////////////




void CMFC2048Dlg::dlg_Left()       //向左移动绘图
{
	p->Cell2CellTemp();            //用于判断是否移动了
	p->left();                     //图形界面向左移动
	if (!p->IfEqual())             //如果移动了
	{
		p->SetRandCell();          //随机产生一个新数字块
		p->step_num++;
		CRect rect1(20, 20, 700, 420);
		InvalidateRect(&rect1);
		prop();
	}
	CRect rect1(20, 20, 700, 420); //在指定区域内重绘
	InvalidateRect(&rect1);
}

void CMFC2048Dlg::dlg_Right()      //向右移动绘图
{
	p->Cell2CellTemp();
	p->right();
	if (!p->IfEqual())
	{
		p->SetRandCell();
		p->step_num++;
		CRect rect1(20, 20, 700, 420);
		InvalidateRect(&rect1);
		prop();
	}
	CRect rect1(20, 20, 700, 420);
	InvalidateRect(&rect1);
}


void CMFC2048Dlg::dlg_Up()          //向上移动绘图 
{
	p->Cell2CellTemp();
	p->up();
	if (!p->IfEqual())
	{
		p->SetRandCell();
		p->step_num++;
		CRect rect1(20, 20, 700, 420);
		InvalidateRect(&rect1);

		prop();
	}
	CRect rect1(20, 20, 700, 420);
	InvalidateRect(&rect1);
}


void CMFC2048Dlg::dlg_Down()          //向下移动绘图
{
	p->Cell2CellTemp();
	p->down();
	if (!p->IfEqual())
	{
		p->SetRandCell();
		p->step_num++;
		CRect rect1(20, 20, 700, 420);
		InvalidateRect(&rect1);
		prop();
	}
	CRect rect1(20, 20, 700, 420);
	InvalidateRect(&rect1);
}


void CMFC2048Dlg::OnHelpAbout()                     //点击Menu 的 About， 显示 关于对话框
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}



void CMFC2048Dlg::OnHelp32772()                     //点击Menu 的 游戏规则，显示 对话框1
{
	// TODO: 在此添加命令处理程序代码
	CDialogEx dlg(IDD_DIALOG1);
	dlg.DoModal();
}


BOOL CMFC2048Dlg::PreTranslateMessage(MSG* pMsg)      //键盘链接移动
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYUP)
	{
		//判断具体键 
		switch (pMsg->wParam)
		{
		case VK_LEFT:case 'A'://按下左键  或A键
			dlg_Left();
			break;
		case VK_RIGHT:case 'D'://按下右键  或D键
			dlg_Right();
			break;
		case VK_UP:case 'W'://按下上键  或W键
			dlg_Up();
			break;
		case VK_DOWN:case 'S'://按下下键  或S键
			dlg_Down();
			break;
		default:
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMFC2048Dlg::GetBestScore()                 //得到最高分        
{
	if (p->score > best_score)
	{
		best_score = p->score;
	}
}


void CMFC2048Dlg::StoreScore()                     //排名并存储分数
{   
	if (p->score != 0)
	{
		fstream file("排行榜.txt", ios::out);          //每次重新写入前都清空     
		file.close();
		file.open("排行榜.txt", ios::in | ios::out | ios::app);
		player[i].num = i + 1;
		player[i].name = tname;
		player[i].step = p->step_num;
		player[i].player_score = p->score;           //将当前用户存入数组中
		int n = i + 1;                               //冒泡排序，按分数由小到大排名
		for (int t = 0; t < n; t++)
		{
			for (int j = t + 1; j < n; j++)
			{
				if (player[t].player_score < player[j].player_score)
				{
					player_temp = player[t];
					player[t] = player[j];
					player[j] = player_temp;
				}
			}
		}
		for (int t = 0; t < n - 1; t++)                           //按排名后顺序写入文件
		{
			file << t + 1 << "  ";
			file << player[t].name << "  ";
			file << player[t].player_score << "  ";
			file << player[t].step << "  " << endl;
		}
		i = n - 1;
		i++;
		file.close();
	}
}

void CMFC2048Dlg::ShowPlayers()                //用于测试，显示所有用户姓名
{
	int number = i;
	CString text;
	for (int t = 0; t < number; t++) {
		text = player[t].name.c_str();
		MessageBox(text);
	}
}


void CMFC2048Dlg::rank_list()                  //显示排行榜
{
	CString CStr;
	string str;
	char s[100] = { 0 };                 
	fstream file;
	file.open("排行榜.txt", ios::in | ios::out | ios::app);

	if (!file)                      //文件未打开
	{
		CString a;
		a = "fail to open file!";
		MessageBox(a);
	}

	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));                  //初始化s内容
		file.getline(s, 99);                      //一行一行地读取
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                   //string转化为CString
			SetDlgItemText(IDC_STATIC1, CStr);    //将字符串显示到静态文本框
		}
	}

	//////////////////////////////////////////////循环十次，只显示前十名的排名

	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));                  //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                 //string转化为CString
			SetDlgItemText(IDC_STATIC2, CStr);    //将字符串显示到静态文本框
		}
	}
	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));    //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                 //string转化为CString
			SetDlgItemText(IDC_STATIC3, CStr);    //将字符串显示到静态文本框
		}
	}
	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));    //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                 //string转化为CString
			SetDlgItemText(IDC_STATIC4, CStr);    //将字符串显示到静态文本框
		}
	}
	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));    //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                 //string转化为CString
			SetDlgItemText(IDC_STATIC5, CStr);    //将字符串显示到静态文本框
		}
	}
	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));    //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                 //string转化为CString
			SetDlgItemText(IDC_STATIC6, CStr);    //将字符串显示到静态文本框
		}
	}
	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));    //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                 //string转化为CString
			SetDlgItemText(IDC_STATIC7, CStr);    //将字符串显示到静态文本框
		}
	}
	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));    //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                 //string转化为CString
			SetDlgItemText(IDC_STATIC8, CStr);    //将字符串显示到静态文本框
		}
	}
	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));    //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                 //string转化为CString
			SetDlgItemText(IDC_STATIC9, CStr);    //将字符串显示到静态文本框
		}
	}
	if (file.peek() != EOF)
	{
		memset(s, 0, sizeof(s));    //一行一行地读取
		file.getline(s, 99);
		if (strlen(s) != 0)
		{
			str = s;
			CStr = str.c_str();                    //string转化为CString
			SetDlgItemText(IDC_STATIC10, CStr);    //将字符串显示到静态文本框
		}
	}
	file.close();
}

void CMFC2048Dlg::prop()                    //获得道具
{
	bool flag = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (p->cell[i][j] == 2 * s)     //遍历，直到出现等于64 128 。。。
			{   
				CDialog dlg(IDD_DIALOG5);   //显示道具卡
				dlg.DoModal();
				s = s * 2;                  //获得道具卡后，S*2
				pr = pr + 1;                //道具卡数+1

				flag = true;
				break;                     //跳出循环
			}

		}
		if(flag==true)
		{
			break;
		}
	}
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//ON_COMMAND(ID_MENU_32774, &CAboutDlg::OnMenu32774)
//ON_COMMAND(ID_HELP_32773, &CAboutDlg::OnHelp32773)
//ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()



void CMFC2048Dlg::OnBnClickedButton1()     // 重新开始 按钮
{
	p->Zero();                             //重新设置方块
	p->SetRandCell_C();
	p->SetRandCell();
	if (p->score != 0)                     //如果分数为0，不存入
	{
		StoreScore();                      //排行并存入文件
		rank_list();                       //显示在排行榜
	}
	p->score = 0;                          //初始化
	p->step_num = 0;
	s = 32;
	pr = 0;
	ChallengeStep = 0;
	ChallengeScore = 0;
	CRect rect1(20, 20, 700, 420);         //重绘
	InvalidateRect(&rect1);
	// TODO: 在此添加控件通知处理程序代码
}


void CMFC2048Dlg::point_zero()            //指定方块消除
{
	CRect rec;
	CPoint point;	
	GetCursorPos(&point);             //获取当前指针的坐标（注意，这是屏幕的）       
	GetWindowRect(&rec);              //获取客户区（客户区的左上角）相对于屏幕的位置	
	int point_x = (point.x - rec.left);        //计算相对于客户区坐标
	int point_y = (point.y - rec.top - 50); 

	for (int i = 0; i < 4; i++)                //设定数字方块的大小和位置（坐标）
	{
		for (int j = 0; j < 4; j++)
		{
			if (point_x > rect[i][j].left && point_x< rect[i][j].right && point_y >rect[i][j].top && point_y < rect[i][j].bottom)
			{
				p->cell[i][j] = 0;                 //如果点击位置在方块区域内，该方块清零
				pr--;                              //道具卡数 -1
			}
		}
		CRect rect1(20, 20, 700, 420);             //重绘
		InvalidateRect(&rect1);
	}
}

void CMFC2048Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
	if (pr != 0)                        //如果道具卡数不为0，可使用道具卡功能
	{
		point_zero();           
	}	
}


Player CMFC2048Dlg::GetPlayer(int n)     //返回player[n]，挑战模式查找用户时用
{
	return player[n];                    
}


void CMFC2048Dlg::LoadPlayers()
{
	int temp = 0;
	fstream file("排行榜.txt", ios::in|ios::out);        //打开文件
	if (!file) {
		CString text, caption;
		text = "File Failed To OPen!";
		file.open("排行榜.txt", ios::out);
		file.close();
		caption = "WRONG";
		MessageBox(text, caption);
	}
	while (!file.eof())                                 //按数组单位，读取文件内容到用户数组
	{
		file >> player[temp].num >> player[temp].name >> player[temp].player_score >> player[temp].step;
		temp++;
	}
	CMFC2048Dlg::i = temp;                              //获得用户人数
	best_score = player[0].player_score;                //获得最高分
	file.close();
}

void CMFC2048Dlg::OnBnClickedButton2()                 //返回开始界面
{ 
	StoreScore();
	CDialog::OnOK();	 
}

void CMFC2048Dlg::ChallengeCheck()
{
	if (p->step_num == CMFC2048Dlg::ChallengeStep)      //当步数相等时，判断分数
	{
		if (p->score < CMFC2048Dlg::ChallengeScore)     //挑战失败
		{
			CDialog dlg(IDD_DIALOG6);                   //显示 失败对话框
			dlg.DoModal();
			p->Zero();                                  //初始化
			p->SetRandCell_C();
			p->SetRandCell();
			p->score = 0;
			p->step_num = 0;
			s = 32;
			pr = 0;
			CRect rect1(20, 20, 700, 420);              //重绘
			InvalidateRect(&rect1);
		}
		else 
		{                                               //挑战成功
			CDialog dlg(IDD_DIALOG7);                   //显示 成功对话框
			dlg.DoModal();
			pr += 2;                                    //道具卡数 +2 
			CRect rect1(20, 20, 700, 420);
			InvalidateRect(&rect1);
		}
		ChallengeStep = 0;                              //重置挑战数据
		ChallengeScore = 0;
	}
}


void CMFC2048Dlg::ChallengeMode()                     //菜单栏  挑战模式
{
	ChallengeDialog a;                                //显示输入框
	a.DoModal();
	int number = CMFC2048Dlg::i;                      //获取人数
	bool flag = false;
	for (int t = 0; t < number; t++)                  //遍历找寻被挑战者(以最高分为准)
	{
		CString temp;
		temp = player[t].name.c_str();
		if (ChallengeDialog::name == temp) 
		{
			CMFC2048Dlg::ChallengeStep = player[t].step;          //获得被挑战者步数
			CMFC2048Dlg::ChallengeScore = player[t].player_score; //获得被挑战者分数
			
			p->Zero();                                            //初始化
			p->SetRandCell_C();
			p->SetRandCell();
			if (p->score != 0)
			{
				StoreScore();
				rank_list();
			}
			p->score = 0;
			p->step_num = 0;
			s = 32;
			pr = 0;

			flag = true;
			break;
		}
	}
	if (flag == false)               //没有找到被挑战者，弹出提示框
	{
		CString text;
		text = "Cannot Find The User!";
		MessageBox(text);
	}
	
	CRect rect1(20, 20, 700, 420);   //重绘
	InvalidateRect(&rect1);
}
