// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "MyDialog.h"
#include "afxdialogex.h"

#include <algorithm>
#include "UIThread.h"

// CMyDialog dialog

IMPLEMENT_DYNAMIC(CMyDialog, CDialogEx)

CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDialog::IDD, pParent) , m_pUIthread(NULL)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strPath);
	DDX_Text(pDX, IDC_ET_CLIENT, m_strClientAddr);
	DDX_Text(pDX, IDC_ET_RECV, m_strRecv);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BT_TRANSFER, &CMyDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SOCKET, &CMyDialog::OnBnClickedSocket)
	ON_BN_CLICKED(IDC_CHECK_UI_THREAD, &CMyDialog::OnBnClickedCheckUiThread)
	ON_MESSAGE(WM_SOCKET, &CMyDialog::OnMessageSocket)
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
	m_pUIthread = AfxBeginThread(RUNTIME_CLASS(CUIThread));

	m_pUIthread->PostThreadMessage(WM_SHOWCHAR, (WPARAM)5, 0);
}

//check ui thread is alive or not
void CMyDialog::OnBnClickedCheckUiThread()
{
	DWORD dwExit;
	GetExitCodeThread(m_pUIthread->m_hThread, &dwExit);

	if (dwExit == STILL_ACTIVE) {
		TRACE("still active\n");
	}
}


void CMyDialog::OnBnClickedSocket()
{
	m_socket = ::socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	ServerAddr.sin_port = htons(8848);
	int rec = bind(m_socket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (rec == SOCKET_ERROR) {
		rec = WSAGetLastError();
		TRACE("%d\n");
		ASSERT(0);
	}

	rec = listen(m_socket, 5);
	if (rec == SOCKET_ERROR) {
		rec = WSAGetLastError();
		TRACE("%d\n");
		ASSERT(0);
	}

	rec = WSAAsyncSelect(m_socket, GetSafeHwnd(), WM_SOCKET, FD_ACCEPT| FD_READ);
	if (rec == SOCKET_ERROR) {
		rec = WSAGetLastError();
		TRACE("%d\n");
		ASSERT(0);
	}
}

LRESULT CMyDialog::OnMessageSocket(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT: OnSocketAccept(wParam);
		break;
	case FD_READ: OnSocketRead(wParam);
		break;
	}

	return 0;
}

void CMyDialog::OnSocketAccept(WPARAM wParam)
{
	SOCKADDR_IN ClientAddr;
	int dwSize = sizeof(ClientAddr);
	SOCKET socket = accept(m_socket, (SOCKADDR*)&ClientAddr, &dwSize);
	if (socket == INVALID_SOCKET) {
		MessageBox(_T("accept socket error!"));
		return;
	}
	m_vcClient.insert(std::pair<SOCKET, SOCKADDR_IN>(socket, ClientAddr));
	m_strClientAddr += inet_ntoa(ClientAddr.sin_addr);
	m_strClientAddr += _T("\r\n");
	UpdateData(FALSE);
}

void CMyDialog::OnSocketRead(WPARAM wParam)
{
	auto iter = m_vcClient.find((SOCKET)wParam);
	if (iter == m_vcClient.end()) {
		ASSERT(0);
	}

	char buf[256];
	recv(wParam, buf, 256, 0);
	m_strRecv += buf;
	m_strRecv += _T("\r\n");

	UpdateData(FALSE);
}
