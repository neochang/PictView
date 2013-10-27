// PictViewView.cpp : implementation of the CPictViewView class
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

/////////////////////////////////////////////////////////////////////////////
// CPictViewView

IMPLEMENT_DYNCREATE(CPictViewView, CScrollView)

BEGIN_MESSAGE_MAP(CPictViewView, CScrollView)
	//{{AFX_MSG_MAP(CPictViewView)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, OnUpdateFileMruFile1)
	ON_COMMAND(ID_USE_SPECIAL_EFFECT, OnUseSpecialEffect)
	ON_UPDATE_COMMAND_UI(ID_USE_SPECIAL_EFFECT, OnUpdateUseSpecialEffect)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_ZOOM_HALF, OnZoomHalf)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_HALF, OnUpdateZoomHalf)
	ON_COMMAND(ID_ZOOM_ORIGINAL, OnZoomOriginal)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_ORIGINAL, OnUpdateZoomOriginal)
	ON_COMMAND(ID_ZOOM_DOUBLE, OnZoomDouble)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_DOUBLE, OnUpdateZoomDouble)
	ON_COMMAND(ID_ZOOM_75PERCENT, OnZoom75percent)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_75PERCENT, OnUpdateZoom75percent)
	ON_COMMAND(ID_ZOOM_150PERCENT, OnZoom150percent)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_150PERCENT, OnUpdateZoom150percent)
	ON_COMMAND(ID_EFFECT_RANDOM, OnEffectRandom)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_RANDOM, OnUpdateEffectRandom)
	ON_COMMAND(ID_EFFECT_MOSAIC, OnEffectMosaic)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_MOSAIC, OnUpdateEffectMosaic)
	ON_COMMAND(ID_EFFECT_BLINDS, OnEffectBlinds)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_BLINDS, OnUpdateEffectBlinds)
	ON_COMMAND(ID_EFFECT_TOPDOWN, OnEffectTopdown)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_TOPDOWN, OnUpdateEffectTopdown)
	ON_COMMAND(ID_EFFECT_BOTTOMUP, OnEffectBottomup)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_BOTTOMUP, OnUpdateEffectBottomup)
	ON_COMMAND(ID_EFFECT_LEFTRIGHT, OnEffectLeftright)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_LEFTRIGHT, OnUpdateEffectLeftright)
	ON_COMMAND(ID_EFFECT_RIGHTLEFT, OnEffectRightleft)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_RIGHTLEFT, OnUpdateEffectRightleft)
	ON_COMMAND(ID_EFFECT_TOPLEFT, OnEffectTopleft)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_TOPLEFT, OnUpdateEffectTopleft)
	ON_COMMAND(ID_EFFECT_BOTTOMLEFT, OnEffectBottomleft)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_BOTTOMLEFT, OnUpdateEffectBottomleft)
	ON_COMMAND(ID_EFFECT_TOPRIGHT, OnEffectTopright)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_TOPRIGHT, OnUpdateEffectTopright)
	ON_COMMAND(ID_EFFECT_BOTTOMRIGHT, OnEffectBottomright)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_BOTTOMRIGHT, OnUpdateEffectBottomright)
	ON_COMMAND(ID_VIEW_PREVIOUS, OnViewPrevious)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIOUS, OnUpdateViewPrevious)
	ON_COMMAND(ID_VIEW_NEXT, OnViewNext)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NEXT, OnUpdateViewNext)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_ZOOM_IN, OnZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, OnUpdateZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, OnZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, OnUpdateZoomOut)
	ON_COMMAND(ID_EDIT_EXTERNAL, OnEditExternal)
	ON_UPDATE_COMMAND_UI(ID_EDIT_EXTERNAL, OnUpdateEditExternal)
	ON_COMMAND(ID_EDIT_IN_MPAINT, OnEditInMpaint)
	ON_UPDATE_COMMAND_UI(ID_EDIT_IN_MPAINT, OnUpdateEditInMpaint)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_PLAY, OnPlay)
	ON_UPDATE_COMMAND_UI(ID_PLAY, OnUpdatePlay)
	ON_COMMAND(ID_PAUSE, OnPause)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdatePause)
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_FULL_SCREEN, OnFullScreen)
	ON_COMMAND(ID_ZOOM_FITSCREEN, OnZoomFitscreen)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_FITSCREEN, OnUpdateZoomFitscreen)
	ON_COMMAND(ID_ROTATE90_CLOCKWISE, OnRotate90Clockwise)
	ON_UPDATE_COMMAND_UI(ID_ROTATE90_CLOCKWISE, OnUpdateRotate90Clockwise)
	ON_COMMAND(ID_EFFECT_MEM_VBLINDS, OnEffectMemVblinds)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_MEM_VBLINDS, OnUpdateEffectMemVblinds)
	ON_COMMAND(ID_EFFECT_MEM_HBLINDS, OnEffectMemHblinds)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_MEM_HBLINDS, OnUpdateEffectMemHblinds)
	ON_COMMAND(ID_EFFECT_MEM_MOSAIC, OnEffectMemMosaic)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_MEM_MOSAIC, OnUpdateEffectMemMosaic)
	ON_COMMAND(ID_EFFECT_MEM_SCANFROMTOP, OnEffectMemScanfromtop)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_MEM_SCANFROMTOP, OnUpdateEffectMemScanfromtop)
	ON_COMMAND(ID_EFFECT_MEM_SCANFROMBOTTOM, OnEffectMemScanfrombottom)
	ON_UPDATE_COMMAND_UI(ID_EFFECT_MEM_SCANFROMBOTTOM, OnUpdateEffectMemScanfrombottom)
	ON_COMMAND(ID_ROTATE90_ANTICLOCKWISE, OnRotate90Anticlockwise)
	ON_UPDATE_COMMAND_UI(ID_ROTATE90_ANTICLOCKWISE, OnUpdateRotate90Anticlockwise)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSave)
	ON_COMMAND(ID_ROTATE180, OnRotate180)
	ON_UPDATE_COMMAND_UI(ID_ROTATE180, OnUpdateRotate180)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictViewView construction/destruction

CPictViewView::CPictViewView()
{
	// TODO: add construction code here

	//m_IsRandomEffect = TRUE;
	m_showX=0;
	m_showY=0;
	m_degree=1;
	m_Llower_rate=1.0;
	m_IsRandomEffect=TRUE;
	m_IsNormalShow=FALSE;	//默认状态为使用特效
	m_Isconvert=FALSE;		//m_Isconvert Specify if the file is to be converted to 32bit

}

CPictViewView::~CPictViewView()
{
}

BOOL CPictViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewView diagnostics

#ifdef _DEBUG
void CPictViewView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPictViewView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPictViewDoc* CPictViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPictViewDoc)));
	return (CPictViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictViewView printing

BOOL CPictViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPictViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPictViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewView drawing

void CPictViewView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

///*******  图像的显示  ***********///
void CPictViewView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here
	CPictViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if(!(pDoc->m_bIsEmptyDir))		//当m_bIsEmptyDir为TRUE时说明当前目录已无文件，不再显示
	{
		if(m_LImage.IsLoad() == FALSE)
			return;

		CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		if(pFrame->m_bScrModeChged)	//进行了显示模式切换，重新计算图片显示位置
		{
			CRect rect;
			GetClientRect(&rect);							//获取用户区矩形
			m_nWindowWidth = rect.right - rect.left;		//计算宽度
			m_nWindowHeight = rect.bottom - rect.top;		//计算高度

			//只有当显示的宽、高小于客户区宽高时才居中，	
			//否则直接从左上角开始显示.如果不这样滚动条位置会不正确
			//而且当显示大小超出客户区时居中也没有意义。
			if(m_LImage.m_nDrawWidth<m_nWindowWidth)
				m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
			else 
				m_showX = 0;
			if(m_LImage.m_nDrawHeight<m_nWindowHeight)
				m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
			else
				m_showY = 0;

			pFrame->m_bScrModeChged = FALSE;
		}
	
		int transform=0;						//从上下左右进入屏幕的渐变变量。
		int transform_w=0,transform_h=0;		//从四个角进入屏幕的渐变的x,y方向的变量。

		if(m_IsRandomEffect && !m_IsNormalShow && m_bIsDrawFirstTime)
		{
			srand( (unsigned)time( NULL ) );	//Seed the random-number generator with current time so that 
												//the numbers will be different every time we run.
			m_EffectNum = rand()%11;			//如果是随机效果,产生随机数，以便在载入及变换时使用随机效果
		}
	/*==============================********************====================*\
	|                           图像载入时的显示特效
	|
	| <!!-只有第一次载入或变换时才可能使用特效，如系统调用OnDraw()则正常显示-!!>
	|
	| 0:正常显示；1:马赛克效果2:从上往下3:从下往上4:从左往右5:从右往左
	| 6:从左上角进入7:从右上角进入8:从左下角进入9:从右下角进入
	\*==============================********************====================*/
		if((m_bIsDrawFirstTime == TRUE)&&(m_IsNormalShow == FALSE))	//是第一次绘制，则使用特效
		{
			switch(m_EffectNum)
			{
		
				case Mosaic:		//马赛克效果
					Effect_Mosaic(pDC);
					break;
				case fromtop:		//从上往下
					Effect_Fromtop(pDC,transform);
					break;
				case frombottom:	//从下往上
					Effect_Frombottom(pDC,transform);
					break;
				case fromleft:		//从左往右
					Effect_Fromleft(pDC,transform);
					break;
				case fromright:		//从右往左
					Effect_Fromright(pDC,transform);
					break;
				case fromtopleft:	//从左上角进入
					Effect_Fromtopleft(pDC, transform_w, transform_h);
					break;
				case fromtopright:	//从右上角进入
					Effect_Fromtopright(pDC, transform_w, transform_h);
					break;
				case frombottomleft://从左下角进入
					Effect_Frombottomleft(pDC, transform_w, transform_h);
					break;
				case frombottomright://从右下角进入
					Effect_Frombottomright(pDC, transform_w, transform_h);
					break;
				case Blinds:		//百叶窗
					Effect_Blinds(pDC);
					break;
				default:            //不使用效果
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
							int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
							0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
			}	// end switch(m_EffectNum)
		}
		else	//不是第一次绘制或用户未选择使用特效，不使用特效
		{
			m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
					int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
					0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
		}
	
		m_bIsDrawFirstTime=FALSE;				//置为FALSE，证明已经不是第一次绘制。
	
		SIZE sz;						
		sz.cx = m_LImage.m_nDrawWidth;			//重新设置滚动条大小
		sz.cy = m_LImage.m_nDrawHeight;
		this->SetScrollSizes(MM_TEXT,sz);
	}
	else	//目录中已无图像
	{
		SIZE sz;
		CRect rect;
		sz.cx = 100;
		sz.cy = 100;
		this->SetScrollSizes(MM_TEXT,sz);

		GetClientRect(&rect);							//获取用户区矩形
		m_nWindowWidth = rect.right - rect.left;		//计算宽度
		m_nWindowHeight = rect.bottom - rect.top;
		pDC->TextOut(m_nWindowWidth/2-100,m_nWindowHeight/2,"该目录已无可显示的图像");
	}

}

/////////////////////////////////////////////////////////////////////////////
// CPictViewView message handlers

//************ 使新建菜单不可用 *********//
void CPictViewView::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

//************ 使“最近的文件”不可用 *********//
void CPictViewView::OnUpdateFileMruFile1(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(FALSE);
}

//************ 点击“使用特效”时 *********//
void CPictViewView::OnUseSpecialEffect() 
{
	// TODO: Add your command handler code here
	if(m_IsNormalShow)
		m_IsNormalShow = FALSE;
	else
		m_IsNormalShow = TRUE;
}

void CPictViewView::OnUpdateUseSpecialEffect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(FALSE == m_IsNormalShow)	//则使用特效，置为Checked.
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);//不使用特效，置为UnChecked.
}

//////////////////////////////////////////////////
//               图像文件的读入
//////////////////////////////////////////////////

