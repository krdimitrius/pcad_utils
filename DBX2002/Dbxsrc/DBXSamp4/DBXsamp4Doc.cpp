// DBXSamp4Doc.cpp : implementation of the CDBXSamp4Doc class
//

#include "stdafx.h"
#include "DBXSamp4.h"

#include "DBXSamp4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBXSamp4Doc

IMPLEMENT_DYNCREATE(CDBXSamp4Doc, CDocument)

BEGIN_MESSAGE_MAP(CDBXSamp4Doc, CDocument)
	//{{AFX_MSG_MAP(CDBXSamp4Doc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBXSamp4Doc construction/destruction

CDBXSamp4Doc::CDBXSamp4Doc()
{
}

CDBXSamp4Doc::~CDBXSamp4Doc()
{
}

BOOL CDBXSamp4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDBXSamp4Doc serialization

void CDBXSamp4Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDBXSamp4Doc diagnostics

#ifdef _DEBUG
void CDBXSamp4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDBXSamp4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBXSamp4Doc commands
