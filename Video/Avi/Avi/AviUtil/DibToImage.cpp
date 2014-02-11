//	DibToImage.cpp
//	In this file are the functions that deal with conversion from bitmap formats to image_type.
//////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>

#include <math.h>
#include "DibToImage.h"

#include "ImageType/ImageType.h"


#define IMAGE16_5_5_5_BLUE( Word )  ( ( (Word) & 0x1F ) << 3 )
#define IMAGE16_5_5_5_GREEN( Word )  ( ( (Word) & 0x3E0 ) >> 2 )
#define IMAGE16_5_5_5_RED( Word )  ( ( (Word) & 0x7C00 ) >> 7 )
/***
*DibToImage(void* pDib) 
*
*Purpose:
*			Fill the fields to hold data corresponding to that in the DIB pointed to 
*			by pDib.
*
*Parameters:
*			pDib - pointer to DIB: BITMAPINFO struct followed by pixels data.
*******************************************************************************/
image_type *
DibToImage(void* pDib )
{
LPBITMAPINFOHEADER	pBmpInfo;
unsigned char*		pDibPixels;	// pointer to  dib's pixels data
LONG row, col;
image_type	*image;
int	flip = 1;


	pBmpInfo =(LPBITMAPINFOHEADER)pDib;	// at the begining of the DIB block there's a BITMAPINFOHEADER struct
	row = pBmpInfo->biHeight;
	if( row < 0 ){
		row = -row;
		flip = 0;
	}
	col = pBmpInfo->biWidth;	
	pDibPixels =(unsigned char*)(pBmpInfo + 1);	// set pDibPixels to point to beyond the BITMAPINFOHEADER struct
	
	image = image_create(row, col, 4, 4, NULL);

	switch ( pBmpInfo->biBitCount )
	{
	case 32:
		{
			Dib_32ToImage(pDib, image);
			break;
		}
	case 24:
		{
			Dib_24ToImage(pDibPixels, row, col, image);
			break;
		}
	case 16:
		{
			Dib_16ToImage(pDib, image);
			break;
		}
	case 12:
			{
				break; // TODO
			}
	default:	// 8,4,1-bits format - same principle(color table)
		{
			Dib_8_4_1ToImage(pBmpInfo, image, flip);
			break;
		}
	}


	return( image );
}


/***
*Dib_32ToImage(...) 
*
*Purpose:
*		Read from DIB when the format is 32-bits.
*
*Parameters:
*		Input:	pDib - pointer to DIB: BITMAPINFO struct followed by pixels data.
*		Output:	image - pointer to image_type to hold the tranformed data
*******************************************************************************/
void Dib_32ToImage(void *pDib, image_type* image)
{
	LPBITMAPINFOHEADER  pBmpInfo = (LPBITMAPINFOHEADER)pDib;
	unsigned char*		pDibPixels;
	if (pBmpInfo->biCompression == BI_RGB)
	{
		pDibPixels =(unsigned char*)(pBmpInfo + 1); 
		Dib_32simpleToImage(pDibPixels, pBmpInfo->biHeight, pBmpInfo->biWidth, image);
	}
}


/***
*CImageType::Dib_32simpleToImage(...) 
*
*Purpose:
*		Read from DIB when the format is 32-bits and compression is BI_RGB.
*		This is just like 24-bits format with one extra unused byte.
*
*Parameters:
*		_pDibPixels - pointer to pixels data.
*		row - number of pixels rows in the image.
*		col - number of pixels columnss in the image.
*		image - pointer to image_type to hold the tranformed data
*******************************************************************************/
void Dib_32simpleToImage(unsigned char* _pDibPixels, int row, int col, image_type* image)
{
u_int	*tp,	*sp;
int	i,	j;


	sp = (u_int*)_pDibPixels;
	for( i =0 ; i < row ; i++ ){
		tp = IMAGE4_PIXEL( image, row - i-1, 0 );
		for( j = 0 ; j < col ; j++ )
			*tp++ = (*sp++)&0xffffff;
	}
}


/***
*Dib_24ToImage(...) 
*
*Purpose:
*		Read from DIB when the format is 24-bits
*
*Parameters:
*		pDibPixels - pointer to pixels data.
*		row - number of pixels rows in the image.
*		col - number of pixels columnss in the image.
*		image - pointer to image_type to hold the tranformed data
*******************************************************************************/
void	Dib_24ToImage(unsigned char* pDibPixels, LONG row, LONG col, image_type* image)
{
//	DWORD*	pImageData;	// pointer to image data 
	int	R, G, B;			// Red, Green, Blue
	int	pad, dib_dib_row_length;
	int	i,	j;
	u_int	*tp;

	// calculate the number of fill bytes at the end of each pixels row
	dib_dib_row_length = (col*3 + 3)/4 * 4;
	pad = dib_dib_row_length - col*3;		// DIB's pad

	for( i = 0; i < row ; i++ )
	{																  
		tp = IMAGE4_PIXEL( image, row - i-1, 0 );
		
		for( j = 0 ; j < col ; j++ ){

			B = pDibPixels[0]; 
			G = pDibPixels[1];
			R = pDibPixels[2];
			

			*tp++ = RGB( B, G, R );
			
			pDibPixels += 3;
		}
		pDibPixels += pad;
	}
}


