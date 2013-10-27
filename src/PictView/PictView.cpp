// PictView.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PictView.h"

#include "MainFrm.h"
#include "PictViewDoc.h"
#include "PictViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern BOOL AFXAPI AfxFullPath(LPTSTR lpszPathOut, LPCTSTR lpszFileIn);

/////////////////////////////////////////////////////////////////////////////
// CPictViewApp

BEGIN_MESSAGE_MAP(CPictViewApp, CWinApp)
	//{{AFX_MSG_MAP(CPictViewApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16,OnOpenRecentMyFile)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictViewApp construction/destruction

CPictViewApp::CPictViewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/*
CPictViewApp::~CPictViewApp()
{
	delete m_pRecentFileListMyFiles;
}
*/

/////////////////////////////////////////////////////////////////////////////
// The one and only CPictViewApp object

CPictViewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPictViewApp initialization

BOOL CPictViewApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	/*
	//维护“最近打开的文件”列表
	m_pRecentFileListMyFiles =new CRecentFileList( 5,"最近的文件","MyFile%d",5);
	m_pRecentFileListMyFiles->ReadList(); 
	*/

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPictViewDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPictViewView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CPictViewApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewApp message handlers

 /*------------------------------------------------------------------------------------*\
 |																						|
 |	下面的函数及PictView 类中被注释掉的void AddToRecentFileList(LPCTSTR lpszPathName)、	|
 |	及本文件中与ID_FILE_MRU_FILE1、"RecentFileList"有关的语句是为了实现维护菜单中最近打	|
 |	开的列表而写的。因为系统默认维护的列表失效了。但是自己维护仍没有起作用。经过分析，	|
 |	发现有关文件打开的操作最好不要在View类中写，就像本程序一样，因为这样的话会绕过App及	|
 |	Doc类对文件打开的消息处理，从而使Recent File List失效。但因本程序对最近打文件列表无	|
 |	需求，并且在View中实现OnFileOpen()较容易进特效处理，故将最近文件列表Disable，而保持	|
 |	了现有的结构。																		|
 |                                                                         2005-4-21	|
 |                                                                           By:Neo		|
 \*------------------------------------------------------------------------------------*/

/*
void CPictViewApp::OnUpdateFileMruFile1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_pRecentFileListMyFiles == NULL) // no MRU files 
		pCmdUI->Enable(FALSE); 
	else 
	m_pRecentFileListMyFiles->UpdateMenu(pCmdUI);
}

BOOL CPictViewApp::OnOpenRecentMyFile(UINT nID)
{
 	int nIndex = nID - ID_FILE_MRU_MYFILE1;
 	if (OpenDocumentFile((*m_pRecentFileListMyFiles)[nIndex]) == NULL)
 	    m_pRecentFileListMyFiles->Remove(nIndex);
 	return TRUE;
}


int CPictViewApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_pRecentFileListMyFiles->WriteList();	//写入最近打开的文档列表
	return CWinApp::ExitInstance();
}

///////////////////////////////////////////////////////////////////////
// Overload of CWinApp::AddToRecentFileList() in class CPictViewApp
///////////////////////////////////////////////////////////////////////
void CPictViewApp::AddToRecentFileList(LPCTSTR lpszPathName)
{
    // Somehow determine doc type, I used file extension
	if (m_pRecentFileListMyFiles!= NULL)
	{
		// fully qualify the path name
		TCHAR szTemp[_MAX_PATH];
		AfxFullPath(szTemp, lpszPathName);

		// then add to recent file list
		m_pRecentFileListMyFiles->Add(szTemp);
	}
}
*/