void CPictViewView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
	CFileDialog		fdialog(TRUE);
	//##**##
	fdialog.m_ofn.lpstrFilter = "所有文件(*.*)\0*.bmp;*.tga;*.pcx;*.jpg;*.jpeg;*.gif\0"
								"BMP(*.bmp)\0*.bmp\0"
								"TGA(*.tga)\0*.tga\0"
								"PCX(*.pcx)\0*.pcx\0"
								"JPEG(*.jpg,*.jpeg)\0*.jpg;*.jpeg\0"
								"GIF(*.gif)\0*.gif\0";
	if(fdialog.DoModal() == IDOK)
	{
		//##**##**********************************************
		//在打开一张新图片时先回收上一张图片的内存，否则会造成内存泄漏
		//如果上次未使用Lib Sources，则不用在此回收，LanImage::Create()中已经回收
		if(m_LImage.m_bReadWithLibSupport)
		{
			//在LanImage::LoadImage()中 m_pJpeg = new CJpeg()分配的空间
			if(m_LImage.m_pJpeg != NULL)	//上次打开的时JPEG格式
			{
				CJpeg * pTempJpeg = m_LImage.m_pJpeg;
				m_LImage.m_pJpeg = NULL;
				if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
					delete [] m_LImage.m_pImage;
				m_LImage.m_pImage = NULL;
				m_LImage.m_pOriginImage = NULL;
				delete pTempJpeg;
			}
			if(m_LImage.m_pGif != NULL)	//上次打开的时GIF格式
			{
				CGif * pTempGif = m_LImage.m_pGif;
				m_LImage.m_pGif = NULL;
				if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
					delete [] m_LImage.m_pImage;
				m_LImage.m_pImage = NULL;
				m_LImage.m_pOriginImage = NULL;
				delete pTempGif;
			}
		}
		else
			m_LImage.Release();
		//***********************************************

		if (m_Isconvert)
		{
			if(FALSE == m_LImage.LoadImage(fdialog.GetPathName(),m_degree,TRUE))
				return ;
		}
		if (!m_Isconvert)
		{
			if(FALSE == m_LImage.LoadImage(fdialog.GetPathName(),m_degree,FALSE))
				return ;
		}

		CString sTitle=fdialog.GetFileName();	//在标题栏显示打开文件的文件名
		CString sPath=fdialog.GetPathName();	//为在状态栏显示路径而写
		CString sImageSize;						//为在状态栏显示图片尺寸
		CString sFileSize;						//为在状态栏显示文件大小
		CString sDisplayRate;					//为在状态栏显示图像当前显示比例
		CPictViewDoc *pDoc=GetDocument();
		pDoc->SetTitle(sTitle);
		pDoc->m_bIsEmptyDoc = FALSE;			//标志为非空文档
		pDoc->m_bIsEmptyDir = FALSE;			//标志当前目录为非空
		m_LImage.m_bBufferIsOriginal = TRUE;

//		if(!m_LImage.m_bReadWithLibSupport)		//读写JPEG,GIF时使用Lib Sources中的方法，不用再转换了
//			m_LImage.Convert32();				//转为32位色;此函数在调用时有问题，并没有起到预期目的，
												//暂时不转化,而用原来图像的象素位数显示
			
//		SIZE sz;
//		sz.cx = m_LImage.m_nWidth;
//		sz.cy = m_LImage.m_nHeight;
//		this->SetScrollSizes(MM_TEXT,sz);

		// **** 计算绘制图片的位置，及显示大小 **>>
		FitScreen();

		// **** 设置状态栏上显示的信息：文件路径，文件大小，图片大小 ****
		CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;	//获得主框架窗口
		CStatusBar *pStatus = &pFrame->m_wndStatusBar;				//获得状态栏对象
		if(pStatus)
		{
			sImageSize.Format("宽×高 = %d×%d",m_LImage.m_nWidth,m_LImage.m_nHeight);
			sFileSize.Format("%.1f KB",m_LImage.nFileSize/1024.0);
			sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
			pStatus->SetPaneText(0,sPath);
			pStatus->SetPaneText(1,sDisplayRate);
			pStatus->SetPaneText(2,sFileSize);
			pStatus->SetPaneText(3,sImageSize);
		}
		else
			AfxMessageBox("Can not get StatusBar pointer!");

		m_bIsDrawFirstTime=TRUE;	//打开一幅图像，第一次绘制，故要使用特效，之后在OnDraw()中被置为FALSE.
		Invalidate(TRUE);	//通知Window，我需要重新绘制
							//因为在MainFrm.cpp中使用SetWindowPlacement()强制程序载入时
							//窗口最大化，如果Invalidate()参数为FALSE，那么会导致载入一
							//幅比前图小的图片时前图示被覆盖部分仍然保留在屏幕上。

		// **** 建立当前目录下的图片文件列表 ****
		pDoc->InitPicList(sPath);
		for(int i=0;i<=(pDoc->m_iFileNumber);i++)		//确定当前打开的文件在列表中的位置
		{
			if(sPath == pDoc->m_PicList[i])
			{
				pDoc->m_iCurrFileNum = i;
				break;
			}
		}

	}
}


//////////////////////////////////////////////////
//               图像文件的保存
//////////////////////////////////////////////////
void CPictViewView::OnFileSave() 
{
	// TODO: Add your command handler code here

	CFileDialog		fdialog(FALSE);
	//##**##
	fdialog.m_ofn.lpstrFilter = "所有文件(*.*)\0*.bmp;*.tga;*.jpg;*.pcx;*.gif\0"
									"BMP(*.bmp)\0*.bmp\0"
						    		"TGA(*.tga)\0*.tga\0"
									"JPEG(*.jpg)\0*.jpg\0"
									"PCX(*.pcx)\0*.pcx\0"
									"GIF(*.gif)\0*.gif\0";
	if(fdialog.DoModal() == IDOK)
	{ 
		CString strFileName = fdialog.GetPathName();
		int nFilterIndex=fdialog.m_ofn.nFilterIndex;

		if(2 == nFilterIndex)					//当用户选择文件过滤器为".BMP"时
		{
			//fdialog.SetDefExt(".bmp");
			strFileName = strFileName + ".bmp";	//自动加扩展名.bmp
			m_LImage.SaveBmp(strFileName);
		}
		else if(3 == nFilterIndex)				//当用户选择文件过滤器为".TGA"时
		{
			//fdialog.SetDefExt(".tga");
			strFileName = strFileName + ".tga";	//自动加扩展名.tga
			m_LImage.SaveTga(strFileName);
		}
		else if(4 == nFilterIndex)				//当用户选择文件过滤器为".jpg"时
		{
			strFileName = strFileName + ".jpg";	//自动加扩展名.jpg
			//打开时使用了Lib Sources中的方法
			//打开的是JPEG图像，则在m_pJpeg中已有CDib对象
			if(m_LImage.m_bReadWithLibSupport && (m_LImage.m_pJpeg!=NULL) )
				m_LImage.m_pJpeg->Save(strFileName,NULL,TRUE,75);
			//打开的是GIF图像，则在m_pGif中已有CDib对象
			else if(m_LImage.m_bReadWithLibSupport && (m_LImage.m_pGif!=NULL) )
			{
				m_LImage.m_pJpeg = new CJpeg();	//因未打开过JPEG图像，先创建对象
				m_LImage.m_pJpeg->Save(strFileName,m_LImage.m_pGif->GetDib(),TRUE,75);
				delete m_LImage.m_pJpeg; m_LImage.m_pJpeg = NULL;
			}
			//打开时未使用Lib Sources中的方法，即打开的是非JPEG图像，先创建CDib对象
			else
			{
				m_LImage.m_pJpeg = new CJpeg();
				CDib* pDib;
				m_LImage.CreateDib(&pDib);
				m_LImage.m_pJpeg->Save(strFileName,pDib,TRUE,75);
				delete pDib;
				delete m_LImage.m_pJpeg; m_LImage.m_pJpeg = NULL;
			}
		}
		else if(5 == nFilterIndex)				//当用户选择文件过滤器为".pcx"时
		{
			strFileName = strFileName + ".pcx";	//自动加扩展名.pcx
			CDib* pDib;
			m_LImage.CreateDib(&pDib);
			m_LImage.SavePcx(strFileName,pDib);
			delete pDib;
		}
		else if(6 == nFilterIndex)				//当用户选择文件过滤器为".gif"时
		{
			strFileName = strFileName + ".gif";	//自动加扩展名.gif
			if(m_LImage.m_bReadWithLibSupport && (m_LImage.m_pGif!=NULL) )
				m_LImage.m_pGif->Save(strFileName,NULL);
			else if(m_LImage.m_bReadWithLibSupport && (m_LImage.m_pJpeg!=NULL) )
			{
				m_LImage.m_pGif = new CGif();	//先创建对象分配空间，否则CGif中的buffer将不可用
				m_LImage.m_pGif->Save(strFileName,m_LImage.m_pJpeg->GetDib());
				delete m_LImage.m_pGif; m_LImage.m_pGif = NULL;
			}
			else
			{
				m_LImage.m_pGif = new CGif();
				CDib* pDib;
				m_LImage.CreateDib(&pDib);
				m_LImage.m_pGif->Save(strFileName,pDib);
				delete pDib;
				delete m_LImage.m_pGif; m_LImage.m_pGif = NULL;
			}
		}
		else	// - - - - - - - - - - - - - - -//未选择，即过滤器仍在“所有文件”时 
		{
			LPCTSTR pszExt = strchr(strFileName,'.');
			if(pszExt)	// - - - - - - - - - - -//用户输入了扩展名或输入的主文件名中含'.'但未包括有效扩展名
			{
				if(_stricmp(pszExt,".bmp") == 0)
					m_LImage.SaveBmp(strFileName);
				else if(_stricmp(pszExt,".tga") == 0)
					m_LImage.SaveTga(strFileName);
				else if( (_stricmp(pszExt,".jpg") == 0)||(_stricmp(pszExt,".jpeg") == 0) )
				{
					//打开时使用了Lib Sources中的方法
					//打开的是JPEG图像，则在m_pJpeg中已有CDib对象
					if(m_LImage.m_bReadWithLibSupport && (m_LImage.m_pJpeg!=NULL) )
						m_LImage.m_pJpeg->Save(strFileName,NULL,TRUE,75);
					//打开的是GIF图像，则在m_pGif中已有CDib对象
					else if(m_LImage.m_bReadWithLibSupport && (m_LImage.m_pGif!=NULL) )
					{
						m_LImage.m_pJpeg = new CJpeg();	//因未打开过JPEG图像，先创建对象
						m_LImage.m_pJpeg->Save(strFileName,m_LImage.m_pGif->GetDib(),TRUE,75);
						delete m_LImage.m_pJpeg; m_LImage.m_pJpeg = NULL;
					}
					else								//打开时未使用Lib Sources中的方法，先创建CDib对象
					{
						m_LImage.m_pJpeg = new CJpeg();
						CDib* pDib;
						m_LImage.CreateDib(&pDib);
						m_LImage.m_pJpeg->Save(strFileName,pDib,TRUE,75);
						delete pDib;
						delete m_LImage.m_pJpeg; m_LImage.m_pJpeg = NULL;
					}
				}
				else if(_stricmp(pszExt,".gif") == 0)
				{
					if(m_LImage.m_bReadWithLibSupport && (m_LImage.m_pGif!=NULL) )
						m_LImage.m_pGif->Save(strFileName,NULL);
					else if(m_LImage.m_bReadWithLibSupport && (m_LImage.m_pJpeg!=NULL) )
					{
						m_LImage.m_pGif = new CGif();
						m_LImage.m_pGif->Save(strFileName,m_LImage.m_pJpeg->GetDib());
						delete m_LImage.m_pGif; m_LImage.m_pGif = NULL;
					}
					else			//打开时未使用Lib Sources中的方法，先创建CDib对象
					{
						m_LImage.m_pGif = new CGif();
						CDib* pDib;
						m_LImage.CreateDib(&pDib);
						m_LImage.m_pGif->Save(strFileName,pDib);
						delete pDib;
						delete m_LImage.m_pGif; m_LImage.m_pGif = NULL;
					}
				}
				else if(_stricmp(pszExt,".pcx") == 0)
				{
					CDib* pDib;
					m_LImage.CreateDib(&pDib);
					m_LImage.SavePcx(strFileName,pDib);
					delete pDib;
				}
				else	// - - - - - - - - - - -//输入的主文件名中含'.'但未包括有效扩展名
				{
					strFileName = strFileName + ".bmp";	//自动保存为BMP格式
					m_LImage.SaveBmp(strFileName);
				}

			}
			else								//用户未输入扩展名，则自动保存为BMP格式。
			{
				//fdialog.SetDefExt(".bmp");
				strFileName = strFileName + ".bmp";
				m_LImage.SaveBmp(strFileName);
			}
		}
		
	}	
	
}
//////////////////////////////////////////////////////////
//                 特效显示函数
//////////////////////////////////////////////////////////

