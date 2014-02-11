/************************
 *	ImageWriteNpm.c	*
 ************************/

#include	<stdlib.h>
#include	<malloc.h>
#include 	<memory.h>

#include	"Uigp/igp.h"
#include	"Ucst/CstType.h"
#include	"ImageType/ImageType.h"

#include	"ImageNpm.h"




static void		image1_write_npm_data( cst_type *cst, image_type *im );
static void		image4_write_npm_data( cst_type *cst, image_type *im );



//returns :
//number of bytes written 
// -1: io error
// -2: internal error
int image_write_npm( image_type *im, char *dir, char *name )
{
char	file[256];
FILE	*fp;
cst_type	*cst;
int bytes;

	sprintf( file, "%s/%s.wbmp", dir, name );

	if( (fp = fopen( file, "wb" )) == NULL )
		return( -1 );


	cst = image_write_npm_cst( im );
	if ( cst == NULL ) 
		return -2;

	fwrite( cst->data, sizeof( char ), CST_BYTES(cst), fp );

	cst_destroy( cst, 1 );

	bytes = ftell(fp);
	fclose( fp );

	return( bytes );
}


cst_type *
image_write_npm_cst( image_type *im )
{
cst_type	*cst;

int	byte_perlin,	bytes;
int ROW = 28, COLUMN = 72;


	byte_perlin = (COLUMN + 7) >> 3;
	bytes = byte_perlin * ROW;

	cst =  cst_alloc( bytes );
	if ( cst == NULL ) 
		return NULL;


	if( im->depth == 4 )
		image4_write_npm_data( cst, im );
	else	
		image1_write_npm_data( cst, im );

	return cst;
}

/*
static void
image_write_npm_int( cst_type *cst, int val )
{
u_char ch[5];
int	n,	i;
	

	n = 0;
	do 
	{
		ch[n] = (u_char)(val & 0x7F);
		val >>= 7;
		if ( n )
			ch[n] |= 0x80;
		n++;
	} while ( val );

	for( i = n-1 ; i >= 0 ; i-- )
		CST_PUTC( cst, ch[i] );
}
*/


static void 
image1_write_npm_data( cst_type *cst, image_type *im )
{

/*	 __________________
	|					|  
	|	===========     | R
	|	===========     | O
	|	===========     | W
	|___________________|
	   COLUMN
*/
int     i, j;
u_char	*p;
u_char  fl_bit,	data;

int left, right, top, bottom;
int ROW = 28, COLUMN = 72; //  72/8 = 9 bytePerS

	left = ( COLUMN - IMAGE_COLUMN( im ) ) >> 1;
	right = left + IMAGE_COLUMN( im ) - 1;
	top = ( ROW - IMAGE_ROW( im ) ) >> 1;
	bottom = top + IMAGE_ROW( im ) - 1;
	
	data = 0;
	for (i = 0; i < top; i++ )
		for (j = 0; j < 9; j++)
			CST_PUTC( cst, data );

	p = im->data;

	for (i = 0; i < IMAGE_ROW( im ) ; i++ ){
		fl_bit = 0x80;
		data = 0;

		
		for (j = 0; j < COLUMN; j++) 
		{
			if ( !fl_bit )
			{
				CST_PUTC( cst, data );
				data = 0;
				fl_bit = 0x80;
			}

			if ( j >= left && j <= right )
			{
				if ( *p++ == 0 ) 		
					data |= fl_bit;
			}
			fl_bit >>= 1;
		}

		if( fl_bit != 0x80 )
			CST_PUTC( cst, data );
	}

	data = 0;
	for (i = bottom+1; i < ROW; i++ )
		for (j = 0; j < 9; j++)
			CST_PUTC( cst, data );
}



static void 
image4_write_npm_data( cst_type *cst, image_type *im )
{
int     i, j;
u_int	*p;
u_char  fl_bit,	data;

int left, right, top, bottom;
int ROW = 28, COLUMN = 72; //  72/8 = 9 bytePerS

	left = ( COLUMN - IMAGE_COLUMN( im ) ) >> 1;
	right = left + IMAGE_COLUMN( im ) - 1;
	top = ( ROW - IMAGE_ROW( im ) ) >> 1;
	bottom = top + IMAGE_ROW( im ) - 1;
	
	data = 0;
	for (i = 0; i < top; i++ )
		for (j = 0; j < 9; j++)
			CST_PUTC( cst, data );

	p = (u_int *)im->data;

	for (i = 0; i < IMAGE_ROW( im ) ; i++ ){
		fl_bit = 0x80;
		data = 0;

		
		for (j = 0; j < COLUMN; j++) 
		{
			if ( !fl_bit )
			{
				CST_PUTC( cst, data );
				data = 0;
				fl_bit = 0x80;
			}

			if ( j >= left && j <= right )
			{
				if ( *p++ == 0 ) 		
					data |= fl_bit;
			}
			fl_bit >>= 1;
		}

		if( fl_bit != 0x80 )
			CST_PUTC( cst, data );
	}

	data = 0;
	for (i = bottom+1; i < ROW; i++ )
		for (j = 0; j < 9; j++)
			CST_PUTC( cst, data );
}


