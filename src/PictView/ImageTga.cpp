#include "stdafx.h"
#include "ClassImage.h"
#include "stdio.h"

static BYTE * RLE_TGA_DecodeLine(BYTE * InBuffer,int iColorBit,int iNumPixel,BYTE * OutBuffer)
{
	register BYTE Data;
	register int Num;
	iColorBit = (iColorBit + 7) / 8;
	while(iNumPixel > 0)
	{
		Data = *InBuffer++;
		if((Data & 0x80) == 0x80)
		{
			Num = (Data & 0x7F) + 1;
			iNumPixel -= Num;
			for(int i=0; i<Num; ++i,OutBuffer += iColorBit)
				memcpy(OutBuffer,InBuffer,iColorBit);
			InBuffer += iColorBit;
		}
		else
		{
			Num = ++Data;
			iNumPixel -= Num;
			Num *= iColorBit;
			memcpy(OutBuffer,InBuffer,Num);
			OutBuffer += Num;
			InBuffer += Num;
		}
	}

	return InBuffer;
}

static BYTE * RLE_TGA_EncodeLine(const BYTE * InBuffer, int iColorBit,
								  int iNumPixel, BYTE * OutBuffer)
{
	DWORD			Data, Next ;
	const BYTE		* pBak ;
	register DWORD	Count ;

	iColorBit = (iColorBit + 7) / 8 ; // 转换为字节数
	while (iNumPixel > 0)
	{
		pBak = InBuffer ; // 记数指针
		memcpy (&Data, InBuffer, iColorBit) ; // 第一个像素
		InBuffer += iColorBit ; iNumPixel-- ; Count = 1 ;
		while ((Count < 0x7F) && (iNumPixel > 0)) // 统计重复像素
		{
			memcpy (&Next, InBuffer, iColorBit) ; // 下一个像素
			if (Next != Data)
				break ;
			InBuffer += iColorBit ; iNumPixel-- ; Count++ ;
		}

		if (Count == 1) // 无重复像素
		{
			while ((Count < 0x7F) && (iNumPixel > 0)) // 统计不重复像素
			{
				Count++ ; Data = Next ;
				InBuffer += iColorBit ; iNumPixel-- ;
				memcpy (&Next, InBuffer, iColorBit) ; // 下一个像素
				if (Data == Next)
					break ;
			}
			// 直接copy不重复像素
			*OutBuffer++ = (BYTE)(Count - 1) ;
			Count = InBuffer - pBak ; // Count->临时变量
			memcpy (OutBuffer, pBak, Count) ;
			OutBuffer += Count ;
		}
		else // 重复像素
		{
			*OutBuffer++ = 0x80 | (BYTE)--Count ;
			memcpy (OutBuffer, &Data, iColorBit) ;
			OutBuffer += iColorBit ;
		}		
	} // End of while
	return OutBuffer ;
}

#pragma pack(push,1)
typedef struct tagTGAHEAD
{
	BYTE	byID_Length;
	//本结构体大小
	BYTE	byPalType;
	//调色板类型：0无调色板，1有调色板
	BYTE	byImageType;
	//01 UC+PAL,02 UC+NP 03 UC+BW,09 RLE+PAL,0A RLE+NP 0B RLE+BW
	WORD	wPalFirstNdx;
	//调色板其始索引
	WORD	wPalLength;
	//调色板长度
	BYTE	byPalBits;
	//调色板中每一颜色占用的位数
	WORD	wLeft;//X
	WORD	wBottom;//X
	WORD	wWidth;
	WORD	wHeight;
	BYTE	byColorBits;
	BYTE	desc;
}TGAHEAD, *PTGAHEAD;

typedef struct tagTGAFooter
{
	long	ext_area;
	long	dev_area;
	char	signature[18]; //"TRUEVISION-XFILE"
}TGAFooter;
#pragma pack(pop)

