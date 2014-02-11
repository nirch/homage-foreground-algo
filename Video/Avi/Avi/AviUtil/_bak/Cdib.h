// cdib.h declaration for Inside Visual C++ CDib class

#ifndef _CDIB_
#define _CDIB_
#include <windows.h>

extern "C" {
#include	"ImageType/ImageType.h"
}


class CDib
{


public:
	LPVOID m_lpvColorTable;
	HBITMAP m_hBitmap;
	LPBYTE m_lpImage;  // starting address of DIB bits
	LPBITMAPINFOHEADER m_lpBMIH; //  buffer containing the BITMAPINFOHEADER
protected:
	DWORD m_dwSizeImage; // of bits -- not BITMAPINFOHEADER or BITMAPFILEHEADER
	int m_nColorTableEntries;
public:
	CDib();

	CDib( int row, int column, int nBitCount);

	~CDib();

	int GetSizeImage() {return m_dwSizeImage;}

	int GetSizeHeader()
		{return sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableEntries;}

	void GetDimensions( int *row, int *column );


	BOOL Draw( HDC hdc, int r0, int c0, int row, int column );

	BOOL DrawSub(HDC hdc, int r0, int c0, int row, int column,
							int sr0, int sc0, int srow, int scolumn );

	HBITMAP CreateSection(HDC hdc = NULL);

#ifndef CE
	HBITMAP CreateBitmap(HDC hdc);
#endif

	BOOL	ReSize( int row, int column, int nBitCount, BOOL Fdata);

	void	data_image( image_type *im, BOOL Vflip );

	void	data24_image( image_type *im, BOOL Vflip );
	void	data24_image3( image_type *im, BOOL Vflip );

	void	data32_image( image_type *im, BOOL Vflip );
	void	data32_image1( image_type *im, BOOL Vflip );
	void	data8_image( image_type *im, BOOL Vflip );


	HBITMAP	Bitmap16();
	HBITMAP Bitmap16tmp();
	HBITMAP	Bitmap8();

	void Empty();
protected:

	void ComputePaletteSize(int nBitCount);
	void ComputeMetrics();
};
#endif // _CDIB_
