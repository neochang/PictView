#include "stdafx.h" 
#include "ClassImage.h"
#include <vfw.h>	//为了使用DrawDibDraw()函数
#include <assert.h>

LanFormat __BitCount2Fmt(int nBitCount)
{
	switch(nBitCount)
	{
	case 1:
		return LanF_Index1;
	case 4:
		return LanF_Index4;
	case 8:
		return LanF_Index8;
	case 16:
		return LanF_R5G5B5;
	case 24:
		return LanF_R8G8B8;
	case 32:
		return LanF_A8R8G8B8;
	}
	return LanF_Unkown;
}
BOOL LanImage::Create(int nWidth,int nHeight,int nBitCount,int ndegree,LanFormat eFmt)
{
	Release();
	if (ndegree==1 || ndegree==4)
	{
		m_eFmt = eFmt;
		m_nWidth = nWidth;
		m_nHeight = nHeight;
	}
	else if(ndegree==2 || ndegree==3)
	{
		m_eFmt = eFmt;
		m_nWidth = nHeight;
		m_nHeight = nWidth;
	}
	m_nBitCount = nBitCount;
	m_nPitch = (nWidth * nBitCount + 31) / 32 * 4;
	m_nImage = m_nPitch * nHeight;

	if(nBitCount <= 8)
	{
		m_nPalette = 1 << nBitCount;
		m_pPal = new RGBQUAD[m_nPalette];
	}
	else
	{
		m_nPalette = 0;		//重点在这里
	}

#ifdef UC_USE_DC
	BITMAPINFOHEADER bih;
	memset(&bih,0,sizeof(bih));
	bih.biSize = sizeof(bih);
	bih.biPlanes = 1;
	bih.biWidth = m_nWidth;
	if(UC_SWAP_HEIGHT(1))
		bih.biHeight = m_nHeight;
	else
		bih.biHeight = -m_nHeight;
	bih.biBitCount = m_nBitCount;
	bih.biSizeImage = m_nImage;
	bih.biClrUsed = m_nPalette;
	HDC hdc = ::GetDC(NULL);
	m_hBitmap = CreateDIBSection(hdc,(BITMAPINFO *)&bih,DIB_RGB_COLORS,(void **)&m_pImage,NULL,0);
	::ReleaseDC(NULL,hdc);
#else
	m_pImage = new BYTE[m_nImage];
#endif

	return TRUE;

}

BOOL LanImage::Create_No(int nWidth,int nHeight,int nBitCount,LanFormat eFmt)
{
	VERIFY(nWidth > 0 && nHeight > 0);			//最初为assert();现改为VERIFY()
	VERIFY(nBitCount > 0 && nBitCount <= 32);
	if(eFmt == LanF_Unkown)
		eFmt = __BitCount2Fmt(nBitCount);
	if(eFmt == LanF_Unkown)
		return FALSE;

	Release();

	m_eFmt = eFmt;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nBitCount = nBitCount;
	m_nPitch = (nWidth * nBitCount + 31) / 32 * 4;
	m_nImage = m_nPitch * nHeight;

	if(nBitCount <= 8)
	{
		m_nPalette = 1 << nBitCount;
		m_pPal = new RGBQUAD[m_nPalette];
	}
	else
	{
		m_nPalette = 0;		//重点在这里
	}

#ifdef UC_USE_DC
	BITMAPINFOHEADER bih;
	memset(&bih,0,sizeof(bih));
	bih.biSize = sizeof(bih);
	bih.biPlanes = 1;
	bih.biWidth = m_nWidth;
	if(UC_SWAP_HEIGHT(1))
		bih.biHeight = m_nHeight;
	else
		bih.biHeight = -m_nHeight;
	bih.biBitCount = m_nBitCount;
	bih.biSizeImage = m_nImage;
	bih.biClrUsed = m_nPalette;
	HDC hdc = ::GetDC(NULL);
	m_hBitmap = CreateDIBSection(hdc,(BITMAPINFO *)&bih,DIB_RGB_COLORS,(void **)&m_pImage,NULL,0);
	::ReleaseDC(NULL,hdc);
#else
	m_pImage = new BYTE[m_nImage];
#endif

	return TRUE;

}

