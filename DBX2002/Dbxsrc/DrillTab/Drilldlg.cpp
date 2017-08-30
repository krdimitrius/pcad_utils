// drilldlg.cpp : implementation file
//

#include "stdafx.h"
#include "stdlib.h"
#include "dbxutils.h"
#include "dtutils.h"
#include "drilltab.h"
#include "drilldlg.h"
#include "fstream.h"
#include "math.h"
#include "statdlg.h"
#include "aboutdlg.h"

#ifdef _DEBUG
// #define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrilltabDlg dialog

CDrilltabDlg::CDrilltabDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CDrilltabDlg::IDD, pParent),
      m_tStatus(DBX_OK),
      m_DsgnIsOpen(FALSE),
      m_WarnedNoSym(FALSE),
      m_DbLineWidth(0),
      m_DbX(0),
      m_DbY(0)
{
    //{{AFX_DATA_INIT(CDrilltabDlg)
    //}}AFX_DATA_INIT
    // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
    m_hIcon = AfxGetApp()->LoadIcon(IDI_DRILLTAB1);
}

CDrilltabDlg::~CDrilltabDlg()
{
    if (m_hIcon)
    {
        DestroyIcon(m_hIcon);
    }
}

void CDrilltabDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDrilltabDlg)
    DDX_Control(pDX, IDRB_LOCLOWLEFT, m_LocLowLeft);
    DDX_Control(pDX, IDRB_HDUNITSIN, m_UnitsInch);
    DDX_Control(pDX, IDEB_YLOC, m_Y);
    DDX_Control(pDX, IDEB_XLOC, m_X);
    DDX_Control(pDX, IDEB_TITLE, m_Title);
    DDX_Control(pDX, IDEB_LINEWIDTH, m_LineWidth);
    DDX_Control(pDX, IDEB_COLMINWIDTH, m_ColumnWidth);
    DDX_Control(pDX, IDEB_COLLABEL, m_ColumnLabel);
    DDX_Control(pDX, IDCB_TEXTSTYLE, m_TextStyle);
    DDX_Control(pDX, IDCB_LAYER, m_Layer);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrilltabDlg, CDialog)
    //{{AFX_MSG_MAP(CDrilltabDlg)
    ON_COMMAND(IDM_FILE_EXIT,  OnFileExit)
    ON_COMMAND(IDM_HELP_ABOUT, OnHelpAbout)
    ON_BN_CLICKED(IDPB_OK, OnOk)
    ON_BN_CLICKED(IDPB_COLDELETE, OnColumnDel)
    ON_BN_CLICKED(IDPB_COLADD, OnColumnAdd)
    ON_BN_CLICKED(IDRB_HDUNITSIN, OnHdunitsin)
    ON_BN_CLICKED(IDRB_HDUNITSMM, OnHdunitsmm)
    //}}AFX_MSG_MAP
    ON_CONTROL(HGN_RECCHANGED, IDGR_DTPREVIEW, OnRecchangedGrid)
    ON_CONTROL(HGN_SELCHANGE, IDGR_DTPREVIEW, OnSelchangeGrid)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrilltabDlg message handlers

//
// Dialog initialization
//
BOOL CDrilltabDlg::OnInitDialog()
{
    int         i;
    int         statcnt = 0;
    BOOL        statisopen = FALSE;
    char        buf[8];
    char        errormsg[128];
    CString     stattext;
    TLayer      layerobj;
    TTextStyle  tstyleobj;
    BOOL        enddlg = FALSE;

    *errormsg = 0;

    //
    // Perform the default initialization of the dialog.
    CDialog::OnInitDialog();

    // Initialize the dialog's caption.
    SetWindowText("Drill Symbol Table");

    // Initialize WinWidgets grid HWND member variable
    m_Grid = ::GetDlgItem(GetSafeHwnd(), IDGR_DTPREVIEW);

    // Grid control communication is performed via Windows messaging prototypes
    ::SendMessage(m_Grid, HGM_SETSTYLE, TRUE, (long) HES_EXTRUDE);
                                          
    // Initialize default line width
    m_LineWidth.LimitText(15);
    m_LineWidth.SetWindowText("10.0mil");

    // Initialize default location (1000, 1000) lower left
    m_X.LimitText(15);
    m_Y.LimitText(15);
    m_X.SetWindowText("1000");
    m_Y.SetWindowText("1000");
    m_LocLowLeft.SetCheck(1);

    // Initialize default hole dia units inch
    // Column head text (Hole Dia (inch)) initialized in grid resource def
    m_UnitsInch.SetCheck(1);

    // Initialize default title
    m_Title.LimitText(63);
    m_Title.SetWindowText("Drill Symbol Table");

    // Column label and min column width
    m_ColumnLabel.LimitText(63);
    m_ColumnWidth.LimitText(2);

    // Initialize min column widths of first three static grid columns
    (void) m_ColWidths.Add(6);
    (void) m_ColWidths.Add(6);
    (void) m_ColWidths.Add(4);

    // Instantiate dialog to pacify the user by reporting initialization progress
    CStatusDlg status_dlg;
    statisopen = TRUE;

    // Open the design to initialize dialog data
    if ((m_tStatus = TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "", &m_tContext)) != DBX_OK)
    {
        strcpy(errormsg, "Communication with ACCEL Tango PCB\ncould not be established!");
        goto EXIT;
    }
    m_DsgnIsOpen = TRUE;

    // Populate layer and text-style combo box controls,
    // grid-related member data, and grid control

    // Initialize the pacifier to report layers
    status_dlg.Display();
    status_dlg.TitleTextSet("Layer Retrieval");
    status_dlg.MsgTextSet("Reading layers... (", statcnt, ")");

    //Loop thru all layers in the design
    m_tStatus = TGetFirstLayer(&m_tContext, &layerobj);
    while (m_tStatus == DBX_OK)
    {
        // Only non-signal layers (but NOT Multi) are valid
        if (layerobj.layerType == DBX_LAYERTYPE_NON_SIGNAL && layerobj.layerId != DBX_LAYER_MULTI)
        {
            int listpos = m_Layer.AddString(layerobj.layerName);
            (void) m_Layer.SetItemData(listpos, layerobj.layerId);
        }
            
        // Update the pacifier
        statcnt++;
        status_dlg.MsgTextSet("Reading layers... (", statcnt, ")");

        // Retrieve the next layer
        m_tStatus = TGetNextLayer(&m_tContext, &layerobj);
    }
    m_tStatus = DBX_OK;

    // Initialize currently selected layer to Board, or the first one
    if (m_Layer.SelectString(-1, "Board") == CB_ERR)
    {
        if (m_Layer.SetCurSel(0) == CB_ERR)
        {
            (void) strcpy(errormsg, "No layers in design!");
            goto EXIT;
        }
    }

    // Re-initialize the pacifier to report text styles
    statcnt = 0;
    status_dlg.TitleTextSet("Text Style Retrieval");
    status_dlg.MsgTextSet("Reading text styles... (", statcnt, ")");

    //Loop thru all possible text style ids in the design
    for (i = 0; i <= 99; ++i)
    {
        if (TGetTextStyle(&m_tContext, i, &tstyleobj) == DBX_OK)
        {
            int listpos = m_TextStyle.AddString(tstyleobj.name);
            (void) m_TextStyle.SetItemData(listpos, (DWORD) i);
        }

        // Update the pacifier every 10th item
        if (!(++statcnt % 10))
        {
            status_dlg.MsgTextSet("Reading text styles... (", statcnt, ")");
        }
    }

    // Initialize currently selected text style to (Default), or the first one
    if (m_TextStyle.SelectString(-1, "(Default)") == CB_ERR)
    {
        if (m_TextStyle.SetCurSel(0) == CB_ERR)
        {
            (void) strcpy(errormsg, "No text styles in design!");
            goto EXIT;
        }
    }

    // Populate hole registry (size, symbol, and quantity member arrays)
    DRILLTAB_ERROR hrstat;
    if ((hrstat = HoleRegister(status_dlg)) == DTAPP_NOHOLES)
    {
        (void) strcpy(errormsg, "No Holes retrieved from design!");
        goto EXIT;
    }
    else if (hrstat == DTAPP_ERROR)
    {
        (void) strcpy(errormsg, "Hole registry not\nproperly constructed!");
        goto EXIT;
    }
    else if (hrstat == DTAPP_USERABORT)
    {
        enddlg = TRUE;
        goto EXIT;
    }

    // Close the design
    if ((m_tStatus = TCloseDesign(&m_tContext, "")) != DBX_OK)
    {
        goto EXIT;
    }
    m_DsgnIsOpen = FALSE;

    // Trap any phantom internal errors (counts should match)
    statcnt = m_HoleSizes.GetSize();
    if (m_DrillSyms.GetSize() != statcnt ||
        m_HoleQntys.GetSize() != statcnt)
    {
        (void) strcpy(errormsg, "Internal hole lists corrupted!");
        goto EXIT;
    }

    // Re-initialize the pacifier to report initialization of grid rows
    status_dlg.TitleTextSet("Drill Table Window");

    // Add grid records and populate their cells
    for (i = 0; i < statcnt; ++i)
    {
        // Re-initialize the pacifier to report initialization of grid rows
        status_dlg.MsgTextSet("Initializing row ", i, " of ", statcnt, "...");

        // Add a record (row) for each hole size
        if (::SendMessage(m_Grid, HGM_ADDREC, 0, NULL) != i + 1)
        {
            (void) strcpy(errormsg, "Drill table preview window\nnot properly constructed!");
            goto EXIT;
        }

        // Initialize this record's hole size cell
        (void) DbUnitsToString(m_HoleSizes[i], DTAPP_UNITS_IN, 3, buf, 8);
        if (!HGSetCellString(m_Grid, 0, i, buf))
        {
            (void) strcpy(errormsg, "Drill table preview window\nnot properly constructed!");
            goto EXIT;
        }

        // Initialize this record's symbol cell
        if ((long) m_DrillSyms[i] >= (long) DBX_DRILLSYM_CROSS)
        {
            int dsnameid = (int) IDS_DS_FIRST + ((int) m_DrillSyms[i] - (int) DBX_DRILLSYM_CROSS);
            CString dsname;
            if (!dsname.LoadString(dsnameid))
            {
                (void) strcpy(errormsg, "Drill table preview window\nnot properly constructed!");
                goto EXIT;
            }
            char* dsn_ptr = dsname.GetBuffer(0);
            if (!HGSetCellString(m_Grid, 1, i, dsn_ptr))
            {
                (void) strcpy(errormsg, "Drill table preview window\nnot properly constructed!");
                goto EXIT;
            }
        }
        else
        {
            if (!HGSetCellString(m_Grid, 1, i, "<None>"))
            {
                (void) strcpy(errormsg, "Drill table preview window\nnot properly constructed!");
                goto EXIT;
            }
        }

        // Initialize this record's hole quantity cell
        int qnty = m_HoleQntys[i];
        if (!HGSetCellData(m_Grid, 2, i, &qnty))
        {
            (void) strcpy(errormsg, "Drill table preview window\nnot properly constructed!");
            goto EXIT;
        }
    }

    ::SendMessage(m_Grid, HGM_UPDATE, TRUE, NULL);

