//*************************************************************************************************
//ImagePcx.cpp:包含本程序需要PCX图像的读入代码
//*************************************************************************************************
#include "stdafx.h"
#include "ClassImage.h"

static BYTE * RLE_PCX_Decode8(BYTE * InBuffer,int nInSize,BYTE * OutBuffer)
{
	register BYTE Data,Num;
	while(nInSize > 0)
	{
		Data = *InBuffer++;
		if((Data & 0xC0) == 0xC0)
		{
			Num = Data & 0x3F;
			memset(OutBuffer,*InBuffer++,Num);
			OutBuffer += Num;
			nInSize -= Num;
		}
		else
		{
			*OutBuffer++ = Data;
			nInSize--;
		}
	}
	return InBuffer;
}

static int RLE_PCX_Decode24(BYTE * InBuffer,int nInSize,BYTE * OutBuffer)
{
	register BYTE Data,Num;
	register int nWrite = 0;
	while(nInSize-- > 0)
	{
		Data = *InBuffer++;
		if((Data & 0xC0) == 0xC0)
		{
			Num = Data & 0x3F;
			memset(OutBuffer,*InBuffer++,Num);
			OutBuffer += Num;
			nWrite += Num;
			nInSize--;
		}
		else
		{
			*OutBuffer++ = Data;
			nWrite++;
		}
	}
	return nWrite;
}

#pragma pack(push)
#pragma pack(1)

typedef struct tagPCXHEAD
{
	BYTE manufacturer;
		//0x0A
	BYTE version;
		//0,2,3,4,5
	BYTE encoding;
		//1 RLE
	BYTE bit_per_pixel;
		//1,4,8
	WORD xmin;
	WORD ymin;
	WORD xmax;
	WORD ymax;
	WORD Xresolution;
	WORD Yresolution;
	BYTE palette[48];
		//1或4Bits图象调色板
	BYTE reserved;
		//0
	BYTE color_planes;
		//色彩平面数目(1,3,4)
	WORD byte_per_line;
		//每行图象的字节宽度
	WORD palette_type;
		//1
	WORD screen_width;
	WORD screen_height;
	BYTE filter[54];
		//0
}PCXHEAD, *PPCXHEAD;

typedef struct tagPCXPALETTE
{
  BYTE rgbRed;
  BYTE rgbGreen;
  BYTE rgbBlue;
} PCXPALETTE;
#pragma pack(pop)

/****
****** Write a single line of a PCX file. *******
****/
BOOL WritePCXLine(int bytes, BYTE *p, FILE *fp)
{
	unsigned int i=0, j=0, t=0;

	do
	{
		i = 0;
		while ((p[t+i]==p[t+i+1]) && ((t+i)<(WORD)bytes) && (i<63))
			++i;
		if (i > 0) /* there are i equal pixels from current position */
		{
			fputc(i|0xc0, fp);          /* write duplicated number */
			fputc(p[t], fp);           /* write pixel value */
			t += i;						/* bytes have been processed */
			j += 2;						/* bytes have been written to file */
		}
		else	/* no duplicated pixel */
		{
			if (((p[t]) & 0xc0) == 0xc0) /* pixel value > 192 ? */
			{
				fputc(0xc1, fp);        /* write identify sign 0xc1 */
				++j;
			}
			fputc(p[t++], fp);
			++j;
		}
	} while (t < (WORD)bytes);

	return (ferror(fp) ? FALSE : TRUE);
}

