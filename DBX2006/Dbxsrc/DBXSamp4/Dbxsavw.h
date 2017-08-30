// dbxsavw.h : interface of the CDbxsamp4View class
//
/////////////////////////////////////////////////////////////////////////////

#include "dbx32.h"

class CDbxsamp4View : public CView
{
public:

    CButton *pStartButton;
    CButton *pExitButton;
    
protected: // create from serialization only
    CDbxsamp4View();
    DECLARE_DYNCREATE(CDbxsamp4View)

// Operations
public:

// Implementation
public:
    virtual ~CDbxsamp4View();
    virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
    //{{AFX_MSG(CDbxsamp4View)
    afx_msg void OnStartButtonClicked();
    afx_msg void OnExitButtonClicked();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

    DbxContext      tContext;       // Global DBX Conversation Data
    long            tStatus;        // Global Return status variable
};

/////////////////////////////////////////////////////////////////////////////
