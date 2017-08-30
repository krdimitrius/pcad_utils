// stat_dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StatusDlg dialog

#include "resource.h"

class StatusDlg : public CDialog
{
// Construction
public:
    StatusDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    BOOL        userCancelled;
    CString     m_MsgText;
    
    //{{AFX_DATA(StatusDlg)
    enum { IDD = IDD_DIALOG_STATUS_BOX };
    CButton     m_CancelBtn;
    CStatic     mTextStatus;
    //}}AFX_DATA

    // this member function is called for closing the dialog box normally
    void Close();
    
    void InitText(const CString& Text, int Count = 1);

    void Update(int Count = 1);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(StatusDlg)
    afx_msg void OnCancel();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

};

