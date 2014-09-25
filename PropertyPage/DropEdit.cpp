// DropEdit.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "DropEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDropEdit

CDropEdit::CDropEdit()
{
	m_bDraging = FALSE;
}

CDropEdit::~CDropEdit()
{
}


BEGIN_MESSAGE_MAP(CDropEdit, CEdit)
	//{{AFX_MSG_MAP(CDropEdit)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(DROPM_DRAGOVER,OnDragOver)
	ON_MESSAGE(DROPM_DROPEX,OnDropEx)
	ON_MESSAGE(DROPM_DROP,OnDrop)
	ON_MESSAGE(DROPM_DRAGLEAVE, OnDragLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDropEdit message handlers

BOOL CDropEdit::Register()
{
	return m_dropEx.Register( this );
}

LRESULT CDropEdit::OnDragOver(WPARAM pDropInfoClass, LPARAM lParm)
{
	COleDropInfo* pInfo = (COleDropInfo* )pDropInfoClass;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(COleDropInfo)));

	if( pInfo->m_pDataObject->IsDataAvailable( CF_TEXT ) )
		return DROPEFFECT_COPY;
	else
		return DROPEFFECT_NONE;
}

LRESULT CDropEdit::OnDropEx(WPARAM pDropInfoClass, LPARAM lParm)
{
	return (DROPEFFECT)-1;
}

LRESULT CDropEdit::OnDrop(WPARAM pDropInfoClass, LPARAM lParm)
{
	COleDropInfo* pInfo = (COleDropInfo* )pDropInfoClass;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(COleDropInfo)));

	if( pInfo->m_pDataObject->IsDataAvailable( CF_TEXT ) )
	{
		HGLOBAL hMem = pInfo->m_pDataObject->GetGlobalData( CF_TEXT );
		TCHAR* lp = (TCHAR *)GlobalLock((HGLOBAL) hMem);//lock source
		if (lp != NULL)
		{
			//Set Windows title with Drop text 
			SetWindowText( lp );
		}
		GlobalUnlock( hMem );//unlock source
		return TRUE;
	}
	else
		return FALSE;
}

LRESULT CDropEdit::OnDragLeave(WPARAM pDropInfoClass,LPARAM lParm)
{
	return FALSE;
}

void CDropEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEdit::OnLButtonDown(nFlags, point);

	Sleep(250);
	MSG msg;
	::PeekMessage(
		&msg,
		GetSafeHwnd(),
		WM_LBUTTONUP,
		WM_LBUTTONUP,
		PM_NOREMOVE
		);
	
	if( msg.message==WM_LBUTTONUP )
		return;

	CString sContens;
	GetWindowText( sContens );
	TCHAR szPath[MAX_PATH];
	szPath[0] = 0;
	_tcscpy_s(szPath, sContens);
	/*HGLOBAL hData = GlobalAlloc(GHND|GMEM_SHARE, sContens.GetLength()+1 ); 
	TCHAR *pS = (TCHAR  *)GlobalLock( hData );
	memcpy( pS, (LPCTSTR)sContens, sContens.GetLength()+1 );
	GlobalUnlock( hData );*/

	LPDROPFILES    lpDropFiles = NULL;
	HGLOBAL        hMemData = NULL;
	UINT		   uBufferSize = 0;
	UINT		   uTcharSize = 0;
	
	uTcharSize = sizeof(TCHAR);
//	UINT uBuffer = _tcslen(szPath) <<1 ;
//	uBufferSize = sizeof(DROPFILES); 
	uBufferSize = sizeof(DROPFILES) + _tcslen(szPath)<< 1 + sizeof(TCHAR);
	hMemData = GlobalAlloc(GHND | GMEM_DDESHARE,uBufferSize);
	ASSERT(hMemData != NULL);

	lpDropFiles = (LPDROPFILES)GlobalLock(hMemData); 
	ASSERT(lpDropFiles != NULL);
	lpDropFiles->pFiles = sizeof(DROPFILES);
	lpDropFiles->fWide = TRUE;
	lpDropFiles->fNC = FALSE;

	LPSTR pGloabalString = (LPSTR)lpDropFiles + sizeof(DROPFILES);
//	LPTSTR pGloabalStringW = (LPTSTR)pGloabalString;
	//testdata  _T("C:\\Users\\dell\\Desktop\\break.txt")
	_tcscpy((LPTSTR)pGloabalString, szPath);	
	OutputDebugString((LPTSTR)pGloabalString);
	OutputDebugString(_T("\n"));
	GlobalUnlock(hMemData);
//	pGloabalString[0] = _T('\0');
	
	m_bDraging = TRUE;
	COleDataSource source;
	source.Empty();
	source.CacheGlobalData( CF_HDROP, hMemData );
	DROPEFFECT dwEffect = source.DoDragDrop(DROPEFFECT_MOVE);
	CString strText;
	strText.Format(_T("%d\n"), dwEffect);
	OutputDebugString(strText);
	GlobalFree( hMemData );
	m_bDraging = FALSE;	
}
