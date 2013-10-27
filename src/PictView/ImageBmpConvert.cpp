#include "stdafx.h" 
#include "ClassImage.h"

inline DWORD _4444_to_32(DWORD clr)
{
	return ((clr & 0x000F) << 4) | ((clr & 0x00F0) << 8) | ((clr & 0x0F00) << 12) | ((clr & 0xF000) << 16);
}
inline DWORD _555_to_32(DWORD clr)
{
	return ((clr & 0x001F) << 3) | ((clr & 0x03E0) << 6) | ((clr & 0x7C00) << 9);
}
inline DWORD _565_to_32(DWORD clr)
{
	return ((clr & 0x001F) << 3) | ((clr & 0x07E0) << 5) | ((clr & 0xF800) << 8);
}
inline DWORD _24_to_32(BYTE r,BYTE g,BYTE b)
{
	return ((DWORD)r<<16) | ((DWORD)g<<8) | ((DWORD)b);
}

inline WORD _32_to_4444(DWORD clr)
{
	return (WORD)(((clr & 0xF0) >> 4) | ((clr & 0xF000) >> 8) | ((clr & 0xF00000) >> 12) | ((clr & 0xF0000000) >> 16));
}
inline WORD _32_to_555(DWORD clr)
{
	return (WORD)(((clr & 0xF8) >> 3) | ((clr & 0xF800) >> 6) | ((clr & 0xF80000) >> 9));
}
inline WORD _32_to_565(DWORD clr)
{
	return (WORD)(((clr & 0xF8) >> 3) | ((clr & 0xFE00) >> 5) | ((clr & 0xF80000) >> 8));
}
inline void _32_to_24(DWORD clr, BYTE & r,BYTE & g,BYTE & b)
{
	b = (BYTE)(clr & 0xFF);
	g = (BYTE)((clr & 0xFF00) >> 8);
	r = (BYTE)((clr & 0xFF0000) >> 16);
}

BOOL LanImage::Convert32()
{
	if(m_eFmt == LanF_A8R8G8B8)
		return TRUE;
	LanImage temp;
	if(temp.Convert32(*this) == FALSE)
		return FALSE;

#ifdef UC_USE_DC
	if(m_hBitmap)
		DeleteObject(m_hBitmap);
#else
	delete [] m_pImage;
#endif
	delete [] m_pPal;

	m_pImage = temp.GetImage();
	m_pPal = NULL;
	m_nPalette = 0;
	m_nBitCount = 32;
	m_nPitch = temp.GetPitch();
	m_nImage = temp.GetSize();
	m_eFmt = LanF_A8R8G8B8;
#ifdef UC_USE_DC
	m_hBitmap = temp.m_hBitmap;
	temp.m_hBitmap = NULL;
#endif
	temp.m_pImage = NULL;

	return TRUE;
}

