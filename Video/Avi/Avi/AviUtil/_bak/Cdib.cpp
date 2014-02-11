// cdib.cpp

#include <windows.h>

#include "cdib.h"




CDib::CDib()
{

	m_hBitmap = NULL;

	m_lpBMIH = NULL;

	m_lpImage = NULL;
}

CDib::CDib( int row, int column, int nBitCount)
{
int		col_byte = ((column*nBitCount + 31)/32 )*4;


	m_hBitmap = NULL;



	m_nColorTableEntries = 0;  /* nBitCount == 24 / 32 only*/
	m_lpBMIH = (LPBITMAPINFOHEADER) new 
		char[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries];

	m_lpBMIH->biSize = sizeof(BITMAPINFOHEADER);
	m_lpBMIH->biWidth = column;
	m_lpBMIH->biHeight = row;
	m_lpBMIH->biPlanes = 1;
	m_lpBMIH->biBitCount = nBitCount;
	m_lpBMIH->biCompression = BI_RGB;
	m_lpBMIH->biSizeImage = col_byte * row;
	m_lpBMIH->biXPelsPerMeter = 0;
	m_lpBMIH->biYPelsPerMeter = 0;
	m_lpBMIH->biClrUsed = m_nColorTableEntries;
	m_lpBMIH->biClrImportant = m_nColorTableEntries;



	m_lpImage = NULL;  // no data yet
}

CDib::~CDib()
{
	Empty();
}

void CDib::GetDimensions( int *row, int *column )
{
	if(m_lpBMIH != NULL){
		*row = (int) m_lpBMIH->biHeight;
		*column = (int) m_lpBMIH->biWidth;
	}
	else	*row = *column = 0;
}







BOOL CDib::Draw(HDC hdc, int r0, int c0, int row, int column )
{
	if (m_lpBMIH == NULL)
		return FALSE;
	if ( row <= 0 )
		row = (int) m_lpBMIH->biHeight;
	if ( column <= 0 )
		column = (int) m_lpBMIH->biWidth;

#ifndef CE
	::SetStretchBltMode( hdc, COLORONCOLOR);
	::StretchDIBits( hdc, c0, r0, column, row,
		0, 0, m_lpBMIH->biWidth, m_lpBMIH->biHeight,
		m_lpImage, (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS, SRCCOPY);
#endif

#ifdef _WIN32_WCE_EMULATION		
	HDC hdcSrc = ::CreateCompatibleDC( hdc );
	HBITMAP hBitmap = m_hBitmap ? m_hBitmap : CreateSection( hdcSrc );
	if ( hBitmap ) 
	{
#ifdef COLOR_GRAY
		unsigned char * grayBytes = new unsigned char[column * row];
		memcpy(grayBytes, m_lpImage, column * row);
		unsigned int * p = (unsigned int *)m_lpImage;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				p[i * column + j] = (unsigned int)grayBytes[i * column + j] * 0x10101;
			}
		}
		delete [] grayBytes;
#endif		
		HGDIOBJ hOld = ::SelectObject( hdcSrc, hBitmap );
		::BitBlt( hdc, c0, r0, column, row, hdcSrc, 0, 0, SRCCOPY );
		::SelectObject( hdcSrc, hOld);
	}
	DeleteDC(hdcSrc);


#elif defined EXPANDI16_CE	

	HDC hdcSrc = ::CreateCompatibleDC( hdc );
	HBITMAP hBitmap = ::CreateBitmap( column, row, 1, 16, m_lpImage );;	
	if ( hBitmap ) 
	{
		HGDIOBJ hOld = ::SelectObject( hdcSrc, hBitmap );
		::BitBlt( hdc, c0, r0, column, row, hdcSrc, 0, 0, SRCCOPY );
		::SelectObject( hdcSrc, hOld);
		::DeleteObject(hBitmap);
	}
	DeleteDC(hdcSrc);
