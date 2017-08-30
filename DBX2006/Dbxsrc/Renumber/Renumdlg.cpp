// dlgdlg.cpp : implementation file
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "stdafx.h"
#include "compitem.h"
#include "complist.h"
#include "rfdesitm.h"
#include "dbxutils.h"
#include "renumber.h"
#include "renumdlg.h"
#include "Dbx32.h"
#include "stat_dlg.h"
#include "cmplstdl.h"
#include "utility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DEFLT_RENUM_PASS_WIDTH   1270000L         // 500 mils

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
    //{{AFX_DATA_INIT(CAboutDlg)
    //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
    //{{AFX_MSG_MAP(CAboutDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// RenumberDlg dialog


RenumberDlg::RenumberDlg(CWnd* pParent /*=NULL*/)
    : CDialog(RenumberDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(RenumberDlg)
    //}}AFX_DATA_INIT

    // clear the list pointers
    pCompList = NULL;
    pTempRefDesList = NULL;
    pPrefsIndices = NULL;
}

RenumberDlg::~RenumberDlg(void)
{
    if (pTempRefDesList)
    {
        // delete only the items from the TempRefDes list that are not also on the pCompList
        DeleteTempRefDesList();
        delete pTempRefDesList;
    }
        
    if (pCompList)
    {
        delete pCompList;
    }
    
    if (pPrefsIndices)
    {
        delete pPrefsIndices;
    }
}

// remove each item from the TempRefDes list and find out if it exists on the master component
// list - if not, delete it
void RenumberDlg::DeleteTempRefDesList(void)
{
    int size = pTempRefDesList->GetSize();
    for(int indx = 0;  indx < size;  indx++)
    {
        ComponentItem   *p_item = (ComponentItem *) pTempRefDesList->GetAt(indx);
        assert(p_item);
        if (pCompList->FindItemPntr(p_item) == FALSE)
        {
            delete p_item;
        }
    }
    pTempRefDesList->CObArray::RemoveAll();
}

void RenumberDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(RenumberDlg)
    DDX_Control(pDX, IDST_NUMCOMPS, m_NbrComps);
    DDX_Control(pDX, IDRB_LFT_RGT_TOP_BOT, m_LftRgtTopBotBtn);
    DDX_Control(pDX, IDRB_BOT_TOP_LFT_RGT, m_BotTopLftRgtBtn);
    DDX_Control(pDX, IDRB_TOP_BOT_LFT_RGT, m_TopBotLftRgtBtn);
    DDX_Control(pDX, IDRB_LFT_RGT_BOT_TOP, m_LftRgtBotTopBtn);
    DDX_Control(pDX, IDRB_FLIPPEDOPTS_ALL, m_FlippedAllBtn);
    DDX_Control(pDX, IDRB_FLIPPEDOPTS_TOPONLY, m_FlippedTopOnlyBtn);
    DDX_Control(pDX, IDRB_FLIPPEDOPTS_TOPBOT, m_FlippedTopBotBtn);
    DDX_Control(pDX, IDRB_FLIPPEDOPTS_BOTONLY, m_FlippedBotOnlyBtn);
    DDX_Control(pDX, IDEB_START_INDEX, m_StartIndexCtl);
    DDX_Control(pDX, IDEB_PASS_WIDTH, m_PassWidthCtl);
    DDX_Control(pDX, IDPB_SET_INDEX, m_SetIndexBtn);
    DDX_Control(pDX, IDPB_SELECT_ALL, m_SelectAllBtn);
    DDX_Control(pDX, IDPB_REFRESH, m_RefreshBtn);
    DDX_Control(pDX, IDPB_CLEAR_ALL, m_ClearAllBtn);
    DDX_Control(pDX, IDPB_RENUMBER, m_RenumberBtn);
    DDX_Control(pDX, IDLB_PREFIX_INDEX, m_PrefixIndex);
    DDX_Control(pDX, IDST_DESIGN_NAME, m_DesignName);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(RenumberDlg, CDialog)
    //{{AFX_MSG_MAP(RenumberDlg)
    ON_BN_CLICKED(IDPB_CLEAR_ALL, OnClearAll)
    ON_BN_CLICKED(IDPB_RENUMBER, OnRenumber)
    ON_BN_CLICKED(IDPB_SELECT_ALL, OnSelectAll)
    ON_BN_CLICKED(IDPB_SET_INDEX, OnSetIndex)
    ON_BN_CLICKED(IDRB_LFT_RGT_BOT_TOP, OnLftRgtBotTop)
    ON_BN_CLICKED(IDRB_LFT_RGT_TOP_BOT, OnLftRgtTopBot)
    ON_BN_CLICKED(IDPB_REFRESH, OnRefresh)
    ON_COMMAND(IDM_HELP_ABOUT, OnHelpAbout)
    ON_BN_CLICKED(IDRB_BOT_TOP_LFT_RGT, OnBotTopLftRgt)
    ON_BN_CLICKED(IDRB_TOP_BOT_LFT_RGT, OnTopBotLftRgt)
    ON_BN_CLICKED(IDRB_FLIPPEDOPTS_ALL, OnFlippedOptsAll)
    ON_BN_CLICKED(IDRB_FLIPPEDOPTS_BOTONLY, OnFlippedOptsBotOnly)
    ON_BN_CLICKED(IDRB_FLIPPEDOPTS_TOPBOT, OnFlippedOptsTopBot)
    ON_BN_CLICKED(IDRB_FLIPPEDOPTS_TOPONLY, OnFlippedOptsTopOnly)
    ON_COMMAND(IDM_FILE_EXIT, OnCancel)
    ON_LBN_SELCHANGE(IDLB_PREFIX_INDEX, OnSelchangePrefixIndex)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// RenumberDlg message handlers