//************ 1.马赛克效果 ***************//
void	CPictViewView::Effect_Mosaic(CDC *pDC)
{
		int m_count=0;
//		int	LanArrow[128][128];			//共分为128*128块

//		for(int i=0;i<128;i++)			//此处for循环最初没有，造成在Release版中程序Crash,
//			for(int j=0;j<128;j++)		//现增加以手动初始化数组
//			{
//				LanArrow[i][j] = 0;
//			}

//		while ( m_count < 16384)		/*-------------------------------------------------*\
//		{								|本块注释掉的语句是原来马赛克的实现方法，即共分成	|
//			int x = rand()%128;			|128×128=16384块，每块大小为8×6，这样128×8=1024	|
//			int y = rand()%128;			|128×6=768，不论原图片的大小，每次画的时候都会取到	|
//			while(LanArrow[x][y] == 1)	|1024×768个象素，这样在显示不足1028×768大小的图片	|
//			{							|时就可能会产生“Access Violation的错误。			|
//				x = rand()%128;			\*-------------------------------------------------*/
//				y = rand()%128;
//			}
//			LanArrow[x][y] = 1;
//			m_count++;
//			m_LImage.Draw(pDC->GetSafeHdc(),
//						  int(m_Llower_rate*8*x)+m_showX,
//						  int(m_Llower_rate*6*y)+m_showY,
//						  int(m_Llower_rate*8),
//						  int(m_Llower_rate*6),
//						  8*x,6*y,8,6);
//		}

		int blockNum_w = 0;		//水平方向分割的块数,或列数
		int blockNum_h = 0;		//垂直方向分割的块数,或行数
		int blockSize = 0;

		if(m_LImage.m_nWidth<=160 || m_LImage.m_nHeight<=160)
			blockSize = 10;
		else if(m_LImage.m_nWidth<=400 || m_LImage.m_nHeight<=400)
			blockSize = 20;
		else
			blockSize = 30;

		blockNum_w = m_LImage.m_nWidth/blockSize;	//每个块为blockSize×blockSize的正方形
		blockNum_h = m_LImage.m_nHeight/blockSize;

		int **LanArrow = new int *[blockNum_h];
		for(int k=0;k<blockNum_h;k++)
		{
			LanArrow[k] = new int [blockNum_w];
		}

		for(int i=0;i<blockNum_h;i++)
			for(int j=0;j<blockNum_w;j++)
			{
				LanArrow[i][j] = 0;
			}

		srand( (unsigned)time( NULL ) );

		while( m_count < blockNum_h*blockNum_w )
		{
			int x = rand()%blockNum_w;	//随机抽取水平方向上第x块，即第x列
			int y = rand()%blockNum_h;	//随机抽取垂直方向上第y块，即第y行
			while(LanArrow[y][x] == 1)	//该块已画过。
			{
				 x = rand()%blockNum_w;
				 y = rand()%blockNum_h;
			}
			LanArrow[y][x] = 1;
			m_count++;
			m_LImage.Draw(pDC->GetSafeHdc(),
						  int(m_Llower_rate*blockSize*x)+m_showX,
						  int(m_Llower_rate*blockSize*y)+m_showY,
						  int(m_Llower_rate*blockSize),
						  int(m_Llower_rate*blockSize),
						  blockSize*x,blockSize*y,blockSize,blockSize);
			Delay(1);
		}
		
		for (int n=0; n<blockNum_h; n++)
			delete [blockNum_w] LanArrow[n];
		delete [blockNum_h] LanArrow;

		//当缩放倍数不为1时由于上面强制取整会使图片中有时出现空白线,
		//且当图片的宽、高不能恰好分为8×8的块时,上面循环过后边界处会有部分未被显示,
		//用下面的语句消去.
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
}

//************ 2.从上往下 ***************//
void	CPictViewView::Effect_Fromtop(CDC *pDC, int transform)
{
		for ( transform=0;transform<=m_LImage.m_nHeight;transform+=12 )
		{
			if((m_LImage.m_nHeight-transform)<12)				//当剩下未显示的部分不足12时，意味着
				m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),	//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
			else
				m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
						  int(m_Llower_rate*m_LImage.m_nWidth),
						  int(m_Llower_rate*transform),
						  0,m_LImage.m_nHeight-transform,m_LImage.m_nWidth,transform);
			Delay(10);
 		}
}

//************ 3.从下往上 ***************//
void	CPictViewView::Effect_Frombottom(CDC *pDC, int transform)
{
		for( transform=0;transform<=m_LImage.m_nHeight;transform+=12 )
		{
			if((m_LImage.m_nHeight-transform)<12)				//当剩下未显示的部分不足12时，意味着
				m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),	//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
			else
				m_LImage.Draw(pDC->GetSafeHdc(),
						  m_showX,
						  int((m_LImage.m_nHeight-transform)*m_Llower_rate)+m_showY,
						  int(m_Llower_rate*m_LImage.m_nWidth),
						  int(m_Llower_rate*transform),
						  0,0,m_LImage.m_nWidth,transform);
			Delay(10);
		}
}

//************ 4.从左往右 ***************//
void	CPictViewView::Effect_Fromleft(CDC *pDC, int transform)
{
		for ( transform=0;transform<=m_LImage.m_nWidth;transform+=12 )
		{
			if((m_LImage.m_nWidth-transform)<12)				//当剩下未显示的部分不足12时，意味着
				m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),	//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
			else
				m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
						  int(m_Llower_rate*transform),
						  int(m_Llower_rate*m_LImage.m_nHeight),
						  m_LImage.m_nWidth-transform,0,
						  transform,m_LImage.m_nHeight);
			Delay(10);
		}
}

//************ 5.从右往左 ***************//
void	CPictViewView::Effect_Fromright(CDC *pDC, int transform)
{
		for ( transform=0;transform<=m_LImage.m_nWidth;transform+=12 )
		{
			if((m_LImage.m_nWidth-transform)<12)				//当剩下未显示的部分不足12时，意味着
				m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),	//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
			else
				m_LImage.Draw(pDC->GetSafeHdc(),
						  int((m_LImage.m_nWidth-transform)*m_Llower_rate)+m_showX,
						  m_showY,
						  int(m_Llower_rate*transform),
						  int(m_Llower_rate*m_LImage.m_nHeight),
						  0,0,transform,m_LImage.m_nHeight);
			Delay(10);
		}	
}

//************ 6.从左上角进入 ***************//
void	CPictViewView::Effect_Fromtopleft(CDC *pDC, int transform_w, int transform_h)
{
		if (m_LImage.m_nWidth > m_LImage.m_nHeight)
		{
			transform_w+=12;	//(1)
			transform_h+=9;
			while(transform_w<m_LImage.m_nWidth)
			{
//				transform_w+=12;	//最初改变transform变量是在这里，但这样有时会出现while判断时transform
//				transform_h+=9;		//小于m_Limage.m_nWidth,而进入循环transform变量增加后已超出m_nWidth
									//致使下面Draw函数中m_LImage.m_nWidth-transform_w为负值,从而程序Crash
									//故去掉此处两行而加至(1)、(2)两处.下同。
				if((m_LImage.m_nWidth-transform_w)<12)				//当剩下未显示的部分不足12时，意味着
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),		//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),	//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
				else
				{
					if ( transform_h>=m_LImage.m_nHeight )
						transform_h=m_LImage.m_nHeight;
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
								int(m_Llower_rate*transform_w),
								int(m_Llower_rate*transform_h),
								m_LImage.m_nWidth-transform_w,m_LImage.m_nHeight-transform_h,
								transform_w,transform_h);
				}
				Delay(10);
				transform_w+=12;	//(2)
				transform_h+=9;
			}
		}
		else
		{
			transform_w+=9;
			transform_h+=12;
			while(transform_h<m_LImage.m_nHeight)
			{
//				transform_w+=12;
//				transform_h+=9;
				if((m_LImage.m_nHeight-transform_h)<12)				//当剩下未显示的部分不足12时，意味着
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),		//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),	//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
				else
				{
					if ( transform_w>=m_LImage.m_nWidth )
						transform_w=m_LImage.m_nWidth;
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
								  int(m_Llower_rate*transform_w),
								  int(m_Llower_rate*transform_h),
								  m_LImage.m_nWidth-transform_w,
								  m_LImage.m_nHeight-transform_h,
								  transform_w,transform_h);
				}
				Delay(10);
				transform_w+=9;
				transform_h+=12;
			}
		}
}

//************ 7.从右上角进入 ***************//
void	CPictViewView::Effect_Fromtopright(CDC *pDC, int transform_w, int transform_h)
{
		if (m_LImage.m_nWidth > m_LImage.m_nHeight)
		{
			transform_w+=12;
			transform_h+=9;
			while(transform_w<m_LImage.m_nWidth)
			{
//				transform_w+=12;
//				transform_h+=9;
				if((m_LImage.m_nWidth-transform_w)<12)				//当剩下未显示的部分不足12时，意味着
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),		//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),	//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
				else
				{
					if ( transform_h>=m_LImage.m_nHeight )
						transform_h=m_LImage.m_nHeight;
					m_LImage.Draw(pDC->GetSafeHdc(),
							  int((m_LImage.m_nWidth-transform_w)*m_Llower_rate)+m_showX,
							  m_showY,
							  int(m_Llower_rate*transform_w),
							  int(m_Llower_rate*transform_h),
							  0,m_LImage.m_nHeight-transform_h,
							  transform_w,transform_h);
				}
				Delay(10);
				transform_w+=12;
				transform_h+=9;
			}
		}
		else
		{
			transform_w+=9;
			transform_h+=12;
			while(transform_h<m_LImage.m_nHeight)
			{
//				transform_w+=12;
//				transform_h+=9;
				if((m_LImage.m_nHeight-transform_h)<12)				//当剩下未显示的部分不足12时，意味着
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),		//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),	//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
				else
				{
					if ( transform_w>=m_LImage.m_nWidth )
						transform_w=m_LImage.m_nWidth;
					m_LImage.Draw(pDC->GetSafeHdc(),
							  int((m_LImage.m_nWidth-transform_w)*m_Llower_rate+m_showX),
							  m_showY,
							  int(m_Llower_rate*transform_w),
							  int(m_Llower_rate*transform_h),
							  0,m_LImage.m_nHeight-transform_h,
							  transform_w,transform_h);
				}
				Delay(10);
				transform_w+=9;
				transform_h+=12;
			}
		}
}

//************ 8.从左下角进入 ***************//
void	CPictViewView::Effect_Frombottomleft(CDC *pDC, int transform_w, int transform_h)
{
		if (m_LImage.m_nWidth >= m_LImage.m_nHeight)
		{
			transform_w+=12;
			transform_h+=9;
			while(transform_w<m_LImage.m_nWidth)
			{
//				transform_w+=12;
//				transform_h+=9;
				if((m_LImage.m_nWidth-transform_w)<12)				//当剩下未显示的部分不足12时，意味着
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),		//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),	//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
				else
				{
					if ( transform_h>=m_LImage.m_nHeight )
						transform_h=m_LImage.m_nHeight;
					m_LImage.Draw(pDC->GetSafeHdc(),
							  m_showX,
							  int((m_LImage.m_nHeight-transform_h)*m_Llower_rate)+m_showY,
							  int(m_Llower_rate*transform_w),
							  int(m_Llower_rate*transform_h),
							  m_LImage.m_nWidth-transform_w,0,
							  transform_w,transform_h);
				}
				Delay(10);
				transform_w+=12;
				transform_h+=9;
			}
		}
		else
		{
			transform_w+=9;
			transform_h+=12;
			while(transform_h<m_LImage.m_nHeight)
			{
//				transform_w+=12;
//				transform_h+=9;
				if((m_LImage.m_nHeight-transform_h)<12)				//当剩下未显示的部分不足12时，意味着
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),		//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),	//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
				else
				{
					if ( transform_w>=m_LImage.m_nWidth )
						transform_w=m_LImage.m_nWidth;
					m_LImage.Draw(pDC->GetSafeHdc(),
							  m_showX,
							  int((m_LImage.m_nHeight-transform_h)*m_Llower_rate)+m_showY,
							  int(m_Llower_rate*transform_w),
							  int(m_Llower_rate*transform_h),
							  m_LImage.m_nWidth-transform_w,0,
							  transform_w,transform_h);
				}
				Delay(10);
				transform_w+=9;
				transform_h+=12;
			}
		}
}

