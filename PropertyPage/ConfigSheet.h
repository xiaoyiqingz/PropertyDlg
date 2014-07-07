#pragma once



// CConfigSheet

#include "ConfigPage0.h"
#include "ConfigPage1.h"

class CConfigSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CConfigSheet)

public:
	CConfigSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CConfigSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CConfigSheet();

protected:
	DECLARE_MESSAGE_MAP()

	CConfigPage0 m_Page0;
	CConfigPage1 m_Page1;
public:
//	afx_msg void OnIdok();

	CString m_strConfigSheetName;
	CString m_strConfigSheetPwdOld;
	CString m_strConfigSheetPwdNew;
	CString m_strConfigSheetPwdAgain;
	
	int m_nConfigSheetDiscoverPort;
	int m_nConfigSheetPubPort;
	int m_nConfigSheetRoutePort;
};

