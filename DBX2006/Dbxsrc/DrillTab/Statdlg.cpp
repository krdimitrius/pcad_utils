// statdlg.cpp : implementation file
//

#include "stdafx.h"
#include "drilltab.h"
#include "statdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusDlg dialog


CStatusDlg::CStatusDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CStatusDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CStatusDlg)
    //}}AFX_DATA_INIT
    CStatusDlg::Create(CStatusDlg::IDD, pParent);
}

void CStatusDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CStatusDlg)
    DDX_Control(pDX, IDST_STATUS_MSG, m_StatusText);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStatusDlg, CDialog)
    //{{AFX_MSG_MAP(CStatusDlg)
        // NOTE: the ClassWizard will add message map macros here
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CStatusDlg message handlers


/////////////////////////////////////////////////////////////////////////////
// CStatusDlg misc member functions

void CStatusDlg::TitleTextSet(char* ttext)
{
    if (ttext && strlen(ttext))
    {
        (void) SetWindowText(ttext);
    }
    return;
}

void CStatusDlg::MsgTextSet(char *itext,   // Initial text
                 int icnt,      // Initial integer to embed (optional, ignored if < 0)
                 char *mtext,   // Middle text (optional)
                 int mcnt,      // Middle integer to embed (optional, ignored if < 0)
                 char* ttext)   // Trailing text (optional)
{
    char    buf[6];
    CString stattext(itext);
//  stattext = CString(itext);
    if (icnt >= 0)
    {
        itoa(icnt, buf, 10);
        stattext = stattext + buf;
    }
    if (mtext && strlen(mtext))
    {
        stattext += mtext;
    }
    if (mcnt >= 0)
    {
        itoa(mcnt, buf, 10);
        stattext += buf;
    }
    if (ttext && strlen(ttext))
    {
        stattext += ttext;
    }
    m_StatusText.SetWindowText(stattext);
    return;
}

void CStatusDlg::Display(void)
{
    (void) SetActiveWindow();
    return;
}

void CStatusDlg::WinDestroy(void)
{
    (void) DestroyWindow();
    return;
}