void RenumberDlg::OnHelpAbout()
{
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
}

void RenumberDlg::OnCancel()
{
    CDialog::OnCancel();
}

void RenumberDlg::OnFileExit()
{
    CDialog::OnCancel();
}

BOOL RenumberDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
                       
    SetWindowText("DBX Component Renumber");
    
    pCompList = NULL;
    bDesignOpen = FALSE;

    SetDefaults();    
    
    if (OpenDesign())
    {
        GetSelectedComponents();
    }
    EnableButtons();
                
    return TRUE;  // return TRUE  unless you set the focus to a control
}   // RenumberDlg::OnInitDialog()

void RenumberDlg::SetDefaults(void)
{
    nSelComps = 0;      // Number of components selected
    nTopComps = 0;
    nBotComps = 0;
    userQuit = FALSE;
    if (pCompList)
    {
        pCompList->RemoveAll();
    }
    else
    {
        pCompList = new ComponentList;
        assert(pCompList);
    }

    CheckRadioButton(IDRB_LFT_RGT_TOP_BOT, IDRB_LFT_RGT_BOT_TOP, IDRB_LFT_RGT_TOP_BOT);
    nFlippedOption = ALL_COMPS;
    nCurrentSide = nLastSide = TOP_SIDE;
    m_FlippedAllBtn.SetCheck(RADIO_BTN_ON);
    m_FlippedTopOnlyBtn.SetCheck(RADIO_BTN_OFF);
    m_FlippedTopBotBtn.SetCheck(RADIO_BTN_OFF);
    m_FlippedBotOnlyBtn.SetCheck(RADIO_BTN_OFF);
    nRenameDirect = LR_DOWN;
    lPassWidth = DEFLT_RENUM_PASS_WIDTH;
    lPassWidthMils = DEFLT_RENUM_PASS_WIDTH / 2540;
    char buf[33];
    m_PassWidthCtl.SetWindowText(ltoa(lPassWidthMils, buf, 10));   // set the pass width in mils
    m_StartIndexCtl.LimitText(4);
    m_PrefixIndex.SetTabStops(32);
}   // RenumberDlg::SetDefaults()

void RenumberDlg::OnRenumber()
{
    if (nSelComps > 0  &&  IsValidPassWidth())
    {
        PrepareOperation();
        RenumberComponents();
        if (nTempRefDes > 0  &&  tStatus == DBX_OK  &&  !userQuit)
        {
            ShowTempRefDesList();
        }
    }
    if (IsIconic())
    {
        ShowWindow(SW_SHOWNORMAL);
    }
}

void RenumberDlg::PrepareOperation(void)
{
    if (m_FlippedAllBtn.GetCheck())
    {
        OnFlippedOptsAll();
        pCompList->ResetFlags(ALL_COMPS);
    }
    else if (m_FlippedTopOnlyBtn.GetCheck())
    {
        OnFlippedOptsTopOnly();
        pCompList->ResetFlags(TOP_ONLY);
    }
    else if (m_FlippedTopBotBtn.GetCheck())
    {
        OnFlippedOptsTopBot();
        pCompList->ResetFlags(TOP_BOTTOM);
    }
    else
    {
        OnFlippedOptsBotOnly();
        pCompList->ResetFlags(BOTTOM_ONLY);
    }
}

void RenumberDlg::ShowTempRefDesList(void)
{
    CCmpLstDlg dlg;
    dlg.SetDialogData(pTempRefDesList, SHOW_COMP_LIST);
    dlg.DoModal();
}

// this member function is called when the user changes the PrefixIndex listbox selection
void RenumberDlg::OnSelchangePrefixIndex()
{
    if (m_PrefixIndex.GetSelCount() > 0)
    {
        m_StartIndexCtl.SetFocus();
    }
}

// this member function is called when the user clicks the Clear All button to clear all
// selections in the PrefixIndex listbox
void RenumberDlg::OnClearAll()
{
    // Clear all of the Prefixes in the list box
    m_PrefixIndex.SetSel(-1, FALSE);
}

// this member function is called when the user clicks the Select All button to select all
// of the items in the PrefixIndex listbox
void RenumberDlg::OnSelectAll()
{
    // Select all of the nets in the list box
    m_PrefixIndex.SetSel(-1, TRUE);
    m_StartIndexCtl.SetFocus();
}