EXIT:
    // Close the pacifier dialog box
    if (statisopen)
    {
        (void) status_dlg.WinDestroy();
    }

    // Close the design without overwriting captured errors
    if (m_DsgnIsOpen)
    {
        (void) TCloseDesign(&m_tContext, "");
        m_DsgnIsOpen = FALSE;
    }

    // Report DBX error
    if (m_tStatus != DBX_OK)
    {
        char buf[32];
        Error_Message_Return(m_tStatus, buf, 32);
        if (strlen(errormsg))
        {
            (void) strcat(errormsg, "\n\n");
        }
        (void) strcat(errormsg, "DBX error: ");
        (void) strcat(errormsg, buf);
    }

    // Display errors and escape partial/corrupt initialization
    if (strlen(errormsg))
    {
        (void) MessageBox(errormsg, "Drill Table Error!", MB_OK | MB_ICONEXCLAMATION);
        enddlg = TRUE;
    }

    // Do not continue (error or user abort)
    if (enddlg)
    {
        EndDialog(IDOK);
    }

    // Successful init - reactivate window (in case something has obscurred us)
    else
    {
        CWnd::SetActiveWindow();
    }

    // return TRUE  unless you set the focus to a control
    return TRUE;
}

//
// Construct hole registry (sizes, symbols, and quantities)
// Input is reference to status reporter (pacifier dialog)
//
DRILLTAB_ERROR CDrilltabDlg::HoleRegister(CStatusDlg &status_dlg)
{
    int                 i;
    PV_STYLE_REGISTRY   pvsreg;

    DRILLTAB_ERROR status = DTAPP_NOERROR;

    // Produce usage counts of each pad/via style
    status = StyleRegister(&pvsreg, status_dlg);

    // Re-initialize the pacifier to report hole sorting
    status_dlg.MsgTextSet("Sorting holes...");

    // Register holes by size
    // Populate hole size, drill symbol, and quantity member arrays

    // Examine registered pad styles (i = 0) and via styles (i = 1)
    for (i = 0; i <= 1; ++i)
    {
        int maxstyle = i ? pvsreg.vsize : pvsreg.psize;

        // Examine each possible style id
        for (int j = 0; j < maxstyle; ++j)
        {
            int             stylecnt = i ? pvsreg.p_viaarray[j] : pvsreg.p_padarray[j];
            TPadViaStyle    styleobj;

            if (!stylecnt)
            {
                continue;
            }
            else if (!i)
            {
                if ((m_tStatus = TGetPadStyle(&m_tContext, j, &styleobj)) != DBX_OK)
                {
                    status = DTAPP_ERROR;
                    goto EXIT;
                }
            }
            else
            {
                if ((m_tStatus = TGetViaStyle(&m_tContext, j, &styleobj)) != DBX_OK)
                {
                    status = DTAPP_ERROR;
                    goto EXIT;
                }
            }

            if (!styleobj.holeDia)
            {
                continue;
            }

            // Determine if this hole size is already registered
            BOOL    match = FALSE;
            int     k, numentr = m_HoleSizes.GetSize();
            for (k = 0; k < numentr; ++k)
            {
                if (styleobj.holeDia == (long) m_HoleSizes[k])
                {
                    match = TRUE;
                    break;
                }
                else if (styleobj.holeDia < (long) m_HoleSizes[k])
                {
                    break;
                }
            }

            // Size match found - add style's hole quantity to existing size's
            if (match)
            {
                int qnty = m_HoleQntys.GetAt(k);
                qnty += stylecnt;
                m_HoleQntys.SetAt(k, qnty);
            }

            // No size match found - new hole is largest - add new record at end
            else if (k >= numentr)
            {
                if (m_HoleSizes.Add(styleobj.holeDia) != numentr)
                {
                    status = DTAPP_ERROR;
                    goto EXIT;
                }
                if (m_DrillSyms.Add(styleobj.drillSymbol) != numentr)
                {
                    status = DTAPP_ERROR;
                    goto EXIT;
                }
                if (m_HoleQntys.Add(stylecnt) != numentr)
                {
                    status = DTAPP_ERROR;
                    goto EXIT;
                }
                ++numentr;
            }

            // No match - add record within interior
            else
            {
                m_HoleSizes.InsertAt(k, styleobj.holeDia);
                m_DrillSyms.InsertAt(k, styleobj.drillSymbol);
                m_HoleQntys.InsertAt(k, stylecnt);
                ++numentr;
            }
        }
    }

    free(pvsreg.p_padarray);
    free(pvsreg.p_viaarray);

    if (!m_HoleSizes.GetSize())
    {
        status = DTAPP_NOHOLES;
    }

EXIT:
    return status;
}

