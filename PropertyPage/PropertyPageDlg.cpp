
// PropertyPageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "PropertyPageDlg.h"
#include "ConfigSheet.h"
#include "afxdialogex.h"
#include "TestDlg.h"
#include "..\HookDll\HookDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  IDC_TANCHUANG  WM_USER + 0x01  


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPropertyPageDlg dialog




CPropertyPageDlg::CPropertyPageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyPageDlg::IDD, pParent)
	, m_strFilePathIn(_T(""))
	, m_strFilePathOut(_T(""))
{
	pWndT = NULL;
	pWndC = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPropertyPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Button);
	DDX_Control(pDX, IDC_CHECK1, m_bCheck);
	DDX_Text(pDX, IDC_EDIT1, m_strFilePathIn);
	DDX_Text(pDX, IDC_EDIT2, m_strFilePathOut);
	DDX_Control(pDX, IDC_EDIT1, m_etSrc);
	DDX_Control(pDX, IDC_EDIT2, m_etDest);
	DDX_Control(pDX, IDC_SYSLINK1, m_syslink);
}

BEGIN_MESSAGE_MAP(CPropertyPageDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Property, &CPropertyPageDlg::OnBnClickedButtonProperty)
	ON_BN_CLICKED(IDC_BUTTON1, &CPropertyPageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CPropertyPageDlg::OnClickedCheck1)
	ON_WM_CLIPBOARDUPDATE()
	ON_BN_CLICKED(IDC_BUTTON2, &CPropertyPageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPropertyPageDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPropertyPageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CPropertyPageDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON5, &CPropertyPageDlg::OnBnClickedButton5)
	ON_WM_DESTROY()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON7, &CPropertyPageDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CPropertyPageDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CPropertyPageDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_DUMP, OnBnClickedDump)
	ON_MESSAGE(WM_FILE_CHANGE, OnFileChange)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CPropertyPageDlg::OnNMClickSyslink1)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK2, &CPropertyPageDlg::OnNMClickSyslink2)
	ON_COMMAND(ID_EXIT, &CPropertyPageDlg::OnExit)
	ON_BN_CLICKED(IDC_BUTTON10, OnBnClickedButton10)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CPropertyPageDlg message handlers
/*
HWND g_Hwnd = NULL;
HHOOK g_Hook = NULL;

LRESULT CALLBACK GetMsgProc(
	_In_  int code,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
)
{
	MSG * pMsg = (MSG *)lParam;
	if (pMsg->message == WM_DROPFILES) {
		::SendMessage(g_Hwnd, WM_CLOSE, 0, 0);
		UnhookWindowsHookEx(g_Hook);
	} else {
		return CallNextHookEx(g_Hook, code, wParam, lParam);
	}
}
*/

BOOL CPropertyPageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_etSrc.Register();
	m_etDest.Register();


	SHChangeNotifyEntry sn = {0};
	sn.fRecursive = TRUE;
	sn.pidl    = 0;

	m_nNotify = SHChangeNotifyRegister( m_hWnd, SHCNRF_InterruptLevel|SHCNRF_ShellLevel,SHCNE_ALLEVENTS, WM_FILE_CHANGE, 1,  &sn );