// this member function is called when the user clicks the Set Indices button to set start
// indices for items in the PrefixIndex listbox
void RenumberDlg::OnSetIndex()
{
    if (IsValidStartIndex())
    {
        CString start_index;
        m_StartIndexCtl.GetWindowText(start_index);
        int     st_indx_int = atoi((const char *)start_index);
        int     *p_selitems=NULL;    
        int     n_selcount = m_PrefixIndex.GetSelCount();
        if (n_selcount > 0)
        {
            p_selitems = new int[n_selcount];
            assert(p_selitems);
        
            m_PrefixIndex.GetSelItems(n_selcount, p_selitems);
            CString pref_str, old_pref_str;
            for (int indx = 0;  indx < n_selcount;  indx++)
            {
                m_PrefixIndex.GetText(p_selitems[indx], old_pref_str);
                pref_str = old_pref_str;                                                            
                                                            
                // now update the starting & working indices in the list
                int pref_ndx = pref_str.Find("\t");
                pref_str.GetBufferSetLength(pref_ndx);
                RefDesItem *p_refdes_item = (RefDesItem *)pPrefsIndices->Find(pref_str);
                assert(p_refdes_item);
                int work_index = p_refdes_item->GetWorkIndex();
                if (st_indx_int < work_index)
                {
                    int mb_ans = AfxMessageBox(IDS_START_INDEX_WARN, MB_YESNO | MB_ICONQUESTION);
                    if (mb_ans == IDNO)
                    {
                        break;
                    }
                }
                p_refdes_item->SetStartIndex(st_indx_int);

                // now modify the string with the new start index and put it back
                // into the listbox
                m_PrefixIndex.DeleteString(p_selitems[indx]);
                FormatLBStr(pref_str, start_index);
                m_PrefixIndex.InsertString(p_selitems[indx], pref_str);
            }
            
            delete p_selitems;
        }
    }
}   // RenumberDlg::OnSetIndex()

BOOL RenumberDlg::IsValidStartIndex()
{
    UpdateData(TRUE);
    
    char value[8];
    m_StartIndexCtl.GetWindowText(value, 4);
    if (strlen(value) > 4)
    {
        AfxMessageBox("Too many characters");
        value[4] = 0;   
        m_StartIndexCtl.SetWindowText(value);
        return FALSE;
    }
    else if (strlen(value) > 0)
    {
        int ndx;
        if ((ndx = strspn(value, "0123456789")) == 0)
        {
            AfxMessageBox("Invalid character");
            value[ndx] = 0;   
            m_StartIndexCtl.SetWindowText(value);
            return FALSE;
        }
    }
    return TRUE;
}

void RenumberDlg::OnLftRgtBotTop()
{
    nRenameDirect = LR_UP;
    m_LftRgtTopBotBtn.SetCheck(RADIO_BTN_OFF);
    m_BotTopLftRgtBtn.SetCheck(RADIO_BTN_OFF);
    m_TopBotLftRgtBtn.SetCheck(RADIO_BTN_OFF);
    m_LftRgtBotTopBtn.SetCheck(RADIO_BTN_ON);
    listSorted = FALSE;
}

void RenumberDlg::OnLftRgtTopBot()
{
    nRenameDirect = LR_DOWN;
    m_LftRgtTopBotBtn.SetCheck(RADIO_BTN_ON);
    m_BotTopLftRgtBtn.SetCheck(RADIO_BTN_OFF);
    m_TopBotLftRgtBtn.SetCheck(RADIO_BTN_OFF);
    m_LftRgtBotTopBtn.SetCheck(RADIO_BTN_OFF);
    listSorted = FALSE;
}

void RenumberDlg::OnBotTopLftRgt()
{
    nRenameDirect = UP_LR;
    m_LftRgtTopBotBtn.SetCheck(RADIO_BTN_OFF);
    m_BotTopLftRgtBtn.SetCheck(RADIO_BTN_ON);
    m_TopBotLftRgtBtn.SetCheck(RADIO_BTN_OFF);
    m_LftRgtBotTopBtn.SetCheck(RADIO_BTN_OFF);
    listSorted = FALSE;
}

void RenumberDlg::OnTopBotLftRgt()
{
    nRenameDirect = DOWN_LR;
    m_LftRgtTopBotBtn.SetCheck(RADIO_BTN_OFF);
    m_BotTopLftRgtBtn.SetCheck(RADIO_BTN_OFF);
    m_TopBotLftRgtBtn.SetCheck(RADIO_BTN_ON);
    m_LftRgtBotTopBtn.SetCheck(RADIO_BTN_OFF);
    listSorted = FALSE;
}

// this member function is called when the user clicks the Refresh button to refresh the
// contents of the PrefixIndex listbox
void RenumberDlg::OnRefresh()
{
    SetDefaults();    
    GetSelectedComponents();
    EnableButtons();
}

void RenumberDlg::OnFlippedOptsAll(void)
{
    nFlippedOption = ALL_COMPS;
    nCurrentSide = nLastSide = TOP_SIDE;
    nTopComps = nSelComps;
    m_FlippedAllBtn.SetCheck(RADIO_BTN_ON);
    m_FlippedTopOnlyBtn.SetCheck(RADIO_BTN_OFF);
    m_FlippedTopBotBtn.SetCheck(RADIO_BTN_OFF);
    m_FlippedBotOnlyBtn.SetCheck(RADIO_BTN_OFF);
//    pPrefsIndices->SetStartIndices(1);
    UpdateDialogControls();
}