//
// Construct registry of pad/via style useage
// Input is pointer to empty registry structure and 
//          reference to status reporter (pacifier dialog)
//
DRILLTAB_ERROR CDrilltabDlg::StyleRegister(PV_STYLE_REGISTRY *pvsreg,
                                           CStatusDlg &status_dlg)
{
    int     statcnt = 0;
    TItem   pcbobj;

    DRILLTAB_ERROR status = DTAPP_NOERROR;

    // Initialize the pacifier to report holes retrieved
    status_dlg.TitleTextSet("Hole Retrieval");
    status_dlg.MsgTextSet("Reading holes... (", statcnt, ")");

    // Initialize the style registry to handle style ids from 0 to 99
    pvsreg->p_padarray = (int*) malloc (100 * sizeof(int));
    pvsreg->p_viaarray = (int*) malloc (100 * sizeof(int));
    (void) memset(pvsreg->p_padarray, 0, 100 * sizeof(int));
    (void) memset(pvsreg->p_viaarray, 0, 100 * sizeof(int));
    pvsreg->psize = pvsreg->vsize = 100;

    // We'll be examinimg all multi-layer items
    if ((m_tStatus = TGetFirstLayerItem(&m_tContext, DBX_LAYER_MULTI, &pcbobj)) != DBX_OK)
    {
        status = DTAPP_NOHOLES;
        goto EXIT;
    }

    // Populate the registry.  Produce usage count of each pad/via style id.
    while (m_tStatus == DBX_OK)
    {
        if (pcbobj.itemType == DBX_PAD)
        {
        	if (pcbobj.pad.padStyleId >= pvsreg->psize)
        	{
                int newsize = pcbobj.pad.padStyleId + 1;
                pvsreg->p_padarray = (int*) realloc(pvsreg->p_padarray, newsize * sizeof(int));
                (void) memset(&pvsreg->p_padarray[pvsreg->psize], 0, (newsize - pvsreg->psize) * sizeof(int));
                pvsreg->psize = newsize;
        	}
        	
            pvsreg->p_padarray[pcbobj.pad.padStyleId]++;

            // Initial encounter of this style - allow abort if no symbol assigned
            if (!m_WarnedNoSym && pvsreg->p_padarray[pcbobj.pad.padStyleId] == 1)
            {
                if ((status = WarnNoSymbol(FALSE, pcbobj.pad.padStyleId)) != DTAPP_NOERROR)
                {
                    goto EXIT;
                }
            }

            // Update the pacifier every 10th item
            if (!(++statcnt % 10))
            {
                status_dlg.MsgTextSet("Reading holes... (", statcnt, ")");
            }
        }
        else if (pcbobj.itemType == DBX_VIA)
        {
        	if (pcbobj.via.viaStyleId >= pvsreg->vsize)
        	{
                int newsize = pcbobj.via.viaStyleId + 1;
                pvsreg->p_viaarray = (int*) realloc(pvsreg->p_viaarray, newsize * sizeof(int));
                (void) memset(&pvsreg->p_viaarray[pvsreg->vsize], 0, (newsize - pvsreg->vsize) * sizeof(int));
                pvsreg->vsize = newsize;
        	}
        	
            pvsreg->p_viaarray[pcbobj.via.viaStyleId]++;

            // Initial encounter of this style - allow abort if no symbol assigned
            if (!m_WarnedNoSym && pvsreg->p_viaarray[pcbobj.via.viaStyleId] == 1)
            {
                if ((status = WarnNoSymbol(TRUE, pcbobj.via.viaStyleId)) != DTAPP_NOERROR)
                {
                    goto EXIT;
                }
            }

            // Update the pacifier every 10th item
            if (!(++statcnt % 10))
            {
                status_dlg.MsgTextSet("Reading holes... (", statcnt, ")");
            }
        }
        else if (pcbobj.itemType == DBX_COMPONENT)
        {
            TPad padobj;
            m_tStatus = TGetFirstCompPad(&m_tContext, pcbobj.component.refDes, &padobj);
            while (m_tStatus == DBX_OK)
            {
            	if (padobj.padStyleId >= pvsreg->psize)
            	{
                    int newsize = padobj.padStyleId + 1;
                    pvsreg->p_padarray = (int*) realloc(pvsreg->p_padarray, newsize * sizeof(int));
                    (void) memset(&pvsreg->p_padarray[pvsreg->psize], 0, (newsize - pvsreg->psize) * sizeof(int));
                    pvsreg->psize = newsize;
            	}
        	
                pvsreg->p_padarray[padobj.padStyleId]++;

                // Initial encounter of this style - allow abort if no symbol assigned
                if (!m_WarnedNoSym && pvsreg->p_padarray[padobj.padStyleId] == 1)
                {
                    if ((status = WarnNoSymbol(FALSE, padobj.padStyleId)) != DTAPP_NOERROR)
                    {
                        goto EXIT;
                    }
                }

                // Update the pacifier every 10th item
                if (!(++statcnt % 10))
                {
                    status_dlg.MsgTextSet("Reading holes... (", statcnt, ")");
                }

                m_tStatus = TGetNextCompPad(&m_tContext, &padobj);
            }
            m_tStatus = DBX_OK;
        }
        m_tStatus = TGetNextLayerItem(&m_tContext, &pcbobj);
    }
    m_tStatus = DBX_OK;

EXIT:
    return status;
}

//
// Produce warning of no symbol assignemt, if appropriate
//
DRILLTAB_ERROR CDrilltabDlg::WarnNoSymbol(BOOL isvia, long styleid)
{
    DRILLTAB_ERROR status = DTAPP_NOERROR;    
    TPadViaStyle   styleobj;
    
    // If warning has already been produced once, ignore
    if (m_WarnedNoSym)
    {
        goto EXIT;
    }

    // Retrieve pad/via style
    if (!isvia)
    {
        if ((m_tStatus = TGetPadStyle(&m_tContext, styleid, &styleobj)) != DBX_OK)
        {
            status = DTAPP_ERROR;
            goto EXIT;
        }
    }
    else
    {
        if ((m_tStatus = TGetViaStyle(&m_tContext, styleid, &styleobj)) != DBX_OK)
        {
            status = DTAPP_ERROR;
            goto EXIT;
        }
    }

    // Produce warning message box, and allow abort
    if (styleobj.drillSymbol < (long) DBX_DRILLSYM_CROSS && styleobj.holeDia)
    {
        char buf[96];
        (void) strcpy(buf, "Encountered at least one hole\n");
        (void) strcat(buf, "size with no symbol assigned!\n\nContinue?");
        int wstat = MessageBox(buf, "Drill Table Warning!", MB_YESNO | MB_ICONQUESTION);
        m_WarnedNoSym = TRUE;
        if (wstat == IDNO)
        {
            status = DTAPP_USERABORT;
            goto EXIT;
        }
    }

EXIT:
    return status;
}

