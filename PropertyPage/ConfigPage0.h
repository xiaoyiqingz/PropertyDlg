#pragma once


// CConfigPage0 dialog

class CConfigPage0 : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigPage0)

public:
	CConfigPage0();
	virtual ~CConfigPage0();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONFIG_PAGE0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDeviceName;
//	virtual void OnOK();
	CString m_strPwdNew;
	CString m_strPwdOld;
	CString m_strPwdAgain;
	BOOL m_bIsChanged;
	virtual void OnOK();
	afx_msg void OnChangeEditDeviceName();
	virtual BOOL OnApply();
	virtual void OnCancel();
//	virtual BOOL OnKillActive();
	afx_msg void OnChangeEditPwdNew();
	afx_msg void OnChangeEditPwdRepeat();
};