BOOL LanImage::CopyFrom(const LanImage & Img)
{
	if(&Img == this || Img.IsLoad() == FALSE)
		return FALSE;

//	if(Create_No(Img,Img.GetWidth(),Img.GetHeight(),Img.m_eFmt) == FALSE)
//		return FALSE;
//	if(Create_No(Img.GetWidth(),Img.GetHeight(),Img.GetBitCount(),Img.m_eFmt) == FALSE)
//		return FALSE;

	memcpy(m_pImage,Img.GetImage(),GetSize());
	memcpy(m_pPal,Img.GetPalette(),GetPalCount() * sizeof(RGBQUAD));

	return TRUE;
}
//-----------------------------------------------------------------------------
void LanImage::Release()
{
#ifdef UC_USE_DC
	if(m_hBitmap)		//删除的是原始图像数据
	{
		DeleteObject(m_hBitmap);
		//m_pOriginImage指向的是m_hBitmap的图像数据空间,空间被释放,置为NULL
		m_pOriginImage = NULL;
	}

	if(!m_bBufferIsOriginal)
	{
		delete [] m_pImage;
		m_pImage = NULL;
	}
#else
	if(m_pImage)		//若没用定义UC_USE_DC,则此处删的是当前显示的数据
	{
		delete [] m_pImage;
		m_pImage = NULL;
	}

	if(!m_bBufferIsOriginal)
	{
		delete [] m_pOriginImage;
		m_pOriginImage = NULL;
	}
#endif
	if(m_pPal)
	{
		delete [] m_pPal;
		m_pPal = NULL;
	}

//	memset(this,0,sizeof(LanImage));
}
//-----------------------------------------------------------------------------
#ifdef UC_USE_DC
HDC LanImage::GetDC()
{
	HDC hdc = CreateCompatibleDC(NULL);
	SelectObject(hdc,m_hBitmap);
	if(m_nPalette > 0)
		SetDIBColorTable(hdc,0,m_nPalette,m_pPal);
	return hdc;
}

void LanImage::ReleaseDC(HDC hdc)
{
	DeleteDC(hdc);
}

#endif