//
// Help/About menu item selection
//
void CDrilltabDlg::OnHelpAbout()
{
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
}

//
// File/Exit menu item selection
//
void CDrilltabDlg::OnFileExit()
{
    CDialog::EndDialog(TRUE);
}

//
// Grid record changed
//
void CDrilltabDlg::OnRecchangedGrid()
{
    // There's currently nothing to do here.
}

//
// Grid selection changed
//
void CDrilltabDlg::OnSelchangeGrid()
{
    GridCtlsUpdate();
}

//
// Update the Label edit box and Minimum Width edit box control contents,
// based on the currently selected grid cell
//
void CDrilltabDlg::GridCtlsUpdate()
{          
    int     iCol = 0;
    int     iRow = 0;
    long    lCell = 0;

    // Capture current selection anchor
    lCell = (LONG) ::SendMessage(m_Grid, HGM_GETSELANCHOR, 0, 0L);

    iCol = LOWORD(lCell);
    iRow = HIWORD(lCell);

    // Retrieve/convert data and update edit box controls
    if (iCol >= 0 && iRow >= -1)
    {   
        char    labelbuf[64], widthbuf[3];
        *labelbuf = *widthbuf = 0;
        itoa(m_ColWidths.GetAt(iCol), widthbuf, 10);
        m_ColumnWidth.SetWindowText(widthbuf);
        ::SendMessage(m_Grid, HGFM_GETNAME, HGColToFld(m_Grid, iCol), (LONG) labelbuf);
        m_ColumnLabel.SetWindowText(labelbuf);
    }
    return;
}

//
// Inch units radio button
//
void CDrilltabDlg::OnHdunitsin()
{
    int     holecnt = m_HoleSizes.GetSize();

    // Reinitialize the field name (column header)
    char tmpstr[18] = "Hole Dia (inch)\0";
    ::SendMessage(m_Grid, HGFM_SETNAME, 0, (long) tmpstr);

    // Reinitialize each row's hole diameter value
    for (int i = 0; i < holecnt; ++i)
    {
        char    buf[20];
        (void) DbUnitsToString(m_HoleSizes[i], DTAPP_UNITS_IN, 3, buf, 20);
        HGSetCellString(m_Grid, 0, i, buf);
    }

    return;
}

//
// mm units radio button
//
void CDrilltabDlg::OnHdunitsmm()
{
    int     holecnt = m_HoleSizes.GetSize();

    // Reinitialize the field name (column header)
    char tmpstr[18] = "Hole Dia (mm)\0";
    ::SendMessage(m_Grid, HGFM_SETNAME, 0, (long) tmpstr);

    // Reinitialize each row's hole diameter value
    for (int i = 0; i < holecnt; ++i)
    {
        char    buf[20];
        (void) DbUnitsToString(m_HoleSizes[i], DTAPP_UNITS_MM, 2, buf, 20);
        HGSetCellString(m_Grid, 0, i, buf);
    }

    return;
}

//
// Column add pushbutton
//
void CDrilltabDlg::OnColumnAdd()
{
    char    labbuf[64], widbuf[3];
    int     ngot, lablen = 0, widlen = 0, widval = 0;

    *labbuf = *widbuf = 0;

    ngot = m_ColumnLabel.GetWindowText(labbuf, 64);
    lablen = ngot ? strlen(labbuf) : 0;

    ngot = m_ColumnWidth.GetWindowText(widbuf, 3);
    if (ngot)
    {
        widlen = strlen(widbuf);
        widval = atoi(widbuf);
    }

    if (widval < 0)
    {
        widval = 0;
    }

    if (!widval && !lablen)
    {
        (void) MessageBox("Must specify either column label\nor non-zero minimum width",
                          "Input Error!", MB_OK | MB_ICONEXCLAMATION);
        return;
    }

    // Add column width value to array data member
    m_ColWidths.Add(widval);

    // New grid column will fit column label text size, or at least 120 units
    CSize labelsize = GetDC()->GetTextExtent(labbuf, lablen);
    if (labelsize.cx < 120)
    {
        labelsize.cx = 120;
    }

    // New column will have text centered in its cells
    long ctlflags = 0L;
    ctlflags = ctlflags | HES_DISPLAYCENTER;

    // Create a new column (field) and update the grid
    HFLD newfld = HGFieldCreate(labbuf, 0, (int) labelsize.cx, 0, HC_STRING, HT_STRING,
                                '\0', '\0', 63, HGCTL_EDIT, ctlflags, "\0");
    ::SendMessage(m_Grid, HGM_ADDFLD, 0, (long) newfld);

    // Set current grid selection to first cell of newly added field
    HGSetCurSel(m_Grid, (int) ::SendMessage(m_Grid, HGM_GETCOLCOUNT, 0, 0L), 0);
    ::SendMessage(m_Grid, HGM_UPDATE, FALSE, NULL);
    ::SetFocus(m_Grid);

    return;
}

//
// Column delete pushbutton
// We allow columns to have duplicate header names.  Since the column delete
// pushbutton keys off of the current contents of the label edit box, we
// must be slightly intelligent about which column we remove from the grid.
//
// If the label edit box text matches the header of the currently selected
// grid column, we assume it is the deletion target.  Otherwise, we delete
// the last column with a header that matches the edit box text.
//
void CDrilltabDlg::OnColumnDel()
{

    char    buf1[64], buf2[64];
    int     icol;
    BOOL    delcol = FALSE;

    // Retrieve text from column label edit box
    *buf1 = 0;
    (void) m_ColumnLabel.GetWindowText(buf1, 64);

    // Determine if currently selected grid column matches Label edit box text
    icol = LOWORD((LONG) ::SendMessage(m_Grid, HGM_GETSELANCHOR, 0, 0L));

    if (icol >=0)
    {
        *buf2 = 0;
        ::SendMessage(m_Grid, HGFM_GETNAME, HGColToFld(m_Grid, icol), (LONG) buf2);

        // Grid column selection matches edit box text
        if (!strcmp(buf1, buf2))
        {
            // Disallow deletion of protected columns
            if (icol <= 2)
            {
                (void) MessageBox("Attempted to delete protected\ndrill table column",
                                  "Drill Table Warning!", MB_OK | MB_ICONEXCLAMATION);
            }

            // Currently selected grid column is the deletion target
            else
            {
                ::SendMessage(m_Grid, HGM_DELETEFLD, icol, 0L);
                m_ColWidths.RemoveAt(icol);
                delcol = TRUE;
            }
            return;
        }
    }

    // Currently selected grid column does not match. Find last occurrance.
    for (icol = ((int) ::SendMessage(m_Grid, HGM_GETCOLCOUNT, 0, 0L)) - 1; icol >= 0; --icol)
    {
        ::SendMessage(m_Grid, HGFM_GETNAME, HGColToFld(m_Grid, icol), (LONG) buf2);

        if (!strcmp(buf1, buf2))
        {
            // Disallow deletion of protected columns.
            if (icol <= 2)
            {
                (void) MessageBox("Attempted to delete protected\ndrill table column",
                                  "Drill Table Warning!", MB_OK | MB_ICONEXCLAMATION);
                return;
            }

            // Column label edit box and grid column heading texts match
            else
            {
                ::SendMessage(m_Grid, HGM_DELETEFLD, icol, 0L);
                m_ColWidths.RemoveAt(icol);
                delcol = TRUE;
                break;
            }
        }
    }

    // Column label edit box text not found on grid columns
    if (!delcol)
    {
        (void) MessageBox("Specified column label\nnot found on drill table!",
                          "Drill Table Warning!", MB_OK | MB_ICONEXCLAMATION);
    }

    return;
}

