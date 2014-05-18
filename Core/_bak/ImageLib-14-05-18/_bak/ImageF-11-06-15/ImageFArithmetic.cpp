/************************
 ***   PfDeblur.cpp   ***
 ************************/
#include	<stdlib.h>
#include	<string.h>

#include "Utime/GpTime.h"

//#ifdef _DEBUG
#define _DUMP
//#endif

#include	"ImageTYpe/ImageType.h"


//#define USE_IPP
#ifdef USE_IPP
#pragma comment( lib, "ippi.lib" )
#include "ippi.h"


image_type *
imageF_abs( image_type *sim, image_type *im )
{
IppiSize roiSize;
IppStatus ret;

	im = image_recreate( im, sim->height, sim->width, 4, 1 );

	roiSize.width = im->width;
	roiSize.height = im->height;

	ret = ippiAbs_32f_C1R( sim->data_f, 4*sim->width,
					im->data_f, 4*im->width, roiSize );


	return( im );
}


image_type *
imageF_absdiff( image_type *im1, image_type *im0, image_type *im )
{
IppiSize roiSize;
//IppStatus ret;

return( NULL );

	im = image_recreate( im, im1->height, im1->width, 4, 1 );

	roiSize.width = im->width;
	roiSize.height = im->height;


	//ret = ippiAbsDiff_32f_C1R( im1->data_f, 4*im1->width,
	//							im0->data_f, 4*im0->width,
	//							im->data_f, 4*im->width, roiSize );
		


	return( im );
}


image_type *
imageF_subtrct( image_type *im1, image_type *im0, image_type *im )
{
IppiSize roiSize;
IppStatus ret;

	im = image_recreate( im, im1->height, im1->width, 4, 1 );

	roiSize.width = im->width;
	roiSize.height = im->height;


	ret = ippiSub_32f_C1R( im0->data_f, 4*im0->width,
								im1->data_f, 4*im1->width,
								im->data_f, 4*im->width, roiSize );



	return( im );
}


image_type *
imageF_add( image_type *im1, image_type *im0, image_type *im )
{
	IppiSize roiSize;
	IppStatus ret;

	im = image_recreate( im, im1->height, im1->width, 4, 1 );

	roiSize.width = im->width;
	roiSize.height = im->height;


	ret = ippiAdd_32f_C1R( im0->data_f, 4*im0->width,
		im1->data_f, 4*im1->width,
		im->data_f, 4*im->width, roiSize );



	return( im );
}

#else

image_type *
imageF_add( image_type *sim, image_type *aim, image_type *im )
{
	int	i,	j;
	float	*sp,	*ap,	*tp;

	im = image_recreate( im, sim->height, sim->width, 4, 1 );

	sp = sim->data_f;
	ap = aim->data_f;
	tp = im->data_f;

	for( i = 0 ; i < im->height ; i++ )
		for( j = 0 ; j < im->width ; j++, sp++, ap++,  tp++ )
			*tp = *sp + *ap;

	return( im );
}



image_type *
imageF_subtrct( image_type *im1, image_type *im0, image_type *im )
{
	float	*tp;
	float	*sp0,	*sp1;
	int	i,	j;

	im = image_recreate( im, im0->row, im0->column, 4, 1 );

	sp1 = (float *)im1->data;
	sp0 = (float *)im0->data;

	tp = (float*)im->data;


	for( i = 0 ; i < im->row ; i++ )
		for( j = 0 ; j < im->column ; j++ ){

			*tp++ = *sp1++ - (float)*sp0++;
		}


		return( im );
}


image_type *
imageF_absdiff( image_type *im1, image_type *im0, image_type *im )
{
	float	*tp;
	float	*sp0,	*sp1;
	int	i,	j;

	im = image_recreate( im, im0->row, im0->column, 4, 1 );

	sp1 = (float *)im1->data;
	sp0 = (float *)im0->data;

	tp = (float*)im->data;


	for( i = 0 ; i < im->row ; i++ )
		for( j = 0 ; j < im->column ; j++ ){

			float tmp = *sp1++ - *sp0++;
			if( tmp < 0 )	tmp = -tmp;
			*tp++ = tmp;
		}

		return( im );
}




image_type *
imageF_abs( image_type *sim, image_type *im )
{
	float	*tp;
	float	*sp;
	int	i,	j;



	im = image_recreate( im, sim->row, sim->column, 4, 1 );

	sp = (float *)sim->data;

	tp = (float*)im->data;


	for( i = 0 ; i < im->row ; i++ )
		for( j = 0 ; j < im->column ; j++, sp++ ){

			*tp++ = (*sp < 0 )? -*sp : *sp;;
		}

		return( im );
}

#endif

