// PolygonFillDemoDoc.cpp : implementation of the CPolygonFillDemoDoc class
//

#include "stdafx.h"
#include "PolygonFillDemo.h"

#include "PolygonFillDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoDoc

IMPLEMENT_DYNCREATE(CPolygonFillDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CPolygonFillDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CPolygonFillDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoDoc construction/destruction

CPolygonFillDemoDoc::CPolygonFillDemoDoc()
{
	// TODO: add one-time construction code here

}

CPolygonFillDemoDoc::~CPolygonFillDemoDoc()
{
}

BOOL CPolygonFillDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoDoc serialization

void CPolygonFillDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoDoc diagnostics

#ifdef _DEBUG
void CPolygonFillDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPolygonFillDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoDoc commands
