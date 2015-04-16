#pragma once


// CUIThreadDlg dialog

class CUIThreadDlg : public CDialog
{
	DECLARE_DYNAMIC(CUIThreadDlg)

public:
	CUIThreadDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CUIThreadDlg();

// Dialog Data
	enum { IDD = IDD_UITHREADDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual void OnCancel();
	virtual void OnOK();
};
