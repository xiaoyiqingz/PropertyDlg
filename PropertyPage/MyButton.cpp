// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "PropertyPage.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMyButton message handlers




void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CButton::OnMouseMove(nFlags, point);
}
