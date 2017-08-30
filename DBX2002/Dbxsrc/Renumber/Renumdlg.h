//
// dlgdlg.h : header file
// the project global header file

#include "complist.h"
#include "compitem.h"
#include "rfdeslst.h"
#include "Dbx32.h"
#include "resource.h"
#include "utility.h"


enum RenameDirection { LR_DOWN, DOWN_LR, LR_UP, UP_LR };

enum CurrentSide { TOP_SIDE, BOTTOM_SIDE };

enum RadioButtonState { RADIO_BTN_OFF, RADIO_BTN_ON, RADIO_BTN_IND };

// Utilities used globally
void FormatLBStr(CString& PrefStr, const CString& StartIndex);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    //{{AFX_DATA(CAboutDlg)
    enum { IDD = IDD_ABOUTBOX };
    //}}AFX_DATA

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CAboutDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    //{{AFX_MSG(CAboutDlg)
//    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// RenumberDlg dialog

class RenumberDlg : public CDialog
{
// Construction
public:
    RenumberDlg(CWnd* pParent = NULL);  // standard constructor
    ~RenumberDlg(void);
    
// Dialog Data
    //{{AFX_DATA(RenumberDlg)
    enum { IDD = IDD_RENUMBER_DLG };
    CStatic     m_NbrComps;                 // used only for debugging, i.e., when _DEBUG defined
    CButton     m_LftRgtTopBotBtn;
    CButton     m_BotTopLftRgtBtn;
    CButton     m_TopBotLftRgtBtn;
    CButton     m_LftRgtBotTopBtn;
    CButton     m_FlippedAllBtn;
    CButton     m_FlippedTopOnlyBtn;
    CButton     m_FlippedTopBotBtn;
    CButton     m_FlippedBotOnlyBtn;
    CEdit       m_StartIndexCtl;
    CEdit       m_PassWidthCtl;
    CButton     m_SetIndexBtn;
    CButton     m_SelectAllBtn;
    CButton     m_RefreshBtn;
    CButton     m_ClearAllBtn;
    CButton     m_RenumberBtn;
    CListBox    m_PrefixIndex;
    CStatic     m_DesignName;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(RenumberDlg)
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    afx_msg void OnSelchangePrefixIndex();
    afx_msg void OnClearAll();
    afx_msg void OnRenumber();
    afx_msg void OnSelectAll();
    afx_msg void OnSetIndex();
    afx_msg void OnLftRgtBotTop();
    afx_msg void OnLftRgtTopBot();
    afx_msg void OnRefresh();
    afx_msg void OnFileExit();
    afx_msg void OnHelpAbout();
    afx_msg void OnBotTopLftRgt();
    afx_msg void OnTopBotLftRgt();
    afx_msg void OnFlippedOptsAll();
    afx_msg void OnFlippedOptsBotOnly();
    afx_msg void OnFlippedOptsTopBot();
    afx_msg void OnFlippedOptsTopOnly();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DbxContext      tContext;       // Global DBX Conversation Data
    long            tStatus;        // Global Return status variable
    TDesign         tDesignInfo;
    BOOL            bDesignOpen;
    BOOL            exit_flag;      // flag used for debugging - commented out for release
    BOOL            listSorted;
    BOOL            userQuit;
        
    // renumber sort and pass control parameters
    long            lPassWidth;     // default: 1270000 app units = 500 mils
    long            lPassStart;
    long            lPassEnd;
    long            lPassWidthMils;
    long            lMinRefPointX;  // The minimum of all component refPoints
    long            lMinRefPointY;  // The minimum of all component refPoints
    long            lMaxRefPointX;  // The maximum of all component refPoints
    long            lMaxRefPointY;  // The maximum of all component refPoints
    CoordName       nSortKey;       // Tells SortComponents which coordinate of refPoint to sort on
    CoordName       nPassKey;       // Tells IsCompInThisPass which coordinate of refPoint to use

    int             nSelComps;      // Number of components selected
    int             nTopComps;      // Number of components on top side
    int             nBotComps;      // Number of components on bottom side

    int             nRenComps;      // Number of components renumbered
    ComponentList   *pCompList;
    int             compIndx;

    // the following is a list of components which have been given temporary refDes's
    int             nTempRefDes;    // Number of components with temporary refDes's
    ComponentList   *pTempRefDesList;

    RefDesList      *pPrefsIndices; // List of RefDes prefixes and indices

    RenameDirection nRenameDirect;

    FlippedOption   nFlippedOption;
    FlippedOption   nLastRenumOperation;
    
    CurrentSide     nCurrentSide;
    CurrentSide     nLastSide;
        
    // member functions
    BOOL OpenDesign(void);

    void SetDefaults(void);
    
    void PrepareOperation(void);

    void DeleteTempRefDesList(void);

    // this function builds a list (CObList pCompList) of components which are 
    // selected/hilited in the PCB design
    void GetSelectedComponents(void);

    void EnableButtons();
    
    void RenumberComponents(void);

    void ModifyComponentRefDes(ComponentItem *pCompItem);
    
    char *GetNewRefDes(char *pOldRefDes);

    BOOL IsCompInThisPass(ComponentItem *pCompItem);
    
    void InitRenumParameters(void);

    void SetNextPass(void);

    void EliminateDuplicateRefDes(char *refDes, ComponentItem *pCompItem);
    
    void RemoveTempRefDesComp(char *pTempRefDes);

    void UpdateDialogControls(void);

    void SortComponents(void);

    BOOL IsValidPassWidth(void);

    void ShowTempRefDesList(void);

    BOOL IsValidStartIndex(void);

};

