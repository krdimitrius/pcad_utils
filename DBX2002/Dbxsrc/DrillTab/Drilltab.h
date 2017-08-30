// drilltab.h : main header file for the DRILLTAB application
//

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrilltabApp:
// See drilltab.cpp for the implementation of this class
//

class CDrilltabApp : public CWinApp
{
public:
    CDrilltabApp();

// Overrides
    virtual BOOL InitInstance();

// Implementation

    //{{AFX_MSG(CDrilltabApp)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

