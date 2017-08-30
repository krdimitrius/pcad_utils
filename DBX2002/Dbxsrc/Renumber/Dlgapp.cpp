// dlgapp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "dlgapp.h"
#include "dlgdlg.h"

#include "ctl3d.h"      // Microsoft's 3-D control library

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgappApp

BEGIN_MESSAGE_MAP(CDlgappApp, CWinApp)
    //{{AFX_MSG_MAP(CDlgappApp)
    //}}AFX_MSG_MAP
    // Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgappApp construction

CDlgappApp::CDlgappApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDlgappApp object

CDlgappApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgappApp initialization

BOOL CDlgappApp::InitInstance()
{
    if (m_hPrevInstance == 0)
    {
        //
        // Set up the "chiseled gray" 3-D controls.
        //
//        Ctl3dRegister(m_hInstance);
    
//        if (Ctl3dGetVer() < 0x220 || !Ctl3dAutoSubclass(m_hInstance))
//        {
//            return FALSE;
//        }
        
        RenumberDlg dlg;
        m_pMainWnd = &dlg;
        dlg.DoModal();
    }
    
    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}

int CDlgappApp::ExitInstance()
{
//    Ctl3dUnregister(m_hInstance);
                                 
    return CWinApp::ExitInstance();                                 
}

