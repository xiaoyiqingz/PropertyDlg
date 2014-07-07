// ConfigPage0.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "ConfigPage0.h"
#include "ConfigSheet.h"
#include "afxdialogex.h"


// CConfigPage0 dialog

IMPLEMENT_DYNAMIC(CConfigPage0, CPropertyPage)

CConfigPage0::CConfigPage0()
	: CPropertyPage(CConfigPage0::IDD
	,IDS_CONFIG_PAGE0_CAPTION)
{
	m_strDeviceName = _T("test");
	m_strPwdNew = _T("");
	m_strPwdOld = _T("");
	m_strPwdAgain = _T("");
	m_bIsChanged = FALSE;
}

CConfigPage0::~CConfigPage0()
{
}

void CConfigPage0::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEVICE_NAME, m_strDeviceName);
	DDX_Text(pDX, IDC_EDIT_PWD_NEW, m_strPwdNew);
	DDX_Text(pDX, IDC_EDIT_PWD_OLD, m_strPwdOld);
	DDX_Text(pDX, IDC_EDIT_PWD_REPEAT, m_strPwdAgain);
}


BEGIN_MESSAGE_MAP(CConfigPage0, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_DEVICE_NAME, &CConfigPage0::OnChangeEditDeviceName)
	ON_EN_CHANGE(IDC_EDIT_PWD_NEW, &CConfigPage0::OnChangeEditPwdNew)
	ON_EN_CHANGE(IDC_EDIT_PWD_REPEAT, &CConfigPage0::OnChangeEditPwdRepeat)
END_MESSAGE_MAP()


// CConfigPage0 message handlers


//void CConfigPage0::OnOK()
//{
//	// TODO: Add your specialized code here and/or call the base class
//
//	MessageBox(_T("hello"));
//	CPropertyPage::OnOK();
//}


void CConfigPage0::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	MessageBox(_T("Page0 OK!"));
	MessageBox(m_strDeviceName);
	m_bIsChanged = FALSE;

	CConfigSheet * pSheet = (CConfigSheet *) GetParent();

	CString strPwd;	
	if ((m_strPwdNew != _T("") || m_strPwdAgain != _T(""))) {
		if (m_strPwdNew != m_strPwdAgain) {
			strPwd.LoadStringW(IDS_PWD_NOT_SAME);
			MessageBox(strPwd, NULL, MB_OK | MB_ICONERROR);
			m_strPwdAgain = _T("");
		} else {
			pSheet->m_strConfigSheetPwdNew = m_strPwdNew;
		}
	}
	pSheet->m_strConfigSheetName = m_strDeviceName;

	CPropertyPage::OnOK();
}


void CConfigPage0::OnChangeEditDeviceName()
{
	SetModified(true);
	m_bIsChanged = TRUE;
	// TODO:  Add your control notification handler code here
}


BOOL CConfigPage0::OnApply()
{
	// TODO: Add your specialized code here and/or call the base class
	m_bIsChanged = FALSE;
	UpdateData(TRUE);	
	

	CConfigSheet * pSheet = (CConfigSheet *) GetParent();

	CString strPwd;	
	if ((m_strPwdNew != _T("") || m_strPwdAgain != _T(""))) {
		if (m_strPwdNew != m_strPwdAgain) {
			strPwd.LoadStringW(IDS_PWD_NOT_SAME);
			MessageBox(strPwd, NULL, MB_OK | MB_ICONERROR);
			m_strPwdAgain = _T("");
		} else {
			pSheet->m_strConfigSheetPwdNew = m_strPwdNew;
		}
	}
	pSheet->m_strConfigSheetName = m_strDeviceName;

	return CPropertyPage::OnApply();
}


void CConfigPage0::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_bIsChanged)
	{
		CString str;
		str.LoadStringW(IDS_CONTENT_CHANGED);
		if (MB_OK == MessageBox(str, NULL, MB_YESNO | MB_ICONQUESTION)) {
			OnOK();
		} 
	}
	
	CPropertyPage::OnCancel();
}


//BOOL CConfigPage0::OnKillActive()
//{
//	// TODO: Add your specialized code here and/or call the base class
//	OnCancel();
//	if(m_bIsChanged)
//	{
//		MessageBox(_T("KillActivity"));
//	}	
//	return CPropertyPage::OnKillActive();
//}


void CConfigPage0::OnChangeEditPwdNew()
{
	SetModified(true);
	m_bIsChanged = TRUE;
	// TODO:  Add your control notification handler code here
}


void CConfigPage0::OnChangeEditPwdRepeat()
{
	SetModified(true);
	m_bIsChanged = TRUE;
	// TODO:  Add your control notification handler code here
}