//************ 9.从右下角进入  ***************//
void	CPictViewView::Effect_Frombottomright(CDC *pDC, int transform_w, int transform_h)
{
		if (m_LImage.m_nWidth >= m_LImage.m_nHeight)
		{
			transform_w+=12;
			transform_h+=9;
			while(transform_w<m_LImage.m_nWidth)
			{
//				transform_w+=12;
//				transform_h+=9;
				if((m_LImage.m_nWidth-transform_w)<12)				//当剩下未显示的部分不足12时，意味着
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),		//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),	//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
				else
				{
					if ( transform_h>=m_LImage.m_nHeight )
						transform_h=m_LImage.m_nHeight;
					m_LImage.Draw(pDC->GetSafeHdc(),
							  int((m_LImage.m_nWidth-transform_w)*m_Llower_rate)+m_showX,
							  int((m_LImage.m_nHeight-transform_h)*m_Llower_rate)+m_showY,
							  int(m_Llower_rate*transform_w),
							  int(m_Llower_rate*transform_h),
							  0,0,transform_w,transform_h);
				}
				Delay(10);
				transform_w+=12;
				transform_h+=9;
			}
		}
		else
		{
			transform_w+=9;
			transform_h+=12;
			while(transform_h<m_LImage.m_nHeight)
			{
//				transform_w+=12;
//				transform_h+=9;
				if((m_LImage.m_nHeight-transform_h)<12)				//当剩下未显示的部分不足12时，意味着
					m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,//这是最后一次Draw了，故不能再用下面
						  int(m_Llower_rate*m_LImage.m_nWidth),		//else中的函数了，否则会造成图片最后
						  int(m_Llower_rate*m_LImage.m_nHeight),	//一条显示不出来.
						  0,0,
						  m_LImage.m_nWidth,m_LImage.m_nHeight);
				else
				{
					if ( transform_w>=m_LImage.m_nWidth )
						transform_w=m_LImage.m_nWidth;
					m_LImage.Draw(pDC->GetSafeHdc(),
							  int((m_LImage.m_nWidth-transform_w)*m_Llower_rate)+m_showX,
							  int((m_LImage.m_nHeight-transform_h)*m_Llower_rate)+m_showY,
							  int(m_Llower_rate*transform_w),
							  int(m_Llower_rate*transform_h),
							  0,0,transform_w,transform_h);
				}
				Delay(10);
				transform_w+=9;
				transform_h+=12;
			}
		}
}

//************ 10.百叶窗 ***************//
void	CPictViewView::Effect_Blinds(CDC *pDC)
{
		int m=1,n=1;
		while(n<=18 && m<=18)
		{
			if(m_LImage.m_nWidth%m==0)
				n = m;
			m++;
		}

		if(n == 1)			//n=1说明对该图片在1到18中没有找到可以整除其宽度的数，
		{					//那么就找 最大的 使其余数最小 的数。
			m = 2;
			n = 2;
			while(m<=18)
			{
				if((m_LImage.m_nWidth%m) <= (m_LImage.m_nWidth%n))
					n = m;
				m++;
			}
		}

		for( int i=0;i<=m_LImage.m_nWidth/n;i+=1 )
		{
			for(int j=0;j<=(n-1);j++)
			{
				m_LImage.Draw(pDC->GetSafeHdc(),
							  int((m_LImage.m_nWidth*j/n)*m_Llower_rate)+m_showX,m_showY,
							  int(i*m_Llower_rate),int(m_LImage.m_nHeight*m_Llower_rate),
							  int(m_LImage.m_nWidth*j/n),0,		//此处之前未加int,造成在Release版中程序Crash
							  i,m_LImage.m_nHeight);
			}
			Delay(10);
		}
		//当缩放倍数不为1时由于上面强制取整会使图片中有时出现空白线,暂时用此法消去，有待改进
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
}