//	SetHook(GetSafeHwnd());
	/*g_Hook = SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, NULL, GetCurrentThreadId());
	g_Hwnd = GetSafeHwnd();*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPropertyPageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPropertyPageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPropertyPageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPropertyPageDlg::ShowTrayIcon()
{
	CString strText(_T("Pro"));
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_SysTray.Create(NULL, WM_APP+1, strText, hIcon,
		IDR_MENU1, FALSE, NULL, _T("hello"), 0UL, 3U);
	m_SysTray.SetTargetWnd(this);
}

void CPropertyPageDlg::OnBnClickedButtonProperty()
{
	// TODO: Add your control notification handler code here
	CConfigSheet ConSheet(IDS_CONFIG_SHEET_CAPTION);
	if (ConSheet.DoModal() != ID_WIZFINISH){
		return;
	}
}


void CPropertyPageDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	char* cBuffer;
	OpenClipboard();
	if (IsClipboardFormatAvailable(CF_TEXT)) {  //将剪切板上文字复制到txt
		HANDLE hClip;
		hClip = GetClipboardData(CF_TEXT);
		cBuffer = (char *)GlobalLock(hClip);
		GlobalUnlock(hClip);
		FILE * fout;
		fopen_s(&fout, "a.txt", "a");
		ASSERT (fout != NULL);
		if (fout == NULL) return;

		fprintf(fout, "%s", cBuffer);

		VERIFY( fclose(fout) != EOF );
				
	}  else if (IsClipboardFormatAvailable(CF_BITMAP)){   //将剪切板上内容显示在界面上
		HBITMAP handler = (HBITMAP)GetClipboardData(CF_BITMAP);
		CBitmap *bitmap = CBitmap::FromHandle(handler);
		CClientDC cdc(this);
		CDC dc;
		dc.CreateCompatibleDC(&cdc);
		dc.SelectObject(bitmap);
		cdc.BitBlt(10,10, 50, 50, &dc, 0, 0, SRCCOPY);
	} else if (IsClipboardFormatAvailable(CF_SYLK)) {
		MessageBox(_T("CF_SYLK"));	
	} else if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
		MessageBox(_T("CF_UNICODETEXT"));	
	} else if (IsClipboardFormatAvailable(CF_OEMTEXT)) {
		MessageBox(_T("CF_UNICODETEXT"));	
	} else if (IsClipboardFormatAvailable(CF_HDROP)) {
		int cch;
		TCHAR szFile[MAX_PATH];
		TCHAR szDest[MAX_PATH];
		TCHAR* szBuffer;
		szDest[0] = 0;
		_tcscpy_s(szDest, _T("G:\\vstest\\PropertyPage\\PropertyPage"));
		HDROP hDrop = (HDROP)GetClipboardData(CF_HDROP);
		int nFile = DragQueryFile(hDrop, -1, NULL, 0);
		for (int i = 0; i < nFile; i++) {
			cch=DragQueryFile(hDrop,i,NULL,0);			
			DragQueryFile(hDrop,i,szFile,sizeof(szFile)); 
			szBuffer = _tcsrchr(szFile, _T('\\'));
	
			_tcscat_s(szDest, szBuffer);
			BOOL res = CopyFile(szFile, szDest, TRUE);
			DWORD dwError = GetLastError();
			//MoveFileEx(szFile, _T("G:\\vstest\\PropertyPage\\PropertyPage\\"), TRUE);
 		}
	} 

	CloseClipboard();	
}


void CPropertyPageDlg::OnClickedCheck1()
{
	// TODO: Add your control notification handler code here

/*
	if (m_bCheck.GetCheck() == BST_CHECKED) {
//		m_preveHwnd =SetClipboardViewer();
		AddClipboardFormatListener(this->GetSafeHwnd());
	} else {
//		ChangeClipboardChain(m_preveHwnd);
		RemoveClipboardFormatListener(this->GetSafeHwnd());
	}*/
}


//void CPropertyPageDlg::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter)
//{
//	CDialog::OnChangeCbChain(hWndRemove, hWndAfter);
//
//	if (hWndRemove == m_preveHwnd) 
//		m_preveHwnd = hWndAfter;
//	// TODO: Add your message handler code here
//}

void CPropertyPageDlg::OnClipboardUpdate()
{
	char* cBuffer;
	OpenClipboard();
	if (IsClipboardFormatAvailable(CF_TEXT)) {  //将剪切板上文字复制到txt
		HANDLE hClip;
		hClip = GetClipboardData(CF_TEXT);
		cBuffer = (char *)GlobalLock(hClip);
		GlobalUnlock(hClip);
		FILE * fout;
		fopen_s(&fout,"a.txt", "a");
		ASSERT (fout != NULL);
		if (fout == NULL) return;

		fprintf(fout, "%s", cBuffer);

		VERIFY( fclose(fout) != EOF );

	}  else if (IsClipboardFormatAvailable(CF_BITMAP)){   //将剪切板上内容显示在界面上
		HBITMAP handler = (HBITMAP)GetClipboardData(CF_BITMAP);
		CBitmap *bitmap = CBitmap::FromHandle(handler);
		CClientDC cdc(this);
		CDC dc;
		dc.CreateCompatibleDC(&cdc);
		dc.SelectObject(bitmap);
		cdc.BitBlt(10,10, 50, 50, &dc, 0, 0, SRCCOPY);
	} else if (IsClipboardFormatAvailable(CF_SYLK)) {
		MessageBox(_T("CF_SYLK"));	
	} else if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
		MessageBox(_T("CF_UNICODETEXT"));	
	} else if (IsClipboardFormatAvailable(CF_OEMTEXT)) {
		MessageBox(_T("CF_UNICODETEXT"));	
	} else if (IsClipboardFormatAvailable(CF_HDROP)) {
		int cch;
		TCHAR szFile[MAX_PATH];
		TCHAR szDestBuffer[MAX_PATH];
		TCHAR szDest[MAX_PATH];
		TCHAR* szBuffer;
		szDestBuffer[0] = 0;
		_tcscpy_s(szDestBuffer, _T("G:\\vstest\\PropertyPage\\PropertyPage\\Res"));

		HDROP hDrop = (HDROP)GetClipboardData(CF_HDROP);
		int nFile = DragQueryFile(hDrop, -1, NULL, 0);
		for (int i = 0; i < nFile; i++) {
			szDest[0] = 0;
			_tcscpy_s(szDest, szDestBuffer);
			cch=DragQueryFile(hDrop,i,NULL,0);			
			DragQueryFile(hDrop,i,szFile,sizeof(szFile));
			szBuffer = _tcsrchr(szFile, _T('\\'));
			_tcscat_s(szDest, szBuffer);

			if (PathIsDirectory(szFile)) {
				CreateMultiDirectory(szFile, szDest);
			} else {
				BOOL res = CopyFile(szFile, szDest, TRUE);
				DWORD dwError = GetLastError();
				//MoveFileEx(szFile, _T("G:\\vstest\\PropertyPage\\PropertyPage\\"), TRUE);
				DWORD dw = dwError;
			}			
		}
	} 

	CloseClipboard();	

	CDialog::OnClipboardUpdate();
}