BOOL LanImage::LoadImage(LPCTSTR pszFileName,int ndegree,BOOL isconvert)
{
	//判断文件的后缀名，以决定图像是何格式.这种方法并不太好，理想的方法应该是读取文件
	//数据并从中取得图像格式的信息。
	LPCTSTR pszExt = _tcsrchr(pszFileName,_T('.'));		//取后缀名
	BOOL bRet = FALSE;

	//如为JPEG格式，则采用Lib Sources中的读法
	if( (_tcsicmp(pszExt,".jpg") == 0) || (_tcsicmp(pszExt,".jpeg") == 0) )
	{
		m_bReadWithLibSupport = TRUE;
		m_pJpeg = new CJpeg();
		//int size = sizeof(m_pJpeg);
		//CString str;
		//str.Format("%d",size);
		//AfxMessageBox(str);////////////
		bRet = m_pJpeg->Load(pszFileName);

		if(!bRet)
		{
			AfxMessageBox("载入JPEG文件时发生错误!");
			return FALSE;
		}

		CDib *pDib = m_pJpeg->GetDib();	//获取CDib指针
		m_pImage = pDib->GetBitsPtr();	//获取DIB数据区指针
		m_nWidth = pDib->GetWidth();
		m_nHeight = pDib->GetHeight();
		m_nBitCount = pDib->GetBitCount();
		m_nImage = m_nHeight*(pDib->GetWidthBytes());
		m_nPitch = pDib->GetWidthBytes();
		m_nPalette = 0;
		//为了得到文件的长度
		CFile file;
		if(file.Open(pszFileName,CFile::modeRead) == FALSE)
		{
			AfxMessageBox("获取文件大小错误：无法打开文件!");
			return FALSE;
		}
		nFileSize = file.GetLength();
		file.Close();
	}
	//如为GIF格式，也采用Lib Sources中的读法
	else if( _tcsicmp(pszExt,".gif") == 0 )
	{
		m_bReadWithLibSupport = TRUE;
		m_pGif = new CGif();
		bRet = m_pGif->Load(pszFileName);

		if(!bRet)
		{
			AfxMessageBox("载入GIF文件时发生错误!");
			return FALSE;
		}

		CDib *pDib = m_pGif->GetDib();	//获取CDib指针
		m_pImage = pDib->GetBitsPtr();	//获取DIB数据区指针
		m_nWidth = pDib->GetWidth();
		m_nHeight = pDib->GetHeight();
		m_nBitCount = pDib->GetBitCount();
		m_nImage = m_nHeight*(pDib->GetWidthBytes());
		m_nPitch = pDib->GetWidthBytes();
		m_nPalette = 0;
		//为了得到文件的长度
		CFile file;
		if(file.Open(pszFileName,CFile::modeRead) == FALSE)
		{
			AfxMessageBox("获取文件大小错误：无法打开文件!");
			return FALSE;
		}
		nFileSize = file.GetLength();
		file.Close();
	}
	else
	{
		m_bReadWithLibSupport = FALSE;
		CFile file;
		if(file.Open(pszFileName,CFile::modeRead) == FALSE)
		{
			AfxMessageBox("无法打开文件!请确认文件是否存在或路径是否正确!");
			return FALSE;
		}

		// 为了得到文件的长度。
		nFileSize = file.GetLength();
	
		BYTE * pFileBuffer = new BYTE[nFileSize]; //

		file.Read(pFileBuffer,nFileSize);

		file.Close();

//##**##
		if(_tcsicmp(pszExt,".bmp") == 0)
			bRet = ReadBmp(pFileBuffer,nFileSize,ndegree,isconvert);
		else if(_tcsicmp(pszExt,".tga") == 0)
			bRet = ReadTga(pFileBuffer,nFileSize,ndegree);
		else if(_tcsicmp(pszExt,".pcx") == 0)
			bRet = ReadPcx(pFileBuffer,nFileSize,ndegree);

		delete [] pFileBuffer;
		pFileBuffer = NULL;
	}

	return bRet;
}

struct LanDrawDib
{
	HDRAWDIB hDraw;
	LanDrawDib()
	{
		hDraw = DrawDibOpen();
	}

	~LanDrawDib(){
		DrawDibClose(hDraw);
	}

	operator HDRAWDIB ()
	{
		return hDraw;
	}

	static LanDrawDib & GetDrawDib()
	{
		static LanDrawDib	__DrawDib;
		return __DrawDib;
	}
};


struct LanDrawHeader : public BITMAPINFOHEADER
{
	RGBQUAD	pal[256];
	LanDrawHeader(){
		memset(this,0,sizeof(LanDrawHeader));
		biSize = sizeof(BITMAPINFOHEADER);
		biPlanes = 1;
	}
};

static LanDrawHeader  g_LanDH;

BOOL LanImage::Draw(HDC hdc,int nDx,int nDy,int nDw,int nDh,
				int nSx,int nSy,int nSw,int nSh,UINT uFlags) const
{
	if(IsLoad() == FALSE)
		return FALSE;

	g_LanDH.biWidth = m_nWidth;
	g_LanDH.biHeight = m_nHeight;
	g_LanDH.biBitCount = m_nBitCount;
	if(m_nBitCount <= 8)
	{
//		memcpy(g_LanDH.pal,m_pPal,(1 << m_nBitCount) * sizeof(RGBQUAD));
		g_LanDH.biClrUsed = m_nPalette;
		memcpy(g_LanDH.pal,m_pPal,m_nPalette * sizeof(RGBQUAD));
	}

	DrawDibDraw(LanDrawDib::GetDrawDib(),hdc,
		nDx,nDy,nDw,nDh,
		&g_LanDH,m_pImage,
		nSx,nSy,nSw,nSh,
		uFlags);

	return TRUE;
}