//
// IDPB_OK message handler (OK pushbutton)
//
void CDrilltabDlg::OnOk()
{
    BOOL    enddlg = TRUE;

    // Retrieve validated dialog data
    if (!DlgDataValidate() && m_tStatus == DBX_OK)
    {
        enddlg = FALSE; // Non-fatal error - keep dialog open
        goto EXIT;
    }
    else if (m_tStatus != DBX_OK)
    {
        goto EXIT;      // Fatal error
    }

    // Force update of currently selected grid cell
    (void) ShowWindow(SW_HIDE);

    // Create drill table
    if (!DrillTableCreate() && m_tStatus == DBX_OK)
    {
        enddlg = FALSE; // Non-fatal error - keep dialog open
        goto EXIT;
    }
    else if (m_tStatus != DBX_OK)
    {
        goto EXIT;      // Fatal error
    }

EXIT:
    // Always make certain to close ACCEL Tango PCB connection
    if (m_DsgnIsOpen)
    {
        m_tStatus = TCloseDesign(&m_tContext, "");
    }

    // Close dialog on successful completion or fatal error
    if (enddlg)
    {
        EndDialog(IDOK);
    }
    else
    {
        (void) ShowWindow(SW_SHOW);
    }

    return;
}

//
// Validate dialog data and convert to usable form
//
BOOL CDrilltabDlg::DlgDataValidate()
{
    char        buf[16];
    TLayer      layerobj;
    TTextStyle  tstylobj;
    int         combosel;
    char        errormsg[128];
    CWnd        *ctrlfocus = NULL;

    *errormsg = 0;

    // Validate and convert line width
    if (!m_LineWidth.GetWindowText(buf, 16) ||
        !StringToDbUnits(buf, &m_DbLineWidth) ||
        m_DbLineWidth <= 0L)
    {
        strcpy(errormsg, "Invalid line width specified!");
        ctrlfocus = (CWnd*) &m_LineWidth;
        goto EXIT;
    }

    // Validate and convert location
    if (!m_X.GetWindowText(buf, 16) ||
        !StringToDbUnits(buf, &m_DbX) ||
        m_DbX <= 0L)
    {
        strcpy(errormsg, "Invalid X location specified!");
        ctrlfocus = (CWnd*) &m_X;
        goto EXIT;
    }
    if (!m_Y.GetWindowText(buf, 16) ||
        !StringToDbUnits(buf, &m_DbY) ||
        m_DbY <= 0L)
    {
        strcpy(errormsg, "Invalid Y location specified!");
        ctrlfocus = (CWnd*) &m_Y;
        goto EXIT;
    }

    // Open the design
    if ((m_tStatus = TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "", &m_tContext)) != DBX_OK)
    {
        strcpy(errormsg, "Communication with ACCEL Tango PCB\ncould not be established!");
        goto EXIT;
    }
    m_DsgnIsOpen = TRUE;

    // Validate existence of selected (non_blank) layer
    combosel = m_Layer.GetCurSel();
    if (combosel == CB_ERR)
    {
        strcpy(errormsg, "Invalid layer specified!");
        ctrlfocus = (CWnd*) &m_Layer;
        goto EXIT;
    }
    if (TGetLayerById(&m_tContext, m_Layer.GetItemData(combosel), &layerobj) != DBX_OK)
    {
        strcpy(errormsg, "Invalid layer specified!");
        ctrlfocus = (CWnd*) &m_Layer;
        goto EXIT;
    }
    m_LayerId = layerobj.layerId;

    // Validate existence of selected (non-blank) text style
    combosel = m_TextStyle.GetCurSel();
    if (combosel == CB_ERR)
    {
        strcpy(errormsg, "Invalid text style specified!");
        ctrlfocus = (CWnd*) &m_TextStyle;
        goto EXIT;
    }
    if (TGetTextStyle(&m_tContext, m_TextStyle.GetItemData(combosel), &tstylobj) != DBX_OK)
    {
        strcpy(errormsg, "Invalid text style specified!");
        ctrlfocus = (CWnd*) &m_TextStyle;
        goto EXIT;
    }
    m_TextStyleId = tstylobj.styleId;

EXIT:
    // Report DBX error
    if (m_tStatus != DBX_OK)
    {
        char errbuf[32];
        Error_Message_Return(m_tStatus, errbuf, 32);
        if (strlen(errormsg))
        {
            (void) strcat(errormsg, "\n\n");
        }
        (void) strcat(errormsg, "DBX error: ");
        (void) strcat(errormsg, errbuf);
        (void) MessageBox(errormsg, "Drill Table Error!", MB_OK | MB_ICONEXCLAMATION);
    }

    // Report input errors
    else if (strlen(errormsg))
    {
        (void) MessageBox(errormsg, "Input Error!", MB_OK | MB_ICONEXCLAMATION);
    }

    // Trap non-fatal errors (allow re-try)
    if (ctrlfocus)
    {
        ctrlfocus->SetFocus();
        return FALSE;
    }

    return TRUE;
}

