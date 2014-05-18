/************************
 ***   PfDeblur.cpp   ***
 ************************/
#include	<stdlib.h>
#include	<string.h>

#include "Utime/GpTime.h"

//#ifdef _DEBUG
#define _DUMP
//#endif


//#define USE_IPP
#ifdef USE_IPP
#pragma comment( lib, "ippi.lib" )
#include "ippi.h"
#endif


#include "ImageDump/ImageDump.h"




#ifdef USE_IPP
image_type *
imageF_median( image_type *sim, int rC, image_type *im )
{
IppiSize dstSize,	maskSize;
IppiPoint anchor;
IppStatus ret;

	im = image_recreate( im, sim->height, sim->width, 11, 1 );

	dstSize.width = im->width-2;
	dstSize.height = im->height-2;

	maskSize.width = 2*rC+1;
	maskSize.height = 2*rC+1;


	anchor.x = rC;//rC;
	anchor.y = rC;//rC;


	ret = ippiFilterMedian_8u_C1R( sim->data+sim->width+1, sim->width,
							im->data+im->width+1, im->width, dstSize,
							maskSize, anchor );
	return( im );
}
#endif

image_type *
imageF_median3( image_type *sim, image_type *im )
{
	int	i,	j,	n,	k;
	float	*sp,	*sp0,	*tp;
	int	align;

//	im = image_recreate( im, sim->height, sim->width, IMAGE_FORMAT_F, 1 );
	im = image_realloc( im, sim->width, sim->height, 1, IMAGE_TYPE_F, 1 );




	align = im->width - 3;
	for( i = 1 ; i < im->height-1 ; i++ ){
		sp = (float *)IMAGE_PIXEL( sim, i, 0 );
		tp = (float *)IMAGE_PIXEL( im, i, 0 );

		*tp++ = *sp++;
		for( j = 1 ; j < im->width-1 ; j++, sp++, tp++ ){

			int	aN = 0;
			float	a[10];
			int	s;
			sp0 = sp - im->width - 1;
			for( k = 0 ; k < 3 ; k++, sp0 += align ){
				for( n = 0 ; n < 3 ; n++, sp0++ ){

					for( s = aN ; s > 0 ; s-- ){
						if( *sp0 > a[s-1] )	break;
						a[s]= a[s-1];
					}
					a[s] = *sp0;
					aN++;
				}
			}

			*tp = a[5];

		}
		*tp++ = *sp++;
	}



	sp = (float *)IMAGE_PIXEL( sim, 0, 0 );
	tp = (float *)IMAGE_PIXEL( im, 0, 0 );
	for( j = 0 ; j < im->width ; j++ )
		*tp++ = *sp;

	sp = (float *)IMAGE_PIXEL( sim, sim->height-1, 0 );
	tp = (float *)IMAGE_PIXEL( im, im->height-1, 0 );
	for( j = 0 ; j < im->width ; j++ )
		*tp++ = *sp;

	return( im );
}



image_type *
imageFM_median3( image_type *sim, image_type *mim, image_type *im )
{
	int	i,	j,	n,	k;
	float	*sp,	*sp0,	*tp;
	u_char	*mp,	*mp0;
	int	align;

//	im = image_recreate( im, sim->height, sim->width, IMAGE_FORMAT_F, 1 );
	im = image_realloc( im, sim->width, sim->height, 1, IMAGE_TYPE_F, 1 );




	align = im->width - 3;
	for( i = 1 ; i < im->height-1 ; i++ ){
		sp = (float *)IMAGE_PIXEL( sim, i, 0 );
		mp = IMAGE_PIXEL( mim, i, 0 );

		tp = (float *)IMAGE_PIXEL( im, i, 0 );

		*tp++ = *sp++;
		for( j = 1 ; j < im->width-1 ; j++, sp++, tp++, mp++ ){

			int	aN = 0;
			float	a[10];
			int	s;
			sp0 = sp - sim->width - 1;
			mp0 = mp - mim->width - 1;

			for( k = 0 ; k < 3 ; k++, sp0 += align, mp0+= align ){
				for( n = 0 ; n < 3 ; n++, sp0++, mp0++ ){

					if( *mp0 == 0 )	continue;

					for( s = aN ; s > 0 ; s-- ){
						if( *sp0 > a[s-1] )	break;
						a[s]= a[s-1];
					}
					a[s] = *sp0;
					aN++;
				}
			}

			k = (aN+1)>>1;
			*tp = a[k];

		}
		*tp++ = *sp++;
	}



	sp = (float *)IMAGE_PIXEL( sim, 0, 0 );
	tp = (float *)IMAGE_PIXEL( im, 0, 0 );
	for( j = 0 ; j < im->width ; j++ )
		*tp++ = *sp;

	sp = (float *)IMAGE_PIXEL( sim, sim->height-1, 0 );
	tp = (float *)IMAGE_PIXEL( im, im->height-1, 0 );
	for( j = 0 ; j < im->width ; j++ )
		*tp++ = *sp;

	return( im );
}