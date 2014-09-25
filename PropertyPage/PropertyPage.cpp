
// PropertyPage.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <DbgHelp.h>
#include <ShellAPI.h>
#include <ShlObj.h>
#include <strsafe.h>
#include "PropertyPage.h"
#include "PropertyPageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPropertyPageApp

BEGIN_MESSAGE_MAP(CPropertyPageApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()



LONG  WINAPI   callback(_EXCEPTION_POINTERS*   excp)   
{   
	SetErrorMode( SEM_NOGPFAULTERRORBOX );

	CString strBuild;
	strBuild.Format(L"Build: %s %s", __DATE__, __TIME__);
	CString strError;
	HMODULE hModule;
	WCHAR szModuleName[MAX_PATH] = L"";
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)excp->ExceptionRecord->ExceptionAddress, &hModule);
	GetModuleFileName(hModule, szModuleName, ARRAYSIZE(szModuleName));
	strError.AppendFormat(_T("%s %d , %d ,%d."), szModuleName,excp->ExceptionRecord->ExceptionCode, excp->ExceptionRecord->ExceptionFlags, excp->ExceptionRecord->ExceptionAddress);

	//生成 mini crash dump
	BOOL bMiniDumpSuccessful;
	WCHAR szPath[MAX_PATH]; 
	WCHAR szFileName[MAX_PATH]; 
	WCHAR* szAppName = _T("zisync");
	WCHAR* szVersion = _T("v1.0");
	DWORD dwBufferSize = MAX_PATH;
	HANDLE hDumpFile;
	SYSTEMTIME stLocalTime;
	MINIDUMP_EXCEPTION_INFORMATION ExpParam;
	GetLocalTime( &stLocalTime );
	GetTempPath( dwBufferSize, szPath );
	StringCchPrintf(szFileName, MAX_PATH, _T("%s%s"), szPath, szAppName);
	CreateDirectory(szFileName, NULL );
	StringCchPrintf(szFileName, MAX_PATH, _T("%s-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp"), 
		szVersion, 
		stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay, 
		stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond, 
		GetCurrentProcessId(), GetCurrentThreadId());
	hDumpFile = CreateFile(szFileName, GENERIC_READ|GENERIC_WRITE, 
		FILE_SHARE_WRITE|FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

	MINIDUMP_USER_STREAM UserStream[2];
	MINIDUMP_USER_STREAM_INFORMATION UserInfo;
	UserInfo.UserStreamCount = 1;
	UserInfo.UserStreamArray = UserStream;
	UserStream[0].Type = CommentStreamW;
	UserStream[0].BufferSize = strBuild.GetLength()*sizeof(WCHAR);
	UserStream[0].Buffer = strBuild.GetBuffer();
	UserStream[1].Type = CommentStreamW;
	UserStream[1].BufferSize = strError.GetLength()*sizeof(WCHAR);
	UserStream[1].Buffer = strError.GetBuffer();

	ExpParam.ThreadId = GetCurrentThreadId();
	ExpParam.ExceptionPointers = excp;
	ExpParam.ClientPointers = TRUE;

	MINIDUMP_TYPE MiniDumpWithDataSeg = MiniDumpNormal;
	bMiniDumpSuccessful = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), 
		hDumpFile, MiniDumpWithDataSeg, &ExpParam, NULL, NULL); 
	::MessageBox(NULL, _T("程序出错！"), _T("错误"), MB_YESNO);
	return   EXCEPTION_EXECUTE_HANDLER;   
}

// CPropertyPageApp construction

CPropertyPageApp::CPropertyPageApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CPropertyPageApp object

CPropertyPageApp theApp;


// CPropertyPageApp initialization

BOOL CPropertyPageApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	SetUnhandledExceptionFilter(callback);

	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	AfxOleInit();
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	m_pMainDialog = new CPropertyPageDlg();
	m_pMainWnd = m_pMainDialog;
	m_pMainDialog->Create(CPropertyPageDlg::IDD, NULL);
	m_pMainDialog->ShowTrayIcon();

	/*CPropertyPageDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}*/

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;
}



int CPropertyPageApp::ExitInstance()
{
	if (m_pMainDialog != NULL) {
		delete m_pMainDialog;
		m_pMainDialog = NULL;
	}

	return CWinApp::ExitInstance();
}
