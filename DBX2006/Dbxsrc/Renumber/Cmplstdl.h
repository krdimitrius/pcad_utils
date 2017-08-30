// cmplstdl.h : header file
//

#include "complist.h"

#define SHOW_COMP_LIST      0
#define SHOW_UNNUM_LIST     1


/////////////////////////////////////////////////////////////////////////////
// CCmpLstDlg dialog

class CCmpLstDlg : public CDialog
{
// Construction
public:
    CCmpLstDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CCmpLstDlg)
    enum { IDD = IDD_COMPLIST };
    CStatic     m_LBHdrType;
    CStatic     m_LBHdrRefDes;
    CStatic     m_LBHdrLoc;
    CListBox    m_CompListCtl;
    //}}AFX_DATA

    void SetDialogData(ComponentList *pList, int nWhich);

    void ShowCompList(void);

    void ShowUnNumberedComps(void);


// Implementation
protected:
    ComponentList   *m_pCList;

    int         m_ShowListBox;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CCmpLstDlg)
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

