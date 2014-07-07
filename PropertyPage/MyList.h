#pragma once
#include "OleDropTargetEx.h"

// CMyList

class CMyList : public CListCtrl
{
	DECLARE_DYNAMIC(CMyList)
public:
	COleDropTargetEx m_coleTarget;

public:
	CMyList();
	virtual ~CMyList();

public:
	void  AddFile(TCHAR *);

protected:
	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL Initialize();
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, DROPEFFECT dropList, CPoint point);
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual void OnDragLeave(CWnd* pWnd);
};


