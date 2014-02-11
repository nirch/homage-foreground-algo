/************************
 *	ImageWriteWbmap.c	*
 ************************/

#include	<stdlib.h>
#include	<malloc.h>
#include 	<memory.h>

#include	"Uigp/igp.h"
#include	"Ucst/CstType.h"

#include	"ImageType/ImageType.h"
#include	"ImageWbmp.h"



static void		image_write_wbmap_int( cst_type *cst, int val );
static void		image1_write_wbmp_data( cst_type *cst, image_type *im );
static void		image4_write_wbmp_data( cst_type *cst, image_type *im );

#define	WBMAP_HEADER_SIZE	10

//returns :
//number of bytes written 
// -1: could not open output file
// -2: internal error
int image_write_wbmp( image_type *im, char *dir, char *name )
{
char	file[256];
FILE	*fp;
cst_type	*cst;
int bytes;

	sprintf( file, "%s/%s.wbmp", dir, name );

	if( (fp = fopen( file, "wb" )) == NULL )
		return( -1 );


	cst = image_write_wbmp_cst( im );
	if ( cst == NULL ) 
		return -2;
	fwrite( cst->data, sizeof( char ), CST_BYTES(cst), fp );

	cst_destroy( cst, 1 );

	bytes = ftell(fp);
	fclose( fp );

	return( bytes );
}


cst_type *
image_write_wbmp_cst( image_type *im )
{//im - image B/W
cst_type	*cst;
int	byte_perlin,	bytes;


	byte_perlin = (IMAGE_COLUMN(im) + 7) >> 3;
	bytes = WBMAP_HEADER_SIZE + byte_perlin * IMAGE_ROW(im);

	cst =  cst_alloc( bytes );
	if ( cst == NULL ) 
		return NULL;

	// WBMAP header

	CST_PUTC( cst, 0x00 );	// B/W, no compression

	CST_PUTC( cst, 0x00 );	// no Ext Header Field

	image_write_wbmap_int( cst, im->column );

	image_write_wbmap_int( cst, im->row );


	if( im->depth == 4 )
		image4_write_wbmp_data( cst, im );
	else	
		image1_write_wbmp_data( cst, im );

	return cst;
}


static void
image_write_wbmap_int( cst_type *cst, int val )
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



static void 
image1_write_wbmp_data( cst_type *cst, image_type *im )
{
int     i, j;
u_char	*p;
u_char  fl_bit,	data;



	p = im->data;
	for (i = 0; i < IMAGE_ROW( im ) ; i++ ){
		fl_bit = 0x80;
		data = 0;

		
		for (j = 0; j < IMAGE_COLUMN( im ); j++) 
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

		if( fl_bit != 0x80 )
			CST_PUTC( cst, data );
	}
}



static void 
image4_write_wbmp_data( cst_type *cst, image_type *im )
{
int     i, j;
u_int	*p;
u_char  fl_bit,	data;



	p = (u_int *)im->data;
	for (i = 0; i < IMAGE_ROW( im ) ; i++ ){
		fl_bit = 0x80;
		data = 0;

		
		for (j = 0; j < IMAGE_COLUMN( im ); j++) 
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

		if( fl_bit != 0x80 )
			CST_PUTC( cst, data );
	}
}
