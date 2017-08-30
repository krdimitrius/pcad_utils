//
// drilldlg.h : header file
//

#include "dbx32.h" 

#include "widgets.h"

typedef enum {
DTAPP_ERROR = 0,
DTAPP_NOERROR,
DTAPP_NOHOLES,
DTAPP_USERABORT,
} DRILLTAB_ERROR;

typedef struct {
int psize;
int vsize;
int *p_padarray;
int *p_viaarray;
} PV_STYLE_REGISTRY;

class CStatusDlg;

/////////////////////////////////////////////////////////////////////////////
// CDrilltabDlg dialog

class CDrilltabDlg : public CDialog
{
// Construction
public:
    CDrilltabDlg(CWnd* pParent = NULL);   // standard constructor
    ~CDrilltabDlg(); 
    
// Dialog Data
    //{{AFX_DATA(CDrilltabDlg)
    enum { IDD = IDD_DTAPP_DLG };
    CButton m_LocLowLeft;
    CButton m_UnitsInch;
    CEdit   m_Y;
    CEdit   m_X;
    CEdit   m_Title;
    CEdit   m_LineWidth;
    CEdit   m_ColumnWidth;
    CEdit   m_ColumnLabel;
    CComboBox   m_TextStyle;
    CComboBox   m_Layer;
    HWND    m_Grid;
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CDrilltabDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

    // Various PCB conversation and status members
    DbxContext      m_tContext;       // Global DBX conversation data
    long            m_tStatus;        // Global DBX status indicator
    BOOL            m_DsgnIsOpen;     // Status of design conversation
    BOOL            m_WarnedNoSym;    // User warned for first symbol-less hole

    // General Drill table grid description members
    CWordArray      m_ColWidths;      // Ordered column widths (spec'd min char count)
    CDWordArray     m_HoleSizes;      // Ordered hole sizes (db units)
    CDWordArray     m_DrillSyms;      // Ordered drill symbol identifiers
    CWordArray      m_HoleQntys;      // Ordered hole counts

    // Converted/validated members (deciphered from dialog input)
    long        m_DbLineWidth;
    long        m_LayerId;
    long        m_TextStyleId;
    long        m_DbX;
    long        m_DbY;

// Implementation
protected:
    void            GridCtlsUpdate();
    DRILLTAB_ERROR  HoleRegister(CStatusDlg &status_dlg);
    DRILLTAB_ERROR  StyleRegister(PV_STYLE_REGISTRY *pvsreg,
                                  CStatusDlg &status_dlg);
    DRILLTAB_ERROR  WarnNoSymbol(BOOL isvia, long styleid);
    BOOL            DlgDataValidate();
    BOOL            DrillTableCreate();
    void            DrillSymbolsCreate(TCoord firstcntr, long yincr);

    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CDrilltabDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnFileExit();
    afx_msg void OnHelpAbout();
    afx_msg void OnOk();
    afx_msg void OnRecchangedGrid();
    afx_msg void OnSelchangeGrid();
    afx_msg void OnColumnDel();
    afx_msg void OnColumnAdd();
    afx_msg void OnHdunitsin();
    afx_msg void OnHdunitsmm();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
