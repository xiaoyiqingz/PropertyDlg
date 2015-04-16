// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "MyDialog.h"
#include "afxdialogex.h"
#include "UIThread.h"

// CMyDialog dialog

IMPLEMENT_DYNAMIC(CMyDialog, CDialogEx)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDialog::IDD, pParent)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strPath);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BT_TRANSFER, &CMyDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDialog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyDialog message handlers


BOOL CMyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	for (int i=0; i<3; i++) {
		m_pThread[i] = NULL;
	}


	return TRUE; 
}

void CMyDialog::OnBnClickedCancel()
{ 
	CFileDialog file(TRUE);
	file.DoModal();
	m_strPath = file.GetPathName();
	UpdateData(FALSE);
	if (MessageBox(_T("是否要进行传输？"), _T("提示"), MB_YESNO) == IDNO)
		return;
	
	BOOL bStart = FALSE; 
	for (int i = 0; i< 3; i++) {
		if (m_pThread[i] == NULL) {
			bStart = TRUE;
			m_pThread[i] = new pp::Thread();
			m_pThread[i]->Initialize();
			m_pThread[i]->m_nID = i;
			m_pThread[i]->StartThread();
			break;
		}
	}

	if (!bStart) {
		MessageBox(_T("3个线程都在传输，请稍后"));
	}
}



void CMyDialog::OnBnClickedButton1()
{
	CWinThread* pUIThread = AfxBeginThread(RUNTIME_CLASS(CUIThread));

	pUIThread->PostThreadMessage(WM_SHOWCHAR, (WPARAM)5, 0);
}
