
// PropertyPageDlg.h : header file
//

#pragma once
#include "MyButton.h"
#include "MyDialog.h"
#include "DropEdit.h"
#include "afxwin.h"
#include "afxcmn.h"

// CPropertyPageDlg dialog
class CPropertyPageDlg : public CDialog
{
// Construction
public:
	CButton m_bCheck;
	HWND	m_preveHwnd;

	CWnd * pWndC;
	CMyDialog*  pWndT;

	CString m_strFilePathIn;
	CString m_strFilePathOut;
	CDropEdit m_etSrc;
	CDropEdit m_etDest;

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonProperty();
	CMyButton m_Button;
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
};
