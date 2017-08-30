// dlgapp.h : main header file for the DLGAPP application
//

#ifndef RENUMAPP_H
#define RENUMAPP_H

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgappApp:
// See dlgapp.cpp for the implementation of this class
//

class CDlgappApp : public CWinApp
{
public:
    CDlgappApp();

// Overrides
    virtual BOOL    InitInstance();
    virtual int     ExitInstance();

// Implementation

    //{{AFX_MSG(CDlgappApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
        
#endif RENUMAPP_H