//******************* 读取PCX ***********************
BOOL LanImage::ReadPcx(LPBYTE pFileBuffer,UINT nFileSize,int ndegree)
{
	PCXHEAD * ph = (PCXHEAD *)pFileBuffer;
	if(ph->manufacturer != 0x0A)
		return FALSE;

	int nWidth = ph->xmax - ph->xmin + 1;
	int nHeight = ph->ymax - ph->ymin + 1;
	int nBitCount = ph->bit_per_pixel * ph->color_planes;

	Create(nWidth,nHeight,nBitCount,ndegree);

	if(nBitCount <= 8)
	{
		BYTE * pImage = pFileBuffer + sizeof(PCXHEAD);
		//非颠倒
		if(UC_SWAP_HEIGHT(0))
		{
			BYTE * pOut = GetLine(0);
			for(int y=0; y<nHeight; ++y)
			{
				pImage = RLE_PCX_Decode8(pImage,ph->byte_per_line,pOut);
				pOut += m_nPitch;
			}
		}
		else
		{//图象颠倒
			BYTE * pOut = GetLine(m_nHeight - 1);
			for(int y=0; y<nHeight; ++y)
			{
				pImage = RLE_PCX_Decode8(pImage,ph->byte_per_line,pOut);
				pOut -= m_nPitch;
			}
		}
	}
	else // 24,32
	{
		BYTE * const pImage = new BYTE[ph->color_planes * ph->byte_per_line * nHeight + 1024];
		int nWrite = RLE_PCX_Decode24(pFileBuffer + sizeof(PCXHEAD),
										nFileSize - sizeof(PCXHEAD),
										pImage);
		BYTE * pCur = pImage;
		
		if(UC_SWAP_HEIGHT(0))
		{//非颠倒
			for(int y=0; y<nHeight; ++y)
			{
				BYTE * pOut = GetLine(y);
				BYTE * pRed = pCur;
				BYTE * pGreen = pRed + ph->byte_per_line;
				BYTE * pBlue = pGreen + ph->byte_per_line;
				for(int x=0; x<nWidth; ++x, pOut += ph->color_planes)
				{
					pOut[0] = *pBlue++;
					pOut[1] = *pGreen++;
					pOut[2] = *pRed++;
				}

				pCur += ph->byte_per_line * ph->color_planes;
			}
		}
		else
		{//图象颠倒
			for(int y=0; y<nHeight; ++y)
			{
				BYTE * pOut = GetLine(m_nHeight - y - 1);
				BYTE * pRed = pCur;
				BYTE * pGreen = pRed + ph->byte_per_line;
				BYTE * pBlue = pGreen + ph->byte_per_line;
				for(int x=0; x<nWidth; ++x, pOut += ph->color_planes)
				{
					pOut[0] = *pBlue++;
					pOut[1] = *pGreen++;
					pOut[2] = *pRed++;
				}

				pCur += ph->byte_per_line * ph->color_planes;
			}
		}
		
		delete [] pImage;
	}

	//调色板
	if(nBitCount <= 8)
	{
		if(ph->palette_type <= 1) //彩色或者单色
		{
			if(ph->version == 3)	//使用系统自己的调色板
			{
				PALETTEENTRY pe[256];
				HDC hdc = ::GetDC(NULL);
				GetSystemPaletteEntries(hdc,0, 1<<nBitCount,pe);
				::ReleaseDC(NULL,hdc);
				for(int i=0; i<(1<<nBitCount); ++i)
				{
					m_pPal[i].rgbBlue = pe[i].peBlue;
					m_pPal[i].rgbGreen = pe[i].peGreen;
					m_pPal[i].rgbRed = pe[i].peRed;
					m_pPal[i].rgbReserved = pe[i].peFlags;
				}
			}
			else	//自带调色板
			{
				BYTE * pCurr = (nBitCount <= 4) ? 
							ph->palette : (pFileBuffer + nFileSize - 768);
				for(int i=0; i<(1<<nBitCount); ++i)
				{
					m_pPal[i].rgbRed = *pCurr++;
					m_pPal[i].rgbGreen = *pCurr++;
					m_pPal[i].rgbBlue = *pCurr++;
				}
			}
		}
		else	//灰度图
		{
			int nPerAdd = 256/(1<<nBitCount);
			for(int i=0; i<(1<<nBitCount); ++i)
			{
				m_pPal[i].rgbBlue = 
				m_pPal[i].rgbGreen = 
				m_pPal[i].rgbRed = 
					i * nPerAdd;
				m_pPal[i].rgbReserved = 0;
			}
		}
	}

	return TRUE;
}

//******************* 保存为PCX (由CDib对象) ***********************
BOOL LanImage::SavePcx(LPCTSTR lpstrFileName, CDib* pDib)
{
	if (pDib == NULL)
		return FALSE;

	HDIB hDib = CopyHandle(pDib->GetHandle());
	if (hDib == NULL)
		return FALSE;

	CDib* pDibTmp = new CDib();
	pDibTmp->Attach(hDib);

	UINT uWidth  = pDibTmp->GetWidth();
	UINT uHeight = pDibTmp->GetHeight();

	// 当打开的图像BitCount不为8时，转为8位格式
	if (pDibTmp->GetBitCount() != 8)
		pDibTmp->ConvertFormat(8);

	// make PCX header
	PCXHEAD header;
	memset((LPBYTE)&header, 0, sizeof(PCXHEAD));
	header.manufacturer = 0x0A;
	header.version = 5;
	header.encoding = 1;
	header.bit_per_pixel = 8;
	//header.bit_per_pixel = 24;
	header.xmin = 0;
	header.ymin = 0;
	header.xmax = uWidth-1;
	header.ymax = uHeight-1;
	//header.Xresolution;
	//header.Yresolution;
	header.palette[0] = (BYTE)0x00;  // for correct process for mono
	header.palette[1] = (BYTE)0x00;
	header.palette[2] = (BYTE)0x00;
	header.palette[3] = (BYTE)0xff;
	header.palette[4] = (BYTE)0xff;
	header.palette[5] = (BYTE)0xff;
	//header.palette[48];
	header.reserved = 0;
	header.color_planes = 1;
	header.byte_per_line = uWidth;
	header.palette_type = 1;
	//filler[58];

	// construct PCX palette from DIB color table
	PCXPALETTE palette[256];
	PALETTEENTRY PaletteColors[256];
	pDibTmp->GetPalette()->GetPaletteEntries(0, 256, PaletteColors);
	for (int i=0;i<256;i++) 
	{
		palette[i].rgbRed   = PaletteColors[i].peRed;
		palette[i].rgbGreen = PaletteColors[i].peGreen;
		palette[i].rgbBlue  = PaletteColors[i].peBlue;
	}

	// get bits ptr
	HDIB hDIB = CopyHandle(pDibTmp->GetHandle());
	delete pDibTmp;
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB);
	BYTE* lpBuffer = (BYTE *)FindDIBBits(lpDIB);
	WORD wWidthBytes = (WORD)BytesPerLine(lpDIB);

	/*** Open the PCX file ***/
	FILE *outFile;
	if ((outFile=fopen(lpstrFileName,"wb")) == NULL)
	{
		GlobalUnlock(hDIB);
		GlobalFree(hDIB);
		return FALSE;
	}

	/*** Write the header ***/
	fwrite((char *)&header, sizeof(PCXHEAD), 1, outFile);

	/*** Write image data ***/
	for ( i=(int)uHeight-1; i>=0; --i)
	{
		if (! WritePCXLine(header.byte_per_line, lpBuffer+i*wWidthBytes, outFile))
		{
			fclose(outFile);
			GlobalUnlock(hDIB);
			GlobalFree(hDIB);
			return FALSE;
		}
	}

	/*** Write the palette data ***/
	fputc(0x0c, outFile);
	fwrite((char *)palette, 1, sizeof(palette), outFile);

	// clear & close
	fclose(outFile);
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	return TRUE;
}