//
// Generate drill table grid-lines/text/symbols in ACCEL Tango PCB
//
BOOL CDrilltabDlg::DrillTableCreate()
{
    int         i;
    long        charwidth;
    long        rowheight;
    long        tablewid = 0;
    long        numrows = (long) ::SendMessage(m_Grid, HGM_GETROWCOUNT, 0, 0L);
    int         numcols = (int)  ::SendMessage(m_Grid, HGM_GETCOLCOUNT, 0, 0L);
    long        titlerow = m_Title.GetWindowTextLength() ? 1L : 0L;
    CDWordArray colmetrics;
    char        errormsg[128];
    CWnd        *ctrlfocus = NULL;
    BOOL        statisopen = TRUE;
    long        proximity;
    int         cornposn;
    long        colposn;

    *errormsg = 0;

    // Instantiate dialog to pacify the user by reporting table creation progress
    CStatusDlg status_dlg;
    statisopen = TRUE;

    // Open the design
    if (!m_DsgnIsOpen)
    {
        if ((m_tStatus = TOpenDesign(DBX_LANGUAGE, DBX_VERSION, "", &m_tContext)) != DBX_OK)
        {
            strcpy(errormsg, "Communication with ACCEL Tango PCB\ncould not be established!");
            goto EXIT;
        }
        m_DsgnIsOpen = TRUE;
    }

    // Initialize the pacifier text
    status_dlg.Display();
    status_dlg.TitleTextSet("Drill Table Creation");
    status_dlg.MsgTextSet("Placing drill table grid lines...");

    // Place a barred M in the design at (1 in, 1 in) to estimate largest
    // single char extents.
    // Reason: Barred M extents closely match true width of barred ampersand
    TText   textobj;
    textobj.textStyleId     = m_TextStyleId;
    strcpy(textobj.text, "~M~");
    textobj.layerId         = m_LayerId;
    textobj.justPoint       = DBX_JUSTIFY_LOWER_LEFT;
    textobj.refPoint.x      = 254000;
    textobj.refPoint.y      = 254000;
    textobj.rotationAng     = 0;
    textobj.isFlipped       = 0;
    textobj.isVisible       = 0;
    textobj.isHighlighted   = 0;
    
    if ((m_tStatus = TPlaceText(&m_tContext, &textobj)) != DBX_OK)
    {
        strcpy(errormsg, "Failure to place text\nin ACCEL Tango PCB design");
        goto EXIT;
    }
    charwidth = textobj.boundRect.upperRight.x - textobj.boundRect.lowerLeft.x;
    rowheight = textobj.boundRect.upperRight.y - textobj.boundRect.lowerLeft.y;
    if ((m_tStatus = TDeleteText(&m_tContext, &textobj)) != DBX_OK)
    {
        strcpy(errormsg, "Failure to place text\nin ACCEL Tango PCB design");
        goto EXIT;
    }

    // All subsequent placed text will be center justified.
    textobj.justPoint = DBX_JUSTIFY_CENTER;

    // Calculate each column width and total drill table width
    for (i = 0; i < numcols; ++i)
    {
        // Retrieve greater of column header width, or specified minimum (in chars)
        int colwidth0 = (int) ::SendMessage(m_Grid, HGFM_GETNAMELEN, HGColToFld(m_Grid, i), NULL);

        int colwidth1 = m_ColWidths.GetAt(i);
        if (colwidth0 > colwidth1)
        {
            colwidth1 = colwidth0;
        }

        // Calculate column width (in db units)
        long colwidth2 = ((long) colwidth1) * charwidth;
        colmetrics.Add(colwidth2);
        tablewid += colwidth2;
    }

    // Calculate lower left drill table corner and ensure fit within workspace
    proximity = (m_DbLineWidth / 2L) + 50800;     // Half the line width plus 20 mil
    cornposn = GetCheckedRadioButton(IDRB_LOCUPLEFT, IDRB_LOCLOWRIGHT);
    if (cornposn == IDRB_LOCUPRIGHT || cornposn == IDRB_LOCLOWRIGHT)
    {
        m_DbX -= tablewid;
    }
    if (cornposn == IDRB_LOCUPLEFT || cornposn == IDRB_LOCUPRIGHT)
    {
        m_DbY -= rowheight * (numrows + 1L + titlerow);
    }
    TDesign dgninfo;
    if ((m_tStatus = TGetDesignInfo(&m_tContext, &dgninfo)) != DBX_OK)
    {
        strcpy(errormsg, "Failure to retrieve info\nfrom ACCEL Tango PCB design");
        goto EXIT;
    }
    if (m_DbX - proximity <= 0 || m_DbY - proximity <= 0 ||
        m_DbX + tablewid + proximity >= dgninfo.workSpaceSize.x ||
        m_DbY + (rowheight * (numrows + 1L + titlerow)) + proximity >= dgninfo.workSpaceSize.y)
    {
        strcpy(errormsg, "Drill table does not fit within\nworkspace at specified corner!");
        ctrlfocus = (CWnd*) &m_X;
        goto EXIT;
    }

    // Create some drill table geometry

    // Initialize reusable line object for rows/columns
    TLine lineobj;
    lineobj.lineType = DBX_LINE;
    lineobj.width = m_DbLineWidth;
    lineobj.layerId = m_LayerId;
    lineobj.isHighlighted = 0;

    // Create row lines for data, headings, and (optional) title
    lineobj.startPt.x = m_DbX;
    lineobj.startPt.y = m_DbY;
    lineobj.endPt.x = m_DbX + tablewid;
    lineobj.endPt.y = m_DbY;
    for (i = 0; i <= (int) numrows + 1 + (int) titlerow; ++i)
    {
        if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK)
        {
            strcpy(errormsg, "Failure to place line\nin ACCEL Tango PCB design");
            goto EXIT;
        }
        lineobj.startPt.y += rowheight;
        lineobj.endPt.y   += rowheight;
    }

    // Create column lines.  First and last may be one row longer than the rest.
    lineobj.startPt.x = m_DbX;
    lineobj.startPt.y = m_DbY;
    lineobj.endPt.x = m_DbX;
    lineobj.endPt.y = m_DbY + (rowheight * (numrows + 1L + titlerow));
    if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK)
    {
        strcpy(errormsg, "Failure to place line\nin ACCEL Tango PCB design");
        goto EXIT;
    }
    lineobj.endPt.y -= rowheight * titlerow;

    for (i = 0; i < numcols - 1; ++i)
    {
        lineobj.startPt.x += colmetrics.GetAt(i);
        lineobj.endPt.x   += colmetrics.GetAt(i);
        if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK)
        {
            strcpy(errormsg, "Failure to place line\nin ACCEL Tango PCB design");
            goto EXIT;
        }
    }

    lineobj.startPt.x += colmetrics.GetAt(numcols - 1);
    lineobj.endPt.x   += colmetrics.GetAt(numcols - 1);
    lineobj.endPt.y += rowheight * titlerow;
    if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK)
    {
        strcpy(errormsg, "Failure to place line\nin ACCEL Tango PCB design");
        goto EXIT;
    }

    // Re-initialize meaningful pacifier text
    status_dlg.MsgTextSet("Placing drill table text...");

    // Create and center title text
    if (titlerow)
    {
        (void) m_Title.GetWindowText(textobj.text, DBX_MAX_TEXTITEM_LEN);
        textobj.refPoint.x = m_DbX + (tablewid / 2L);
        textobj.refPoint.y = m_DbY + (rowheight * (numrows + 1L)) + (rowheight / 2L);
        if ((m_tStatus = TPlaceText(&m_tContext, &textobj)) != DBX_OK)
        {
            strcpy(errormsg, "Failure to place text\nin ACCEL Tango PCB design");
            goto EXIT;
        }
    }

    // Create and center column header texts
    colposn = m_DbX;
    textobj.refPoint.y = m_DbY + (rowheight * numrows) + (rowheight / 2L);   // Center of header row
    for (i = 0; i < numcols; ++i)
    {
        textobj.refPoint.x = colposn + (colmetrics.GetAt(i) / 2L);  // Center of column
        ::SendMessage(m_Grid, HGFM_GETNAME, HGColToFld(m_Grid, i), (LONG) textobj.text);
        if ((m_tStatus = TPlaceText(&m_tContext, &textobj)) != DBX_OK)
        {
            strcpy(errormsg, "Failure to place text\nin ACCEL Tango PCB design");
            goto EXIT;
        }
        colposn += colmetrics.GetAt(i);
    }


    // Create and center cell texts
    colposn = m_DbX;
    for (i = 0; i < numcols; ++i)
    {
        unsigned int colchars = m_ColWidths.GetAt(i);
        ::SendMessage(m_Grid, HGFM_GETNAME, HGColToFld(m_Grid, i), (LONG) textobj.text);

        // Greater of max char designation or column header string length
        if (strlen(textobj.text) > colchars)
        {
            colchars = strlen(textobj.text);
        }

        for (int j = 0; j < (int) numrows; ++j)
        {
            // Ignore valid drill symbols (created later)
            if (i == 1 && (long) m_DrillSyms[j] >= (long) DBX_DRILLSYM_CROSS)
            {
                    continue;
            }

            *textobj.text = 0;

            if (HGGetCellText(m_Grid, i, j, textobj.text, DBX_MAX_TEXTITEM_LEN) && strlen(textobj.text))
            {
                if (strlen(textobj.text) > colchars)
                {
                    textobj.text[colchars] = '\0';
                }
                textobj.refPoint.x = colposn + (colmetrics.GetAt(i) / 2L);
                textobj.refPoint.y = m_DbY + (rowheight * (numrows - (long) j)) - (rowheight / 2L);
                if ((m_tStatus = TPlaceText(&m_tContext, &textobj)) != DBX_OK)
                {
                    strcpy(errormsg, "Failure to place text\nin ACCEL Tango PCB design");
                    goto EXIT;
                }
            }
        }
        colposn += colmetrics.GetAt(i);
    }

    // Re-initialize meaningful pacifier text
    status_dlg.MsgTextSet("Placing drill table symbols...");

    // Create and center symbol geometry
    TCoord  firstcntr;
    firstcntr.x = m_DbX + colmetrics[0] + (colmetrics[1] / 2L);
    firstcntr.y = m_DbY + (rowheight * numrows) - (rowheight / 2L);

    DrillSymbolsCreate(firstcntr, rowheight);
    if (m_tStatus != DBX_OK)
    {
        strcpy(errormsg, "Drill symbols not created!");
        goto EXIT;
    }

