// PictView.h : main header file for the PICTVIEW application
//

#if !defined(AFX_PICTVIEW_H__E385D5F5_B128_429E_BAE3_69C4BDE03CD1__INCLUDED_)
#define AFX_PICTVIEW_H__E385D5F5_B128_429E_BAE3_69C4BDE03CD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
//#include "afxadv.h"


/////////////////////////////////////////////////////////////////////////////
// CPictViewApp:
// See PictView.cpp for the implementation of this class
//

class CPictViewApp : public CWinApp
{
public:
	CRecentFileList *m_pRecentFileListMyFiles;
public:
	CPictViewApp();
	//~CPictViewApp();
	//void AddToRecentFileList(LPCTSTR lpszPathName);	//÷ÿ‘ÿCWinApp::AddToRecentFileList().

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPictViewApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTVIEW_H__E385D5F5_B128_429E_BAE3_69C4BDE03CD1__INCLUDED_)
