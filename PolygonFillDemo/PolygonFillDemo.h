// PolygonFillDemo.h : main header file for the POLYGONFILLDEMO application
//

#if !defined(AFX_POLYGONFILLDEMO_H__F9DE151C_5F34_488C_A63D_88530DA7A513__INCLUDED_)
#define AFX_POLYGONFILLDEMO_H__F9DE151C_5F34_488C_A63D_88530DA7A513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPolygonFillDemoApp:
// See PolygonFillDemo.cpp for the implementation of this class
//

class CPolygonFillDemoApp : public CWinApp
{
public:
	CPolygonFillDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPolygonFillDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPolygonFillDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POLYGONFILLDEMO_H__F9DE151C_5F34_488C_A63D_88530DA7A513__INCLUDED_)