void RenumberDlg::OnFlippedOptsBotOnly(void)
{
    if (nFlippedOption != BOTTOM_ONLY)
    {
        nCurrentSide = nLastSide = BOTTOM_SIDE;
        nTopComps = nBotComps;
        m_FlippedAllBtn.SetCheck(RADIO_BTN_OFF);
        m_FlippedTopOnlyBtn.SetCheck(RADIO_BTN_OFF);
        m_FlippedTopBotBtn.SetCheck(RADIO_BTN_OFF);
        m_FlippedBotOnlyBtn.SetCheck(RADIO_BTN_ON);
        if (nLastRenumOperation == TOP_ONLY)
        {
            pPrefsIndices->UpdateStartIndices();
            UpdateDialogControls();
        }
        nFlippedOption = BOTTOM_ONLY;
    }
}

void RenumberDlg::OnFlippedOptsTopBot(void)
{
    nFlippedOption = TOP_BOTTOM;
    nCurrentSide = TOP_SIDE;
    nLastSide = BOTTOM_SIDE;
    nTopComps = nSelComps - nBotComps;
    m_FlippedAllBtn.SetCheck(RADIO_BTN_OFF);
    m_FlippedTopOnlyBtn.SetCheck(RADIO_BTN_OFF);
    m_FlippedTopBotBtn.SetCheck(RADIO_BTN_ON);
    m_FlippedBotOnlyBtn.SetCheck(RADIO_BTN_OFF);
//    pPrefsIndices->SetStartIndices(1);
    UpdateDialogControls();
}

void RenumberDlg::OnFlippedOptsTopOnly(void)
{
    if (nFlippedOption != TOP_ONLY)
    {
        nCurrentSide = nLastSide = TOP_SIDE;
        nTopComps = nSelComps - nBotComps;
        m_FlippedAllBtn.SetCheck(RADIO_BTN_OFF);
        m_FlippedTopOnlyBtn.SetCheck(RADIO_BTN_ON);
        m_FlippedTopBotBtn.SetCheck(RADIO_BTN_OFF);
        m_FlippedBotOnlyBtn.SetCheck(RADIO_BTN_OFF);

        // if the 
        if (nLastRenumOperation == BOTTOM_ONLY)
        {
            pPrefsIndices->UpdateStartIndices();
            UpdateDialogControls();
        }
        nFlippedOption = TOP_ONLY;
    }
}

/////////////////////////////////////////////////////////////////////////////
// RenumberDlg helper functions

BOOL RenumberDlg::OpenDesign(void)
{
    if (bDesignOpen)
        return bDesignOpen;
        
    tStatus = TOpenDesign( DBX_LANGUAGE, DBX_VERSION, "", &tContext);
    if (tStatus == DBX_OK)
    {
        tStatus = TGetDesignInfo( &tContext, &tDesignInfo );
        if (tStatus == DBX_OK)
        {
            bDesignOpen = TRUE;
            CString design_name = tDesignInfo.designName;
            m_DesignName.SetWindowText(design_name.Mid( design_name.ReverseFind( '\\' ) + 1));
        }
        else
        {
            char errbuf[80];
            strcpy(errbuf, "ERROR: ");
            Error_Message_Return (tStatus, &errbuf[7], 73);
            AfxMessageBox(errbuf);
        }
    }
    else
    {
        char errbuf[80];
        strcpy(errbuf, "ERROR: ");
        Error_Message_Return (tStatus, &errbuf[7], 73);
        AfxMessageBox(errbuf);
    }
    return bDesignOpen;
}

void RenumberDlg::EnableButtons()
{
    if (nSelComps == 0)
    {
        m_RenumberBtn.EnableWindow(FALSE);
        m_SetIndexBtn.EnableWindow(FALSE);
        m_SelectAllBtn.EnableWindow(FALSE);
        m_ClearAllBtn.EnableWindow(FALSE);
        m_FlippedAllBtn.EnableWindow(FALSE);
        m_FlippedTopOnlyBtn.EnableWindow(FALSE);
        m_FlippedTopBotBtn.EnableWindow(FALSE);
        m_FlippedBotOnlyBtn.EnableWindow(FALSE);
        m_LftRgtTopBotBtn.EnableWindow(FALSE);
        m_LftRgtBotTopBtn.EnableWindow(FALSE);
        m_TopBotLftRgtBtn.EnableWindow(FALSE);
        m_BotTopLftRgtBtn.EnableWindow(FALSE);
    }
    else
    {
        m_RenumberBtn.EnableWindow(TRUE);
        m_SetIndexBtn.EnableWindow(TRUE);
        m_SelectAllBtn.EnableWindow(TRUE);
        m_ClearAllBtn.EnableWindow(TRUE);
        m_FlippedAllBtn.EnableWindow(TRUE);
        m_FlippedTopOnlyBtn.EnableWindow(TRUE);
        m_FlippedTopBotBtn.EnableWindow(TRUE);
        m_FlippedBotOnlyBtn.EnableWindow(TRUE);
        m_LftRgtTopBotBtn.EnableWindow(TRUE);
        m_LftRgtBotTopBtn.EnableWindow(TRUE);
        m_TopBotLftRgtBtn.EnableWindow(TRUE);
        m_BotTopLftRgtBtn.EnableWindow(TRUE);
        m_FlippedAllBtn.SetCheck(TRUE);

        char numcomps_buf[60];
        itoa(nSelComps, numcomps_buf, 10);
        strcat(numcomps_buf, " Components");
        m_NbrComps.SetWindowText(numcomps_buf);
    }
}

