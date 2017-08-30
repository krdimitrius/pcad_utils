// statdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatusDlg dialog

class CStatusDlg : public CDialog
{
// Construction
public:
    CStatusDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CStatusDlg)
    enum { IDD = IDD_STATUS_DLG };
    CStatic m_StatusText;
    //}}AFX_DATA
    
// Implementation
public:
    void TitleTextSet(char* ttext);
    void MsgTextSet(char* itext,
                     int icnt = -1,
                     char* mtext = NULL,
                     int mcnt = -1,
                     char* ttext = NULL);
    void Display(void);
    void WinDestroy(void);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CStatusDlg)
        // NOTE: the ClassWizard will add member functions here
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