//**** 此函数为了在打开图像时没有创建CDib的情况下创建CDib对象 ****
BOOL LanImage::CreateDib(CDib **pDib)
{
	BITMAPINFOHEADER	bmiHeader;
	HDIB				hDIB;
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = m_nWidth;
	bmiHeader.biHeight = m_nHeight;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = m_nBitCount;
	bmiHeader.biCompression = BI_RGB;
	bmiHeader.biSizeImage = m_nImage;
	bmiHeader.biXPelsPerMeter = 0;
	bmiHeader.biYPelsPerMeter = 0;
	//如果打开的图片BitCount>8则无调色板
	if(m_nBitCount>8)
		bmiHeader.biClrUsed = 0;
	else
		bmiHeader.biClrUsed = m_nPalette;
	bmiHeader.biClrImportant = 0;
	
	// Allocate enough memory for the new CF_DIB, and copy bits 
	DWORD dwHeaderSize = sizeof(BITMAPINFOHEADER);
	DWORD dwPaletteSize = sizeof(RGBQUAD)*m_nPalette;
	DWORD dwBitsSize = WIDTHBYTES(m_nWidth*m_nBitCount) * m_nHeight;
	if(m_nBitCount>8)
		hDIB = GlobalAlloc(GHND, dwHeaderSize + dwBitsSize);
	else
		hDIB = GlobalAlloc(GHND, dwHeaderSize + dwPaletteSize + dwBitsSize);

	if (hDIB == NULL)
		return FALSE;
		
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB); 
	memcpy(lpDIB, (LPBYTE)&bmiHeader, dwHeaderSize);
	if(m_nBitCount<=8)		//写调色板
		memcpy(lpDIB+dwHeaderSize,m_pPal,dwPaletteSize);
	memcpy(FindDIBBits((LPBYTE)lpDIB), m_pImage, dwBitsSize);

	*pDib = new CDib();
	(*pDib)->Attach(hDIB);
	GlobalUnlock(hDIB);
	return TRUE;
}