EXIT:
    // Close the pacifier dialog box
    if (statisopen)
    {
        (void) status_dlg.WinDestroy();
    }

    // Close the design without overwriting captured errors
    if (m_DsgnIsOpen)
    {
        (void) TCloseDesign(&m_tContext, "");
        m_DsgnIsOpen = FALSE;
    }

    // Report DBX error
    if (m_tStatus != DBX_OK)
    {
        char errbuf[32];
        Error_Message_Return(m_tStatus, errbuf, 32);
        if (strlen(errormsg))
        {
            (void) strcat(errormsg, "\n\n");
        }
        (void) strcat(errormsg, "DBX error: ");
        (void) strcat(errormsg, errbuf);
        (void) MessageBox(errormsg, "Drill Table Error!", MB_OK | MB_ICONEXCLAMATION);
    }

    // Report input errors (allow re-try)
    else if (strlen(errormsg))
    {
        (void) MessageBox(errormsg, "Input Error!", MB_OK | MB_ICONEXCLAMATION);
    }

    if (ctrlfocus)
    {
        ctrlfocus->SetFocus();
        return FALSE;
    }

    return TRUE;
}

//
// Create and place drill table symbol geometry
//
void CDrilltabDlg::DrillSymbolsCreate(TCoord firstcntr, long yincr)
{
    long    size = yincr - (yincr / 5L);   // Utilize 80% of column height
    long    x = firstcntr.x;
    long    y = firstcntr.y;
    long    delta = size / 2;
    long    on_45 = (long) (delta / sqrt(2.0));
    long    symcnt = m_DrillSyms.GetSize();
    int     dsnameid;               // For retrieval of alpha-char drill symbols
    CString dsname;
    char    *dsn_ptr;
    // Initialize reusable line, arc, and text objects
    TLine lineobj;
    lineobj.lineType = DBX_LINE;
    lineobj.width = m_DbLineWidth;
    lineobj.layerId = m_LayerId;
    lineobj.isHighlighted = 0;

    TArc arcobj;
    arcobj.width = m_DbLineWidth;
    arcobj.radius = delta;
    arcobj.startAng = 0;
    arcobj.sweepAng = 3600;
    arcobj.layerId = m_LayerId;
    arcobj.isHighlighted = 0;

    TText   textobj;
    textobj.textStyleId     = m_TextStyleId;
    textobj.layerId         = m_LayerId;
    textobj.justPoint       = DBX_JUSTIFY_CENTER;
    textobj.rotationAng     = 0;
    textobj.isFlipped       = 0;
    textobj.isVisible       = 1;
    textobj.isHighlighted   = 0;
    
    // Create each symbol
    for (int i = 0; i < symcnt; ++i, y-=yincr)
    {
        // Create bounding shape geometry
        switch ((long) m_DrillSyms[i])
        {
            case DBX_DRILLSYM_BOX_LINE:
            case DBX_DRILLSYM_BOX_V:
            case DBX_DRILLSYM_BOX_X:
            case DBX_DRILLSYM_BOX_CROSS:
            case DBX_DRILLSYM_BOX_Y:
            case DBX_DRILLSYM_BOX_T:
                lineobj.startPt.x = x - delta;
                lineobj.startPt.y = y - delta;
                lineobj.endPt.x = x + delta;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.y = lineobj.endPt.y = y + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x - delta;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.x = lineobj.endPt.x = x + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_DIAMOND_LINE:
            case DBX_DRILLSYM_DIAMOND_V:
            case DBX_DRILLSYM_DIAMOND_X:
            case DBX_DRILLSYM_DIAMOND_CROSS:
            case DBX_DRILLSYM_DIAMOND_Y:
            case DBX_DRILLSYM_DIAMOND_T:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y + delta;
                lineobj.endPt.x = x - delta;
                lineobj.endPt.y = y;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.y = y - delta;
                lineobj.endPt.x = x + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.x = x;
                lineobj.startPt.y = y - delta;
                lineobj.endPt.x = x - delta;
                lineobj.endPt.y = y;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.y = y + delta;
                lineobj.endPt.x = x + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_CIRCLE_LINE:
            case DBX_DRILLSYM_CIRCLE_V:
            case DBX_DRILLSYM_CIRCLE_X:
            case DBX_DRILLSYM_CIRCLE_CROSS:
            case DBX_DRILLSYM_CIRCLE_Y:
            case DBX_DRILLSYM_CIRCLE_T:
                arcobj.centerPt.x = x;
                arcobj.centerPt.y = y;
                if ((m_tStatus = TPlaceArc(&m_tContext, &arcobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_CROSS:
            case DBX_DRILLSYM_X:
            case DBX_DRILLSYM_Y:
            case DBX_DRILLSYM_T:
            case DBX_DRILLSYM_HOUR:
            case DBX_DRILLSYM_SIDE_HOUR:
            case DBX_DRILLSYM_UPPER_A:
            case DBX_DRILLSYM_UPPER_B:
            case DBX_DRILLSYM_UPPER_C:
            case DBX_DRILLSYM_UPPER_D:
            case DBX_DRILLSYM_UPPER_E:
            case DBX_DRILLSYM_UPPER_F:
            case DBX_DRILLSYM_UPPER_G:
            case DBX_DRILLSYM_UPPER_H:
            case DBX_DRILLSYM_UPPER_I:
            case DBX_DRILLSYM_UPPER_J:
            case DBX_DRILLSYM_UPPER_K:
            case DBX_DRILLSYM_UPPER_L:
            case DBX_DRILLSYM_UPPER_M:
            case DBX_DRILLSYM_UPPER_N:
            case DBX_DRILLSYM_UPPER_O:
            case DBX_DRILLSYM_UPPER_P:
            case DBX_DRILLSYM_UPPER_Q:
            case DBX_DRILLSYM_UPPER_R:
            case DBX_DRILLSYM_UPPER_S:
            case DBX_DRILLSYM_UPPER_U:
            case DBX_DRILLSYM_UPPER_V:
            case DBX_DRILLSYM_UPPER_W:
            case DBX_DRILLSYM_UPPER_Z:
            case DBX_DRILLSYM_LOWER_A:
            case DBX_DRILLSYM_LOWER_B:
            case DBX_DRILLSYM_LOWER_C:
            case DBX_DRILLSYM_LOWER_D:
            case DBX_DRILLSYM_LOWER_E:
            case DBX_DRILLSYM_LOWER_F:
            case DBX_DRILLSYM_LOWER_G:
            case DBX_DRILLSYM_LOWER_H:
            case DBX_DRILLSYM_LOWER_I:
            case DBX_DRILLSYM_LOWER_J:
            case DBX_DRILLSYM_LOWER_K:
            case DBX_DRILLSYM_LOWER_L:
            case DBX_DRILLSYM_LOWER_M:
            case DBX_DRILLSYM_LOWER_N:
            case DBX_DRILLSYM_LOWER_O:
            case DBX_DRILLSYM_LOWER_P:
            case DBX_DRILLSYM_LOWER_Q:
            case DBX_DRILLSYM_LOWER_R:
            case DBX_DRILLSYM_LOWER_S:
            case DBX_DRILLSYM_LOWER_T:
            case DBX_DRILLSYM_LOWER_U:
            case DBX_DRILLSYM_LOWER_V:
            case DBX_DRILLSYM_LOWER_W:
            case DBX_DRILLSYM_LOWER_Y:
            case DBX_DRILLSYM_LOWER_Z:
                break;

            default:
                break;
        }

        // Create geometry for internals
        switch ((long) m_DrillSyms[i])
        {
            case DBX_DRILLSYM_CROSS:
            case DBX_DRILLSYM_BOX_CROSS:
            case DBX_DRILLSYM_CIRCLE_CROSS:
            case DBX_DRILLSYM_DIAMOND_CROSS:
                lineobj.startPt.x = x - delta;
                lineobj.startPt.y = y;
                lineobj.endPt.x = x + delta;
                lineobj.endPt.y = y;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.x = x;
                lineobj.startPt.y = y + delta;
                lineobj.endPt.x = x;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
               break;

            case DBX_DRILLSYM_X:
            case DBX_DRILLSYM_BOX_X:
                lineobj.startPt.x = x - delta;
                lineobj.startPt.y = y + delta;
                lineobj.endPt.x = x + delta;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.x = x + delta;
                lineobj.startPt.y = y + delta;
                lineobj.endPt.x = x - delta;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_Y:
            case DBX_DRILLSYM_BOX_Y:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y;
                lineobj.endPt.x = x;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x - delta;
                lineobj.endPt.y = y + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_T:
            case DBX_DRILLSYM_DIAMOND_T:
            case DBX_DRILLSYM_BOX_T:
            case DBX_DRILLSYM_CIRCLE_T:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y;
                lineobj.endPt.x = x;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.x = x - delta;
                lineobj.endPt.x = x + delta;
                lineobj.endPt.y = y;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_HOUR:
                lineobj.startPt.x = x - delta;
                lineobj.startPt.y = y + delta;
                lineobj.endPt.x = x + delta;
                lineobj.endPt.y = y + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.y = y - delta;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.y = y + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.x = x + delta;
                lineobj.endPt.x = x - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_SIDE_HOUR:
                lineobj.startPt.x = x - delta;
                lineobj.startPt.y = y + delta;
                lineobj.endPt.x = x - delta;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.x = x + delta;
                lineobj.endPt.x = x + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.x = x - delta;
                lineobj.endPt.x = x + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_BOX_LINE:
            case DBX_DRILLSYM_DIAMOND_LINE:
            case DBX_DRILLSYM_CIRCLE_LINE:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y + delta;
                lineobj.endPt.x = x;
                lineobj.endPt.y = y;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_BOX_V:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y;
                lineobj.endPt.x = x - delta;
                lineobj.endPt.y = y + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x + delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_DIAMOND_V:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y;
                lineobj.endPt.x = x - delta/2;
                lineobj.endPt.y = y + delta/2;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x + delta/2;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
               break;

            case DBX_DRILLSYM_DIAMOND_X:
                lineobj.startPt.x = x - delta/2;
                lineobj.startPt.y = y + delta/2;
                lineobj.endPt.x = x + delta/2;
                lineobj.endPt.y = y - delta/2;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.y = y - delta/2;
                lineobj.endPt.y = y + delta/2;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_DIAMOND_Y:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y;
                lineobj.endPt.x = x - delta/2;
                lineobj.endPt.y = y + delta/2;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x + delta/2;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_CIRCLE_V:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y;
                lineobj.endPt.x = x - on_45;
                lineobj.endPt.y = y + on_45;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x + on_45;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_CIRCLE_X:
                lineobj.startPt.x = x - on_45;
                lineobj.startPt.y = y + on_45;
                lineobj.endPt.x = x + on_45;
                lineobj.endPt.y = y - on_45;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.startPt.y = y - on_45;
                lineobj.endPt.y = y + on_45;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_CIRCLE_Y:
                lineobj.startPt.x = x;
                lineobj.startPt.y = y;
                lineobj.endPt.x = x - on_45;
                lineobj.endPt.y = y + on_45;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x + on_45;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                lineobj.endPt.x = x;
                lineobj.endPt.y = y - delta;
                if ((m_tStatus = TPlaceLine(&m_tContext, &lineobj)) != DBX_OK) return;
                break;

            case DBX_DRILLSYM_UPPER_A:
            case DBX_DRILLSYM_UPPER_B:
            case DBX_DRILLSYM_UPPER_C:
            case DBX_DRILLSYM_UPPER_D:
            case DBX_DRILLSYM_UPPER_E:
            case DBX_DRILLSYM_UPPER_F:
            case DBX_DRILLSYM_UPPER_G:
            case DBX_DRILLSYM_UPPER_H:
            case DBX_DRILLSYM_UPPER_I:
            case DBX_DRILLSYM_UPPER_J:
            case DBX_DRILLSYM_UPPER_K:
            case DBX_DRILLSYM_UPPER_L:
            case DBX_DRILLSYM_UPPER_M:
            case DBX_DRILLSYM_UPPER_N:
            case DBX_DRILLSYM_UPPER_O:
            case DBX_DRILLSYM_UPPER_P:
            case DBX_DRILLSYM_UPPER_Q:
            case DBX_DRILLSYM_UPPER_R:
            case DBX_DRILLSYM_UPPER_S:
            case DBX_DRILLSYM_UPPER_U:
            case DBX_DRILLSYM_UPPER_V:
            case DBX_DRILLSYM_UPPER_W:
            case DBX_DRILLSYM_UPPER_Z:
            case DBX_DRILLSYM_LOWER_A:
            case DBX_DRILLSYM_LOWER_B:
            case DBX_DRILLSYM_LOWER_C:
            case DBX_DRILLSYM_LOWER_D:
            case DBX_DRILLSYM_LOWER_E:
            case DBX_DRILLSYM_LOWER_F:
            case DBX_DRILLSYM_LOWER_G:
            case DBX_DRILLSYM_LOWER_H:
            case DBX_DRILLSYM_LOWER_I:
            case DBX_DRILLSYM_LOWER_J:
            case DBX_DRILLSYM_LOWER_K:
            case DBX_DRILLSYM_LOWER_L:
            case DBX_DRILLSYM_LOWER_M:
            case DBX_DRILLSYM_LOWER_N:
            case DBX_DRILLSYM_LOWER_O:
            case DBX_DRILLSYM_LOWER_P:
            case DBX_DRILLSYM_LOWER_Q:
            case DBX_DRILLSYM_LOWER_R:
            case DBX_DRILLSYM_LOWER_S:
            case DBX_DRILLSYM_LOWER_T:
            case DBX_DRILLSYM_LOWER_U:
            case DBX_DRILLSYM_LOWER_V:
            case DBX_DRILLSYM_LOWER_W:
            case DBX_DRILLSYM_LOWER_Y:
            case DBX_DRILLSYM_LOWER_Z:
                dsnameid = (int) IDS_DS_FIRST + ((int) m_DrillSyms[i] - (int) DBX_DRILLSYM_CROSS);
                if (!dsname.LoadString(dsnameid)) break;
                dsn_ptr = dsname.GetBuffer(0);
                strcpy(textobj.text, dsn_ptr);
                textobj.refPoint.x = x;
                textobj.refPoint.y = y;
                if ((m_tStatus = TPlaceText(&m_tContext, &textobj)) != DBX_OK) return;
                break;

            default:
                break;
        }
    }

    return;
}

