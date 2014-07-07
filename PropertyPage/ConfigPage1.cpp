// ConfigPage1.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "ConfigPage1.h"
#include "ConfigSheet.h"
#include "afxdialogex.h"


// CConfigPage1 dialog

IMPLEMENT_DYNAMIC(CConfigPage1, CPropertyPage)

CConfigPage1::CConfigPage1()
	: CPropertyPage(CConfigPage1::IDD
	,IDS_CONFIG_PAGE1_CAPTION)
{
	m_nRoutePort = 8848;
	m_nPubPort = 9526;
	m_nDiscoverPort = 9527;

	m_bIsChanged = FALSE;
}

CConfigPage1::~CConfigPage1()
{
}

void CConfigPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DISCOVER_PORT, m_nDiscoverPort);
	DDV_MinMaxInt(pDX, m_nDiscoverPort, 1024, 65535);
	DDX_Text(pDX, IDC_EDIT_PUB_PORT, m_nPubPort);
	DDV_MinMaxInt(pDX, m_nPubPort, 1024, 65535);
	DDX_Text(pDX, IDC_EDIT_ROUTE_PORT, m_nRoutePort);
	DDV_MinMaxInt(pDX, m_nRoutePort, 1024, 65535);
}


BEGIN_MESSAGE_MAP(CConfigPage1, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_DISCOVER_PORT, &CConfigPage1::OnChangeEditDiscoverPort)
	ON_EN_CHANGE(IDC_EDIT_PUB_PORT, &CConfigPage1::OnChangeEditPubPort)
	ON_EN_CHANGE(IDC_EDIT_ROUTE_PORT, &CConfigPage1::OnChangeEditRoutePort)
END_MESSAGE_MAP()


// CConfigPage1 message handlers


void CConfigPage1::OnOK()
{
	UpdateData(TRUE);
	m_bIsChanged = FALSE;
	CConfigSheet * pSheet = (CConfigSheet *)GetParent();
	pSheet->m_nConfigSheetDiscoverPort = m_nDiscoverPort;
	pSheet->m_nConfigSheetPubPort = m_nPubPort;
	pSheet->m_nConfigSheetRoutePort = m_nRoutePort;

	CString strText,strText2;
	strText += pSheet->m_strConfigSheetName + _T("\n"); 
	strText += pSheet->m_strConfigSheetPwdNew + _T("\n");
	strText2 += pSheet->m_nConfigSheetDiscoverPort + _T("\n"); 
	strText2 += pSheet->m_nConfigSheetPubPort + _T("\n"); 
//	strText2 += pSheet->m_nConfigSheetRoutePort;

	MessageBox(strText);
//	MessageBox(strText2);
	CPropertyPage::OnOK();
}


BOOL CConfigPage1::OnApply()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	m_bIsChanged = FALSE;
	CConfigSheet * pSheet = (CConfigSheet *)GetParent();
	pSheet->m_nConfigSheetDiscoverPort = m_nDiscoverPort;
	pSheet->m_nConfigSheetPubPort = m_nPubPort;
	pSheet->m_nConfigSheetRoutePort = m_nRoutePort;

	return CPropertyPage::OnApply();
}


void CConfigPage1::OnChangeEditDiscoverPort()
{
	if (m_bIsChanged == FALSE) {
		SetModified(TRUE);
		m_bIsChanged = TRUE;
	}
	// TODO:  Add your control notification handler code here
}


void CConfigPage1::OnChangeEditPubPort()
{
	if (m_bIsChanged == FALSE) {
		SetModified(TRUE);
		m_bIsChanged = TRUE;
	}
	// TODO:  Add your control notification handler code here
}


void CConfigPage1::OnChangeEditRoutePort()
{
	if (m_bIsChanged == FALSE) {
		SetModified(TRUE);
		m_bIsChanged = TRUE;
	}
	// TODO:  Add your control notification handler code here
}
