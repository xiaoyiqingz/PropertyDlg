#pragma once

#define	WM_SHOWCHAR	(WM_USER+1)

// CUIThread

class CUIThreadDlg;

class CUIThread : public CWinThread
{
	DECLARE_DYNCREATE(CUIThread)
public:
	CUIThreadDlg*	m_pUIDlg;

public:
	CUIThread();           // protected constructor used by dynamic creation
	virtual ~CUIThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void ShowInfo(WPARAM wParam, LPARAM lParam);
};


