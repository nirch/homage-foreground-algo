/****************************************

 ***	ImageWrteEms.c				  ***

 *** 3GPP TS 23.040 V5.1.0 ( 2001-09) ***

 ****************************************/

#include	<stdlib.h>
#include	<malloc.h>
#include 	<memory.h>

#include	"Uigp/igp.h"
#include	"Ucst/CstType.h"

#include	"ImageType/ImageType.h"
#include	"ImageEms.h"

// bit per pixel
#define BPP_BW				1
#define BPP_GREY2B			2
#define BPP_COLOR6B			6


static void
image_write_ems_bw( cst_type *cst, image_type *im, int Align );

static void
image4_write_ems_bw( cst_type *cst, image_type *im, int Align );

static void
image1_write_ems_bw( cst_type *cst, image_type *im, int Align );


static void
image_write_ems_grey2b( cst_type *cst, image_type *im );

static void
image_write_ems_color6b( cst_type *cst, image_type *im );


//retCode : number of bytes written
//			-1: couldn't open output file
//			-2: error while writing out.
int image_write_ems( image_type *im, char *dir, char *name,
							int BitsPerPixel, int Align )
{
char		file[256];
FILE		*fp;
cst_type	*cst;
int bytes;

	sprintf( file, "%s/%s.ems", dir, name );

	if( (fp = fopen( file, "wb" )) == NULL )
		return( -1 );

	cst = image_write_ems_cst( im, BitsPerPixel, Align);
	if ( cst == NULL ) 
		return -2;// error while writing!

	fwrite( cst->data, sizeof( char ), CST_BYTES(cst), fp );

	cst_destroy( cst, 1 );

	bytes = ftell(fp);
	fclose( fp );

	return( bytes );//success
}


//returns : 
// number of bytes written
// -1 - error writing to cst
int image_write_ems_file( image_type *im, FILE *fp, int BitsPerPixel, int Align)
{
cst_type	*cst;
int bytes;

	cst = image_write_ems_cst( im, BitsPerPixel, Align );
	if ( cst == NULL ) 
		return -1;
	fwrite( cst->data, sizeof( char ), CST_BYTES(cst), fp );

	cst_destroy( cst, 1 );

	bytes = ftell(fp);
	return(bytes);
}


cst_type *
image_write_ems_cst( image_type *im, int BitsPerPixel, 
					int Align )
{
int			h,	w;
int			nbyte;
cst_type	*cst;

	h = IMAGE_ROW( im );
	w = IMAGE_COLUMN( im );

	if ( Align )
		nbyte = ((w + 7) / 8)*h + 1;
	else
		nbyte = (h*w +7) / 8 + 1;

	cst =  cst_alloc( nbyte );
	if ( cst == NULL )
		return NULL;

	CST_PUTC( cst, 1 ); //header

	switch ( BitsPerPixel )
	{
		case BPP_BW :
			image_write_ems_bw( cst, im, Align );
			break;
		case BPP_GREY2B :
			image_write_ems_grey2b( cst, im );
			break;
		case BPP_COLOR6B :
			image_write_ems_color6b( cst, im );
			break;
	}

	return cst;
}


static void
image_write_ems_bw( cst_type *cst, image_type *im, int Align )
{
	if( im->depth == 4 )
		image4_write_ems_bw( cst, im, Align );
	else	
		image1_write_ems_bw( cst, im, Align );
}

static void
image4_write_ems_bw( cst_type *cst, image_type *im, int Align )
{
u_int	*p;
u_char	data;
u_char	fl_bit;
int		i, j;


	p		= (u_int *)im->data;
	data	= 0;
	fl_bit	= 0x80;

	for (i = 0; i < IMAGE_ROW( im ); i++ ) 
	{
		if ( Align && fl_bit != 0x80 )
		{
			CST_PUTC( cst, data );
			data = 0;
			fl_bit = 0x80;
		}

		for (j = 0; j < IMAGE_COLUMN( im ); j++ ) 
		{
			if ( !fl_bit )
			{
				CST_PUTC( cst, data );
				data = 0;
				fl_bit = 0x80;
			}

			if ( *p++ ) 		
				data |= fl_bit;
			fl_bit >>= 1;
		}

	}

	if( fl_bit != 0x80 )
		CST_PUTC( cst, data );

}


static void
image1_write_ems_bw( cst_type *cst, image_type *im, int Align )
{
u_char	*p;
u_char	data;
u_char	fl_bit;
int		i, j;


	p		= (u_char *)im->data;
	data	= 0;
	fl_bit	= 0x80;

	for (i = 0; i < IMAGE_ROW( im ); i++ ) 
	{
		if ( Align && fl_bit != 0x80 )
		{
			CST_PUTC( cst, data );
			data = 0;
			fl_bit = 0x80;
		}

		for (j = 0; j < IMAGE_COLUMN( im ); j++ ) 
		{
			if ( !fl_bit )
			{
				CST_PUTC( cst, data );
				data = 0;
				fl_bit = 0x80;
			}

			if ( *p++ ) 		
				data |= fl_bit;
			fl_bit >>= 1;
		}

	}

	if( fl_bit != 0x80 )
		CST_PUTC( cst, data );

}


static void
image_write_ems_grey2b( cst_type *cst, image_type *im )
{
u_int	*p, pF;
u_char	data;
u_char	fl_bit;
int		i, j;


	p		= (u_int *)im->data;
	data	= 0;
	fl_bit	= 0x80;

	for (i = 0; i < IMAGE_ROW( im ) ; i++ )
	{
		for (j = 0; j < IMAGE_COLUMN( im ); j++) 
		{
			if ( !fl_bit )
			{
				CST_PUTC( cst, data );
				data = 0;
				fl_bit = 0x80;
			}

			pF = (*p) & 0xF0;
			if ( pF == 0xF0 || pF == 0xC0 ) 		
				data |= fl_bit;
			fl_bit >>= 1;
			if ( pF == 0xF0 || pF == 0x40 ) 		
				data |= fl_bit;
			fl_bit >>= 1;

			p++;
		}
	}

	if( fl_bit != 0x80 )
		CST_PUTC( cst, data );

}


static void
image_write_ems_color6b( cst_type *cst, image_type *im )
{
u_int	*p, pF;
u_char	data;
u_char	fl_bit;
int		i, j, A;
u_int	xF0, xC0, x40;


	p		= (u_int *)im->data;
	data	= 0;
	fl_bit	= 0x80;

	for (i = 0; i < IMAGE_ROW( im ) ; i++ )
	{
		for (j = 0; j < IMAGE_COLUMN( im ); j++) 
		{
			xF0 = 0xF00000;
			xC0 = 0xC00000;
			x40 = 0x400000;
			for ( A = 0; A < SP_NO; A++, 
						xF0 >>= 8, xC0 >>= 8, x40 >>= 8 )
			{
				if ( !fl_bit )
				{
					CST_PUTC( cst, data );
					data = 0;
					fl_bit = 0x80;
				}
				pF = (*p) & xF0;
				if ( pF == xF0 || pF == xC0 ) 		
					data |= fl_bit;
				fl_bit >>= 1;
				if ( pF == xF0 || pF == x40 ) 		
					data |= fl_bit;
				fl_bit >>= 1;
			}

			p++;
		}
	}

	if( fl_bit != 0x80 )
		CST_PUTC( cst, data );

}
 