void RenumberDlg::GetSelectedComponents(void)
{
    if (!OpenDesign())
        return;

    // this list keeps track of RefDes prefixes, start indices, and work indices
    pPrefsIndices = new RefDesList;
    assert(pPrefsIndices);
        
    StatusDlg status_dlg;
    status_dlg.InitText("Reading selected components ()");

    lMinRefPointX = LONG_MAX;
    lMinRefPointY = LONG_MAX;
    lMaxRefPointX = 0;
    lMaxRefPointY = 0;

    TItem selected_item;
    tStatus = TGetFirstSelectedItem(&tContext, &selected_item);
    while (tStatus == DBX_OK  &&  !status_dlg.userCancelled)
    {
        if (selected_item.itemType == DBX_COMPONENT)
        {
            nSelComps++;
            lMinRefPointX = min(lMinRefPointX, selected_item.component.refPoint.x);
            lMinRefPointY = min(lMinRefPointY, selected_item.component.refPoint.y);
            lMaxRefPointX = max(lMaxRefPointX, selected_item.component.refPoint.x);
            lMaxRefPointY = max(lMaxRefPointY, selected_item.component.refPoint.y);

            // if component is flipped, update the flipped component counter
            if (selected_item.component.isFlipped != 0)
                nBotComps++;

            ComponentItem *p_newitem = new ComponentItem(&selected_item.component);
            pCompList->Add(p_newitem);
            p_newitem->SetRenumberFlag(FALSE);
            // count the unique refDes prefixes
            char refdes[DBX_MAX_NAME_LEN];
            strcpy(refdes, selected_item.component.refDes);
            char *ndx = strpbrk(refdes, "0123456789");
            assert(ndx);
            *ndx = '\0';
            if (pPrefsIndices->Find(refdes) == NULL)
            {
                pPrefsIndices->AddTail(new RefDesItem(refdes));

                // update the status dialog
                if (!IsIconic())
                {
                    status_dlg.Update(nSelComps);
                }
            }
        }
        tStatus = TGetNextSelectedItem(&tContext, &selected_item);
    }

    if (tStatus != DBX_NO_MORE_ITEMS  &&  !status_dlg.userCancelled)
    {
        char errbuf[80];
        strcpy(errbuf, "ERROR: ");
        Error_Message_Return (tStatus, &errbuf[7], 73);
        AfxMessageBox(errbuf);
    }
    else
    {
        tStatus = DBX_OK;
        if (!nSelComps)
        {
            AfxMessageBox("ERROR: No components selected");
        }
        else if (status_dlg.userCancelled)
        {
            nSelComps = 0;      // Number of components selected
        }
        else
        {
            // Close the status dialog box
            status_dlg.Close();
            UpdateDialogControls();
        }
    }

    listSorted = FALSE;

    // TEMP CODE - USED FOR DEBUGGING
//    if (nSelComps > 0)
//    {
//        CCmpLstDlg dlg;
//        dlg.SetDialogData(pCompList, SHOW_COMP_LIST);
//        dlg.DoModal();
//    }
    // END TEMP CODE
    
    // close the design
    bDesignOpen = FALSE;
    tStatus = TCloseDesign(&tContext, "");
}   // RenumberDlg::GetSelectedComponents()

void RenumberDlg::UpdateDialogControls(void)
{
    // clear the Prefix-Index listbox
    m_PrefixIndex.ResetContent();

    for(int ndx = 0;  ndx < pPrefsIndices->GetCount();  ndx++)
    {
        char buf[17];
        // add this prefix to the Prefix/Index listbox
        POSITION pos = pPrefsIndices->FindIndex(ndx);
        RefDesItem *p_refdes_item = (RefDesItem *)pPrefsIndices->GetAt(pos);
        CString prefix = p_refdes_item->GetRefDesPref();
        CString start_index = itoa(p_refdes_item->GetStartIndex(), buf, 10);
        FormatLBStr(prefix, start_index);
        m_PrefixIndex.AddString(prefix);
    }
}   // RenumberDlg::UpdateDialogControls()

