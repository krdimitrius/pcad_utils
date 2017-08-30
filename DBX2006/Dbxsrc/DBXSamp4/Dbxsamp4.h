// dbxsamp4.h : main header file for the DBXSAMP4 application
//
#ifndef DBXSAMP4_H
#define DBXSAMP4_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
            
/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4App:
// See dbxsamp4.cpp for the implementation of this class
//

class CDbxsamp4App : public CWinApp
{
public:
	CDbxsamp4App();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CDbxsamp4App)
//	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
#endif // DBXSAMP4_H