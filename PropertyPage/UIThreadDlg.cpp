// UIThreadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "UIThreadDlg.h"
#include "afxdialogex.h"


// CUIThreadDlg dialog

IMPLEMENT_DYNAMIC(CUIThreadDlg, CDialog)

CUIThreadDlg::CUIThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUIThreadDlg::IDD, pParent)
{

}

CUIThreadDlg::~CUIThreadDlg()
{
}

void CUIThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUIThreadDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUIThreadDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUIThreadDlg message handlers


void CUIThreadDlg::OnBnClickedButton1()
{
	MessageBox(_T("this is a UI thread"));
}


void CUIThreadDlg::OnCancel()
{
	CDialog::OnCancel();

	// not good and output will have a warning:
	//calling DestroyWindow in CDialog::~CDialog --OnDestroy or PostNcDestroy in derived class will not be called.
	//PostMessage(WM_QUIT);  

	DestroyWindow();  // you should always do this
}


void CUIThreadDlg::OnOK()
{
	CDialog::OnOK();
	DestroyWindow();    // to end this ui thread
}
