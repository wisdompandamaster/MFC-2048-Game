
// MFC2048.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号

// CMFC2048App:
// 有关此类的实现，请参阅 MFC2048.cpp
//

class CMFC2048App : public CWinApp
{
public:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;//GDI+
	ULONG_PTR gdiplusToken;
public:
	CMFC2048App();

// 重写
public:
	virtual BOOL InitInstance();
	 
// 实现
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
extern CMFC2048App theApp;
//////////////////////////////////////////////////////////////////////////////////////以上为自动生成的代码
class MFC2048
{
public:
	int TwoOrFour();           //随机返回2或4
	void SetRandCell_C();      //在四个角处得到随机2或4
	void SetRandCell();        //在空白块上产生随机2或4
	void Zero();               //将所有数字方格初始化为0
	void Cell2CellTemp();      //将当前所有 cell 存到 cell_temp，在判断是否移动时用 
	bool IfEqual();            //判断是否移动
	void left();               //向左移动 并记分
	void right();              //向右移动 并记分
	void up();                 //向上移动 并记分
	void down();               //向下移动 并记分
	bool Isover();             //判断游戏是否结束

public:
	int size=4;                                    //棋盘大小
	int cell[9][9];                                //数字方格
	int cell_temp[9][9];                           //用来装数字方格的临时格
	long score;                                    //分数
	long step_num;                                 //步数
	static COLORREF GetTColor(int i);              //根据 数字 获得 字体颜色
	static COLORREF GetBkColor(int i);             //根据 数字 获得 方格背景颜色
	static int GetFontSize(int len);               //根据 数字位数 获得 数字字体大小
};