void RenumberDlg::RenumberComponents(void)
{
    if (!OpenDesign())
        return;

    // sort the component list for vertical or horizontal rename passes
    SortComponents();
    if (!listSorted)        // if user didn't allow sort to complete, return to the dialog
        return;

    nRenComps = 0;
    StatusDlg status_dlg;
    status_dlg.InitText("Renumbering selected components ()");

    // prepare a list for components which may have to be given temporary refDes's
    nTempRefDes = 0;    // Number of components with temporary refDes's
    pTempRefDesList = new ComponentList;

    // reset the work indices for each prefix to the start index for that prefix
    pPrefsIndices->ResetWorkIndices();

    int n_this_side = nTopComps;
    BOOL    done = FALSE;
    do
    {
        InitRenumParameters();
        while(n_this_side > 0  &&  tStatus == DBX_OK)
        {
            for(int indx = 0;  tStatus == DBX_OK && indx < nSelComps && n_this_side > 0;  indx++)
            {
                // Get a component from the list
                ComponentItem *p_item = (ComponentItem *) (*pCompList)[indx];
                assert(p_item);
                // TEMP CODE - USED FOR DEBUGGING
//                char *ref_des = p_item->GetRefDes();
                // END TEMP CODE
                
                if ((IsCompInThisPass(p_item)) == TRUE)
                {
                    ModifyComponentRefDes(p_item);
                    if (tStatus == DBX_OK)
                    {
                        n_this_side--;
                        nRenComps++;
                        p_item->SetRenumberFlag(TRUE);
                        if ((nRenComps % 3) == 0  &&  !IsIconic())
                        {
                            status_dlg.Update(nRenComps);
                        }
                    }
                }
                if (status_dlg.userCancelled)
                {
                    int ans = AfxMessageBox(IDS_RENUM_NOTDONE_WARN, MB_YESNO | MB_ICONQUESTION);
                    if (ans == IDYES)
                    {
                        n_this_side = 0;
                        userQuit = TRUE;
                    }
                    else
                    {
                        status_dlg.userCancelled = FALSE;
                    }
                }
            }   // for(int indx
    
            if (n_this_side > 0)
            {
                SetNextPass();
            }

            // TEMP CODE - USED FOR DEBUGGING
//            CCmpLstDlg dlg;
//            dlg.SetDialogData(pCompList, SHOW_UNNUM_LIST);
//            dlg.DoModal();
            // END TEMP CODE
        }   // while(n_selcomps > 0
        
        // we're done after the bottom side is renumbered
        done = (nCurrentSide == nLastSide  ||  status_dlg.userCancelled);
        nCurrentSide = nLastSide;
        n_this_side = nBotComps;
    }   while(tStatus == DBX_OK  &&  !done);
    
    if (!status_dlg.userCancelled)
    {
        // Close the status dialog box
        status_dlg.Close();
        
        // we need to remember what the last operation was
        nLastRenumOperation = nFlippedOption;
    }
    
    bDesignOpen = FALSE;
    tStatus = TCloseDesign(&tContext, "");
}   // RenumberDlg::RenumberComponents()

// sort the component list for vertical or horizontal rename passes
void RenumberDlg::SortComponents(void)
{
    if (listSorted)
        return;
        
    // check system correctness
    assert(pCompList->GetSize() == nSelComps);

    // the sort key is dependent on the Rename Direction specified by the user such that if the
    // user has requested a vertical rename (i.e., Top to Bottom, Left to Right), we sort on the
    // component refPoint X value and delimit each pass on the refPoint Y value

    nSortKey = (nRenameDirect == LR_DOWN || nRenameDirect == LR_UP) ? COORD_X_VALUE : COORD_Y_VALUE;
    // the pass delimiter is the opposite of the sort key
    nPassKey = (nRenameDirect == LR_DOWN || nRenameDirect == LR_UP) ? COORD_Y_VALUE : COORD_X_VALUE;

    StatusDlg status_dlg;
    status_dlg.InitText("Sorting components list ()");

    for(int indx = 0;  indx < nSelComps;  indx++)
    {
        ComponentItem *p_item_j;
        ComponentItem *p_item_m;
        p_item_m = (ComponentItem *)pCompList->GetAt(indx);
        assert(p_item_m);
        
        int min = indx;
        for(int jndx = indx+1;  jndx < nSelComps;  jndx++)
        {
            // Compare component refPoints
            p_item_j = (ComponentItem *)pCompList->GetAt(jndx);
            assert(p_item_j);
            switch(nRenameDirect)
            {
                case LR_DOWN:
                {
                    long refpt_j = p_item_j->GetRefPointValue(nSortKey);
                    long refpt_m = p_item_m->GetRefPointValue(nSortKey);
                    if (p_item_j->GetRefPointValue(nSortKey) < p_item_m->GetRefPointValue(nSortKey))
                    {
                        min = jndx;
                        p_item_m = p_item_j;
                    }
                    break;
                }
                case DOWN_LR:
                {
                    if (p_item_j->GetRefPointValue(nSortKey) > p_item_m->GetRefPointValue(nSortKey))
                    {
                        min = jndx;
                        p_item_m = p_item_j;
                    }
                    break;
                }
                case LR_UP:
                {
                    if (p_item_j->GetRefPointValue(nSortKey) < p_item_m->GetRefPointValue(nSortKey))
                    {
                        min = jndx;
                        p_item_m = p_item_j;
                    }
                    break;
                }
                case UP_LR:
                {
                    if (p_item_j->GetRefPointValue(nSortKey) < p_item_m->GetRefPointValue(nSortKey))
                    {
                        min = jndx;
                        p_item_m = p_item_j;
                    }
                    break;
                }
            }   // switch
        }   // for(int jndx

        // now swap the two elements
        p_item_j = (ComponentItem *)pCompList->GetAt(indx);
        assert(p_item_j);
        pCompList->SetAt(indx, p_item_m); 
        pCompList->SetAt(min, p_item_j); 

        if (status_dlg.userCancelled)
        {
            return;
        }
        if ((indx % 3) == 0)                  
        {
            status_dlg.Update(indx);
        }
    }   // for(int indx
    listSorted = TRUE;

    // TEMP CODE - USED FOR DEBUGGING
//    CCmpLstDlg dlg;
//    dlg.SetDialogData(pCompList, SHOW_UNNUM_LIST);
//    dlg.DoModal();
}