//****** 旋转图像-顺时针90度 ********
//
//		注意图像的4字节对齐!!!
//
//-----------------------------------
void LanImage::Rotate90Clockwise()
{
	BYTE* pNewImage = NULL;
	
	int iSrcWidth = m_nWidth;
	int iSrcHeight = m_nHeight;
	int iSrcRowBytes = m_nPitch;

	//计算翻转后一行占用的字节数及数据区的大小
	int iNewPitch = (iSrcHeight * m_nBitCount + 31) / 32 * 4;	//4字节对齐
	int iNewImgDataSize = iNewPitch * iSrcWidth;

	//为翻转后的数据分配空间
	pNewImage = new BYTE[iNewImgDataSize];
	switch(m_nBitCount)
	{
	case 8:	//8位图像的翻转
		{
			int OutPointer = 0;
			for(int y = 0;y < iSrcHeight;y++)
			{
				BYTE *pIn = GetLine(y);
				for(int x = 0;x < iSrcWidth;x++)
				{
					int OutColumn = y;				//这两行看起来是做逆时针旋转，但由于DIB
					int OutRow = iSrcWidth - x - 1;	//是由下到上存储图像的，故实际上是顺时针
					//int OutColumn = iSrcHeight - y - 1;//而这两行注释掉的则正相反，是逆时针的
					//int OutRow = x;
					OutPointer = OutRow * iNewPitch + OutColumn;
					CopyMemory(&pNewImage[OutPointer],&pIn[x],1);
				}
			}
		}
		break;
	case 1:		//1位和4位比较麻烦，要对位进行操作
		{
			memset(pNewImage,0,iNewImgDataSize);	//全置为0，便于后面的按位或操作
			int OutPointer = 0;
			for(int y=0;y<iSrcHeight;y++)
			{
				BYTE* pIn = GetLine(y);
				for(int x=0;x<iSrcRowBytes;x++)
				{
					int BitPointer = 0;		//确定是在该字节中的第几位
					int OutColumn = y/8;	//8行翻转后才构成一字节
					BYTE byTempIn = pIn[x];	//取一个字节，即8个象素
					BYTE byTempOut;

					for(BitPointer=0;BitPointer<8;BitPointer++)
					{
						int OutRow = iSrcWidth - (x*8+BitPointer) - 1;
						//注意：最高位代表最左边的象素!
						switch(BitPointer)
						{
						case 0:
							byTempOut = (byTempIn & 0x80);	//1000 0000
							byTempOut = (byTempOut >> (y%8));//得出此位在目的字节中应在哪一位
							break;
						case 1:
							byTempOut = (byTempIn & 0x40);	//0100 0000
							if(y%8-1 < 0)
								byTempOut = (byTempOut << (1-y%8));
							else
								byTempOut = (byTempOut >> (y%8-1));
							break;
						case 2:
							byTempOut = (byTempIn & 0x20);	//0010 0000
							if(y%8-2 < 0)
								byTempOut = (byTempOut << (2-y%8));
							else
								byTempOut = (byTempOut >> (y%8-2));
							break;
						case 3:
							byTempOut = (byTempIn & 0x10);	//0001 0000
							if(y%8-3 < 0)
								byTempOut = (byTempOut << (3-y%8));
							else
								byTempOut = (byTempOut >> (y%8-3));
							break;
						case 4:
							byTempOut = (byTempIn & 0x08);	//0000 1000
							if(y%8-4 < 0)
								byTempOut = (byTempOut << (4-y%8));
							else
								byTempOut = (byTempOut >> (y%8-4));
							break;
						case 5:
							byTempOut = (byTempIn & 0x04);	//0000 0100
							if(y%8-5 < 0)
								byTempOut = (byTempOut << (5-y%8));
							else
								byTempOut = (byTempOut >> (y%8-5));
							break;
						case 6:
							byTempOut = (byTempIn & 0x02);	//0000 0010
							if(y%8-6 < 0)
								byTempOut = (byTempOut << (6-y%8));
							else
								byTempOut = (byTempOut >> (y%8-6));
							break;
						case 7:
							byTempOut = (byTempIn & 0x01);	//0000 0001
							byTempOut = (byTempOut << (7-y%8));
							break;
						}

						OutPointer = OutRow * iNewPitch +OutColumn;
						BYTE byDestBuffer = pNewImage[OutPointer];
						byDestBuffer = (byDestBuffer | byTempOut);
						pNewImage[OutPointer] = byDestBuffer;
					}//for(BitPointer)
				}//for(x)
			}//for(y)
		}
		break;
	case 4:
		{
			memset(pNewImage,0,iNewImgDataSize);	//全置为0，便于后面的按位或操作
			int OutPointer = 0;
			for(int y=0;y<iSrcHeight;y++)
			{
				BYTE* pIn = GetLine(y);
				for(int x=0;x<iSrcRowBytes;x++)
				{
					int PixPointer = 0;		//确定是在该字节中的第几个象素
					int OutColumn = y/2;	//2行翻转后构成一字节
					BYTE byTempIn = pIn[x];	//取一个字节，即2个象素
					BYTE byTempOut;

					for(PixPointer=0;PixPointer<2;PixPointer++)
					{
						int OutRow = iSrcWidth - (x*2+PixPointer) - 1;
						//注意：最高位代表最左边的象素!
						switch(PixPointer)
						{
						case 0:
							byTempOut = (byTempIn & 0xF0);	//1111 0000
							byTempOut = (byTempOut >> (y%2*4));
							break;
						case 1:
							byTempOut = (byTempIn & 0x0F);	//0000 1111
							byTempOut = (byTempIn << (4-y%2*4));
							break;
						}

						OutPointer = OutRow * iNewPitch +OutColumn;
						BYTE byDestBuffer = pNewImage[OutPointer];
						byDestBuffer = (byDestBuffer | byTempOut);
						pNewImage[OutPointer] = byDestBuffer;
					}//for(PixPointer)
				}//for(x)
			}//for(y)
		}
		break;
	case 16:
		{
			int OutPointer = 0;
			for(int y = 0;y < iSrcHeight;y++)
			{
				BYTE *pIn = GetLine(y);
				for(int x = 0;x < iSrcWidth;x++)
				{
					//16位时一个象素占两字节宽
					int OutColumn = y*2;			//这两行看起来是做逆时针旋转，但由于DIB
					int OutRow = iSrcWidth - x - 1;	//是由下到上存储图像的，故实际上是顺时针
					//int OutColumn = iSrcHeight - y - 1;//而这两行注释掉的则正相反，是逆时针的
					//int OutRow = x;
					OutPointer = OutRow * iNewPitch + OutColumn;
					CopyMemory(&pNewImage[OutPointer],&pIn[x*2],2);
				}
			}
		}
		break;
	case 24:
		{
			int OutPointer = 0;
			for(int y = 0;y < iSrcHeight;y++)
			{
				BYTE *pIn = GetLine(y);
				for(int x = 0;x < iSrcWidth;x++)
				{
					//16位时一个象素占三字节宽
					int OutColumn = y*3;			//这两行看起来是做逆时针旋转，但由于DIB
					int OutRow = iSrcWidth - x - 1;	//是由下到上存储图像的，故实际上是顺时针
					//int OutColumn = iSrcHeight - y - 1;//而这两行注释掉的则正相反，是逆时针的
					//int OutRow = x;
					OutPointer = OutRow * iNewPitch + OutColumn;
					CopyMemory(&pNewImage[OutPointer],&pIn[x*3],3);
				}
			}
		}
		break;
	case 32:
		{
			int OutPointer = 0;
			for(int y = 0;y < iSrcHeight;y++)
			{
				BYTE *pIn = GetLine(y);
				for(int x = 0;x < iSrcWidth;x++)
				{
					//16位时一个象素占四字节宽
					int OutColumn = y*4;			//这两行看起来是做逆时针旋转，但由于DIB
					int OutRow = iSrcWidth - x - 1;	//是由下到上存储图像的，故实际上是顺时针
					//int OutColumn = iSrcHeight - y - 1;//而这两行注释掉的则正相反，是逆时针的
					//int OutRow = x;
					OutPointer = OutRow * iNewPitch + OutColumn;
					CopyMemory(&pNewImage[OutPointer],&pIn[x*4],4);
				}
			}
		}
		break;
	}

	//打开图像后未做变换，则不能delete,因这时的m_pImage指向的空间不是在此new出来的
	if(m_bBufferIsOriginal)
	{
		m_pOriginImage = m_pImage;	//保留原来的图像数据
		m_nOriginWidth = m_nWidth;
		m_nOriginHeight = m_nHeight;
		m_nOriginPitch = m_nPitch;
		m_nOriginImage = m_nImage;
	}
	else
		delete [] m_pImage;

	m_pImage = pNewImage;
	pNewImage = NULL;
	//交换宽高[!-注意：不能在此函数开头就改变m_LImage的宽高，因为在从源数据区取数据时用到了
	//GetLine()函数，而此函数与原图片的宽高和m_nPitch有关，如开始就破坏了原图片的宽高值，
	//那么将得到错误的结果。-]
	m_nWidth = iSrcHeight;
	m_nHeight = iSrcWidth;
	m_nPitch = iNewPitch;
	m_nImage = iNewImgDataSize;
	m_bBufferIsOriginal = FALSE;
}
