// DBXSamp4Doc.h : interface of the CDBXSamp4Doc class
//
/////////////////////////////////////////////////////////////////////////////
#ifndef DBXSAMP4DOC_H
#define DBXSAMP4DOC_H

class CDBXSamp4Doc : public CDocument
{
protected: // create from serialization only
	CDBXSamp4Doc();
	DECLARE_DYNCREATE(CDBXSamp4Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBXSamp4Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDBXSamp4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDBXSamp4Doc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif //DBXSAMP4DOC_H