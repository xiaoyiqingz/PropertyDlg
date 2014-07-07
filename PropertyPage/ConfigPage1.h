#pragma once


// CConfigPage1 dialog

class CConfigPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CConfigPage1)

public:
	CConfigPage1();
	virtual ~CConfigPage1();

// Dialog Data
	enum { IDD = IDD_DIALOG_CONFIG_PAGE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
//	CString m_strConfigSheetPort;

	int m_nDiscoverPort;
	int m_nPubPort;
	int m_nRoutePort;
	BOOL m_bIsChanged;
	virtual void OnOK();
	virtual BOOL OnApply();
	afx_msg void OnChangeEditDiscoverPort();
	afx_msg void OnChangeEditPubPort();
	afx_msg void OnChangeEditRoutePort();
};
