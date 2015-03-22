// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "TestDlg.h"
#include "afxdialogex.h"

#define  IDC_3STATE   WM_USER+1
// CTestDlg dialog

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	,m_nRadio(0)
{

	m_edit = 0;
}

CTestDlg::~CTestDlg()
{
	m_Button.DestroyWindow();
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadio);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CTestDlg::OnKillfocusEdit1)
	ON_BN_CLICKED(IDC_STARTUP_RUN_EX, &CTestDlg::OnBnClickedStartupRunEx)
	ON_BN_CLICKED(IDC_UNSTARTUP_RUNEX, &CTestDlg::OnBnClickedUnstartupRunex)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestDlg message handlers


BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Button.Create(_T("3state"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE, 
		CRect(10, 10, 100, 30), this, IDC_3STATE);

	m_Button.SetCheck(BST_INDETERMINATE);
	return TRUE; 
}

void CTestDlg::OnKillfocusEdit1()
{
	UpdateData(TRUE);
}


void CTestDlg::OnBnClickedStartupRunEx()
{
	HKEY hKey; 
	//找到系统的启动项 
	LPCTSTR lpRun = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"); 
	//打开启动项Key HKEY_LOCAL_MACHINE must have administraror Acess
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey); 
	if(lRet == ERROR_SUCCESS) 
	{ 
		TCHAR  pKey[MAX_PATH] = _T("\"");
		TCHAR  pFileName[MAX_PATH] = {0}; 
		//得到程序自身的全路径 
		DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH); 
		
		_tcscat_s(pKey, pFileName);
		_tcscat_s(pKey, _T("\""));
		_tcscat_s(pKey, _T(" -autorun"));
		//添加一个子Key,并设置值 // 下面的"test"是应用程序名字（不加后缀.exe）
		lRet = RegSetValueEx(hKey, _T("PropertyPage"), 0, REG_SZ, (BYTE *)pKey, (_tcsclen(pKey)+1)*sizeof(TCHAR)); 
		
		//关闭注册表 
		RegCloseKey(hKey); 
		
		if(lRet != ERROR_SUCCESS) 
		{ 
			AfxMessageBox(_T("系统参数错误,不能完成开机启动设置")); 
		} 
		else
		{
			AfxMessageBox(_T("打开开机启动成功")); 
		}
	} 
}


void CTestDlg::OnBnClickedUnstartupRunex()
{
//取消开机启动
	HKEY hKey; 
//找到系统的启动项 
	LPCTSTR lpRun = _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"); 
	//打开启动项Key 
	long lRet = RegOpenKeyEx(HKEY_CURRENT_USER, lpRun, 0, KEY_WRITE, &hKey); 
	
	if(lRet == ERROR_SUCCESS) 
	{ 
		TCHAR pFileName[MAX_PATH] = {0}; 
		//得到程序自身的全路径 
		DWORD dwRet = GetModuleFileName(NULL, pFileName, MAX_PATH); 
		//添加一个子Key,并设置值 // 下面的"test"是应用程序名字（不加后缀.exe）
		lRet = RegDeleteValue(hKey, _T("PropertyPage"));
		//关闭注册表 
		RegCloseKey(hKey); 
		if(lRet != ERROR_SUCCESS) { 
			AfxMessageBox(_T("系统参数错误,不能完成取消开机启动设置")); 
		} 
		else {
			AfxMessageBox(_T("关闭开机启动成功")); 
		}
	}
}


void CTestDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	CString strRadio;
	strRadio.Format(_T("%d\n"), m_nRadio);
	OutputDebugString(strRadio);

	DWORD dwstyle1 =  GetDlgItem(IDC_RADIO1)->GetStyle();
	DWORD dwstyle2 =  GetDlgItem(IDC_RADIO2)->GetStyle();
	DWORD dwstyle3 =  GetDlgItem(IDC_RADIO3)->GetStyle();

	if (dwstyle1 & WS_GROUP) {
		OutputDebugString(_T("RADIO1\n"));
	} 
	if (dwstyle2 & WS_GROUP) {
		OutputDebugString(_T("RADIO2\n"));
	} 
	if (dwstyle3 & WS_GROUP) {
		OutputDebugString(_T("RADIO3\n"));
	}
}

/************************************************************************/
/* 使用runas在程序中获取管理员权限，并使用netsh给程序添加防火墙规则                                                                     */
/************************************************************************/
void CTestDlg::OnBnClickedButton3()
{
/*	TCHAR szModulePath[MAX_PATH] = {0};  

	GetModuleFileName(GetModuleHandle(NULL), szModulePath, sizeof(szModulePath) / sizeof(TCHAR));  

	CString strParameters = _T("advfirewall firewall add rule name=\"pr\" dir=in program=\"");  
	strParameters += szModulePath;  
	strParameters += _T("\" security=authnoencap action=allow");   
	SHELLEXECUTEINFO shellExecute = {0};  
	shellExecute.cbSize = sizeof SHELLEXECUTEINFO;  
	shellExecute.fMask = SEE_MASK_NOCLOSEPROCESS;  
	shellExecute.lpFile = _T("netsh");  
	shellExecute.lpParameters = strParameters; 
	shellExecute.lpVerb = _T("runas");
	shellExecute.nShow = SW_HIDE;  
	if (ShellExecuteEx(&shellExecute))  
	{  
		WaitForSingleObject(shellExecute.hProcess, 2000);  
		CloseHandle(shellExecute.hProcess);  
	}*/
	HINSTANCE hInstance = ShellExecute(NULL, _T("runas"), _T("netsh.exe"), _T("advfirewall firewall delete rule name=\"zisyncd\""), NULL, SW_NORMAL);
	/*HINSTANCE hInstance = ShellExecute(NULL, _T("runas"), _T("G:\\ZiSyncProj\\ZiSyncWin\\build\\Win32\\Release\\zisyncd.exe"), NULL,NULL, SW_SHOWNORMAL);*/
	/*HINSTANCE hInstance = ShellExecute(NULL, _T("taskbarpin"), _T("C:\\Users\\dell\\Desktop\\自同步.lnk"), NULL, NULL, SW_SHOWNORMAL);*/
	CString strId;
	strId.Format(_T("%d"), hInstance);
}

