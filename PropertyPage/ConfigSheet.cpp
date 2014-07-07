// ConfigSheet.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "ConfigSheet.h"


// CConfigSheet

IMPLEMENT_DYNAMIC(CConfigSheet, CPropertySheet)

CConfigSheet::CConfigSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_Page0);
	AddPage(&m_Page1);

	// m_psh.dwFlags |= PSH_NOAPPLYNOW;
	m_psh.dwFlags &= ~PSH_HASHELP;
	for(int i=0; i<GetPageCount(); ++i)
		GetPage(i)->m_psp.dwFlags &= ~PSP_HASHELP;

	SetActivePage(1);
	SetActivePage(0);
}

CConfigSheet::CConfigSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

	AddPage(&m_Page0);
	AddPage(&m_Page1);
	
	m_psh.dwFlags |= PSH_WIZARD97;
	
	SetActivePage(1);
	SetActivePage(0);
}

CConfigSheet::~CConfigSheet()
{
}


BEGIN_MESSAGE_MAP(CConfigSheet, CPropertySheet)
END_MESSAGE_MAP()


// CConfigSheet message handlers

/*
void CConfigSheet::OnIdok()
{
	// TODO: Add your command handler code here
	m_Page0.UpdateData(TRUE);
	if (GetActiveIndex() == 1){
		m_Page1.UpdateData(TRUE);
	}
		
	m_strConfigSheetName = m_Page0.m_strDeviceName;
	m_strConfigSheetPwdOld = m_Page0.m_strPwdOld;
	m_strConfigSheetPwdNew = m_Page0.m_strPwdNew;
	m_strConfigSheetPwdAgain = m_Page0.m_strPwdAgain;

	m_nConfigSheetDiscoverPort = m_Page1.m_nDiscoverPort;
	m_nConfigSheetPubPort = m_Page1.m_nPubPort;
	m_nConfigSheetRoutePort = m_Page1.m_nRoutePort;
	MessageBox(m_strConfigSheetName);

	CString str,str1,str2;
	str.Format(_T("%d"),m_nConfigSheetDiscoverPort);
	MessageBox(str);

	str1.LoadStringW(IDS_PWD);
	if (m_strConfigSheetPwdOld != str1){
		str2.LoadStringW(IDS_PWD_WRONG);
		MessageBox (str2, NULL, MB_OK | MB_ICONERROR);
		return;
	}else if (m_strConfigSheetPwdNew != m_strConfigSheetPwdAgain){
		str2.LoadStringW(IDS_PWD_NOT_SAME);
		MessageBox(str2, NULL, MB_OK | MB_ICONERROR);
		return;
	}


}

*/