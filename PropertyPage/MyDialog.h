#pragma once
#include <map>
#include "Thread.h"

#define  WM_SOCKET	(WM_USER + 1)
// CMyDialog dialog

class CMyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialog)
private:
//for thread	
	CString		m_strPath;
	pp::Thread*	m_pThread[3];
	CWinThread* m_pUIthread;

//for socket
	SOCKET						m_socket;
	std::map<SOCKET, SOCKADDR_IN>	m_vcClient;
	CString						m_strClientAddr;
	CString						m_strRecv;
public:
	CMyDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMyDialog();

// Dialog Data
	enum { IDD = IDD_MYDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	void	OnSocketAccept(WPARAM wParam);
	void	OnSocketRead(WPARAM wParam);

public:
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedSocket();
	afx_msg void OnBnClickedCheckUiThread();
	afx_msg LRESULT OnMessageSocket(WPARAM wParam, LPARAM lParam);
};
