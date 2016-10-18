// PolygonFillDemoView.h : interface of the CPolygonFillDemoView class
//
/////////////////////////////////////////////////////////////////////////////
#include"StdAfx.h"
#if !defined(AFX_POLYGONFILLDEMOVIEW_H__2D88D208_CEA5_4383_B98B_603E44B4991E__INCLUDED_)
#define AFX_POLYGONFILLDEMOVIEW_H__2D88D208_CEA5_4383_B98B_603E44B4991E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagEDGE
{
     double xi;
     double dx;
     int ymax;
}EDGE;
typedef struct tagEDGES
{
  vector<EDGE> EDGE;
}EDGES;
typedef struct PolygonNode
{
	vector<CPoint> pts;
}MyPolygon;
class CPolygonFillDemoView : public CView
{
protected: // create from serialization only
	CPolygonFillDemoView();
	DECLARE_DYNCREATE(CPolygonFillDemoView)

// Attributes
public:
	CPolygonFillDemoDoc* GetDocument();
	CPen myPen;
	bool IS_Drawing;
    MyPolygon myPolygon;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolygonFillDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdateEDGE(vector<EDGE> &Edges,int y);
	void FillEdge(vector<EDGE> Edges,int y);
	void Insert_Sort(vector<EDGE> &Edges);
	void Bubble_Sort(vector<EDGE> &Edges);
	void InitScanLineNewEdgeTable(vector<EDGES> &slNet,MyPolygon py,int yMax,int yMin);
	void GetPolygonMinMax(MyPolygon polygon,int &yMax,int &yMin);
	void ScanLinePolygonFill(MyPolygon py, int color);
	virtual ~CPolygonFillDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPolygonFillDemoView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDrawPolygon();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PolygonFillDemoView.cpp
inline CPolygonFillDemoDoc* CPolygonFillDemoView::GetDocument()
   { return (CPolygonFillDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLYGONFILLDEMOVIEW_H__2D88D208_CEA5_4383_B98B_603E44B4991E__INCLUDED_)
