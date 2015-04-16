#include "stdafx.h"
#include "Thread.h"

namespace pp {


Thread::Thread()
	: m_pThread(NULL) , 
	 m_nID(0)
{
}

Thread::~Thread()
{
	if (m_pThread !=NULL) {
		WaitForSingleObject(m_pThread->m_hThread, INFINITE);
		delete m_pThread;
		m_pThread = NULL;
	}
}

UINT Thread::Run()
{
	TRACE("Thread start:%d\n", m_nID);
	return 0;
}

void Thread::Initialize()
{
	m_pThread = AfxBeginThread(ThreadFunc, this, THREAD_PRIORITY_NORMAL, 0U, 
		CREATE_SUSPENDED);
	m_pThread->m_bAutoDelete = FALSE;
}

BOOL Thread::StartThread()
{
	DWORD dwRes =  m_pThread->ResumeThread();
	ASSERT(dwRes != 0xFFFFFFFF);
	return dwRes != 0xFFFFFFFF;
}

UINT AFX_CDECL Thread::ThreadFunc(LPVOID pParam)
{
	return ((IRunable*)pParam)->Run();
}

} //namespace pp