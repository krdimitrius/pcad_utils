// drilltab.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "drilltab.h"
#include "drilldlg.h"
#include "widgets.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrilltabApp

BEGIN_MESSAGE_MAP(CDrilltabApp, CWinApp)
    //{{AFX_MSG_MAP(CDrilltabApp)
    //}}AFX_MSG_MAP
    // Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrilltabApp construction

CDrilltabApp::CDrilltabApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDrilltabApp object

CDrilltabApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CDrilltabApp initialization

BOOL CDrilltabApp::InitInstance()
{
    // Initialize WinWidgets tools
    WidgetsInit();
            
    CDrilltabDlg dlg;
    m_pMainWnd = &dlg;
    int nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
    }

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}