BOOL LanImage::ReadTga(LPBYTE pFileBuffer,UINT nFileSize,int ndegree)
{
	TGAHEAD  * ph = (TGAHEAD *)pFileBuffer;
	TGAFooter * pf = (TGAFooter *)(pFileBuffer + nFileSize - 26);
	if(ph->byColorBits ==15)	//16位色555格式，应该将byCorlorBits置为16.
		ph->byColorBits = 16;

	//判断是否正是一个TGA图
//	if(strncmp(pf->signature,"TRUEVISION-XFILE",16) != 0)
//	{
//		delete [] pFileBuffer;
//		return FALSE;
//	}

	if(FALSE == Create(ph->wWidth,ph->wHeight,ph->byColorBits,ndegree))
		return FALSE;
	if(ph->byID_Length == 0)
		ph->byID_Length = sizeof(TGAHEAD);

	BYTE * pCurr = pFileBuffer + ph->byID_Length;
	DWORD dwPicth = ph->wWidth * ph->byColorBits / 8;	//一行图象数据的长度

	//读调色板
	if(ph->byPalType == 1)
	{
		if(ph->byPalBits == 24 || ph->byPalBits == 32)
		{
			for(int i=ph->wPalFirstNdx; i<ph->wPalFirstNdx + ph->wPalLength; ++i)
			{
				m_pPal[i].rgbBlue = *pCurr++;
				m_pPal[i].rgbGreen = *pCurr++;
				m_pPal[i].rgbRed = *pCurr++;
				if(ph->byPalBits == 32)
					m_pPal[i].rgbReserved = *pCurr++;
				else
					m_pPal[i].rgbReserved = 0;
			}
		}
		else
		{
			return FALSE;
		}
	}

	//解码图象数据
	if(ph->byImageType & 0x08) //压缩
	{
		if(UC_SWAP_HEIGHT(ph->desc & 0x20))	//上下颠倒
		{
			BYTE * pOut = GetLine(m_nHeight - 1);
			for(int i=0; i<ph->wHeight; ++i, pOut -= m_nPitch)
				pCurr = RLE_TGA_DecodeLine(pCurr,ph->byColorBits,ph->wWidth,pOut);
		}
		else
		{
			BYTE * pOut = GetLine(0);
			for(int i=0; i<ph->wHeight; ++i, pOut += m_nPitch)
				pCurr = RLE_TGA_DecodeLine(pCurr,ph->byColorBits,ph->wWidth,pOut);
		}
	}
	else//未压缩
	{
		if(UC_SWAP_HEIGHT(ph->desc & 0x20))	//上下颠倒
		{
			BYTE * pOut = GetLine(m_nHeight - 1);
			for(int i=0; i<ph->wHeight; ++i, pCurr += dwPicth, pOut -= m_nPitch)
				memcpy(pOut,pCurr,dwPicth);
		}
		else
		{
			BYTE * pOut = GetLine(0);
			for(int i=0; i<ph->wHeight; ++i, pCurr += dwPicth, pOut += m_nPitch)
				memcpy(pOut,pCurr,dwPicth);
		}
	}

	return TRUE;
}


//UINT VPIC_API vpic_WriteTGA(const VPicture & pic,BYTE * pStart,VP_LAYER_INFO * pLayerInfo,UINT uFlags)
BOOL LanImage::SaveTga(LPCTSTR pszFileName) const
{
	CFile file;
	if(FALSE == file.Open(pszFileName,CFile::modeCreate | CFile::modeWrite))
		return FALSE;

	TGAHEAD				th;
	
	TGAFooter			tf;
	tf.ext_area = tf.dev_area = 0;
	strcpy(tf.signature,"TRUEVISION-XFILE");

	memset(&th,0,sizeof(th));
	if(GetBitCount() <= 8)
	{
		th.byPalType = 1;
		th.wPalLength = 1 << GetBitCount();
		th.byPalBits = 32;
		th.byImageType = 1;
	}
	else
		th.byImageType = 2;
	
	th.desc = 0;
	th.wWidth = this->GetWidth();
	th.wHeight = this->GetHeight();
	th.byColorBits = this->GetBitCount();

	// 写文件头
	file.Write(&th,sizeof(th));
	// 写调色板
	if(th.byPalType)
	{
		file.Write(this->GetPalette(),sizeof(RGBQUAD) * (1 << this->GetBitCount()));
	}
	// 写图象数据
	int height = th.wHeight;
	int length = th.wWidth * th.byColorBits / 8;
	
	for(int y=0;y<height;++y)
		file.Write(GetLine(y),length);
	
	// 写信息尾
	file.Write(&tf,sizeof(tf));

	return TRUE;
}
