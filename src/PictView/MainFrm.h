// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__56937ADC_A76C_414F_A968_468B05E9DEE6__INCLUDED_)
#define AFX_MAINFRM_H__56937ADC_A76C_414F_A968_468B05E9DEE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected:	// create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:	//自己添加的成员变量
	WINDOWPLACEMENT	m_OldWndPlacement;	//用来保存原窗口位置
	BOOL			m_bFullScreen;		//全屏显示标志
	BOOL			m_bScrModeChged;	//标志是否进行显示模式(全屏/非全屏)切换
	BOOL			m_bIsPlay;			//是否正在进行幻灯片播放
	BOOL			m_bIsFullBarShowed;	//全屏工具栏当前是否显示
	BOOL			m_bTiming;			//是否正在计时(以自动隐藏工具栏)
	CRect			m_FullScreenRect;	//表示全屏显示时的窗口位置
	CToolBar		*m_pwndFullScrnBar;	//全屏时的工具栏


public:
	CStatusBar  m_wndStatusBar;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void EndFullScreen();
	void StartTimer();
	void StopTimer();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar    m_wndToolBar;

// Generated message map functions
public:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewStatusBar();
	afx_msg void OnUpdateViewStatusBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLeft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRight(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnFullScreen();
	afx_msg void OnUpdateFullScreen(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__56937ADC_A76C_414F_A968_468B05E9DEE6__INCLUDED_)