/***
*Dib_16ToImage(...) 
*
*Purpose:
*		Read from DIB when the format is 16-bits.
*
*Parameters:
*		pDib - pointer to DIB: BITMAPINFO struct followed by pixels data. 
*		image - pointer to image_type to hold the tranformed data
*******************************************************************************/
void	Dib_16ToImage(void* pDib, image_type* image)
{
	LPBITMAPINFOHEADER  pBmpInfo = (LPBITMAPINFOHEADER)pDib;
//	DWORD*	pImageData;
	WORD*		pDibPixels;
	DWORD		*masks, red_mask, green_mask, blue_mask;
	int	R, G, B,		pad, dib_row_length;
	int row, col;
	int	i,	j;
	u_int	*tp;
	
	if (pBmpInfo->biCompression == BI_RGB)
	{
		pDibPixels =(WORD*)(pBmpInfo + 1); 
		red_mask		= REDMASK;
		green_mask	= GREENMASK;
		blue_mask	= BLUEMASK;
	}
	else if (pBmpInfo->biCompression == BI_BITFIELDS)
	{
		masks =(DWORD*)( pBmpInfo + 1 );
		red_mask		= masks[0];
		green_mask	= masks[1];
		blue_mask	= masks[2];

		pDibPixels =(WORD*)(masks + 3); 
	}



	row = pBmpInfo->biHeight;
	col = pBmpInfo->biWidth;


	dib_row_length = (col*2 + 3)/4 * 4;
	pad = dib_row_length - col*2;		// DIB's pad

	for( i = 0; i < row ; i++ ){																  

		tp = IMAGE4_PIXEL( image, row - i-1, 0 );
		
		for( j = 0 ; j < col ; j++ ){ 
			// Each color's 5 bits need to be rounded to 8 bits by adding zeros on their right( LSB bits ).

			B= IMAGE16_5_5_5_BLUE(*pDibPixels);   
			G = IMAGE16_5_5_5_GREEN(*pDibPixels);
			R = IMAGE16_5_5_5_RED(*pDibPixels);


			*tp++ = RGB( B, G, R );

			pDibPixels++;
		}

		pDibPixels += pad;
	}
}	

/***
*Dib_8_4_1ToImage( LPBITMAPINFOHEADER pBmpInfo ) 
*
*Purpose:
*		Read from DIB when the format is 8, 4 or 1-bit. We use one function for all
*		3 formats because of their similarity, and reduce duplicated code.
*
*Parameters:
*		pBmpInfo - pointer to BITMAPINFOHEADER struct followed by pixels data
*		image - pointer to image_type to hold the tranformed data.
*******************************************************************************/
void	Dib_8_4_1ToImage(LPBITMAPINFOHEADER	pBmpInfo, image_type* image, int flip)
{
	unsigned char*		pDibPixels;
///	DWORD		*pImageData; 
	RGBQUAD	tmpRGB, *pColorTable;
	LONG		row, col;
	int		BitCount, ColortableSize, pad, dib_row_length;
	int index, mask, shift;
	int	i,	j,	k;
	u_int	*tp;


	row = pBmpInfo->biHeight;
	if( row < 0 )	row = -row;
	col = pBmpInfo->biWidth;
	BitCount = pBmpInfo->biBitCount;
	
	// calculate the number of fill bytes at the end of each pixels row
	dib_row_length = (BitCount/8 * col + 3)/4 * 4;
	pad = dib_row_length - BitCount/8 * col;		// DIB's pad

//	ColortableSize = (1 << BitCount) * sizeof(RGBQUAD);
	ColortableSize = pBmpInfo->biClrUsed * sizeof(RGBQUAD);
	pColorTable = (RGBQUAD*)(pBmpInfo + 1);
	pDibPixels = (unsigned char*)pColorTable + ColortableSize;

	shift = BitCount * (8/BitCount - 1);
//	mask =(int) pow(2, BitCount) - 1;
	mask = (1<<BitCount) - 1;


	for( i = 0; i < row ; ++i )
	{																  
	
		if( flip )
			tp = IMAGE4_PIXEL( image, row - i-1, 0 );
		else
			tp = IMAGE4_PIXEL( image, i, 0 );

		for( j = 0 ; j < col ; ){

			for(  k = 0; k < 8/BitCount; ++k, mask >> shift){
				index = *pDibPixels & mask;
				index >>= BitCount * ((8/BitCount - 1) - k);
				tmpRGB = pColorTable[index];
				
				// we need to reverse the order of R, G, B
				*tp++ = RGB( tmpRGB.rgbBlue , tmpRGB.rgbGreen, tmpRGB.rgbRed );
				j++;
			}
			
			pDibPixels ++;
		}
		pDibPixels += pad;
	}
}