BOOL LanImage::Convert32(const LanImage &Img)
{
	if(&Img == this || Img.IsLoad() == FALSE)
		return FALSE;

	Create_No(Img.GetWidth(),Img.GetHeight(),32);

	switch(Img.m_eFmt)
	{
	case LanF_A8R8G8B8:
		memcpy(GetImage(),Img.GetImage(),Img.GetSize());
		break;
	case LanF_R8G8B8:
		{
			BYTE * pIn = (BYTE *)Img.GetImage();
			DWORD * pOut = (DWORD *)GetImage();
			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					pOut[x] = _24_to_32(pIn[x*3+2],pIn[x*3+1],pIn[x*3+0]);
				}
				pIn = (BYTE *)((int)pIn + Img.GetPitch());
				pOut = (DWORD *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_R5G5B5:
		{
			WORD * pIn = (WORD *)Img.GetImage();
			DWORD * pOut = (DWORD *)GetImage();
			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					pOut[x] = _555_to_32(pIn[x]);
				}
				pIn = (WORD *)((int)pIn + Img.GetPitch());
				pOut = (DWORD *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_R5G6B5:
		{
			WORD * pIn = (WORD *)Img.GetImage();
			DWORD * pOut = (DWORD *)GetImage();
			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					pOut[x] = _565_to_32(pIn[x]);
				}
				pIn = (WORD *)((int)pIn + Img.GetPitch());
				pOut = (DWORD *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_A4R4G4B4:
		{
			WORD * pIn = (WORD *)Img.GetImage();
			DWORD * pOut = (DWORD *)GetImage();
			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					pOut[x] = _4444_to_32(pIn[x]);
				}
				pIn = (WORD *)((int)pIn + Img.GetPitch());
				pOut = (DWORD *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_Index8:
		{
			const RGBQUAD * pal = Img.GetPalette();
			BYTE * pIn = (BYTE *)Img.GetImage();
			DWORD * pOut = (DWORD *)GetImage();

			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; x++)
				{
					int nIndex = pIn[x];
					pOut[x] = _24_to_32(pal[nIndex].rgbRed,pal[nIndex].rgbGreen,pal[nIndex].rgbBlue);
				}

				pIn = (BYTE *)((int)pIn + Img.GetPitch());
				pOut = (DWORD *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_Index4:
		{
			const RGBQUAD * pal = Img.GetPalette();
			BYTE * pIn = (BYTE *)Img.GetImage();
			DWORD * pOut = (DWORD *)GetImage();

			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; x += 2)
				{
					int nIndex = (pIn[x/2] & 0xF0) >> 4;
					pOut[x+0] = _24_to_32(pal[nIndex].rgbRed,pal[nIndex].rgbGreen,pal[nIndex].rgbBlue);
					if(x + 1 < m_nWidth)
					{
						nIndex = pIn[x/2] & 0x0F;
						pOut[x+1] = _24_to_32(pal[nIndex].rgbRed,pal[nIndex].rgbGreen,pal[nIndex].rgbBlue);
					}
				}

				pIn = (BYTE *)((int)pIn + Img.GetPitch());
				pOut = (DWORD *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_Index1:
		{
			const RGBQUAD * pal = Img.GetPalette();
			BYTE * pIn = (BYTE *)Img.GetImage();
			DWORD * pOut = (DWORD *)GetImage();

			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; x += 8)
				{
					for(int n=min(8,m_nWidth-x)-1; n>=0; --n)
					{
						int nIndex = (pIn[x/8] & (1 << n)) >> n;
						pOut[x+8-n] = _24_to_32(pal[nIndex].rgbRed,pal[nIndex].rgbGreen,pal[nIndex].rgbBlue);
					}
				}

				pIn = (BYTE *)((int)pIn + Img.GetPitch());
				pOut = (DWORD *)((int)pOut + GetPitch());
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL LanImage::ConvertFrom32(LanFormat eFmt)
{
	if(m_eFmt == eFmt)
		return TRUE;
	LanImage temp;
	if(FALSE == temp.ConvertFrom32(*this,eFmt))
		return FALSE;

#ifdef UC_USE_DC
	if(m_hBitmap)
		DeleteObject(m_hBitmap);
#else
	delete [] m_pImage;
#endif
	delete [] m_pPal;

	m_pImage = temp.GetImage();
	m_pPal = temp.GetPalette();
	m_nPalette = temp.GetPalCount();
	m_nBitCount = temp.GetBitCount();
	m_nPitch = temp.GetPitch();
	m_nImage = temp.GetSize();
	m_eFmt = eFmt;

#ifdef UC_USE_DC
	m_hBitmap = temp.m_hBitmap;
	temp.m_hBitmap = NULL;
#endif
	temp.m_pImage = NULL;

	return TRUE;
}

BOOL LanImage::ConvertFrom32(const LanImage &Img,LanFormat eFmt)
{
	if(&Img == this || Img.IsLoad() == FALSE)
		return FALSE;

	switch(eFmt)
	{
	case LanF_A8R8G8B8:
		Create(Img.GetWidth(),Img.GetHeight(),32,eFmt);
		memcpy(GetImage(),Img.GetImage(),Img.GetSize());
		break;
	case LanF_R8G8B8:
		Create(Img.GetWidth(),Img.GetHeight(),24,eFmt);
		{
			DWORD * pIn = (DWORD *)Img.GetImage();
			BYTE * pOut = (BYTE *)GetImage();
			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					_32_to_24(pIn[x],pOut[x*3+2],pOut[x*3+1],pOut[x*3+0]);
				}
				pIn = (DWORD *)((int)pIn + Img.GetPitch());
				pOut = (BYTE *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_R5G5B5:
		Create(Img.GetWidth(),Img.GetHeight(),16,eFmt);
		{
			DWORD * pIn = (DWORD *)Img.GetImage();
			WORD * pOut = (WORD *)GetImage();
			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					pOut[x] = _32_to_555(pIn[x]);
				}
				pIn = (DWORD *)((int)pIn + Img.GetPitch());
				pOut = (WORD *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_R5G6B5:
		Create(Img.GetWidth(),Img.GetHeight(),16,eFmt);
		{
			DWORD * pIn = (DWORD *)Img.GetImage();
			WORD * pOut = (WORD *)GetImage();
			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					pOut[x] = _32_to_565(pIn[x]);
				}
				pIn = (DWORD *)((int)pIn + Img.GetPitch());
				pOut = (WORD *)((int)pOut + GetPitch());
			}
		}
		break;
	case LanF_A4R4G4B4:
		Create(Img.GetWidth(),Img.GetHeight(),16,eFmt);
		{
			DWORD * pIn = (DWORD *)Img.GetImage();
			WORD * pOut = (WORD *)GetImage();
			for(int y=0; y<m_nHeight; ++y)
			{
				for(int x=0; x<m_nWidth; ++x)
				{
					pOut[x] = _32_to_4444(pIn[x]);
				}
				pIn = (DWORD *)((int)pIn + Img.GetPitch());
				pOut = (WORD *)((int)pOut + GetPitch());
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