BOOL CPropertyPageDlg::CreateMultiDirectory(LPCTSTR lpSrcPath, LPCTSTR lpDestPath)
{
	CreateDirectory(lpDestPath,  NULL);
	DWORD dwResCD = GetLastError();
	TCHAR szSrc[MAX_PATH];
	_tcscpy_s(szSrc, lpSrcPath);
	_tcscat_s(szSrc, _T("\\*"));

	WIN32_FIND_DATA Data;
	Data.cFileName[0] = 0;
	HANDLE handle = FindFirstFile(szSrc, &Data);
	TCHAR szPath[MAX_PATH];
	TCHAR szDestBuffer[MAX_PATH];
	TCHAR szDest[MAX_PATH];

	do {
		if (!_tcscmp(Data.cFileName, _T(".")) || !_tcscmp(Data.cFileName, _T("..")))
			continue;

		szDest[0] = 0; 
		szPath[0] = 0;
		_tcscpy_s(szDestBuffer, lpDestPath);
		_tcscpy_s(szPath, lpSrcPath);
		_tcscat_s(szPath, _T("\\"));
		_tcscat_s(szPath, Data.cFileName);

		szDest[0] = 0;
		_tcscpy_s(szDest, szDestBuffer);
		_tcscat_s(szDest, _T("\\"));
		_tcscat_s(szDest, Data.cFileName);

		if (Data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			CreateMultiDirectory(szPath, szDest);
		} else {			
			BOOL res =CopyFile(szPath, szDest, TRUE);
			DWORD dwRes = GetLastError();
			DWORD dw = dwRes;
		}
	} while (FindNextFile(handle, &Data));

	return TRUE;
}



//void CPropertyPageDlg::OnDrawClipboard()
//{
//	CDialog::OnDrawClipboard();
//
//	char* cBuffer;
//	OpenClipboard();
//	if (IsClipboardFormatAvailable(CF_TEXT)) {  //将剪切板上文字复制到txt
//		HANDLE hClip;
//		hClip = GetClipboardData(CF_TEXT);
//		cBuffer = (char *)GlobalLock(hClip);
//		GlobalUnlock(hClip);
//		FILE * fout;
//		fout = fopen ("a.txt", "a");
//		ASSERT (fout != NULL);
//		if (fout == NULL) return;
//
//		fprintf(fout, "%s", cBuffer);
//
//		VERIFY( fclose(fout) != EOF );
//
//	}  else if (IsClipboardFormatAvailable(CF_BITMAP)){   //将剪切板上内容显示在界面上
//		HBITMAP handler = (HBITMAP)GetClipboardData(CF_BITMAP);
//		CBitmap *bitmap = CBitmap::FromHandle(handler);
//		CClientDC cdc(this);
//		CDC dc;
//		dc.CreateCompatibleDC(&cdc);
//		dc.SelectObject(bitmap);
//		cdc.BitBlt(10,10, 50, 50, &dc, 0, 0, SRCCOPY);
//	} else if (IsClipboardFormatAvailable(CF_SYLK)) {
//		MessageBox(_T("CF_SYLK"));	
//	} else if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
//		MessageBox(_T("CF_UNICODETEXT"));	
//	} else if (IsClipboardFormatAvailable(CF_OEMTEXT)) {
//		MessageBox(_T("CF_UNICODETEXT"));	
//	} else if (IsClipboardFormatAvailable(CF_HDROP)) {
//		int cch;
//		TCHAR szFile[MAX_PATH];
//		TCHAR szDest[MAX_PATH];
//		TCHAR* szBuffer;
//		szDest[0] = 0;
//		_tcscpy(szDest, _T("G:\\vstest\\PropertyPage\\PropertyPage"));
//		HDROP hDrop = (HDROP)GetClipboardData(CF_HDROP);
//		int nFile = DragQueryFile(hDrop, -1, NULL, 0);
//		for (int i = 0; i < nFile; i++) {
//			cch=DragQueryFile(hDrop,i,NULL,0);			
//			DragQueryFile(hDrop,i,szFile,sizeof(szFile)); 
//			szBuffer = _tcsrchr(szFile, _T('\\'));
//
//			_tcscat(szDest, szBuffer);
//			BOOL res = CopyFile(szFile, szDest, TRUE);
//			DWORD dwError = GetLastError();
//			//MoveFileEx(szFile, _T("G:\\vstest\\PropertyPage\\PropertyPage\\"), TRUE);
//		}
//	} 
//
//	CloseClipboard();	
//}


