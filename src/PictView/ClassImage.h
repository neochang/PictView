#pragma once

#include <afx.h>
#include "Lib/Jpeg.h"
#include "Lib/Gif.h"
#pragma comment(lib,"vfw32.lib")

#ifndef UC_SWAP_HEIGHT
#define UC_SWAP_HEIGHT(a)	((a))
#endif
#define UC_USE_DC	//\\\\\\\\\\\\\\\\

enum LanFormat
{
	LanF_Unkown		= 0,
	LanF_A8R8G8B8	= 1,
	LanF_R8G8B8		= 2,
	LanF_R5G6B5		= 3,
	LanF_R5G5B5		= 4,
	LanF_A4R4G4B4	= 5,
	LanF_Index8		= 6,
	LanF_Index4		= 7,
	LanF_Index1		= 8,
};


class LanImage
{
public:
	BYTE *		m_pImage;
	CJpeg*		m_pJpeg;		//CJpeg类对象指针，采用Lib Sources中的读法时使用
								//#不可直接用对象,因CJpeg类中还有指针，在析构时会出错
	CGif*		m_pGif;
	int			m_nWidth;		//图像实际宽度
	int			m_nHeight;		//图像实际高度
	int			m_nDrawWidth;	//图像显示宽度
	int			m_nDrawHeight;	//图像显示高度
	int			m_nBitCount;
	int			m_nPitch;		//DIB一行所占字节数
	int			m_nImage;		//图像数据的字节数
	int			m_nPalette;
	long		nFileSize;
	//----------------------	//当被旋转时保存原来的图像可能被改变的信息
	BYTE *		m_pOriginImage;
	int			m_nOriginWidth;
	int			m_nOriginHeight;
	int			m_nOriginPitch;
	int			m_nOriginImage;
	BOOL		m_bBufferIsOriginal;
	//----------------------
	BOOL		m_bReadWithLibSupport;	//是使用Lib Sources中的方法，因其中的读写方法与ClassImage的不同
	RGBQUAD		*m_pPal;
	LanFormat	m_eFmt;
#ifdef UC_USE_DC
	HBITMAP	m_hBitmap;
#endif
public:
	LanImage()
	{
		memset(this,0,sizeof(LanImage));
		m_bReadWithLibSupport = FALSE;
		m_pJpeg = NULL;
		m_pGif = NULL;
		m_pPal = NULL;
	}

	~LanImage()
	{
#ifdef UC_USE_DC
		if(m_hBitmap)
			DeleteObject(m_hBitmap);	//m_hBitmap中包含了m_pImage最初指向的区域
#else
		if(m_bReadWithLibSupport)//如果使用了Lib Sources，这时m_pImage指向的是原来CJpeg类的一部分空间，
			m_pImage = NULL;	//而该类已摧毁，故那部分空间已由其收回。
		
		delete [] m_pImage;
		m_pImage = NULL;
#endif
		delete m_pJpeg;
		m_pJpeg = NULL;
		delete m_pGif;
		m_pGif = NULL;

		if(m_pPal)
		{
			delete [] m_pPal;
			m_pPal = NULL;
		}
	}

///////////////////////////////////////////////////////////////////////////
//	The following eight functions are implemented is file ClassImage.cpp

	BOOL Create(int nWidth,int nHeight,int nBitCount,int ndegree,LanFormat eFmt = LanF_Unkown);
	BOOL Create_No(int nWidth,int nHeight,int nBitCount,LanFormat eFmt = LanF_Unkown);
	BOOL LoadImage(LPCTSTR pszFileName,int ndegree,BOOL isconvert);
 	BOOL CopyFrom(const LanImage & Img);
	void Release();
	//######
	BOOL CreateDib(CDib **pDib);	//从由数据区创建CDib对象,参数**pDib为了传进指针的地址
	void Rotate90Clockwise();		//顺时针旋转图像90度
	
#ifdef UC_USE_DC
	HDC  GetDC();
	void ReleaseDC(HDC hdc);
#endif
/////////////////////////////////////////////////////////////////////////////
//##**##
	BOOL ReadBmp(LPBYTE pBuffer,UINT uLength,int ndegree,BOOL isconvert);	//Implemented in file ImageBmp.cpp
	BOOL ReadTga(LPBYTE pBuffer,UINT uLength,int ndegree);					//Implemented in file ImageTga.cpp
	BOOL ReadPcx(LPBYTE pBuffer,UINT uLength,int ndegree);					//Implemented in file ImagePcx.cpp


//////////////////////////////////////////////////////////////////////////////
//  The following four functions are implemented in file ImageBmpConvert.cpp

	BOOL Convert32();
	BOOL Convert32(const LanImage &Img);
	BOOL ConvertFrom32(LanFormat eFmt);
	BOOL ConvertFrom32(const LanImage &Img,LanFormat eFmt);
///////////////////////////////////////////////////////////////////////////////
//##**##
	BOOL SaveBmp(LPCTSTR pszFileName) const;
	BOOL SaveTga(LPCTSTR pszFileName) const;
	BOOL SavePcx(LPCTSTR lpstrFileName, CDib* pDib);

	//Function of Displaying the image:
	BOOL Draw(HDC hdc,int nDx,int nDy,int nDw,int nDh,
				int nSx,int nSy,int nSw,int nSh,UINT uFlags = 0) const;

	BOOL	IsLoad() const{ return m_pImage != NULL;}
	
	int		GetWidth() const{ return m_nWidth;}
	int		GetHeight() const{ return m_nHeight;}
	int		GetBitCount() const{ return m_nBitCount;}
	int		GetPitch() const{ return m_nPitch;}
	int		GetBltPitch() const
	{
		if(UC_SWAP_HEIGHT(0))
			return m_nPitch;
		else
			return -m_nPitch;
	}
	LanFormat GetFormat()
	{
		return m_eFmt;
	}
	int		GetPalCount() const{ return m_nPalette;}
	RGBQUAD*GetPalette(){ return m_pPal;}
	const RGBQUAD *	GetPalette() const{ return m_pPal;}
	int		GetSize() const{ return m_nImage;}
	BYTE *	GetImage(){ return m_pImage;}
	const BYTE * GetImage() const{ return m_pImage;}

	BYTE * GetBltLine(int nLine)	/////////////////////////////
	{
		if(UC_SWAP_HEIGHT(0))
			return m_pImage + m_nPitch * nLine;
		else
			return m_pImage + m_nPitch * (m_nHeight - nLine - 1);
	}

	const BYTE * GetBltLine(int nLine) const
	{
		if(UC_SWAP_HEIGHT(0))
			return m_pImage + m_nPitch * nLine;
		else
			return m_pImage + m_nPitch * (m_nHeight - nLine - 1);
	}

	BYTE * GetLine(int nLine)
	{
		return m_pImage + m_nPitch * nLine;
	}
	const BYTE * GetLine(int nLine) const
	{
			return m_pImage + m_nPitch * nLine;
	}
private:
	LanImage(const LanImage &);
	LanImage & operator = (const LanImage &);
};