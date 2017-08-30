// dbxsavw.cpp : implementation of the CDbxsamp4View class
//

#include "stdafx.h"
#include "dbxsamp4.h"

#include "fstream.h"

#include "dbxsavw.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4View

IMPLEMENT_DYNCREATE(CDbxsamp4View, CView)
                               
BEGIN_MESSAGE_MAP(CDbxsamp4View, CView)
    //{{AFX_MSG_MAP(CDbxsamp4View)
    ON_BN_CLICKED(IDPB_START_BUTTON, OnStartButtonClicked)
    ON_BN_CLICKED(IDPB_EXIT_BUTTON, OnExitButtonClicked)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4View construction/destruction

CDbxsamp4View::CDbxsamp4View()
                    : pStartButton(NULL), pExitButton(NULL)
{}

CDbxsamp4View::~CDbxsamp4View()
{
    if (pStartButton != NULL)
    {
        delete pStartButton;
    }

    if (pExitButton != NULL)
    {
        delete pExitButton;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4View drawing

void CDbxsamp4View::OnDraw(CDC* pDC)
{
    if (! pStartButton)
    {
        pStartButton = new CButton();
        pStartButton->Create("Start", WS_VISIBLE | BS_PUSHBUTTON, CRect(40,100,160,130), this, IDPB_START_BUTTON);
    }
    
    if (! pExitButton)
    {
        pExitButton = new CButton();
        pExitButton->Create("Exit", WS_VISIBLE | BS_PUSHBUTTON, CRect(40,150,160,180), this, IDPB_EXIT_BUTTON);
    }
}   


/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4View diagnostics

#ifdef _DEBUG
void CDbxsamp4View::AssertValid() const
{
    CView::AssertValid();
}

void CDbxsamp4View::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CDbxsamp4View message handlers

void CDbxsamp4View::OnStartButtonClicked() // do netlstrpt
{
    TNet    net;
    float   length;
    
    length = 0.0f;
    ofstream out_file( "netlist.rpt", ios::out );
    if (!out_file)
    {
        goto EXIT;
    }
    tStatus = TOpenDesign( DBX_LANGUAGE, DBX_VERSION, "", &tContext);
    out_file << tStatus << endl;
        
    out_file << "TangoPRO Netlist Report" << endl;
    out_file << "" << endl;
    out_file << "========================================================================" << endl;
    out_file << "" << endl;
    out_file << "Units used = mil" << endl;
    out_file << "Net Name" << "\t" << "Net Length" << "\t" << "Number of Nodes" << endl;
    out_file << "------------------------------------------------------------------------" << endl;
    out_file << "" << endl;
    
    tStatus = TGetFirstNet( &tContext, &net );
    while ( tStatus == DBX_OK )
    {
        out_file << net.netName << "\t\t" << (net.length/2540) << "\t\t" << net.nodeCount << endl;
        length = ( length + ( net.length/2540 ) );
        tStatus = TGetNextNet( &tContext, &net );
    }
    
    out_file << "" << endl;
    out_file << "Total length of all nets: " << length << endl;
    
    out_file.close();

EXIT:
    tStatus = TCloseDesign( &tContext, "" );
}


void CDbxsamp4View::OnExitButtonClicked()
{
    //
    // This code first closes down the DBX session, and then sends the
    // main window a CLOSE message which quits the application
    //
    tStatus = TCloseDesign( &tContext, "" );
    AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
}