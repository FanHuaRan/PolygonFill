// PolygonFillDemoView.cpp : implementation of the CPolygonFillDemoView class
//

#include "stdafx.h"
#include "PolygonFillDemo.h"

#include "PolygonFillDemoDoc.h"
#include "PolygonFillDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoView

IMPLEMENT_DYNCREATE(CPolygonFillDemoView, CView)

BEGIN_MESSAGE_MAP(CPolygonFillDemoView, CView)
	//{{AFX_MSG_MAP(CPolygonFillDemoView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_Draw, OnDrawPolygon)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoView construction/destruction

CPolygonFillDemoView::CPolygonFillDemoView()
{
	// TODO: add construction code here
	IS_Drawing=true;
	myPen.CreatePen(PS_SOLID,1,RGB(255,255,0));
}

CPolygonFillDemoView::~CPolygonFillDemoView()
{
}

BOOL CPolygonFillDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoView drawing

void CPolygonFillDemoView::OnDraw(CDC* pDC)
{
	CPolygonFillDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	/*
	 CPoint point1;
	 point1.x=200;
	 point1.y=230;
	 CPoint point2;
	 point2.x=250;
	 point2.y=230;
	 CPoint point3;
	 point3.x=28;
	 point3.y=250;
	 CPoint point4;
	 point4.x=21;
	 point4.y=250;
	 CPoint point5;
	 point5.x=210;
	 point5.y=550;
	 */
	 CPoint point1;
	 point1.x=446;
	 point1.y=56;
	 CPoint point2;
	 point2.x=620;
	 point2.y=71;
	 CPoint point3;
	 point3.x=537;
	 point3.y=197;
	 MyPolygon py;
	 py.pts.push_back(point1);
	 py.pts.push_back(point2);
	 py.pts.push_back(point3);
	// py.pts.push_back(point4);
	// py.pts.push_back(point5);
	 ScanLinePolygonFill(py,RGB(255,0,0));
	 
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoView printing

BOOL CPolygonFillDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPolygonFillDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPolygonFillDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoView diagnostics

#ifdef _DEBUG
void CPolygonFillDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CPolygonFillDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPolygonFillDemoDoc* CPolygonFillDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPolygonFillDemoDoc)));
	return (CPolygonFillDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoView message handlers
//多边形扫描线填充
void CPolygonFillDemoView::ScanLinePolygonFill(MyPolygon py, int color)
{
     int ymin = 100000;
     int ymax = 0;
	 GetPolygonMinMax(py, ymax, ymin);
	 vector<EDGES> slNet;
	 //初始化有序边表
     InitScanLineNewEdgeTable(slNet, py, ymax,ymin);
	 //初始化活性边
	 vector<EDGE> edges;
	 //填充每条扫描边
	 for(int i=ymin;i<(ymax+1);i++)
	 {
		vector<EDGE> edTest=slNet[i-ymin].EDGE;
		for(int j=0;j<slNet[i-ymin].EDGE.size();j++)
		{
			edges.push_back(edTest[j]);
		} 
		//进行插入排序 从小到大排列新边表
		Insert_Sort(edges);
		//填充
		FillEdge(edges,i);
		//修改结点
        UpdateEDGE(edges,i);
		//冒泡排序
		Bubble_Sort(edges);
	 }
}

//寻找多边形的y坐标的最大最小值
void CPolygonFillDemoView::GetPolygonMinMax(MyPolygon polygon, int &yMax, int &yMin)
{
   for(int i=0;i<polygon.pts.size();i++)
   {
       CPoint temp=polygon.pts[i];
	   if(yMax<polygon.pts[i].y)
	   {
		   yMax=polygon.pts[i].y;
	   }
	    if(yMin>polygon.pts[i].y)
	   {
		   yMin=polygon.pts[i].y;
	   }
   }
}
//InitScanLineNewEdgeTable()函数根据多边形的顶点和边的情况初始化有序边表，
////////////实现过程中体现了对左顶点和右顶点的区间修正原则：
void CPolygonFillDemoView::InitScanLineNewEdgeTable(vector<EDGES> &slNet,MyPolygon py,int yMax,int yMin)
{
	for(int xx=0;xx<py.pts.size();xx++)
	{
		int x=py.pts[xx].x;
		int y=py.pts[xx].y;
	}
	int lenth=py.pts.size();
	//将边底点y坐标为i的边存入新边表
	for(int i=yMin;i<(yMax+1);i++)
	{
		EDGES  edges;
		for(int j=0;j<lenth;j++)
		{
			CPoint p0=py.pts[j];
			if(p0.y==i)
			{
				CPoint p1;
				CPoint p2;
				if(j==(lenth-1))
				{
					p1=py.pts[0];
					p2=py.pts[lenth-2];
				}
				else if(j==0)
				{
					p1=py.pts[1];
					p2=py.pts[lenth-1];
				}
				else
				{	p1=py.pts[j+1];
					p1=py.pts[j-1];
				}
				//如果是水平边或者p0不为底点则不做处理
				if(p0.y<p1.y)
				{
					 EDGE edge1;
					 edge1.xi=p0.x;
					 edge1.dx=((double)(p1.x-p0.x)/(p1.y-p0.y));
					 edge1.ymax=p1.y;
				   	 edges.EDGE.push_back(edge1);
				}
				//如果是水平边或者p0不为底点则不做处理
				if(p0.y<p2.y)
				{
				  EDGE edge2;
			  	  edge2.xi=p0.x;
				  edge2.dx=((double)(p2.x-p0.x)/(p2.y-p0.y));
				  edge2.ymax=p2.y;
				  edges.EDGE.push_back(edge2);
				}
			}
		}
			slNet.push_back(edges);
		}
}
//冒泡排序
void CPolygonFillDemoView::Bubble_Sort(vector<EDGE> &Edges)
{
	int n=Edges.size();
	int i,j,swap;
	EDGE temp;
	for(i=0;i<n-1;i++)
	{
		swap=0;
		for(j=0;j<n-i-1;j++)
		{
			if(Edges[j].xi>Edges[j+1].xi)
			{
				temp=Edges[j];
				Edges[j]=Edges[j+1];
				Edges[j+1]=temp;
				swap=1;
			}
		}
		if(swap==0) break;
	}
}
//插入排序
void CPolygonFillDemoView::Insert_Sort(vector<EDGE> &Edges)
{
	int n=Edges.size();
	EDGE temp;
	for(int i=1;i<n;i++)
	{
		if(Edges[i].xi<Edges[i-1].xi)
		{
			temp=Edges[i];
			for(int j=i-1;temp.xi<Edges[j].xi;j--)
			{
				Edges[j+1]=Edges[j];
			}
			Edges[j+1]=temp;
		}
	}
}
//填充活性边中间的像素
void CPolygonFillDemoView::FillEdge(vector<EDGE> Edges,int y)
{
	  CClientDC dc(this);
	  if(Edges.size()<2)
		  return;
	  for(int i=0;i<Edges.size();i++)
	  {
		  if(i==(Edges.size()-1))
			  break;
		  int x=Edges[i].xi;
		  while(x<Edges[i+1].xi)
		  {
			dc.SetPixel(x,y,RGB(255,0,0));
			x++;
		  }
	  }
}
//根据y值修改活化边
void CPolygonFillDemoView::UpdateEDGE(vector<EDGE> &Edges,int y)
{
	for(vector<EDGE>::iterator it=Edges.begin();it!=Edges.end();it++)
	{
	   //如果边结点的ymax值大于扫描线 则删除该结点
	   if(it->ymax==(y+1))
	   {
		   Edges.erase(it);
	   }
	   //否则就把xi加上对应的斜率倒数
	   else if(it->ymax>(y+1))
	   {
		   it->xi+=it->dx;
	   }
	}
}

void CPolygonFillDemoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(IS_Drawing==true)
	{
		myPolygon.pts.push_back(point);
		if(myPolygon.pts.size()!=1)
		{
			CClientDC dc(this);
			CPen myPen(PS_SOLID,1,RGB(255,0,0));
			dc.SelectObject(myPen);
			dc.MoveTo(myPolygon.pts[myPolygon.pts.size()-2]);
			dc.LineTo(myPolygon.pts[myPolygon.pts.size()-1]);
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CPolygonFillDemoView::OnDrawPolygon() 
{
	// TODO: Add your command handler code here
	IS_Drawing=true;
	myPolygon.pts.clear();
}

void CPolygonFillDemoView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(IS_Drawing)
	{
		if(myPolygon.pts.size()<3)
		{
			MessageBox("请至少点击三个点");
			return;
		}
		
			CClientDC dc(this);
			CPen myPen(PS_SOLID,1,RGB(255,0,0));
			dc.SelectObject(myPen);
			dc.MoveTo(myPolygon.pts[myPolygon.pts.size()-2]);
			dc.LineTo(myPolygon.pts[myPolygon.pts.size()-1]);
			dc.LineTo(myPolygon.pts[0]);
			IS_Drawing=false;
			ScanLinePolygonFill(myPolygon,0);
	}
	CView::OnRButtonDown(nFlags, point);
}
