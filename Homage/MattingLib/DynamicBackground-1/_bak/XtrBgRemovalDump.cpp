/****************************
 ***   XtrBgRemoval.cpp   ***
 ****************************/
#include	<stdlib.h>
#include	<string.h>


#include	"Uigp/igp.h"
#include	"ImageType/ImageType.h"

#include <math.h>

#include	"XtrBgRemoval.h"



static image_type *image1_var( image_type *vim );



void CXtrBgRemoval::Dump( char *outFile )
{
char	dir[256],	name[256],	extension[256];
char	file[256];
image_type *im;

	gp_filename_split( outFile, dir, name, extension );



	sprintf( file, "%s/%s-bg.bmp", dir, name );

	im = image6_to_image3( m_mim );

	image_write_bmp( im, file );

	image_destroy( im, 1 );




	if( m_xim != NULL ){
		sprintf( file, "%s/%s-bg-x.bmp", dir, name );

		im = image6_to_image3( m_xim );

		image_write_bmp( im, file );

		image_destroy( im, 1 );
	}



	if( m_yim != NULL ){
		sprintf( file, "%s/%s-bg-y.bmp", dir, name );

		im = image6_to_image3( m_yim );

		image_write_bmp( im, file );

		image_destroy( im, 1 );
	}


	if( m_var != NULL ){
		im = image1_var( m_var );
		sprintf( file, "%s/%s-bg-v.bmp", dir, name );
		image_write_bmp( im, file );

		image_destroy( im, 1 );
	}
}



static image_type *
image1_var( image_type *vim )
{
image_type *im;
int	i,	j;
short	*sp;
u_char	*tp;
int	max,	tmp;

	im = image_create( vim->row, vim->column, 1, 1, NULL );


	sp = (short *)vim->data;
	tp = (u_char *)im->data;

	max = 0;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++ ){
			tmp = (*sp++)>>4;
			sp++;

			if( tmp > max ) max = tmp;

			*tp++ = tmp+128;
		}
	}

	return( im );
}