//******** [内存特效]-水平百叶窗 *************//
void CPictViewView::Effect_Blinds_H_Mem()
{
	int iSrcWidth = m_LImage.m_nWidth;
	int iSrcHeight = m_LImage.m_nHeight;
	//int iBitCount = m_LImage.m_nBitCount;
	int iSrcRowBytes = m_LImage.m_nPitch;
	int iBlindHeight = 0;	//水平百叶窗一条的高度
	int i,j,k;

	if(iSrcWidth<=160 || iSrcHeight<=160)
		iBlindHeight = 10;
	else
		iBlindHeight = 20;

	int iBlindNum =			//一幅图像分成的条数
		((iSrcHeight % iBlindHeight == 0) ? iSrcHeight / iBlindHeight : (iSrcHeight / iBlindHeight + 1));

	CDC* pDC = GetDC();

	//保存原始图像
	BYTE *pOriginImage = new BYTE[m_LImage.m_nImage];
	CopyMemory(pOriginImage,m_LImage.m_pImage,m_LImage.m_nImage);

	//对图像变换,一次设一个字节,对不同BitCount的图像均适用
	//先逐渐消隐:
	for(i = 0;i < iBlindHeight;i++)
	{
		for(j = 0 ;j < iBlindNum;j++)
		{
			for(k = 0;k < iSrcRowBytes; k++)
			{
				//处理边界不够一整条的情况
				if( (j * iBlindHeight + i) * iSrcRowBytes + k > m_LImage.m_nImage )
					continue;
				m_LImage.m_pImage[(j * iBlindHeight + i) * iSrcRowBytes + k] = 255;//设为白色
			}
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
		Delay(100);
	}

	//逐渐恢复:
	for(i = 0;i < iBlindHeight;i++)
	{
		for(j = 0 ;j < iBlindNum;j++)
		{
			for(k = 0;k < iSrcRowBytes; k++)
			{
				//处理边界不够一整条的情况
				if( (j * iBlindHeight + i) * iSrcRowBytes + k > m_LImage.m_nImage )
					continue;
				CopyMemory(&m_LImage.m_pImage[(j * iBlindHeight + i) * iSrcRowBytes + k],
					       &pOriginImage[(j * iBlindHeight + i) * iSrcRowBytes + k],1);
			}
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
		Delay(100);
	}

	delete [] pOriginImage;
	pOriginImage = NULL;
	
}

//************** [内存特效]-垂直百叶窗 ****************//
// ---- 垂直百叶窗要考虑不同BitCount的情况 ------------//
void CPictViewView::Effect_Blinds_V_Mem()
{
	int iSrcWidth = m_LImage.m_nWidth;
	int iSrcHeight = m_LImage.m_nHeight;
	int iBitCount = m_LImage.m_nBitCount;
	int iSrcRowBytes = m_LImage.m_nPitch;
	int iBlindWidth = 16;	//垂直百叶窗一条的宽度,定为16象素更容易适合不同BitCount的图像，
							//这点与水平百叶窗不同
	int i,j,k;

	int iBlindNum =			//一幅图像分成的条数
		((iSrcWidth % iBlindWidth == 0) ? iSrcWidth / iBlindWidth : (iSrcWidth / iBlindWidth + 1));

	int iBytesPerPixel = ( (iBitCount>8) ? iBitCount/8 : 1 );//一个象素占的字节数，1、4位的不用考虑,设为1
	int iBytesPerBlind;		//百叶窗一条宽度占用的字节数
	switch(iBitCount)
	{
		case 1:
			iBytesPerBlind = 2;
			break;
		case 4:
			iBytesPerBlind = 8;
			break;
		case 8:
			iBytesPerBlind = 16;
			break;
		case 16:
			iBytesPerBlind = 32;
			break;
		case 24:
			iBytesPerBlind = 48;
			break;
		case 32:
			iBytesPerBlind = 64;
			break;
	}

	CDC* pDC = GetDC();

	//保存原始图像
	BYTE *pOriginImage = new BYTE[m_LImage.m_nImage];
	CopyMemory(pOriginImage,m_LImage.m_pImage,m_LImage.m_nImage);

	//对图像变换,1、4位的一次变一个字节，也就是分别变8、2个象素，其他的则一次变一个象素
	//这样在1位和4位的时候速度比其他的要快
	//先逐渐消隐:
	for(i = 0;i < iBytesPerBlind;)
	{
		for(j = 0;j < iBlindNum;j++)
		{
			for(k = 0;k < iSrcHeight; k++)
			{
				//处理最右边界不够一整条的情况
				if( j*iBytesPerBlind+i > iSrcRowBytes )
					continue;
				memset(&m_LImage.m_pImage[k*iSrcRowBytes+j*iBytesPerBlind+i],255,iBytesPerPixel);//设为白色
			}
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);

			Delay(100);

		i+=iBytesPerPixel;
	}

	//逐渐恢复:
	for(i = 0;i < iBytesPerBlind;)
	{
		for(j = 0;j < iBlindNum;j++)
		{
			for(k = 0;k < iSrcHeight; k++)
			{
				//处理最右边界不够一整条的情况
				if( j*iBytesPerBlind+i > iSrcRowBytes )
					continue;
				CopyMemory(&m_LImage.m_pImage[k*iSrcRowBytes+j*iBytesPerBlind+i],
							&pOriginImage[k*iSrcRowBytes+j*iBytesPerBlind+i],iBytesPerPixel);
			}
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);

			Delay(100);

		i+=iBytesPerPixel;
	}

	delete [] pOriginImage;
	pOriginImage = NULL;
}

//******** [内存特效]-马赛克 ***********//
void CPictViewView::Effect_Mosaic_Mem()
{
	int  iSrcWidth     = m_LImage.m_nWidth;
	int  iSrcHeight    = m_LImage.m_nHeight;
	int  iBitCount     = m_LImage.m_nBitCount;
	int  iSrcRowBytes  = m_LImage.m_nPitch;
	int  iBytesNum     = iBitCount * 4; //32 * iBitCount / 8
	CDC *pDC = GetDC();
	//先保存源数据
	BYTE* pOriginImage = new BYTE[m_LImage.m_nImage];
	CopyMemory(pOriginImage,m_LImage.m_pImage,m_LImage.m_nImage);

	int nCount = 0;
	int i,j;
	//32×32象素为一块
	int nWidthCount  = ((iSrcRowBytes % iBytesNum==0) ? iSrcRowBytes / iBytesNum : (iSrcRowBytes /iBytesNum + 1)); 
	int nHeightCount = ((iSrcHeight % 32==0) ? iSrcHeight / 32 : (iSrcHeight/32 + 1));

	int **ImageArray = new int *[nHeightCount];
	for(int k=0;k<nHeightCount;k++)
	{
		ImageArray[k] = new int [nWidthCount];
	}

	for(i=0;i<nHeightCount;i++)
		for(j=0;j<nWidthCount;j++)
	{
		ImageArray[i][j] = 0;
	}

	//1.将图片转为白色
	srand( (unsigned)time( NULL ) );
	while ( nCount < nWidthCount * nHeightCount)
	{
		int x = rand() % nHeightCount;
		int y = rand() % nWidthCount;

		while(ImageArray[x][y] == 1)
		{
			x = rand()% nHeightCount;
			y = rand()% nWidthCount;
		}

		ImageArray[x][y] = 1;
		nCount++;

		//改变m_pImage的值
		for(i = 0;i < 32 ;i++)
		{
			for(j = 0;j<iBytesNum; j++)
			{	
				//处理边缘的数据在图片不是32的倍数的时候要处理特别处理
				//1.处理横向
				if((iSrcWidth%32!=0)&&(y == nWidthCount-1)&&(iSrcRowBytes % iBytesNum - 1<j))
					continue;
				//2.处理纵向
				if((iSrcHeight%32 !=0)&&(x == nHeightCount-1)&&((iSrcHeight%32-1)<i))
					continue;
				*(m_LImage.GetLine((x * 32 + i)) + y * iBytesNum + j) = 255;
			}
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);

		Delay(10);
	}

	//2.将图片转为原色
	nCount = 0;
	while ( nCount < nWidthCount * nHeightCount)
	{
		int x = rand() % nHeightCount;
		int y = rand() % nWidthCount;

		while(ImageArray[x][y] == 0)
		{
			x = rand()% nHeightCount;
			y = rand()% nWidthCount;
		}

		ImageArray[x][y] = 0;
		nCount++;

		//改变m_pImage的值
		for(i = 0;i < 32;i++)
		{
			for(j = 0;j <iBytesNum; j++)
			{	
				//处理边缘的数据在图片不是32的倍数的时候一定要处理
				//1.处理横向
				if((iSrcWidth % 32 !=0)&&(y == nWidthCount-1)&&(iSrcRowBytes % iBytesNum - 1<j))
					continue;
				//2.处理纵向
				if((iSrcHeight%32 !=0)&&(x == nHeightCount-1)&&((iSrcHeight%32- 1)<i))
					continue;
				m_LImage.m_pImage[(x * 32 + i)*iSrcRowBytes + y * iBytesNum + j] = 
					pOriginImage[(x * 32 + i)*iSrcRowBytes + y * iBytesNum + j];
			}
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);

		Delay(10);
	}
	//清理确定随机块的数组
	for(k=0;k<nHeightCount;k++)
	{
		delete []ImageArray[k];
	}
	delete ImageArray;
	delete [] pOriginImage;
}

//******** [内存特效]-向下扫描 ***********//
void CPictViewView::Effect_ScanFromTop_Mem()
{
	int iSrcWidth = m_LImage.m_nWidth;
	int iSrcHeight = m_LImage.m_nHeight;
	int iSrcRowBytes = m_LImage.m_nPitch;
	int i,j;

	CDC* pDC = GetDC();

	//保存原始图像
	BYTE *pOriginImage = new BYTE[m_LImage.m_nImage];
	CopyMemory(pOriginImage,m_LImage.m_pImage,m_LImage.m_nImage);

	//先扫描消隐:[注意DIB存储是由下向上的!!]
	for(i=iSrcHeight-1;i>=0;i--)
	{
		for(j=0;j<iSrcRowBytes;j++)
		{
			m_LImage.m_pImage[i*iSrcRowBytes+j] = 255;	//设为白色
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
		Delay(10);
	}
	//再扫描恢复:
	for(i=iSrcHeight-1;i>=0;i--)
	{
		for(j=0;j<iSrcRowBytes;j++)
		{
			m_LImage.m_pImage[i*iSrcRowBytes+j] = pOriginImage[i*iSrcRowBytes+j];	//设为白色
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
		Delay(10);
	}

	delete [] pOriginImage;
	pOriginImage = NULL;
}

//******** [内存特效]-向上扫描 ***********//
void CPictViewView::Effect_ScanFromBottom_Mem()
{
	int iSrcWidth = m_LImage.m_nWidth;
	int iSrcHeight = m_LImage.m_nHeight;
	int iSrcRowBytes = m_LImage.m_nPitch;
	int i,j;

	CDC* pDC = GetDC();

	//保存原始图像
	BYTE *pOriginImage = new BYTE[m_LImage.m_nImage];
	CopyMemory(pOriginImage,m_LImage.m_pImage,m_LImage.m_nImage);

	//先扫描消隐:[注意DIB存储是由下向上的!!]
	for(i=0;i<iSrcHeight;i++)
	{
		for(j=0;j<iSrcRowBytes;j++)
		{
			m_LImage.m_pImage[i*iSrcRowBytes+j] = 255;	//设为白色
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
		Delay(10);
	}
	//再扫描恢复:
	for(i=0;i<iSrcHeight;i++)
	{
		for(j=0;j<iSrcRowBytes;j++)
		{
			m_LImage.m_pImage[i*iSrcRowBytes+j] = pOriginImage[i*iSrcRowBytes+j];	//设为白色
		}
		m_LImage.Draw(pDC->GetSafeHdc(),m_showX,m_showY,
				int(m_Llower_rate*m_LImage.m_nWidth),int(m_Llower_rate*m_LImage.m_nHeight),
				0,0,m_LImage.m_nWidth,m_LImage.m_nHeight);
		Delay(10);
	}

	delete [] pOriginImage;
	pOriginImage = NULL;
}

//******* 在鼠标移动时显示坐标及全屏时重新显示工具栏 ************//
void CPictViewView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	//CScrollView::OnMouseMove(nFlags, point);
	CString str;
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	//在鼠标移动时显示坐标
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	if(pStatus)
	{
		str.Format("X = %d , Y = %d",point.x,point.y);
		pStatus->SetPaneText(4,str);
	}
	//全屏时重新显示工具栏
	if(pFrame->m_bFullScreen)
	{
		CRect HotRect;			//此触发区域不可太小，至少要比浮动工具栏稍大，因为当激活浮动
		HotRect.left = 700;		//工具栏时，相当于鼠标在另一个窗口内，则被其遮住的触发区失效
		HotRect.right = 1028;	//若此区域和浮动工具栏一样大或比其小，那么在判断鼠标是否在触
		HotRect.top = -5;		//发区时会有问题。
		HotRect.bottom = 80;	//
		if(HotRect.PtInRect(point))	//当鼠标移到触发区域时
		{
			if(!pFrame->m_bIsFullBarShowed)	//若工具栏未显示，则显示即可
			{
				pFrame->m_bIsFullBarShowed = TRUE;
				RECT	rectDesktop;
				RECT	FullScrnBarRect;
				::GetWindowRect(::GetDesktopWindow(), &rectDesktop);
				pFrame->m_pwndFullScrnBar->GetWindowRect(&FullScrnBarRect);
				int BarWidth = FullScrnBarRect.right - FullScrnBarRect.left;
				int BarPos_x = rectDesktop.right - rectDesktop.left - BarWidth - 10;
				pFrame->FloatControlBar(pFrame->m_pwndFullScrnBar,CPoint(BarPos_x,3));
				//AfxMessageBox("Bar Displayed!");//For Debuging Purpose.
			}
			else		//工具栏已显示
			{
				if(pFrame->m_bTiming)
				{
					pFrame->StopTimer();		//停止计时，因用户把鼠标放在工具栏上
					//AfxMessageBox("Timer Killed!");//For Debuging Purpose.
					pFrame->m_bTiming = FALSE;
					//AfxMessageBox("m_bTiming FALSE!");//For Debuging Purpose.
				}
			}
		}
		else	//当鼠标不在触发区域时
		{
			if(pFrame->m_bIsFullBarShowed)		//若工具栏已显示
			{
				if(!pFrame->m_bTiming)		//若未开始计时
				{
					pFrame->StartTimer();	//则开始计时
					//AfxMessageBox("Timer Started!");//For Debuging Purpose.
					pFrame->m_bTiming = TRUE;
					//AfxMessageBox("m_bTiming TRUE!");//For Debuging Purpose.
				}
			}
		}
	}
}

// *********  缩放 恢复原始大小(100%)  ********* //
void CPictViewView::OnZoomOriginal() 
{
	// TODO: Add your command handler code here
	m_Llower_rate = 1;
	m_LImage.m_nDrawWidth = m_LImage.m_nWidth;	//使显示宽高跟随缩放比例变化是为了缩放后仍能居中显示
	m_LImage.m_nDrawHeight = m_LImage.m_nHeight;
	if(m_LImage.m_nDrawWidth<m_nWindowWidth)
		m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
	else 
		m_showX = 0;
	if(m_LImage.m_nDrawHeight<m_nWindowHeight)
		m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
	else
		m_showY = 0;

	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();									//通知Window，需要重绘
}

void CPictViewView::OnUpdateZoomOriginal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  缩放 适合屏幕大小 ********* //
void CPictViewView::OnZoomFitscreen() 
{
	// TODO: Add your command handler code here
//	CRect rect;
//	GetClientRect(&rect);							//获取用户区矩形
//	int iClientRectWidth = rect.right - rect.left;	//计算宽度
//	int iClientRectHeight = rect.bottom - rect.top;	//计算高度

	m_LImage.m_nDrawWidth = m_nWindowWidth - 4;	//先将宽放大到满屏(或客户区),再计算出高度
	m_Llower_rate = float(m_LImage.m_nDrawWidth)/float(m_LImage.m_nWidth);
	m_LImage.m_nDrawHeight = int(m_LImage.m_nHeight*m_Llower_rate);
	m_showX = 0;
	m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;

	if(m_LImage.m_nDrawHeight>=m_nWindowHeight)	//如果这时得出的高超出客户区，则用高重新计算
	{
		m_LImage.m_nDrawHeight = m_nWindowHeight - 4;
		m_Llower_rate = float(m_LImage.m_nDrawHeight)/float(m_LImage.m_nHeight);
		m_LImage.m_nDrawWidth = int(m_LImage.m_nWidth*m_Llower_rate);
		m_showY = 0;
		m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
	}

	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();									//通知Window，需要重绘
}

void CPictViewView::OnUpdateZoomFitscreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  缩放 50%  ********* //
void CPictViewView::OnZoomHalf() 
{
	// TODO: Add your command handler code here
	m_Llower_rate = 0.5;
	m_LImage.m_nDrawWidth = m_LImage.m_nWidth/2;	//使显示宽高跟随缩放比例变化是为了缩放后仍能居中显示
	m_LImage.m_nDrawHeight = m_LImage.m_nHeight/2;
	if(m_LImage.m_nDrawWidth<m_nWindowWidth)
		m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
	else 
		m_showX = 0;
	if(m_LImage.m_nDrawHeight<m_nWindowHeight)
		m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
	else
		m_showY = 0;

	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;						//以便在用户选“使用特效”时，缩放用特效显示
	Invalidate();									//通知Window，需要重绘
}

void CPictViewView::OnUpdateZoomHalf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  缩放 75%  ********* //
void CPictViewView::OnZoom75percent() 
{
	// TODO: Add your command handler code here
	m_Llower_rate = 0.75;
	m_LImage.m_nDrawWidth = int(m_LImage.m_nWidth*0.75);	//使显示宽高跟随缩放比例变化是为了缩放后仍能居中显示
	m_LImage.m_nDrawHeight = int(m_LImage.m_nHeight*0.75);
	if(m_LImage.m_nDrawWidth<m_nWindowWidth)
		m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
	else 
		m_showX = 0;
	if(m_LImage.m_nDrawHeight<m_nWindowHeight)
		m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
	else
		m_showY = 0;

	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();									//通知Window，需要重绘
}

void CPictViewView::OnUpdateZoom75percent(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  缩放 150%  ********* //
void CPictViewView::OnZoom150percent() 
{
	// TODO: Add your command handler code here
	m_Llower_rate = 1.5;
	m_LImage.m_nDrawWidth = int(m_LImage.m_nWidth*1.5);	//使显示宽高跟随缩放比例变化是为了缩放后仍能居中显示
	m_LImage.m_nDrawHeight = int(m_LImage.m_nHeight*1.5);
	if(m_LImage.m_nDrawWidth<m_nWindowWidth)
		m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
	else 
		m_showX = 0;
	if(m_LImage.m_nDrawHeight<m_nWindowHeight)
		m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
	else
		m_showY = 0;

	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();									//通知Window，需要重绘
}

void CPictViewView::OnUpdateZoom150percent(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  缩放 200%  ********* //
void CPictViewView::OnZoomDouble() 
{
	// TODO: Add your command handler code here
	m_Llower_rate = 2;
	m_LImage.m_nDrawWidth = m_LImage.m_nWidth*2;	//使显示宽高跟随缩放比例变化是为了缩放后仍能居中显示
	m_LImage.m_nDrawHeight = m_LImage.m_nHeight*2;
	if(m_LImage.m_nDrawWidth<m_nWindowWidth)
		m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
	else 
		m_showX = 0;
	if(m_LImage.m_nDrawHeight<m_nWindowHeight)
		m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
	else
		m_showY = 0;

	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();									//通知Window，需要重绘
}

void CPictViewView::OnUpdateZoomDouble(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  菜单"逐渐放大"  ********* //
void CPictViewView::OnZoomIn() 
{
	// TODO: Add your command handler code here
	m_Llower_rate += 0.1f;
	m_LImage.m_nDrawWidth = int(m_LImage.m_nWidth*m_Llower_rate);//使显示宽高跟随缩放比例变化是为了缩放后仍能居中显示
	m_LImage.m_nDrawHeight = int(m_LImage.m_nHeight*m_Llower_rate);
	if(m_LImage.m_nDrawWidth<m_nWindowWidth)
		m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
	else 
		m_showX = 0;
	if(m_LImage.m_nDrawHeight<m_nWindowHeight)
		m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
	else
		m_showY = 0;

	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();									//通知Window，需要重绘
}

void CPictViewView::OnUpdateZoomIn(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  菜单"逐渐缩小"  ********* //
void CPictViewView::OnZoomOut() 
{
	// TODO: Add your command handler code here
	m_Llower_rate -= 0.1f;
	if(m_Llower_rate>0)
	{
		m_LImage.m_nDrawWidth = int(m_LImage.m_nWidth*m_Llower_rate);//使显示宽高跟随缩放比例变化是为了缩放后仍能居中显示
		m_LImage.m_nDrawHeight = int(m_LImage.m_nHeight*m_Llower_rate);
		if(m_LImage.m_nDrawWidth<m_nWindowWidth)
			m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
		else 
			m_showX = 0;
		if(m_LImage.m_nDrawHeight<m_nWindowHeight)
			m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
		else
			m_showY = 0;

		//设置状态栏"显示比例"
		CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
		CStatusBar *pStatus = &pFrame->m_wndStatusBar;
		CString sDisplayRate;
		sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
		pStatus->SetPaneText(1,sDisplayRate);

		m_bIsDrawFirstTime = TRUE;
		Invalidate();									//通知Window，需要重绘
	}
}

void CPictViewView::OnUpdateZoomOut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir || m_Llower_rate<0)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  菜单"随机效果"  ********* //
void CPictViewView::OnEffectRandom() 
{
	// TODO: Add your command handler code here
	if(m_IsRandomEffect)			//"随机效果"菜单项相当于复选框，每点击一次状态改变一次，
	{								//其他效果菜单项则单击只能选定，不能反选定。
		m_IsRandomEffect = FALSE;
		m_EffectNum = Mosaic;		//不使用随机效果时程序默认指定为马赛克效果
	}
	else
		m_IsRandomEffect = TRUE;
}

void CPictViewView::OnUpdateEffectRandom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(m_IsRandomEffect)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"马赛克"  ********* //
void CPictViewView::OnEffectMosaic() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = Mosaic;
}

void CPictViewView::OnUpdateEffectMosaic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(Mosaic == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"百叶窗"  ********* //
void CPictViewView::OnEffectBlinds() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = Blinds;
}

void CPictViewView::OnUpdateEffectBlinds(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(Blinds == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"从上往下"  ********* //
void CPictViewView::OnEffectTopdown() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = fromtop;
}

void CPictViewView::OnUpdateEffectTopdown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(fromtop == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"从下往上"  ********* //
void CPictViewView::OnEffectBottomup() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = frombottom;
}

void CPictViewView::OnUpdateEffectBottomup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(frombottom == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"从左往右"  ********* //
void CPictViewView::OnEffectLeftright() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = fromleft;
}

void CPictViewView::OnUpdateEffectLeftright(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(fromleft == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"从右往左"  ********* //
void CPictViewView::OnEffectRightleft() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = fromright;
}

void CPictViewView::OnUpdateEffectRightleft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(fromright == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"从左上进入"  ********* //
void CPictViewView::OnEffectTopleft() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = fromtopleft;
}

void CPictViewView::OnUpdateEffectTopleft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(fromtopleft == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"从左下进入"  ********* //
void CPictViewView::OnEffectBottomleft() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = frombottomleft;
}

void CPictViewView::OnUpdateEffectBottomleft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(frombottomleft == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"从右上进入"  ********* //
void CPictViewView::OnEffectTopright() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = fromtopright;
}

void CPictViewView::OnUpdateEffectTopright(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(fromtopright == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"从右下进入"  ********* //
void CPictViewView::OnEffectBottomright() 
{
	// TODO: Add your command handler code here
	m_IsRandomEffect = FALSE;
	m_EffectNum = frombottomright;
}

void CPictViewView::OnUpdateEffectBottomright(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(m_IsNormalShow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
	if(frombottomright == m_EffectNum)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

// *********  菜单"上一张"  ********* //
void CPictViewView::OnViewPrevious() 
{
	// TODO: Add your command handler code here
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];

	CPictViewDoc *pDoc=GetDocument();
	//-------------------------------------------------
	//已到达第一张,则返回，不进行任何操作；因为如果当前
	//显示的是当前目录列表中第二张图片,而第一张图片较大，
	//解码需较长时间，如一张大的JPEG，那么当点击界面中上一张
	//后在绘图尚未完成的情况下(此时UI尚未更新，仍可接受命今)
	//又点一次该按钮，则会导致程序崩溃，因为数组越界了
	if(pDoc->m_iCurrFileNum == 0)
		return;
	//-------------------------------------------------
	BOOL	bFind = FALSE;	//标志是否原来的“当前打开项”能在新列表中找到				//*
	CString OriginalCurrent;															//*
	OriginalCurrent = pDoc->m_PicList[pDoc->m_iCurrFileNum];							//*
	pDoc->InitPicList(OriginalCurrent);				//重建列表以防止当前目录中文件已改变//*
	for(int i=0;i<=(pDoc->m_iFileNumber);i++)		//确定当前打开的文件在新列表中的位置//*
	{												//以得到新列表中下一张的位置		//*
		if(OriginalCurrent == pDoc->m_PicList[i])										//*
		{																				//*
			pDoc->m_iCurrFileNum = i;													//*
			bFind = TRUE;																//*
			break;																		//*
		}																				//*
	}																					//*
	if(bFind)
		pDoc->m_iCurrFileNum = pDoc->m_iCurrFileNum - 1;//得到上一张图在文件列表中的位置
	else
		pDoc->m_iCurrFileNum = 0;

	_splitpath(pDoc->m_PicList[pDoc->m_iCurrFileNum], drive, dir, fname, ext);

	CString sTitle;
	sTitle.Format("%s%s",fname,ext);	//在标题栏显示打开文件的文件名
	pDoc->SetTitle(sTitle);
	CString sImageSize;					//为在状态栏显示图片尺寸
	CString sFileSize;					//为在状态栏显示文件大小
	CString sDisplayRate;				//为在状态栏显示图像当前显示比例
	
	//##**##**********************************************
	//在打开一张新图片时先回收上一张图片的内存，否则会造成内存泄漏
	//如果上次未使用Lib Sources中的方法，则不用在此回收，LanImage::Create()中已经回收
	if(m_LImage.m_bReadWithLibSupport)
	{
		//在LanImage::LoadImage()中 m_pJpeg = new CJpeg()分配的空间
		if(m_LImage.m_pJpeg != NULL)	//上次打开的时JPEG格式
		{
			CJpeg * pTempJpeg = m_LImage.m_pJpeg;
			m_LImage.m_pJpeg = NULL;
			if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
				delete [] m_LImage.m_pImage;
			m_LImage.m_pImage = NULL;
			m_LImage.m_pOriginImage = NULL;
			delete pTempJpeg;
		}
		if(m_LImage.m_pGif != NULL)	//上次打开的时GIF格式
		{
			CGif * pTempGif = m_LImage.m_pGif;
			m_LImage.m_pGif = NULL;
			if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
				delete [] m_LImage.m_pImage;
			m_LImage.m_pImage = NULL;
			m_LImage.m_pOriginImage = NULL;
			delete pTempGif;
		}
	}
	else
		m_LImage.Release();
	//***********************************************
	if (m_Isconvert)
	{
		if(FALSE == m_LImage.LoadImage(pDoc->m_PicList[pDoc->m_iCurrFileNum],m_degree,TRUE))
			return ;
	}
	if (!m_Isconvert)
	{
		if(FALSE == m_LImage.LoadImage(pDoc->m_PicList[pDoc->m_iCurrFileNum],m_degree,FALSE))
			return ;
	}

	m_LImage.m_bBufferIsOriginal = TRUE;
//	if(!m_LImage.m_bReadWithLibSupport)
//		m_LImage.Convert32();

	// **** 计算绘制图片的位置，及显示大小 **>>
	FitScreen();

	// **** 设置状态栏上显示的信息：文件路径，文件大小，图片大小 ****
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;	//获得主框架窗口
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;				//获得状态栏对象
	if(pStatus)
	{
		sImageSize.Format("宽×高 = %d×%d",m_LImage.m_nWidth,m_LImage.m_nHeight);
		sFileSize.Format("%.1f KB",m_LImage.nFileSize/1024.0);
		sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
		pStatus->SetPaneText(0,pDoc->m_PicList[pDoc->m_iCurrFileNum]);
		pStatus->SetPaneText(1,sDisplayRate);
		pStatus->SetPaneText(2,sFileSize);
		pStatus->SetPaneText(3,sImageSize);
	}
	else
		AfxMessageBox("Can not get StatusBar pointer!");

	m_bIsDrawFirstTime=TRUE;
	Invalidate(TRUE);
}

void CPictViewView::OnUpdateViewPrevious(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPictViewDoc *pDoc=GetDocument();
	if(pDoc->m_iCurrFileNum == 0 || pDoc->m_bIsEmptyDoc == TRUE)	//已经到达第一张图片或空文档
		pCmdUI->Enable(FALSE);			//注意:文件全部删除时m_iCurrFileNum仍为0，与ViewNext不同
	else
		pCmdUI->Enable(TRUE);
}

// *********  菜单"下一张"  ********* //
void CPictViewView::OnViewNext() 
{
	// TODO: Add your command handler code here
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];

	CPictViewDoc *pDoc=GetDocument();
	//-------------------------------------------------
	//已到达最后一张,则返回，不进行任何操作；因为如果当前
	//显示的是当前目录列表中倒数第二张图片,而最后一张图片较大，
	//解码需较长时间，如一张大的JPEG，那么当点击界面中下一张
	//后在绘图尚未完成的情况下(此时UI尚未更新，仍可接受命今)
	//又点一次该按钮，则会导致程序崩溃，因为数组越界了
	if(pDoc->m_iCurrFileNum == pDoc->m_iFileNumber)
		return;
	//--------------------------------------------------
	BOOL	bFind = FALSE;	//标志是否原来的“当前打开项”能在新列表中找到				//*
	CString OriginalCurrent;															//*
	OriginalCurrent = pDoc->m_PicList[pDoc->m_iCurrFileNum];							//*
	pDoc->InitPicList(OriginalCurrent);				//重建列表以防止当前目录中文件已改变//*
	for(int i=0;i<=(pDoc->m_iFileNumber);i++)		//确定当前打开的文件在列表中的位置	//*
	{												//以得到新列表中下一张的位置		//*
		if(OriginalCurrent == pDoc->m_PicList[i])										//*
		{																				//*
			pDoc->m_iCurrFileNum = i;													//*
			bFind = TRUE;																//*
			break;																		//*
		}																				//*
	}																					//*
	if(bFind)											//如找到，即当前图片未被移除
		pDoc->m_iCurrFileNum = pDoc->m_iCurrFileNum + 1;//得到下一张图在文件列表中的位置
	else												//未找到，即当前图片被移除
		pDoc->m_iCurrFileNum = 0;						//从新列表第一张显示

	_splitpath(pDoc->m_PicList[pDoc->m_iCurrFileNum], drive, dir, fname, ext);

	CString sTitle;
	sTitle.Format("%s%s",fname,ext);	//在标题栏显示打开文件的文件名
	pDoc->SetTitle(sTitle);
	CString sImageSize;					//为在状态栏显示图片尺寸
	CString sFileSize;					//为在状态栏显示文件大小
	CString sDisplayRate;				//为在状态栏显示图像当前显示比例
	
	//##**##**********************************************
	//在打开一张新图片时先回收上一张图片的内存，否则会造成内存泄漏
	//如果上次未使用Lib Sources中的方法，则不用在此回收，LanImage::Create()中已经回收
	if(m_LImage.m_bReadWithLibSupport)
	{
		//在LanImage::LoadImage()中 m_pJpeg = new CJpeg()分配的空间
		if(m_LImage.m_pJpeg != NULL)	//上次打开的时JPEG格式
		{
			CJpeg * pTempJpeg = m_LImage.m_pJpeg;
			m_LImage.m_pJpeg = NULL;
			if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
				delete [] m_LImage.m_pImage;
			m_LImage.m_pImage = NULL;
			m_LImage.m_pOriginImage = NULL;
			delete pTempJpeg;
		}
		if(m_LImage.m_pGif != NULL)	//上次打开的时GIF格式
		{
			CGif * pTempGif = m_LImage.m_pGif;
			m_LImage.m_pGif = NULL;
			if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
				delete [] m_LImage.m_pImage;
			m_LImage.m_pImage = NULL;
			m_LImage.m_pOriginImage = NULL;
			delete pTempGif;
		}
	}
	else
		m_LImage.Release();
	//***********************************************
	if (m_Isconvert)
	{
		if(FALSE == m_LImage.LoadImage(pDoc->m_PicList[pDoc->m_iCurrFileNum],m_degree,TRUE))
			return ;
	}
	if (!m_Isconvert)
	{
		if(FALSE == m_LImage.LoadImage(pDoc->m_PicList[pDoc->m_iCurrFileNum],m_degree,FALSE))
			return ;
	}

	m_LImage.m_bBufferIsOriginal = TRUE;
//	if(!m_LImage.m_bReadWithLibSupport)
//		m_LImage.Convert32();

	// **** 计算绘制图片的位置，及显示大小 **>>
	FitScreen();

	// **** 设置状态栏上显示的信息：文件路径，文件大小，图片大小 ****
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;	//获得主框架窗口
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;				//获得状态栏对象
	if(pStatus)
	{
		sImageSize.Format("宽×高 = %d×%d",m_LImage.m_nWidth,m_LImage.m_nHeight);
		sFileSize.Format("%.1f KB",m_LImage.nFileSize/1024.0);
		sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
		pStatus->SetPaneText(0,pDoc->m_PicList[pDoc->m_iCurrFileNum]);
		pStatus->SetPaneText(1,sDisplayRate);
		pStatus->SetPaneText(2,sFileSize);
		pStatus->SetPaneText(3,sImageSize);
	}
	else
		AfxMessageBox("Can not get StatusBar pointer!");

	m_bIsDrawFirstTime=TRUE;
	Invalidate(TRUE);
}

void CPictViewView::OnUpdateViewNext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPictViewDoc *pDoc=GetDocument();
	if(pDoc->m_iCurrFileNum == pDoc->m_iFileNumber || pDoc->m_bIsEmptyDoc == TRUE
		|| pDoc->m_iFileNumber < 0)	//已经到达最后一张图片或空文档或文件全部被删除
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  菜单"删除"  ********* //
void CPictViewView::OnEditDelete() 
{
	// TODO: Add your command handler code here
	char drive[_MAX_DRIVE];   
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];   
	char ext[_MAX_EXT];
	CString FromStr;

	CPictViewDoc *pDoc = GetDocument();
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;	//获得主框架窗口
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;				//获得状态栏对象
	FromStr = pDoc->m_PicList[pDoc->m_iCurrFileNum];
	FromStr+='\0';
	SHFILEOPSTRUCT FileOp; 
	FileOp.hwnd = NULL; 
	FileOp.wFunc = FO_DELETE; 
	FileOp.pFrom = FromStr;//FromBuff; 
	FileOp.pTo = NULL; 
	FileOp.fFlags = FOF_ALLOWUNDO | FOF_NOERRORUI;
	FileOp.fAnyOperationsAborted = TRUE;
	FileOp.hNameMappings = NULL;
	FileOp.lpszProgressTitle = _T("正在删除文件……");
	::SHFileOperation( &FileOp );

	if(FileOp.fAnyOperationsAborted)	//如果删除操作示执行，则不用重建列表，下面的操作不用执行
		return;

	//删除之后重建列表，然后：如果删除的是第一张，重新显示现在的第一张；如果删除的最后一张,
	//重新显示现在的最后一张；如果删除的其他图片，则显示其下一张(正好在列表中被删图片的位置)
	pDoc->ReInitPicList();
	if(!(pDoc->m_iFileNumber < 0))	//若最后一张也被删除，经过上面的ReInitPicList(),m_iFileNumber变为负
	{
		if(pDoc->m_iCurrFileNum == 0)							//删除的是第一张
			pDoc->m_iCurrFileNum = 0;							//重新显示现在的第一张
		else if(pDoc->m_iCurrFileNum == pDoc->m_iFileNumber+1)	//删除的最后一张(ReInit后m_iFileNumber已经减1)
			pDoc->m_iCurrFileNum = pDoc->m_iCurrFileNum - 1;	//重新显示现在的最后一张
		else													//删除中间的图片
			pDoc->m_iCurrFileNum = pDoc->m_iCurrFileNum;		//m_iCurrFileNum不用变
		_splitpath(pDoc->m_PicList[pDoc->m_iCurrFileNum], drive, dir, fname, ext);

		CString sTitle;
		sTitle.Format("%s%s",fname,ext);	//在标题栏显示打开文件的文件名
		pDoc->SetTitle(sTitle);
		CString sImageSize;					//为在状态栏显示图片尺寸
		CString sFileSize;					//为在状态栏显示文件大小
		CString sDisplayRate;				//为在状态栏显示图像当前显示比例
	
		//##**##**********************************************
		//在打开一张新图片时先回收上一张图片的内存，否则会造成内存泄漏
		//如果上次未使用Lib Sources中的方法，则不用在此回收，LanImage::Create()中已经回收
		if(m_LImage.m_bReadWithLibSupport)
		{
			//在LanImage::LoadImage()中 m_pJpeg = new CJpeg()分配的空间
			if(m_LImage.m_pJpeg != NULL)	//上次打开的时JPEG格式
			{
				CJpeg * pTempJpeg = m_LImage.m_pJpeg;
				m_LImage.m_pJpeg = NULL;
				if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
					delete [] m_LImage.m_pImage;
				m_LImage.m_pImage = NULL;
				m_LImage.m_pOriginImage = NULL;
				delete pTempJpeg;
			}
			if(m_LImage.m_pGif != NULL)	//上次打开的时GIF格式
			{
				CGif * pTempGif = m_LImage.m_pGif;
				m_LImage.m_pGif = NULL;
				if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
					delete [] m_LImage.m_pImage;
				m_LImage.m_pImage = NULL;
				m_LImage.m_pOriginImage = NULL;
				delete pTempGif;
			}
		}
		else
			m_LImage.Release();
		//***********************************************
		if (m_Isconvert)
		{
			if(FALSE == m_LImage.LoadImage(pDoc->m_PicList[pDoc->m_iCurrFileNum],m_degree,TRUE))
				return ;
		}
		if (!m_Isconvert)
		{
			if(FALSE == m_LImage.LoadImage(pDoc->m_PicList[pDoc->m_iCurrFileNum],m_degree,FALSE))
				return ;
		}

		m_LImage.m_bBufferIsOriginal = TRUE;
//		if(!m_LImage.m_bReadWithLibSupport)
//			m_LImage.Convert32();

		// **** 计算绘制图片的位置，及显示大小 **>>
		FitScreen();

		// **** 设置状态栏上显示的信息：文件路径，文件大小，图片大小 ****
		if(pStatus)
		{
			sImageSize.Format("宽×高 = %d×%d",m_LImage.m_nWidth,m_LImage.m_nHeight);
			sFileSize.Format("%.1f KB",m_LImage.nFileSize/1024.0);
			sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
			pStatus->SetPaneText(0,pDoc->m_PicList[pDoc->m_iCurrFileNum]);
			pStatus->SetPaneText(1,sDisplayRate);
			pStatus->SetPaneText(2,sFileSize);
			pStatus->SetPaneText(3,sImageSize);
		}
		else
			AfxMessageBox("Can not get StatusBar pointer!");

		m_bIsDrawFirstTime=TRUE;
		Invalidate(TRUE);
	}
	else	//最后一张被删除，目录为空，则
	{
		pDoc->m_bIsEmptyDir = TRUE;
		pDoc->SetTitle("无标题");
		pStatus->SetPaneText(0,"未打开任何图像");
		pStatus->SetPaneText(1,"");
		pStatus->SetPaneText(2,"");
		Invalidate(TRUE);
	}
}

void CPictViewView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CPictViewDoc *pDoc=GetDocument();
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	if(pDoc->m_bIsEmptyDoc == TRUE || pDoc->m_iFileNumber < 0 || pFrame->m_bIsPlay)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  菜单"用默认程序打开"  ********* //
void CPictViewView::OnEditExternal() 
{
	// TODO: Add your command handler code here
	CPictViewDoc* pDoc = GetDocument();

//	LPCTSTR ext = _tcsrchr(pDoc->m_PicList[pDoc->m_iCurrFileNum],_T('.'));
//	if((ext[1] =='b'||ext[1] =='B')&&(ext[2] =='m'||ext[2] =='M')
//	&&(ext[3] =='p'||ext[3] =='P'))
//	{
//		if(NULL== ShellExecute(NULL,"open","pDoc->m_PicList[pDoc->m_iCurrFileNum]",
//			NULL,"",SW_SHOW))
//		return ;
//	}
	CString Str;
	Str += '\"';	//防止把空格当作分隔符的程序无法识别路径中含空格的文件名
	for(int i=0;i<(pDoc->m_PicList[pDoc->m_iCurrFileNum].GetLength());i++)
	{
		if(pDoc->m_PicList[pDoc->m_iCurrFileNum].GetAt(i) == '\\')	//SellExecute参数中文件全路径中的'\'必须用转义字符
		{
			Str += pDoc->m_PicList[pDoc->m_iCurrFileNum].GetAt(i);
			Str += '\\';
		}
		else
		{
			Str += pDoc->m_PicList[pDoc->m_iCurrFileNum].GetAt(i);
		}
	}
	Str += '\"';	//防止把空格当作分隔符的程序无法识别路径中含空格的文件名

	if(NULL== ShellExecute(NULL,"open",Str,NULL,NULL,SW_SHOW))
		return ;
}

void CPictViewView::OnUpdateEditExternal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

// *********  菜单"用画图打开并编辑"  ********* //
void CPictViewView::OnEditInMpaint() 
{
	// TODO: Add your command handler code here
	CPictViewDoc* pDoc = GetDocument();
	CString Str;
	Str += '\"';	//画图程序处理参数时遇到空格会当作分隔符，故如不加引号，则遇到路径中有空格就无法打开。
	for(int i=0;i<(pDoc->m_PicList[pDoc->m_iCurrFileNum].GetLength());i++)
	{
		if(pDoc->m_PicList[pDoc->m_iCurrFileNum].GetAt(i) == '\\')	//SellExecute参数中文件全路径中的'\'必须用转义字符
		{
			Str += pDoc->m_PicList[pDoc->m_iCurrFileNum].GetAt(i);
			Str += '\\';
		}
		else
		{
			Str += pDoc->m_PicList[pDoc->m_iCurrFileNum].GetAt(i);
		}
	}
	Str += '\"';

	if(NULL== ShellExecute(NULL,"open","mspaint.exe",Str,NULL,SW_SHOW))
		return ;
}

void CPictViewView::OnUpdateEditInMpaint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

//**** 用ESC键退出全屏的消息处理函数 *******
void CPictViewView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_ESCAPE)//如果按的键为Esc键
	{
		//获取主框架窗口的指针
		CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		//调用主窗口类的自定义函数 EndFullScreen() ，便可退出全屏显示状态
		pFrame->EndFullScreen();
	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//******* 定时器处理(幻灯片播放)函数 ***********
void CPictViewView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == IDT_TIMER_PLAY)	//是幻灯片播放定时器时
	{
		CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;	//获得主框架窗口
		if(FALSE == pFrame->m_bIsPlay)		//先判断播放标志，如果为FALSE，
		{									//说明用户已按"停止"键或已退出全屏
			KillTimer(IDT_TIMER_PLAY);		//那么KillTimer
			return;							//并返回
		}

		char drive[_MAX_DRIVE];   
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];   
		char ext[_MAX_EXT];

		CPictViewDoc *pDoc=GetDocument();

		if(pDoc->m_iCurrFileNum == pDoc->m_iFileNumber)		//若已到最后一张，
			pDoc->m_iCurrFileNum = 0;						//从第一张重新开始
		else												//否则，
			pDoc->m_iCurrFileNum = pDoc->m_iCurrFileNum + 1;//继续下一张

		_splitpath(pDoc->m_PicList[pDoc->m_iCurrFileNum], drive, dir, fname, ext);

		CString sTitle;
		sTitle.Format("%s%s",fname,ext);	//在标题栏显示打开文件的文件名
		pDoc->SetTitle(sTitle);
		CString sImageSize;					//为在状态栏显示图片尺寸
		CString sFileSize;					//为在状态栏显示文件大小
		CString sDisplayRate;				//为在状态栏显示图像当前显示比例

		//##**##**********************************************
		//在打开一张新图片时先回收上一张图片的内存，否则会造成内存泄漏
		//如果上次未使用Lib Sources中的方法，则不用在此回收，LanImage::Create()中已经回收
		if(m_LImage.m_bReadWithLibSupport)
		{
			//在LanImage::LoadImage()中 m_pJpeg = new CJpeg()分配的空间
			if(m_LImage.m_pJpeg != NULL)	//上次打开的时JPEG格式
			{
				CJpeg * pTempJpeg = m_LImage.m_pJpeg;
				m_LImage.m_pJpeg = NULL;
				if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
					delete [] m_LImage.m_pImage;
				m_LImage.m_pImage = NULL;
				m_LImage.m_pOriginImage = NULL;
				delete pTempJpeg;
			}
			if(m_LImage.m_pGif != NULL)	//上次打开的时GIF格式
			{
				CGif * pTempGif = m_LImage.m_pGif;
				m_LImage.m_pGif = NULL;
				if(!m_LImage.m_bBufferIsOriginal)	//进行过变换
					delete [] m_LImage.m_pImage;
				m_LImage.m_pImage = NULL;
				m_LImage.m_pOriginImage = NULL;
				delete pTempGif;
			}
		}
		else
			m_LImage.Release();
		//***********************************************
		if (m_Isconvert)
		{
			if(FALSE == m_LImage.LoadImage(pDoc->m_PicList[pDoc->m_iCurrFileNum],m_degree,TRUE))
				return ;
		}
		if (!m_Isconvert)
		{
			if(FALSE == m_LImage.LoadImage(pDoc->m_PicList[pDoc->m_iCurrFileNum],m_degree,FALSE))
				return ;
		}

		m_LImage.m_bBufferIsOriginal = TRUE;
//		if(!m_LImage.m_bReadWithLibSupport)
//			m_LImage.Convert32();

		// **** 计算绘制图片的位置，及显示大小 **>>
		FitScreen();

		// **** 设置状态栏上显示的信息：文件路径，文件大小，图片大小 ****
		CStatusBar *pStatus = &pFrame->m_wndStatusBar;				//获得状态栏对象
		if(pStatus)
		{
			sImageSize.Format("宽×高 = %d×%d",m_LImage.m_nWidth,m_LImage.m_nHeight);
			sFileSize.Format("%.1f KB",m_LImage.nFileSize/1024.0);
			sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
			pStatus->SetPaneText(0,pDoc->m_PicList[pDoc->m_iCurrFileNum]);
			pStatus->SetPaneText(1,sDisplayRate);
			pStatus->SetPaneText(2,sFileSize);
			pStatus->SetPaneText(3,sImageSize);
		}
		else
			AfxMessageBox("Can not get StatusBar pointer!");

		m_bIsDrawFirstTime=TRUE;
		Invalidate(TRUE);
	}//End if(nIDEvent == IDT_TIMER_PLAY)

	//CScrollView::OnTimer(nIDEvent);
}

//**** 全屏工具栏"开始幻灯片" ****
void CPictViewView::OnPlay() 
{
	// TODO: Add your command handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsPlay = TRUE;
	SetTimer(IDT_TIMER_PLAY,3000,NULL);
}

void CPictViewView::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CPictViewDoc *pDoc = GetDocument();
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir || pFrame->m_bIsPlay)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

//**** 全屏工具栏"停止幻灯片" ****
void CPictViewView::OnPause() 
{
	// TODO: Add your command handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	pFrame->m_bIsPlay = FALSE;
}

void CPictViewView::OnUpdatePause(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CPictViewDoc *pDoc = GetDocument();
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir || !(pFrame->m_bIsPlay))
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

//****** 填充背景色 *******
BOOL CPictViewView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	/*
	CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	if(pFrame)	//动画窗口时Frame尚为空，如在此不加判断则会报错
	{
		if(pFrame->m_bFullScreen)
		{
			CRect rect;
			CBrush brush;
			brush.CreateSolidBrush(RGB(0,0,0));
			pDC->GetClipBox(rect);
			pDC->FillRect(rect,&brush);
		}
		else
		{
			CRect rect;
			CBrush brush;
			brush.CreateSolidBrush(RGB(255,255,255));
			pDC->GetClipBox(rect);
			pDC->FillRect(rect,&brush);
		}
	}

	return TRUE;
	*/
	return CScrollView::OnEraseBkgnd(pDC);
}

// ****************** 右键菜单 ***************************
void CPictViewView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CMenu PopupMenu,*pPopup;
	PopupMenu.LoadMenu(IDR_POPUPMENU);
	pPopup = PopupMenu.GetSubMenu(0);

	/////因Popup Menu不接收界面更新消息，故其可用或不可用状态要自行处理
	UINT uEnable;
	CPictViewDoc *pDoc=GetDocument();
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	//"上一张"
	if(pDoc->m_iCurrFileNum == 0 || pDoc->m_bIsEmptyDoc == TRUE)//已经到达第一张图片或空文档
	{								//注意:文件全部删除时m_iCurrFileNum仍为0，与ViewNext不同
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_VIEW_PREVIOUS,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_VIEW_PREVIOUS,uEnable);
	}
	//"下一张"
	if(pDoc->m_iCurrFileNum == pDoc->m_iFileNumber || pDoc->m_bIsEmptyDoc == TRUE
		|| pDoc->m_iFileNumber < 0)	//已经到达最后一张图片或空文档或文件全部被删除
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_VIEW_NEXT,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_VIEW_NEXT,uEnable);
	}
	//"顺时针旋转90度"
	if(pDoc->m_bIsEmptyDoc == TRUE || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_ROTATE90_CLOCKWISE,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_ROTATE90_CLOCKWISE,uEnable);
	}
	//"逆时针旋转90度"
	if(pDoc->m_bIsEmptyDoc == TRUE || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_ROTATE90_ANTICLOCKWISE,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_ROTATE90_ANTICLOCKWISE,uEnable);
	}
	//"放大"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_ZOOM_IN,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_ZOOM_IN,uEnable);
	}
	//"缩小"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir || m_Llower_rate<0)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_ZOOM_OUT,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_ZOOM_OUT,uEnable);
	}
	//"适合大小"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_ZOOM_FITSCREEN,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_ZOOM_FITSCREEN,uEnable);
	}
	//"原始大小"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_ZOOM_ORIGINAL,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_ZOOM_ORIGINAL,uEnable);
	}
	//"显示水平百叶窗"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_HBLINDS,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_HBLINDS,uEnable);
	}
	//"显示垂直百叶窗"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_VBLINDS,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_VBLINDS,uEnable);
	}
	//"显示马赛克效果"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_MOSAIC,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_MOSAIC,uEnable);
	}
	//"显示向上扫描"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_SCANFROMBOTTOM,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_SCANFROMBOTTOM,uEnable);
	}
	//"显示向下扫描"
	if(pDoc->m_bIsEmptyDoc || pDoc->m_bIsEmptyDir)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_SCANFROMTOP,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_EFFECT_MEM_SCANFROMTOP,uEnable);
	}
	//"删除"
	if(pDoc->m_bIsEmptyDoc == TRUE || pDoc->m_iFileNumber < 0 || pFrame->m_bIsPlay)
	{
		uEnable = MF_BYCOMMAND|MF_GRAYED;
		pPopup->EnableMenuItem(ID_EDIT_DELETE,uEnable);
	}
	else
	{
		uEnable = MF_BYCOMMAND|MF_ENABLED;
		pPopup->EnableMenuItem(ID_EDIT_DELETE,uEnable);
	}
	//"全屏"
	MENUITEMINFO MInfo;
	MInfo.cbSize = sizeof(MENUITEMINFO);
	MInfo.fMask = MIIM_STATE;	//说明将要设置fState
	if(pFrame->m_bFullScreen)
	{
		MInfo.fState = MFS_CHECKED;
		SetMenuItemInfo(pPopup->m_hMenu,ID_FULL_SCREEN,FALSE,&MInfo);
	}
	else
	{
		MInfo.fState = MFS_UNCHECKED;
		SetMenuItemInfo(pPopup->m_hMenu,ID_FULL_SCREEN,FALSE,&MInfo);
	}
	/////

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);
}

