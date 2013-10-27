#include "stdafx.h"
#include "ClassImage.h"

BOOL LanImage::ReadBmp(LPBYTE pBuffer,UINT uLength,int ndegree,BOOL isconvert)
{
	const LPBYTE pBackup = pBuffer;
	
	const BITMAPFILEHEADER & bfh = *(const BITMAPFILEHEADER *)pBuffer;
	pBuffer += sizeof(BITMAPFILEHEADER);
	if(bfh.bfType != 'MB')
	{
		AfxMessageBox("bfh.bfType != \'MB\'");
		return 0;
	}

	const BITMAPINFOHEADER & bih = *(const BITMAPINFOHEADER *)pBuffer;
	pBuffer += sizeof(BITMAPINFOHEADER);
	if(bih.biSize != sizeof(bih))
	{
		AfxMessageBox("bih.biSize != sizeof(bih)");
		return 0;
	}
	if(bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)
	{
		AfxMessageBox("bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4");
		return 0;
	}

	if(!isconvert)
		Create(bih.biWidth,bih.biHeight,bih.biBitCount,ndegree);
	else
		Create_No(bih.biWidth,bih.biHeight,bih.biBitCount);

	if(bih.biClrUsed)
		m_nPalette = bih.biClrUsed;
	//有些BMP图片虽然没有调色板，但bih.biClrUsed却不是0，而是其实际使用的颜色数，
	//如test_pics中的GM_Tools1.bmp此值即为16777216.所以要判断m_nPalette是否超过256
	if(m_nPalette && (m_nPalette<=256))
		memcpy(m_pPal,pBuffer,sizeof(RGBQUAD)*m_nPalette);

	//BI_BITSFIELDS
	if(bih.biCompression == BI_BITFIELDS)
	{
		const UINT * uMask = (const UINT *)pBuffer;
		if((uMask[1] & 0x07E0) == 0x07E0) //565
			m_eFmt = LanF_R5G6B5;
		else if((uMask[1] & 0x00F0) == 0x00F0) //4444
			m_eFmt = LanF_A4R4G4B4;
	}

	pBuffer = pBackup + bfh.bfOffBits;
	if(UC_SWAP_HEIGHT(bih.biHeight > 0))
		memcpy(m_pImage,pBuffer,m_nImage);
	else
	{
		BYTE * pTemp = GetLine(m_nHeight - 1);
		for(int i=0; i<bih.biHeight; ++i)
		{
			memcpy(pTemp,pBuffer,m_nPitch);
			pTemp -= m_nPitch;
			pBuffer += m_nPitch;
		}
	}

	return TRUE;
}
BOOL LanImage::SaveBmp(LPCTSTR pszFileName) const
{
	if(IsLoad() == FALSE)
		return FALSE;

	BITMAPFILEHEADER	bfh;
	BITMAPINFOHEADER 	bih;
	UINT				dwMask[3];

	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfType = 'MB';
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih) + m_nPalette * sizeof(RGBQUAD);
	
	memset(&bih,0,sizeof(bih));
	bih.biSize = sizeof(bih);
	bih.biWidth = m_nWidth;
	bih.biHeight = m_nHeight;
	bih.biBitCount = m_nBitCount;
	bih.biPlanes = 1;
	bih.biSizeImage = m_nImage;
	if(bih.biBitCount == 16)
	{
		bih.biCompression = BI_BITFIELDS;
		  dwMask[0] = 0x7C00;
		  dwMask[1] = 0x03E0;
		  dwMask[2] = 0x001F;
		bfh.bfOffBits += sizeof(dwMask);
	}
	else
		bih.biCompression = BI_RGB;
	if(m_nBitCount <= 8)
		bih.biClrUsed = m_nPalette;

	bfh.bfSize = bfh.bfOffBits + m_nImage;

	FILE * fp = fopen(pszFileName,"wb");
	//写文件头
	fwrite(&bfh,1,sizeof(bfh),fp);
	//写信息头
	fwrite(&bih,1,sizeof(BITMAPINFOHEADER),fp);
	//写调色板
	if(m_nPalette)
		fwrite(m_pPal,1,sizeof(RGBQUAD) * m_nPalette,fp);
	//写掩码
	else if(m_nBitCount == 16)
		fwrite(dwMask,1,sizeof(dwMask),fp);
	//图象是颠倒的
	const BYTE * pImage = GetLine(0);
	for(int i=0; i<m_nHeight; ++i)
	{
		fwrite(pImage,1,m_nPitch,fp);
		pImage += m_nPitch;
	}

	fclose(fp);

	return TRUE;
}
