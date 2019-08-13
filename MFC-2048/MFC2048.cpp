
// MFC2048.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "MFC2048.h"
#include "MFC2048Dlg.h"
#include "StartDlg.h"
#include<fstream>
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////                                                          
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFC2048App

BEGIN_MESSAGE_MAP(CMFC2048App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFC2048App 构造

CMFC2048App::CMFC2048App()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFC2048App 对象

CMFC2048App theApp;

// CMFC2048App 初始化
   
BOOL CMFC2048App::InitInstance()
{   
	StartDlg start;   //显示开始界面
	start.DoModal();
	
	AfxOleInit();
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	//GDI+初始化
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	//CDialogEx MyDlg(IDD_DIALOG3);
	//MyDlg.DoModal();
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CMFC2048Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}                                                         
//////////////////////////////////////////////////////////////////////////////////////以上为自动生成的代码
int MFC2048::TwoOrFour()             
{
	if (rand() % 10 > 4)              //得到随机数除以10后的余数
	{
		return 2;                     //余数大于4，返回2
	}
	else
	{
		return 4;                     //否则返回4
	}
}


void MFC2048::Zero()                  //将数字方格初始化为0
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cell[i][j] = 0;
		}
	}
}


void MFC2048::SetRandCell_C()              //在四个角处得到随机2或4
{
	int x = rand() % 4;
	switch (x)
	{
	case 0:
		cell[0][0] = TwoOrFour();
		break;
	case 1:
		cell[3][0] = TwoOrFour();
		break;
	case 2:
		cell[0][3] = TwoOrFour();
		break;
	case 3:
		cell[3][3] = TwoOrFour();
		break;
	default:
		break;
	}
}


void MFC2048::SetRandCell()           //在随机空白块上产生随机2或4
{
	int i, j;
	do {
		i = rand() % 4;
		j = rand() % 4;
	} while (cell[i][j] != 0);
	cell[i][j] = TwoOrFour();
}


void MFC2048::Cell2CellTemp()         //将当前所有 cell 存到 cell_temp
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cell_temp[i][j] = cell[i][j];
		}
	}
}


