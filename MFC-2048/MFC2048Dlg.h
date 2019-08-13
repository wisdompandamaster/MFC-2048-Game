
// MFC2048Dlg.h: 头文件
//
#include<fstream>
#include<cstring>
#include<algorithm>
using namespace std;
#pragma once


struct Player {               //玩家 结构体
	int num = 0;
	string name = "name";
	long player_score = 0;
	int step = 0;
};


// CMFC2048Dlg 对话框
class CMFC2048Dlg : public CDialogEx
{
// 构造
public:
	CMFC2048Dlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC2048_DIALOG };
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
	afx_msg void OnHelpAbout();
	afx_msg void OnHelp32772();
//////////////////////////////////////////////////////////////////////以上为自动生成的代码


public:
	void dlg_Left();                  //图形界面向左移动
	void dlg_Right();                 //图形界面向右移动
	void dlg_Up();                    //图形界面向上移动
	void dlg_Down();                  //图形界面向下移动
	void GetBestScore();              //得到最高分
	void StoreScore();                //排名并存储分数
	void rank_list();                 //显示排行榜
	void prop();                      //道具实现函数
	void point_zero();                //点击处清零
	Player GetPlayer(int n);          //返回player[n]
	void LoadPlayers();               //加载文件中数据到数组中
	void ChallengeCheck();            //判断挑战是否成功
	void ShowPlayers();               //用于测试数组中内容

public:
	CRect rect[9][9];                           //图形界面的数字方格
	MFC2048 *p = (MFC2048 *) AfxGetApp();       //得到MFC2048的类指针，以调用MFC2048中的函数
	static int i;                               //存分数时计数
	static string tname;                        //当前玩家的姓名
	static int ChallengeStep;                   //被挑战者的步数
	static long ChallengeScore;                 //被挑战者的分数
	int s = 32;                                 //用来出现道具的方块
	int pr = 0;                                 //用来记数道具
	Player player[50],player_temp;              //玩家 和 临时玩家
	long best_score = 0;                        //最高分
	virtual BOOL PreTranslateMessage(MSG* pMsg);//获取键盘信息，并响应
	afx_msg void OnBnClickedButton1();          //重新开始 按扭
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);    //点击消除点击处方块
	afx_msg void OnBnClickedButton2();                        //返回 按钮 返回开始界面     
	afx_msg void ChallengeMode();                             //菜单栏  挑战模式
};

