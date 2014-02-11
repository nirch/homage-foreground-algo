#include <windows.h>

#include	"CDib.h"





void
CDib::data_image( image_type *im, BOOL Vflip )
{
	switch ( m_lpBMIH->biBitCount ){
	case 24:
			if( im->depth == 3 )
					CDib::data24_image3( im, Vflip );
			else	CDib::data24_image( im, Vflip );
		break;

	case 32:
			CDib::data32_image( im, Vflip );

		break;
	}
}



void
CDib::data24_image3( image_type *im, BOOL Vflip )
{
int	i,	j;
u_char	*p;
int col_byte,	picSize;
u_char *picArray, *pCurrPixel;
int	row,	col;

	row = IMAGE_ROW(im);
	col = IMAGE_COLUMN(im);


	col_byte = ((col*3 + 3)/4 )*4;


	p = im->data;


	picSize = row * col_byte;
	picArray = m_lpImage;


	// Initialize bitmap
	for(i = 0; i < row; i++){
		pCurrPixel = picArray + (row-1-i) * col_byte;

		for(j = 0; j < col; j++){
			*(pCurrPixel++) = *p++;
			*(pCurrPixel++) = *p++;
			*(pCurrPixel++) = *p++;
		}
	}

}



void
CDib::data24_image( image_type *im, BOOL Vflip )
{
int	i,	j;
u_int	*p,	*t;
int col_byte;
u_char *picArray, *pCurrPixel;
int	row,	col,	col4;
int	col4_byte;

	row = IMAGE_ROW(im);
	col = IMAGE_COLUMN(im);

	col_byte = ((col*3 + 3)/4 )*4;
	col4_byte = 	col_byte /4;


	col4 = ( col /4  ) *4;

	p = (u_int *)im->data;


	picArray = m_lpImage;


	// Initialize bitmap
	for(i = 0; i < row; i++)
	{
		if( Vflip == TRUE )
			t = ((u_int *)picArray) + (row - 1 - i) * col4_byte;
		else	
			t = ((u_int *)picArray) + i * col4_byte;


		

		for( j = 0 ; j < col4 ; j += 4 ){

			*t++ = ( (*p) ) | ( ( *(p+1) ) << 24 );
			p++;
			*t++ = ( (*p)>>8 ) | ( ( *(p+1) ) << 16 );
			p++;

			*t++ = ( (*p)>>16 ) | ( ( *(p+1)<<8 ));
			p++;
			p++;
		}

		pCurrPixel = (u_char *)t;


		for(; j < col; j++){
			*(pCurrPixel++) = (*p) & 0xff;
			*(pCurrPixel++) = ((*p) >> 8 ) & 0xff;
			*(pCurrPixel++) = (*p) >> 16;
			p++;
		}
	}

}



void
CDib::data32_image( image_type *im, BOOL Vflip )
{
int	i,	j;
u_int	*p,	*t;
u_char *picArray;
int	row,	col;

	if( im->depth == 1 ){
		CDib::data32_image1( im, Vflip );
		return;
	}

	row = IMAGE_ROW(im);
	col = IMAGE_COLUMN(im);


	p = (u_int *)im->data;


	picArray = m_lpImage;


	// Initialize bitmap
	for(i = 0; i < row; i++){

		if( Vflip == TRUE )
				t = (u_int *)(picArray + (row-1-i) * col*4);
		else	t = (u_int *)(picArray + i * col*4);

		for( j = 0 ; j < col ; j++ ){

			*t++ = *p++;
		}
	}
}


void
CDib::data32_image1( image_type *im, BOOL Vflip )
{
int	i,	j;
u_char	*p;
u_int	*t;
u_char *picArray;
int	row,	col,	tmp;

	row = IMAGE_ROW(im);
	col = IMAGE_COLUMN(im);


	p = (u_char *)im->data;


	picArray = m_lpImage;


	// Initialize bitmap
	for(i = 0; i < row; i++){

		if( Vflip == TRUE )
				t = (u_int *)(picArray + (row-1-i) * 4*col);
		else	t = (u_int *)(picArray + i * 4*col);

		for( j = 0 ; j < col ; j++ ){
			tmp = *p++;

			*t++ = IMAGE4_RGB(tmp, tmp, tmp );
		}
	}
}


void
CDib::data8_image( image_type *im, BOOL Vflip )
{
int	i,	j;
u_int	*p;
u_char	*t;
u_char *picArray;
int	row,	col;
int	R,	G,	B;


	row = IMAGE_ROW(im);
	col = IMAGE_COLUMN(im);


	p = (u_int *)im->data;


	picArray = m_lpImage;


	// Initialize bitmap
	for(i = 0; i < row; i++){

		if( Vflip == TRUE )
				t = (u_char *)(picArray + (row-1-i) * col);
		else	t = (u_char *)(picArray + i * col);

		for( j = 0 ; j < col ; j++ ){
			R = IMAGE4_RED( *p);
			G = IMAGE4_GREEN( *p);
			B = IMAGE4_BLUE( *p);

			p++;

			*t++ = (u_char)(0.29900 * R + 0.58700 * G + 0.11400 * B + 0.5);
		}
	}
}