// **** 右键菜单中"全屏"命令 ****
void CPictViewView::OnFullScreen() 
{
	// TODO: Add your command handler code here
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	pFrame->OnFullScreen();
}

//**** 载入时如果图片超出客户区，则将其缩小到合适大小 ****
void CPictViewView::FitScreen()
{
	CRect rect;
	GetClientRect(&rect);							//获取用户区矩形
	m_nWindowWidth = rect.right - rect.left;		//计算用户区宽度
	m_nWindowHeight = rect.bottom - rect.top;		//计算用户区高度

	//如果图片的宽或高有一个超出用户区大小，则缩放到适合大小
	if( (m_LImage.m_nWidth >m_nWindowWidth) || (m_LImage.m_nHeight>m_nWindowHeight) )
	{
		m_LImage.m_nDrawWidth = m_nWindowWidth - 4;	//先将宽放大到满屏(或客户区),再计算出高度
		m_Llower_rate = float(m_LImage.m_nDrawWidth)/float(m_LImage.m_nWidth);
		m_LImage.m_nDrawHeight = int(m_LImage.m_nHeight*m_Llower_rate);
		m_showX = 0;
		m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;

		if(m_LImage.m_nDrawHeight>=m_nWindowHeight)	//如果这时得出的高超出客户区，则用高重新计算
		{
			m_LImage.m_nDrawHeight = m_nWindowHeight - 4;
			m_Llower_rate = float(m_LImage.m_nDrawHeight)/float(m_LImage.m_nHeight);
			m_LImage.m_nDrawWidth = int(m_LImage.m_nWidth*m_Llower_rate);
			m_showY = 0;
			m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
		}
	}
	//如未超出，则按原始大小显示
	else
	{
		m_LImage.m_nDrawWidth = m_LImage.m_nWidth;		//之所以不直接使用m_nWidth和m_nHeight,是为了
		m_LImage.m_nDrawHeight = m_LImage.m_nHeight;	//不改变原始图像属性，以便缩放后仍能正确显示图像,
														//故在此初始化m_nDrawWidth,m_nDrawHeight
		//只有当显示的宽、高小于客户区宽高时才居中，	
		//否则直接从左上角开始显示.如果不这样滚动条位置会不正确
		//而且当显示大小超出客户区时居中也没有意义。
		if(m_LImage.m_nDrawWidth<m_nWindowWidth)
			m_showX = m_nWindowWidth/2 - m_LImage.m_nDrawWidth/2;
		else 
			m_showX = 0;
		if(m_LImage.m_nDrawHeight<m_nWindowHeight)
			m_showY = m_nWindowHeight/2 - m_LImage.m_nDrawHeight/2;
		else
			m_showY = 0;
		m_Llower_rate = 1.0;			//打开图像时按原始大小显示
	}
}

