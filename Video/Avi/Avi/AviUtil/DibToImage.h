//	DibToImage.h:
//	Prototypes and macros for functions in DibToImage.cpp
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DIB_TO_IMAGE_
#define _DIB_TO_IMAGE_


#include "ImageType/ImageType.h"


// masks constant defined for 16-bits bitmap formats
#define BLUEMASK	0x001F	// 5 LSB bits
#define GREENMASK	(BLUEMASK << 5)
#define REDMASK	(BLUEMASK << 10)

// Function prototypes
image_type *	DibToImage(void* pDib );

void	Dib_32ToImage(void *pDib, image_type* image);

void	Dib_32simpleToImage(unsigned char* _pDibPixels, int row, int col, image_type* image);

void	Dib_24ToImage(unsigned char* pDibPixels, LONG row, LONG col, image_type* image);

void	Dib_16ToImage(void* pDib, image_type* image);

void	Dib_8_4_1ToImage(LPBITMAPINFOHEADER	pBmpInfo, image_type* image, int flip);


#endif // #ifndef _DIB_TO_IMAGE_