void CPropertyPageDlg::OnBnClickedButton2()
{
/*
	CoInitialize(NULL); 

	LPWSTR lpwLibaryPath;
	TCHAR szPath[MAX_PATH];
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Libraries, KF_FLAG_DEFAULT_PATH, NULL, &lpwLibaryPath))) {
		_tcscpy_s(szPath, lpwLibaryPath);
		_tcscat_s(szPath, _T("\\ZiSync.library-ms"));
	}
	

	if (PathFileExists(szPath)) {
		MessageBox(_T("该库已存在!"));
		
		CoTaskMemFree(lpwLibaryPath);
		lpwLibaryPath = NULL;
		::CoUninitialize();
		return;
	}
	
	// 利用Shell API创建库
	IShellLibrary *pIShelLibrary;
	HRESULT hr = SHCreateLibrary(IID_PPV_ARGS(&pIShelLibrary));

	if (SUCCEEDED(hr))
	{
		// 如果库创建成功，添加不同的文件路径到当前库中

		IShellItem *pIShellItem;
		SHAddFolderPathToLibrary(pIShelLibrary, _T("G:\\zisync3"));

		// 将当前库保存到系统的库目录下
		// 也就是添加一个新的库“MyDownload”
		hr = pIShelLibrary->SaveInKnownFolder(FOLDERID_Libraries ,_T("ZiSync"), 
			LSF_MAKEUNIQUENAME, &pIShellItem);

		// 释放对象
		if (pIShellItem != NULL) {
			pIShellItem->Release();

		}
		if (pIShelLibrary != NULL) {
			pIShelLibrary->Release();
		}
		::CoUninitialize();
	}*/
}

void CPropertyPageDlg::OnBnClickedButton3()
{
/*
	CoInitialize(NULL);

	IShellLibrary *pIShelLibrary;
	LPWSTR lpwLibaryPath;
	TCHAR szPath[MAX_PATH];
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Libraries, KF_FLAG_DEFAULT_PATH, NULL, &lpwLibaryPath))) {
		_tcscpy_s(szPath, lpwLibaryPath);
		_tcscat_s(szPath, _T("\\ZiSync.library-ms"));
	}

	HRESULT hr = SHLoadLibraryFromParsingName(szPath, STGM_READWRITE, 
		IID_PPV_ARGS(&pIShelLibrary));
	HRESULT hr1 = SHAddFolderPathToLibrary(pIShelLibrary, _T("G:\\zisync1"));

	pIShelLibrary->Commit();
	
	CoTaskMemFree(lpwLibaryPath);
	lpwLibaryPath = NULL;
	if (pIShelLibrary != NULL) {
		pIShelLibrary->Release();
	
	::CoUninitialize();
	}*/
}


void CPropertyPageDlg::OnBnClickedButton4()
{

	/*CoInitialize(NULL);

	IShellLibrary *pIShelLibrary;
	LPWSTR lpwLibaryPath;
	TCHAR szPath[MAX_PATH];
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Libraries, KF_FLAG_DEFAULT_PATH, NULL, &lpwLibaryPath))) {
		_tcscpy_s(szPath, lpwLibaryPath);
		_tcscat_s(szPath, _T("\\ZiSync.library-ms"));
	}

	HRESULT hr = SHLoadLibraryFromParsingName(szPath, STGM_READWRITE, 
		IID_PPV_ARGS(&pIShelLibrary));
	SHRemoveFolderPathFromLibrary(pIShelLibrary, _T("G:\\zisync1"));

	CoTaskMemFree(lpwLibaryPath);
	lpwLibaryPath = NULL;
	pIShelLibrary->Commit();
	if (pIShelLibrary != NULL ) {
		pIShelLibrary->Release();
	}	

	::CoUninitialize();*/
}


