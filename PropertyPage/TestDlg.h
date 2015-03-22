#pragma once
#include "explorer1.h"

// CTestDlg dialog

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)
public:
	CButton	m_Button;
	int m_nRadio;
public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestDlg();
	
// Dialog Data
	enum { IDD = IDD_TESTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillfocusEdit1();
	int m_edit;
	afx_msg void OnBnClickedStartupRunEx();
	afx_msg void OnBnClickedUnstartupRunex();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual BOOL OnInitDialog();
};