bool MFC2048::IfEqual()                    //判断是否移动
{
	int sum_equal = 0;
	for (int i = 0; i < 4; i++)                   
	{
		for (int j = 0; j < 4; j++)
		{
			if (cell_temp[i][j] == cell[i][j])  //如果16个方格都和按键之前相等，没有移动，返回true     
			{                                   //否则返回false
				sum_equal++;
			}
		}
	}
	if ( 4 *  4 == sum_equal)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void MFC2048::up()
{
	int i, j, n;
	for (i = 0; i < 4; i++)                     //当前行i从第一行到第四行
	{
		for (n = 0; n < 4 - 1; n++)             //当前列n从第一列到第三列
		{
			if (cell[i][n] == 0)                //如果当前列为0
			{
				for (j = n + 1; j < 4; j++)     //对比列j,从n+1列到第4列
				{
					if (cell[i][j] != 0)        //对比的数不为0的话
					{
						cell[i][n] = cell[i][j];        //将对比的数给当前的位置
						cell[i][j] = 0;
						break;
					}
				}
			}
			//相邻两数相等时合并两数
			for (j = n + 1; j < 4; j++)         //对比列j,从n+1列到第4列
			{
				if (cell[i][j] != 0)            //判断是否为0
				{
					if (cell[i][n] == cell[i][j])
					{
						cell[i][n] += cell[i][j];   //合并相等数
						cell[i][j] = 0;             //右边的数归零
						score += cell[i][n];        //合并记分
						break;
					}
					break;
				}
			}
		}
	}
}


void MFC2048::down()
{
	int i, j, n;
	for (i = 0; i < 4; i++)
	{
		for (n = 4 - 1; n > 0; n--)
		{
			if (cell[i][n] == 0)
			{
				for (j = n - 1; j >= 0; j--)
				{
					if (cell[i][j] != 0)
					{
						cell[i][n] = cell[i][j];
						cell[i][j] = 0;
						break;
					}
				}
			}

			for (j = n - 1; j >= 0; j--)
			{
				if (cell[i][j] != 0)
				{
					if (cell[i][n] == cell[i][j])
					{
						cell[i][n] += cell[i][j];
						cell[i][j] = 0;
						score += cell[i][n];
						break;
					}
					break;
				}
			}
		}
	}
}


void MFC2048::left()
{
	int i, j, n;
	for (i = 0; i < 4; i++)
	{
		for (n = 0; n < 4 - 1; n++)
		{
			if (cell[n][i] == 0)
			{
				for (j = n + 1; j < 4; j++)
				{
					if (cell[j][i] != 0)
					{
						cell[n][i] = cell[j][i];
						cell[j][i] = 0;
						break;
					}
				}
			}

			for (j = n + 1; j < 4; j++)
			{
				if (cell[j][i] != 0)
				{

					if (cell[n][i] == cell[j][i])
					{
						cell[n][i] += cell[j][i];
						cell[j][i] = 0;
						score += cell[n][i];
						break;
					}
					break;

				}
			}
		}
	}
}


void MFC2048::right()
{
	int i, j, n;
	for (i = 0; i < 4; i++)
	{
		for (n = 4 - 1; n > 0; n--)
		{
			if (cell[n][i] == 0)
			{
				for (j = n - 1; j >= 0; j--)
				{
					if (cell[j][i] != 0)
					{
						cell[n][i] = cell[j][i];
						cell[j][i] = 0;
						break;
					}
				}
			}

			for (j = n - 1; j >= 0; j--)
			{
				if (cell[j][i] != 0)
				{
					if (cell[n][i] == cell[j][i])
					{
						cell[n][i] += cell[j][i];
						cell[j][i] = 0;
						score += cell[n][i];
						break;
					}
					break;
				}
			}
		}
	}
}


COLORREF MFC2048::GetTColor(int i)      //返回字体颜色RGB
{
	if (i < 8)
	{
		return RGB(117, 109, 98);       
	}
	else
	{
		return RGB(250, 240, 230);
	}
}


COLORREF MFC2048::GetBkColor(int i)    //返回背景颜色RGB
{
	switch (i)
	{
	case 2:
		return RGB(236, 228, 217);
		break;
	case 4:
		return RGB(236, 224, 198);
		break;
	case 8:
		return RGB(244, 177, 121);
		break;
	case 16:
		return RGB(244, 148, 98);
		break;
	case 32:
		return RGB(244, 128, 95);
		break;
	case 64:
		return RGB(244, 94, 60);
		break;
	case 128:
		return RGB(237, 206, 133);
		break;
	case 256:
		return RGB(237, 206, 116);
		break;
	case 512:
		return RGB(237, 200, 90);
		break;
	case 1024:
		return RGB(237, 198, 55);
		break;
	case 2048:
		return RGB(237, 193, 30);
		break;
	case 4096:
		return RGB(237, 104, 110);
		break;
	case 8192:
		return RGB(237, 70, 80);
		break;
	case 16384:
		return RGB(244, 55, 63);
		break;
	case 32768:
		return RGB(144, 180, 214);
		break;
	case 65536:
		return RGB(95, 160, 224);
		break;
	case 131072:
		return RGB(24, 130, 204);
		break;

	default:
		return RGB(20, 100, 180);
		break;
	}
}


int MFC2048::GetFontSize(int len)        //返回字体大小
{
	switch (len)
	{
	case 1:             //数的位数
		return 60;      //字体大小
		break;
	case 2:
		return 55;
		break;
	case 3:
		return 44;
		break;
	case 4:
		return 30;
		break;
	case 5:
		return 25;
		break;						 
	case 6:
		return 20;
		break;
	case 7:
		return 23;
		break;
	case 8:
		return 20;
		break;
	default:
		return 10;
		break;
	}
}


bool MFC2048::Isover()                           //判断游戏是否结束
{                                           
	int i, j;                              
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (cell[i][j] == 0)                 //如果有方格为0，返回0
			{
				return 0;
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4 - 1; j++)
		{
			if (cell[i][j] == cell[i][j + 1])    //如果有竖向方格相等，返回0
			{
				return 0;
			}
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4 - 1; j++)
		{
			if (cell[j + 1][i] == cell[j][i])    //如果有横向方格相等，返回0
			{
				return 0;
			}
		}
	}

	return 1;                                    //否则返回1  表示游戏结束
}


int CMFC2048App::ExitInstance()                    //关于GDI+ ，不会用，放弃
{
	// TODO: 在此添加专用代码和/或调用基类
	GdiplusShutdown(gdiplusToken);//释放GDI系统资源
	return CWinApp::ExitInstance();
}