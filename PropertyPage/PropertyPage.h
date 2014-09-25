
// PropertyPage.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "PropertyPageDlg.h"

// CPropertyPageApp:
// See PropertyPage.cpp for the implementation of this class
//

class CPropertyPageApp : public CWinApp
{
public:
	CPropertyPageApp();

protected:
	CPropertyPageDlg *		m_pMainDialog;
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CPropertyPageApp theApp;