//********* 顺时针旋转90度 ***********
void CPictViewView::OnRotate90Clockwise() 
{
	// TODO: Add your command handler code here
	m_LImage.Rotate90Clockwise();
	FitScreen();
	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();
}

void CPictViewView::OnUpdateRotate90Clockwise(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

//********* 逆时针旋转90度 ***********
void CPictViewView::OnRotate90Anticlockwise() 
{
	// TODO: Add your command handler code here
	m_LImage.Rotate90Clockwise();
	m_LImage.Rotate90Clockwise();
	m_LImage.Rotate90Clockwise();
	FitScreen();
	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();
}

void CPictViewView::OnUpdateRotate90Anticlockwise(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

//********* 旋转180度 ***********
void CPictViewView::OnRotate180() 
{
	// TODO: Add your command handler code here
	m_LImage.Rotate90Clockwise();
	m_LImage.Rotate90Clockwise();
	FitScreen();
	//设置状态栏"显示比例"
	CMainFrame *pFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CStatusBar *pStatus = &pFrame->m_wndStatusBar;
	CString sDisplayRate;
	sDisplayRate.Format("显示比例: %.3f",m_Llower_rate);
	pStatus->SetPaneText(1,sDisplayRate);

	m_bIsDrawFirstTime = TRUE;
	Invalidate();
}

void CPictViewView::OnUpdateRotate180(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}
//==================================================
// *****   直接显示的特效(非载入特效)   ****
//--------------------------------------------------
//*************  []垂直百叶窗 **************
void CPictViewView::OnEffectMemVblinds() 
{
	// TODO: Add your command handler code here
	Effect_Blinds_V_Mem();
}

void CPictViewView::OnUpdateEffectMemVblinds(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

//*************  []水平百叶窗 **************
void CPictViewView::OnEffectMemHblinds() 
{
	// TODO: Add your command handler code here
	Effect_Blinds_H_Mem();
}

void CPictViewView::OnUpdateEffectMemHblinds(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

//*************  []马赛克 **************
void CPictViewView::OnEffectMemMosaic() 
{
	// TODO: Add your command handler code here
	Effect_Mosaic_Mem();
}

void CPictViewView::OnUpdateEffectMemMosaic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

//*************  []向下扫描 **************
void CPictViewView::OnEffectMemScanfromtop() 
{
	// TODO: Add your command handler code here
	Effect_ScanFromTop_Mem();
}

void CPictViewView::OnUpdateEffectMemScanfromtop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

////*************  []向上扫描 **************
void CPictViewView::OnEffectMemScanfrombottom() 
{
	// TODO: Add your command handler code here
	Effect_ScanFromBottom_Mem();
}

void CPictViewView::OnUpdateEffectMemScanfrombottom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(TRUE == ((CPictViewDoc *)GetDocument())->m_bIsEmptyDoc || 
		  ((CPictViewDoc *)GetDocument())->m_bIsEmptyDir)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

