// dbxsamp4.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "dbxsamp4.h"

#include "mainfrm.h"
#include "dbxsavw.h"
#include "dbxsamp4doc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4App

BEGIN_MESSAGE_MAP(CDbxsamp4App, CWinApp)
	//{{AFX_MSG_MAP(CDbxsamp4App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4App construction

CDbxsamp4App::CDbxsamp4App()
{}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDbxsamp4App object

CDbxsamp4App NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4App initialization

BOOL CDbxsamp4App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	SetDialogBkColor();        // set dialog background color to gray
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

    //
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
    //
	AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,
			RUNTIME_CLASS(CDBXSamp4Doc),
			RUNTIME_CLASS(CMainFrame),     // main SDI frame window
			RUNTIME_CLASS(CDbxsamp4View)));

    //
    // create a new document
    //
    OnFileNew();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4App commands