void RenumberDlg::InitRenumParameters(void)
{
    // init the pass control parameters
    switch(nRenameDirect)
    {
        case LR_DOWN:
        {
            lPassStart = lMaxRefPointY;
            lPassEnd = lPassStart - lPassWidth;
            break;
        }
        case DOWN_LR:
        case UP_LR:
        {
            lPassStart = lMinRefPointX;
            lPassEnd = lPassStart + lPassWidth;
            break;
        }
        case LR_UP:
        {
            lPassStart = lMinRefPointY;
            lPassEnd = lPassStart + lPassWidth;
            break;
        }
    }
}    

void RenumberDlg::SetNextPass(void)
{
    lPassStart = lPassEnd;
    switch(nRenameDirect)
    {
        case LR_DOWN:
        {
            lPassEnd -= lPassWidth;
            if (lPassEnd < lMinRefPointY)
                lPassEnd = lMinRefPointY;
            break;
        }
        case DOWN_LR:
        case UP_LR:
        {
            lPassEnd += lPassWidth;
            if (lPassEnd > lMaxRefPointX)
                lPassEnd = lMaxRefPointX;
            break;
        }
        case LR_UP:
        {
            lPassEnd += lPassWidth;
            if (lPassEnd > lMaxRefPointY)
                lPassEnd = lMaxRefPointY;
            break;
        }
    }
}    

BOOL RenumberDlg::IsCompInThisPass(ComponentItem *pCompItem)
{
    // TEMP CODE - USED FOR DEBUGGING
//    char *ref_des = pCompItem->GetRefDes();
    // END TEMP CODE
    // has this component already been renumbered?
    if (pCompItem->GetRenumberFlag() == FALSE)
    {
        // if component is flipped, check our flippedness mode
        if (pCompItem->IsFlipped())
        {
            if ((nFlippedOption == TOP_BOTTOM  &&  nCurrentSide == TOP_SIDE)  ||
                 nFlippedOption == TOP_ONLY)
                return FALSE;
        }
        else
        {
            // component is on top side of board (not flipped)
            if ((nFlippedOption == TOP_BOTTOM  &&  nCurrentSide == BOTTOM_SIDE)  ||
                 nFlippedOption == BOTTOM_ONLY)
                return FALSE;
        }

        long refpt = pCompItem->GetRefPointValue(nPassKey);
        // LR_DOWN - from smallest to largest X, largest to smallest Y
        // DOWN_LR - from largest to smallest Y, smallest to largest X
        // LR_UP - smallest to largest X, smallest to largest Y
        // UP_LR - smallest to largest Y, smallest to largest X
        if (nRenameDirect == LR_DOWN)
        {
            return (lPassStart >= refpt  &&  refpt >= lPassEnd);
        }
        else
            return (refpt >= lPassStart  &&  refpt <= lPassEnd);
    }
    return FALSE;
}   // RenumberDlg::IsCompInThisPass()

void RenumberDlg::ModifyComponentRefDes(ComponentItem *pCompItem)
{
    // now modify the refdes - first, check if this component has a question mark
    // in its refDes - if so, remove it from the pTempRefDesList
    char old_refdes[DBX_MAX_NAME_LEN];
    strcpy(old_refdes, pCompItem->GetRefDes());
    if (strchr(old_refdes, '_'))
        RemoveTempRefDesComp(old_refdes);   // remove component from temp refdes list

    char *new_refdes = GetNewRefDes(old_refdes);
    // If there is already a component by this name (new_refdes), rename it to a 
    // temporary refDes so that we can give the current component 'pCompItem' its refDes.
    // When we encounter the component with the temporary refDes, we'll give it a real
    // new refDes.
    EliminateDuplicateRefDes(new_refdes, pCompItem);

    // set the component's refDes to the new one and send the modify command
    pCompItem->SetRefDes(new_refdes);
    TComponent      *p_comp = pCompItem->GetComponent();
    assert(p_comp);         // should never fire
    tStatus = TModifyComponent(&tContext, p_comp);
    if (tStatus != DBX_OK)
    {
        char errbuf[80];
        strcpy(errbuf, "ERROR: ");
        Error_Message_Return (tStatus, &errbuf[7], 73);
        AfxMessageBox(errbuf);
    }
    delete new_refdes;
}   // RenumberDlg::ModifyComponentRefDes()

