// PictViewDoc.cpp : implementation of the CPictViewDoc class
//

#include "stdafx.h"
#include "PictView.h"

#include "PictViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc

IMPLEMENT_DYNCREATE(CPictViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CPictViewDoc, CDocument)
	//{{AFX_MSG_MAP(CPictViewDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc construction/destruction

CPictViewDoc::CPictViewDoc()
{
	// TODO: add one-time construction code here
	m_bIsEmptyDoc = TRUE;	//是否为空文档
	m_bIsEmptyDir = FALSE;	//程序初始时置为FALSE.否则会直接在用户区显示“无图像”提示。
}

CPictViewDoc::~CPictViewDoc()
{
}

BOOL CPictViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	m_bIsEmptyDoc=TRUE;	//标志为空文档
	//SetTitle("未打开任何文件"); //Set File name for Title line when window is loaded.
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc serialization

void CPictViewDoc::Serialize(CArchive& ar)
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

BOOL CPictViewDoc::InitPicList(LPCTSTR pszFileName)
{ 
	//BOOL bRet = FALSE;
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];
	_splitpath(pszFileName, drive, dir, fname, ext); 

	CString str;
	str.Format("%s%s",drive,dir);
	str = str + "*.*";

	CFileFind cFind;
	BOOL ans = cFind.FindFile(str);
	m_iFileNumber = 0;
	while(ans)
	{
		if(m_iFileNumber<MAX_SEARCH_NUM)
		{
			ans = cFind.FindNextFile();
			if(cFind.IsDirectory())		//如果找到的是目录则跳过
				continue;
			CString FilName = cFind.GetFileName();
			LPCTSTR pszExt = _tcsrchr(FilName,_T('.'));

			if(pszExt)		//如果有扩展名，则继续分析扩展名，否则不分析。如果无扩展名仍分析
							//则_tcsicmp()会执行出错.
			{//##**##
				if((_tcsicmp(pszExt,".bmp") == 0)||(_tcsicmp(pszExt,".tga") == 0)
					||(_tcsicmp(pszExt,".pcx") == 0)||(_tcsicmp(pszExt,".jpg") == 0)
					||(_tcsicmp(pszExt,".jpeg") == 0)||(_tcsicmp(pszExt,".gif") == 0))
				{
					m_PicList[m_iFileNumber] = cFind.GetFileName();
					CString FilePath;
					FilePath.Format("%s%s",drive,dir);
					m_PicList[m_iFileNumber] = FilePath + m_PicList[m_iFileNumber] ;
					m_iFileNumber++;
				}
			}
		}
		else
		{
			CString	sPrompt;
			int		num = MAX_SEARCH_NUM;
			sPrompt.Format("当前目录中包含的图片文件多于%d个，当翻页浏览时将只显示前%d个。",num,num);
			AfxMessageBox("sPrompt");
		}
	}

	m_iFileNumber--;	//因为上面while每循环一次m_iFileNumber加1，当最后一张图片进入列表后仍加1
						//故比实际的个数多一，在此减去。
	cFind.Close();
	return TRUE;
}

void CPictViewDoc::ReInitPicList()
{
	//在删除的图片列表前的文件列表部分不变
	//在删除的图片列表后的部分列表前移
	for(int i = m_iCurrFileNum + 1;i<=m_iFileNumber;i++)
	{
		m_PicList[i - 1] = m_PicList[i];
	}
	m_iFileNumber--;
}
/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc diagnostics

#ifdef _DEBUG
void CPictViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPictViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictViewDoc commands

void CPictViewDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bIsEmptyDoc || m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	
}

void CPictViewDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_bIsEmptyDoc || m_bIsEmptyDir)
		pCmdUI->Enable(!m_bIsEmptyDoc);
	else
		pCmdUI->Enable(TRUE);

}
