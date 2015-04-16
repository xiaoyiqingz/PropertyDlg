// UIThread.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "UIThread.h"
#include "UIThreadDlg.h"

// CUIThread

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)

CUIThread::CUIThread()
{
}

CUIThread::~CUIThread()
{
}

BOOL CUIThread::InitInstance()
{
	m_pUIDlg = new CUIThreadDlg();
	m_pUIDlg->Create(CUIThreadDlg::IDD, NULL);
	m_pUIDlg->ShowWindow(SW_SHOW);
	m_pMainWnd = m_pUIDlg;

	return TRUE;
}

int CUIThread::ExitInstance()
{
	if (m_pUIDlg != NULL) {
		delete m_pUIDlg;
		m_pUIDlg = NULL;
	}

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)
	ON_THREAD_MESSAGE(WM_SHOWCHAR, &CUIThread::ShowInfo)
END_MESSAGE_MAP()

//1.注意使用ON_THREAD_MESSAGE
//2.函数原型  void FUNC(WPARAM wParam, LPARAM lParam)
void CUIThread::ShowInfo(WPARAM wParam, LPARAM lParam)
{
	// 接受线程消息
	CString strInfo;
	strInfo.Format(_T("%d"), wParam);
	MessageBox(NULL, strInfo, NULL, MB_OK);

	//如果想给带窗口的线程发送窗口消息，直接PostMessage即可
}


// CUIThread message handlers
