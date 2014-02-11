//  Defines the entry point for the console application.
//
#include	<string.h>
#include	<math.h>
#include <stdlib.h>

#include	"ImageType/ImageType.h"
#include	"ImageDump/ImageDump.h"

#include	"Imagelabel/BwLabel.h"

#include "ImageMorphology/ImageMorphology.h"


#include	"DynamicBackground.h"


typedef struct bn_type {
	u_char	dval;
	u_char	flag;

	short	no;
} bn_type;




static image_type *	dbBox_image(  image_type *sim, image_type *gvar, image_type *im );

static image_type *	dbBox_sobol(  image_type *sim, image_type *gvar, image_type *im );


static image_type *	dbBox_imageN(  image_type *tim, image_type *mim, image_type *im );


static void		dbBox_remove_blob164( image_type *sim, int nT );

static void	dbBox_extend( image_type *sim );


//#define _DUMP


static int iFrame;
static int tS;




int CDynamicBackground::ProcessBox( image_type *sim )
{
//	m_inBoxIm = dbBox_image( sim, m_gvar, m_inBoxIm );

	m_inBoxIm = dbBox_sobol( sim, m_gvar, m_inBoxIm );

	return( 1 );
}


int CDynamicBackground::GetBoxImage( image_type **im )
{

//	*im = dbBox_imageN(  m_inBoxIm, mim, *im );

	*im = m_inBoxIm;

	return( 1 );
}


int CDynamicBackground::GetBoxImage( image_type *mim, image_type **im )
{

	*im = dbBox_imageN(  m_inBoxIm, mim, *im );

	return( 1 );
}






static image_type *
dbBox_image(  image_type *sim, image_type *gvar, image_type *im )
{
u_char	*tp,	*sp;
bn_type	*gv;
int	i,	j;
int	k,	n,	align;
float	sum;


	im = image_recreate( im, gvar->height, gvar->width, 1, 1 );


	align = sim->width - 8;
	gv = ( bn_type*)gvar->data;

	tp = im->data;
	for( i = 0 ; i < gvar->height ; i++ ){
		for( j = 0 ; j < gvar->width ; j++, gv++, tp++ ){
			if( gv->flag != 0 ){
				*tp = 0;
				continue;
			}


			sp = IMAGE_PIXEL( sim, i*8, j*8 );
			for( k = 0, sum = 0 ; k < 8 ; k++, sp += align ){
				for( n = 0 ; n < 8 ; n++, sp++ ){
					sum += *sp;
				}
			}

			float av = sum/64.0;


			sp = IMAGE_PIXEL( sim, i*8, j*8 );
			for( k = 0, sum = 0 ; k < 8 ; k++, sp += align ){
				for( n = 0 ; n < 8 ; n++, sp++ ){
					float d = *sp - av;
					if( d < 0 )	d = -d;
					sum += d;
				}
			}

			float var = sum / 64.0;

			*tp = ( var < 8 )? 192: 128;
		}

	}

	dbBox_remove_blob164( im, 6 );

	dbBox_extend( im );

	return( im );
}




static image_type *
dbBox_sobol(  image_type *sim, image_type *gvar, image_type *im )
{
u_char	*tp,	*sp;
bn_type	*gv;
int	i,	j;
int	k,	n,	align;
float	no;


	im = image_recreate( im, gvar->height, gvar->width, 1, 1 );


	align = sim->width - 8;
	gv = ( bn_type*)gvar->data;

	tp = im->data;
	for( i = 1 ; i < gvar->height - 1 ; i++ ){
		for( j = 0 ; j < gvar->width ; j++, gv++, tp++ ){
			if( gv->flag != 0 ){
				*tp = 0;
				continue;
			}


			sp = IMAGE_PIXEL( sim, i*8, j*8 );
			u_char *sp0 = sp - sim->column;
			u_char *sp1 = sp + sim->column;
			for( k = 0, no = 0 ; k < 8 ; k++, sp += align, sp0 += align, sp1+= align ){
				for( n = 0 ; n < 8 ; n++, sp++, sp0++, sp1++ ){
	

					int cx = ((*(sp0+1) - *(sp0-1)) + 2*(*(sp+1) -  *(sp-1)) + (*(sp1+1) - *(sp1-1)));
					int cy = ((*(sp1-1) - *(sp0-1)) + 2*(*(sp1+0) - *(sp0+0)) + (*(sp1+1) - *(sp0+1)));

					int val = ABS(cx) + ABS(cy );

					if( val > 15*8 )
						no++;
				
				}
			}



			*tp = ( no < 1 )? 192: 128;
		}

	}

	dbBox_remove_blob164( im, 6 );

	dbBox_extend( im );

	return( im );
}





static void
dbBox_extend( image_type *sim )
{
u_char	*sp,	*sp0,	*sp1;
int	i,	j,	n;


	for( i = 1 ; i < sim->height-1 ; i++ ){

		sp = IMAGE_PIXEL( sim, i, 1 );

		sp0 = sp - sim->width;
		sp1 = sp + sim->width;

		for( j = 1 ; j < sim->width-1 ; j++, sp++, sp0++, sp1++ ){
			if( *sp >= 192 )	continue;


			n = 0;
			if( *(sp-1) >= 192)	n++;
			if( *(sp+1) >= 192)	n++;


			if( *(sp0+1) >= 192 )	n++;
			if( *(sp0  ) >= 192)	n++;
			if( *(sp0+1) >= 192 )	n++;

			if( *(sp1+1) >= 192 )	n++;
			if( *(sp1  ) >= 192)	n++;
			if( *(sp1+1) >= 192 )	n++;


			if( n >= 2 )
				*sp = 164;
		}
	}
}



static void 
dbBox_remove_blob164( image_type *sim, int nT )
{
image_type *im;
bwLabel_type *abw;
int nBw; 
int	i,	j;


	im = image_create( sim->height, sim->width, 2, 1, NULL );

	u_char *sp = sim->data;
	short *bp = im->data_s;
	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ )
			*bp = ( *sp == 192 )? 1 : 0;


	image2_bwLabel( im, &abw, &nBw );
	if( nBw <= 1 ){
		free( abw );
		image_destroy( im, 1);
		return;
	}

	//	image2_bwLabel_set_direction( im, abw, nBw );
	image2_bwLabel_set_id( im, abw );



	for( i = 0 ; i < nBw ; i++ ){
		if( abw[i].no < nT )
			abw[i].id = -1;
	}



	sp = sim->data;
	bp = im->data_s;

	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ ){
			if( *sp == 0 )	continue;
			if( abw[*bp].id < 0 )
				*sp = 128;
		}

	free( abw );
	image_destroy( im, 1 );
}




static image_type *
dbBox_imageN(  image_type *tim, image_type *mim, image_type *im )
{
	u_char	*tp,	*sp;
	int	i,	j;
	int	k,	n,	align;
	float	sum;




	im = image_make_copy( mim, im );

	if( tim == NULL )
		return( im );


	align = im->width - 8;

	sp = tim->data;
	for( i = 0 ; i < tim->height ; i++ ){
		for( j = 0 ; j < tim->width ; j++, sp++ ){
			if( *sp == 0 )	continue;

			int color = *sp;
			tp = IMAGE_PIXEL( im, i*8, j*8 );
			for( k = 0, sum = 0 ; k < 8 ; k++, tp += align ){
				for( n = 0 ; n < 8 ; n++, tp++ ){
					if( *tp != 0 )
						*tp = color;
				}
			}
		}

	}

	return( im );
}