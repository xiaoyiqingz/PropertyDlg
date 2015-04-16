#pragma once
#include "Thread.h"

// CMyDialog dialog

class CMyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialog)
private:
	CString		m_strPath;
	pp::Thread*	m_pThread[3];

public:
	CMyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDialog();

// Dialog Data
	enum { IDD = IDD_MYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