void CPropertyPageDlg::OnBnClickedButton6()
{
	DeleteFile(_T("C:\\Users\\dell\\AppData\\Roaming\\Microsoft\\Windows\\Libraries\\ZiSync.library-ms"));
}


void CPropertyPageDlg::OnBnClickedButton5()
{

	CWnd *  pWnd = NULL;
	HWND hwnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);

	if (hwnd) {
		pWnd = CWnd::FromHandle(hwnd);
	}
	CRect  Rect;
	pWnd->GetWindowRect(&Rect);
	pWndT = new CMyDialog();
	pWndT->Create(IDD_MYDIALOG, NULL);

	pWndT->ShowWindow(SW_SHOW);
	pWndT->MoveWindow(Rect.right - 200, Rect.top-90, 188, 90);
}


void CPropertyPageDlg::OnBnClickedDump()
{
	SetTimer(1, 1000, NULL);
}


void CPropertyPageDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int n = 5;
	int a = 15;
	int b;
	switch (nIDEvent) {
		case 1:
			n--;
			b = a / n;
			CString strText;
			strText.Format(_T("%d\n"), b);
			m_strFilePathOut = strText;
			UpdateData(FALSE);
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CPropertyPageDlg::OnDestroy()
{
	CDialog::OnDestroy();
	if (pWndT) {
		delete pWndT;
		pWndT = NULL;
	}

	if (pWndC) {
		pWndC = NULL;
	}
	// TODO: Add your message handler code here
}



void CPropertyPageDlg::OnDropFiles(HDROP hDropInfo)
{
	UINT nFile;
	TCHAR szFilePath[MAX_PATH+1];
	nFile = ::DragQueryFile(hDropInfo, (UINT)(-1), NULL, 0);
	for (UINT i = 0; i < nFile; i++) {
		szFilePath[0] = 0;
		::DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		m_strFilePathIn += szFilePath;
	}

	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}


void CPropertyPageDlg::OnBnClickedButton7()
{
	m_strFilePathOut = m_strFilePathIn;
	UpdateData(FALSE);
}


void CPropertyPageDlg::OnBnClickedButton8()
{
	m_strFilePathIn = m_strFilePathOut = _T("");
	UpdateData(FALSE);
}

void CPropertyPageDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	if (pWndC != NULL) {
		if (pWndC->IsWindowVisible()) {
			pWndC->ShowWindow(SW_HIDE);
		} else {
			pWndC->ShowWindow(SW_SHOW);
		}
	}	
}

void CPropertyPageDlg::OnBnClickedButton10()
{
	CTestDlg dlg;
	dlg.DoModal();
}


LRESULT CPropertyPageDlg::OnFileChange(WPARAM wParam, LPARAM lParam)
{
	SHNotifyInfo*   pShellInfo   =   (SHNotifyInfo*)wParam;
	TCHAR szSrc[MAX_PATH] = {0};
	TCHAR szDes[MAX_PATH] = {0};

	SHGetPathFromIDList( (LPCITEMIDLIST)pShellInfo->dwItem1, szSrc );
	SHGetPathFromIDList( (LPCITEMIDLIST)pShellInfo->dwItem2, szDes );
	switch(lParam)
	{
	case SHCNE_CREATE:
		m_strFilePathIn.Format(_T("%s"), szSrc);
		m_strFilePathOut.Format(_T("%s"), szDes);
		UpdateData(FALSE);
		break;
	}

	return S_OK;
}

void CPropertyPageDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)  
{   
	PNMLINK pNMLink = (PNMLINK) pNMHDR;   
	ShellExecuteW(NULL, L"open", _T("http://www.zisync.com"), NULL, NULL, SW_SHOWNORMAL); 	        
	*pResult = 0;  
}  

void CPropertyPageDlg::OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult)  
{   
	PNMLINK pNMLink = (PNMLINK) pNMHDR;   
	ShellExecuteW(NULL, L"open", _T("mailto:zisync@126.com"), NULL, NULL, SW_SHOWNORMAL); 	        
	*pResult = 0;  
}  

void CPropertyPageDlg::OnExit()
{
	DestroyWindow();
}

