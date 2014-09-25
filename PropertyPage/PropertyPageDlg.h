
// PropertyPageDlg.h : header file
//

#pragma once
#include "MyButton.h"
#include "MyDialog.h"
#include "DropEdit.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "Utils/SystemTray.h"

#define  WM_FILE_CHANGE WM_USER+0x02

// CPropertyPageDlg dialog
class CPropertyPageDlg : public CDialog
{
// Construction
public:
	CButton m_bCheck;
	HWND	m_preveHwnd;
	CWnd * pWndC;
	CMyDialog*  pWndT;

	CMyButton m_Button;
	CString m_strFilePathIn;
	CString m_strFilePathOut;
	CDropEdit m_etSrc;
	CDropEdit m_etDest;

	ULONG  m_nNotify;

	CSystemTray  m_SysTray;
public:
	CPropertyPageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PROPERTYPAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	BOOL CreateMultiDirectory(LPCTSTR lpSrcPath, LPCTSTR lpDestPath);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnFileChange(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	void	ShowTrayIcon();

public:
	afx_msg void OnBnClickedButtonProperty();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClickedCheck1();
	afx_msg void OnClipboardUpdate();
//	afx_msg void OnDrawClipboard();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnDestroy();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	CLinkCtrl m_syslink;
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSyslink2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnExit();
	afx_msg void OnBnClickedDump();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

typedef struct
{
	DWORD dwItem1;  // dwItem1 contains the previous PIDL or name of the folder. 
	DWORD dwItem2;  // dwItem2 contains the new PIDL or name of the folder. 
}SHNotifyInfo;