#elif defined (CASIO) || defined (IPAQ)		
	HDC hdcSrc = ::CreateCompatibleDC( hdc );
	HBITMAP hBitmap = Bitmap16();
	if ( hBitmap ) 
	{
		HGDIOBJ hOld = ::SelectObject( hdcSrc, hBitmap );
		::BitBlt( hdc, c0, r0, column, row, hdcSrc, 0, 0, SRCCOPY );
		::SelectObject( hdcSrc, hOld);
		::DeleteObject(hBitmap);
	}
	DeleteDC(hdcSrc);
#elif defined(TRIUM)
	HDC hdcSrc = ::CreateCompatibleDC( hdc );
	HBITMAP hBitmap = Bitmap8();
	if ( hBitmap ) 
	{
		HGDIOBJ hOld = ::SelectObject( hdcSrc, hBitmap );
		::BitBlt( hdc, c0, r0, column, row, hdcSrc, 0, 0, SRCCOPY );
		::SelectObject( hdcSrc, hOld);
		::DeleteObject(hBitmap);
	}
	::DeleteDC(hdcSrc);
#endif
	return TRUE;
}



BOOL CDib::DrawSub(HDC hdc, int r0, int c0, int row, int column,
				   int sr0, int sc0, int srow, int scolumn )
{
	if(m_lpBMIH == NULL) return FALSE;
#ifndef CE
	::SetStretchBltMode( hdc, COLORONCOLOR);
	::StretchDIBits( hdc, c0, r0, column, row,
		sc0, m_lpBMIH->biHeight-srow-sr0, scolumn, srow,
		m_lpImage, (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS, SRCCOPY);
#endif
	return TRUE;
}




HBITMAP CDib::CreateSection(HDC hdc /* = NULL */)
{
	if(m_lpBMIH == NULL) 
		return NULL;

	if(m_lpImage != NULL) 
		return NULL; // can only do this if image doesn't exist
	if ( hdc == NULL)
		hdc = GetDC(NULL);

#ifdef _WIN32_WCE_EMULATION
	m_hBitmap = ::CreateDIBSection( hdc, (LPBITMAPINFO) m_lpBMIH,
			DIB_RGB_COLORS,	(LPVOID*) &m_lpImage, NULL, 0);
#elif defined (IPAQ) || defined (CASIO)
	m_lpImage = (unsigned char *)malloc( m_lpBMIH->biWidth * m_lpBMIH->biHeight * 4);
#elif defined (TRIUM)
	m_lpImage = (unsigned char *)malloc( m_lpBMIH->biWidth * m_lpBMIH->biHeight);
#else
	m_hBitmap = ::CreateDIBSection( hdc, (LPBITMAPINFO) m_lpBMIH,
			DIB_RGB_COLORS,	(LPVOID*) &m_lpImage, NULL, 0);
#endif

	return m_hBitmap;
}




#ifndef CE
HBITMAP CDib::CreateBitmap(HDC hdc)
{
    if (m_lpImage == NULL) return NULL;
    HBITMAP hBitmap = ::CreateDIBitmap( hdc, m_lpBMIH,
            CBM_INIT, m_lpImage, (LPBITMAPINFO) m_lpBMIH, DIB_RGB_COLORS);

    return hBitmap;
}
#endif



void CDib::Empty()
{
	if( m_lpBMIH != NULL )	delete [] m_lpBMIH;


	if(m_hBitmap != NULL) ::DeleteObject(m_hBitmap);

	m_lpBMIH = NULL;
	m_lpImage = NULL;


	m_hBitmap = NULL;

}


BOOL
CDib::ReSize( int row, int column, int nBitCount, BOOL Fdata)
{

	if( column == m_lpBMIH->biWidth && m_lpBMIH->biHeight == row && m_lpBMIH->biBitCount == nBitCount ){
		if( Fdata == TRUE && m_hBitmap == NULL)
			CreateSection();
		return( FALSE );
	}


	if(m_hBitmap != NULL){
		::DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}


	m_lpBMIH->biSize = sizeof(BITMAPINFOHEADER);
	m_lpBMIH->biWidth = column;
	m_lpBMIH->biHeight = row;
	m_lpBMIH->biPlanes = 1;
	m_lpBMIH->biBitCount = nBitCount;
	m_lpBMIH->biCompression = BI_RGB;

	int		col_byte = ((column*nBitCount + 31)/32 )*4;
	m_lpBMIH->biSizeImage = col_byte * row;

	m_lpBMIH->biXPelsPerMeter = 0;
	m_lpBMIH->biYPelsPerMeter = 0;
	m_lpBMIH->biClrUsed = m_nColorTableEntries;
	m_lpBMIH->biClrImportant = m_nColorTableEntries;

	m_lpImage = NULL;  // no data yet


	if( Fdata == TRUE )
		CreateSection();

	return( TRUE );
}




HBITMAP CDib::Bitmap16()
{
int row = m_lpBMIH->biHeight; 
int col = m_lpBMIH->biWidth;

int col_byte = col * 2;
int picSize = row * col_byte;

	u_int	*p = (u_int *)m_lpImage;
	u_short *picArray = (u_short *)malloc( picSize );
	u_short *pCurrPixel;

	// Initialize bitmap
	for(int i = 0; i < row; i++)
	{
		pCurrPixel = picArray + (row - 1 - i) * col_byte / 2;
		for (int j = 0; j < col; j++)
		{
			*pCurrPixel++ = ((*p >> 3) & 0x1f) | ((*p >> 5) & 0x7e0) | 
				((*p >> 8) & 0xf800);
			p++;
		}
	}

	HBITMAP hBitmap = ::CreateBitmap( col, row, 1, 16, picArray );
	free(picArray);
	return( hBitmap ); 
}


HBITMAP CDib::Bitmap16tmp()
{
int row = m_lpBMIH->biHeight; 
int col = m_lpBMIH->biWidth;

int col_byte = col * 2;
int picSize = row * col_byte;

	u_int	*p = (u_int *)m_lpImage;


	u_short *picArray = (u_short *)malloc( picSize );
	memset(picArray, 0, picSize); 

	u_short *pCurrPixel;


	int	color = 0x0000ff;
	for(int i = 50; i < row-25; i++)
	{
		pCurrPixel = picArray + (row - 1 - i) * col_byte / 2;
		for (int j = 0; j < col; j++)
		{
//			*pCurrPixel++ = ((*p >> 3) & 0x1f) | ((*p >> 5) & 0x7e0) | 
//				((*p >> 8) & 0xf800);
			*pCurrPixel++ = ((color >> 3) & 0x1f) | ((color >> 5) & 0x7e0) | 
				((color >> 8) & 0xf800);
			p++;
		}
	}


	HBITMAP hBitmap = ::CreateBitmap( col, row, 1, 16, picArray );
///	if( hBitmap == NULL )	wno("Bitmap16 - hBitmap", 0);

	free(picArray);

	return( hBitmap ); 
}

HBITMAP CDib::Bitmap8()
{
int row = m_lpBMIH->biHeight; 
int col = m_lpBMIH->biWidth;
int col_byte = col * 2;
int picSize = row * col_byte;

	u_char	*p = m_lpImage;
	u_short *picArray = (u_short *)malloc( picSize );
	u_short *pCurrPixel;
	for (int i = 0; i < row; i++)
	{
		pCurrPixel = picArray + (row - 1 - i) * col_byte / 2;
		for (int j = 0; j < col; j++)
		{
			int Y = *p >> 3;
			*pCurrPixel++ = Y * 0x421;
			p++;
		}
	}

	HBITMAP hBitmap = ::CreateBitmap( col, row, 1, 16, picArray );
	free(picArray);
	return( hBitmap ); 
}

