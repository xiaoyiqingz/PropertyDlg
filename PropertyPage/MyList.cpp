// MyList.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "MyList.h"


// CMyList

IMPLEMENT_DYNAMIC(CMyList, CListCtrl)

CMyList::CMyList()
{

}

CMyList::~CMyList()
{
}


BEGIN_MESSAGE_MAP(CMyList, CListCtrl)
END_MESSAGE_MAP()

BOOL CMyList::Initialize()
{
	m_coleTarget.Register(this);
	return TRUE;
}

DROPEFFECT CMyList::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	return DROPEFFECT_COPY;
}

DROPEFFECT CMyList::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, DROPEFFECT dropList, CPoint point)
{
	return DROPEFFECT_COPY;
}

BOOL CMyList::OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	UINT              nFileCount = 0;
	HDROP           hDropFiles = NULL;
	HGLOBAL        hMemData = NULL;

	AfxMessageBox(_T("OnDrop"));
	if(pDataObject->IsDataAvailable(CF_HDROP))
	{
		hMemData = pDataObject->GetGlobalData(CF_HDROP);
		hDropFiles = (HDROP)GlobalLock((HGLOBAL)hMemData); 
		if(hDropFiles != NULL)
		{

			TCHAR chTemp[_MAX_PATH+1] = {0};
			nFileCount = DragQueryFile(hDropFiles, 0xFFFFFFFF, NULL, 0);
			for(UINT nCur=0; nCur<nFileCount; ++nCur)
			{
				ZeroMemory(chTemp, _MAX_PATH+1);
				DragQueryFile(hDropFiles, nCur, (LPTSTR)chTemp, _MAX_PATH+1);
				AddFile(chTemp);
			}
		}
		GlobalUnlock(hMemData);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CMyList::OnDragLeave(CWnd* pWnd)
{

}

void CMyList::AddFile(TCHAR *)
{
	
}

// CMyList message handlers
