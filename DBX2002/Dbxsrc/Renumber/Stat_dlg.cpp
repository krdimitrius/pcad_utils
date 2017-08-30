// stat_dlg.cpp : implementation file
//

#include "stdafx.h"
#include "renumdlg.h"
#include "stat_dlg.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StatusDlg dialog

StatusDlg::StatusDlg(CWnd* pParent /*=NULL*/)
    : CDialog(StatusDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(StatusDlg)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
    
    StatusDlg::Create( StatusDlg::IDD, pParent );
    userCancelled = FALSE;
}

void StatusDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(StatusDlg)
    DDX_Control(pDX, IDPB_CANCEL, m_CancelBtn);
    DDX_Control(pDX, IDC_TEXT_STATUS, mTextStatus);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(StatusDlg, CDialog)
    //{{AFX_MSG_MAP(StatusDlg)
    ON_BN_CLICKED(IDPB_CANCEL, OnCancel)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StatusDlg message handlers

void StatusDlg::OnCancel()
{
    CWnd::DestroyWindow();
    userCancelled = TRUE;
}

// this member function is called for closing the dialog box normally
void StatusDlg::Close()
{
    CWnd::DestroyWindow();
}

void StatusDlg::InitText(const CString& Text, int Count)
{
    m_MsgText = Text;
    Update(Count);
}

void StatusDlg::Update(int Count)
{
    char buf[17];
    itoa(Count, buf, 10);
    int indx = m_MsgText.Find("(") + 1;
    m_MsgText.GetBufferSetLength(indx);
    m_MsgText += buf;
    m_MsgText += ")";
    
    SetWindowText("Renumber Components");
    mTextStatus.SetWindowText(m_MsgText);
    RECT rect;
    mTextStatus.GetWindowRect(&rect);
    mTextStatus.InvalidateRect(&rect);
    mTextStatus.UpdateWindow();
}