char * RenumberDlg::GetNewRefDes(char *pOldRefDes)
{
    // calling function is responsible for deleting this memory object
    char *p_new_refdes = new char[DBX_MAX_NAME_LEN];
    assert(p_new_refdes);
    
    strcpy(p_new_refdes, pOldRefDes);
    char *ndx_ptr = strpbrk(p_new_refdes, "0123456789");
    *ndx_ptr = '\0';
    RefDesItem *p_item = (RefDesItem *)pPrefsIndices->Find(p_new_refdes);
    assert(p_item);
    char buf[17];
    strcat(p_new_refdes, itoa(p_item->GetWorkIndex(), buf, 10));
    p_item->IncrementWorkIndex();
    return p_new_refdes;
}   // RenumberDlg::GetNewRefDes()

// This member searches for components with the specified 'refDes' - if one is found,
// it is given a temporary refDes and added to the pTempRefDesList
void RenumberDlg::EliminateDuplicateRefDes(char *pRefDes, ComponentItem *pCompItem)
{
    TComponent  comp;
    tStatus = TGetCompByRefDes(&tContext, pRefDes, &comp);
    if (tStatus == DBX_OK  &&  comp.compId != pCompItem->GetCompId())
    {
        // now find this component item in the master list
        ComponentItem *p_item = (ComponentItem *)pCompList->FindItemById(comp.compId);
        if (p_item == NULL)
        {
            // the ComponentItem for this component not in our master list - create it
            p_item = new ComponentItem(&comp);
        }
        TComponent      *p_comp = p_item->GetComponent();
        assert(p_comp);         // should never fire

        char temp_refdes[DBX_MAX_NAME_LEN];
        int temp_index = 0;
        strcpy(temp_refdes, pRefDes);
        strcat(temp_refdes, "_");
        do
        {
            char    buf[17];
            temp_index++;
            strcat(temp_refdes, itoa(temp_index, buf, 10));
            
            p_item->SetRefDes(temp_refdes);
            tStatus = TModifyComponent(&tContext, p_comp);
            if (tStatus == DBX_OK)
            {
                nTempRefDes++;    // Number of components with temporary refDes's
                pTempRefDesList->Add(p_item);
            }
            else if (tStatus != DBX_DUPLICATE_REFDES)
            {
                char errbuf[80];
                strcpy(errbuf, "ERROR: ");
                Error_Message_Return (tStatus, &errbuf[7], 73);
                AfxMessageBox(errbuf);
            }
        }   while(tStatus == DBX_DUPLICATE_REFDES);
    }
    else if (tStatus != DBX_OK  &&  tStatus != DBX_ITEM_NOT_FOUND)
    {
        char errbuf[80];
        strcpy(errbuf, "ERROR: ");
        Error_Message_Return (tStatus, &errbuf[7], 73);
        AfxMessageBox(errbuf);
    }
}   // RenumberDlg::EliminateDuplicateRefDes()

void RenumberDlg::RemoveTempRefDesComp(char *pTempRefDes)
{
    for(int indx = 0;  indx < nTempRefDes;  indx++)
    {
        // Get a component from the list
        ComponentItem *p_item = (ComponentItem *) (*pTempRefDesList)[indx];
        assert(p_item);
        char *p_refdes = p_item->GetRefDes();
        assert(p_refdes);
        if (strcmp(p_refdes, pTempRefDes) == 0)
        {
            pTempRefDesList->RemoveAt(indx);
            nTempRefDes--;    // Number of components with temporary refDes's
            break;
        }
    }
}   // RenumberDlg::RemoveTempRefDesComp()

BOOL RenumberDlg::IsValidPassWidth()
{
    UpdateData(TRUE);
    
    char ctl_text[80];
    m_PassWidthCtl.GetWindowText(ctl_text, 79);
    if (strlen(ctl_text) > 4)
    {
        AfxMessageBox("Too many characters - maximum entry = 9999");
        ctl_text[4] = 0;   
        m_PassWidthCtl.SetWindowText(ctl_text);
        m_PassWidthCtl.SetFocus();
        return FALSE;
    }
    else if (strlen(ctl_text) > 0)
    {
        int ndx;
        if ((ndx = strspn(ctl_text, "0123456789")) == 0)
        {
            AfxMessageBox("Entry must be numeric");
            ctl_text[ndx] = 0;   
            m_PassWidthCtl.SetWindowText(ctl_text);
            m_PassWidthCtl.SetFocus();
            return FALSE;
        }
        else
        {
            int passwidth = atoi(ctl_text);
            if (passwidth < 1)
            {
                AfxMessageBox("Entry must be greater than 0");
                m_PassWidthCtl.SetWindowText("");
                m_PassWidthCtl.SetFocus();
                return FALSE;
            }
            else
            {
                lPassWidthMils = passwidth;
                lPassWidth = lPassWidthMils * 2540;
            }
        }
    }
    return TRUE;
}

