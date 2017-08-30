// cmplstdl.cpp : implementation file
//

#include <assert.h>

#include "stdafx.h"
#include "renumber.h"
#include "cmplstdl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmpLstDlg dialog


CCmpLstDlg::CCmpLstDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CCmpLstDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CCmpLstDlg)
    //}}AFX_DATA_INIT
}

void CCmpLstDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCmpLstDlg)
    DDX_Control(pDX, IDST_LBHDR_TYPE, m_LBHdrType);
    DDX_Control(pDX, IDST_LBHDR_REFDES, m_LBHdrRefDes);
    DDX_Control(pDX, IDST_LBHDR_LOC, m_LBHdrLoc);
    DDX_Control(pDX, IDLB_COMPLIST, m_CompListCtl);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCmpLstDlg, CDialog)
    //{{AFX_MSG_MAP(CCmpLstDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCmpLstDlg message handlers

BOOL CCmpLstDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    if (m_ShowListBox == SHOW_COMP_LIST)
        ShowCompList();
    else
        ShowUnNumberedComps();
            
    UpdateData(FALSE);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCmpLstDlg::OnCancel()
{
    // TODO: Add extra cleanup here
    
    CDialog::OnCancel();
}

void CCmpLstDlg::OnOK()
{
    // TODO: Add extra validation here
    
    CDialog::OnOK();
}

void CCmpLstDlg::SetDialogData(ComponentList *pList, int nWhich)
{
    m_pCList = pList;
    m_ShowListBox = nWhich;
}

void CCmpLstDlg::ShowUnNumberedComps(void)
{
    SetWindowText("Un-Numbered Components");

    // calculate where the tab stops should be
    WORD dlgWidthUnits = LOWORD(GetDialogBaseUnits()) / 4;
    WORD tabStopList[2];
    tabStopList[0] = (dlgWidthUnits * 12 * 2);
    tabStopList[1] = (dlgWidthUnits * 24 * 2);
    m_CompListCtl.SetTabStops(2, (LPINT)tabStopList);
    m_CompListCtl.ResetContent();
    
    //Loop through the component list, adding each to the listbox
    for (int index = 0;  index < m_pCList->GetSize();  index++)
    {
        char buf[40];
        // Get a component from the list
        ComponentItem *p_item = (ComponentItem *)m_pCList->GetAt(index);
        assert(p_item);
        if (p_item->GetRenumberFlag() == FALSE)
        {
            CString lb_item = itoa(index, buf, 10);
            lb_item += "\t";        
            lb_item += p_item->GetRefDes();
            lb_item += "\t";        
            long x = p_item->GetRefPointValue(COORD_X_VALUE);
            lb_item += ltoa(x, buf, 10);        
            lb_item += ", ";
            long y = p_item->GetRefPointValue(COORD_Y_VALUE);
            lb_item += ltoa(y, buf, 10);        
            lb_item += "\t";        
            if (p_item->IsFlipped())
                lb_item += " BOT";
            else
                lb_item += " TOP";
            m_CompListCtl.AddString(lb_item);
        }
    }
}

void CCmpLstDlg::ShowCompList(void)
{
    SetWindowText("Component List");

    // calculate where the tab stops should be
    WORD dlgWidthUnits = LOWORD(GetDialogBaseUnits()) / 4;
    WORD tabStopList[2];
    
    // tab stop for the Type column
    tabStopList[0] = (dlgWidthUnits * 17 * 2);
    
    // tab stop for the Location column
    tabStopList[1] = (dlgWidthUnits * 36 * 2);
    m_CompListCtl.SetTabStops(2, (LPINT)tabStopList);
    m_CompListCtl.ResetContent();
    
    //Loop through the component list, adding each to the listbox
    for (int index = 0;  index < m_pCList->GetSize();  index++)
    {
        char buf[17];
        // Get a component from the list
        ComponentItem *p_item = (ComponentItem *)m_pCList->GetAt(index);
        assert(p_item);
        char    *p_refdes = p_item->GetRefDes();
        CString lb_item = p_refdes;
        lb_item += "\t";        
//        if (strlen(p_refdes) < 8)
//            lb_item += "\t";        
        char    *p_comp_type = p_item->GetCompType();
        lb_item += p_comp_type;
        lb_item += "\t";        
//        if (strlen(p_comp_type) < 8)
//            lb_item += "\t";        

        int x = (int)(p_item->GetRefPointValue(COORD_X_VALUE) / 2540);
        lb_item += itoa(x, buf, 10);        
        lb_item += ",";
        int y = (int)(p_item->GetRefPointValue(COORD_Y_VALUE) / 2540);
        lb_item += itoa(y, buf, 10);        
        m_CompListCtl.AddString(lb_item);
    }
}
