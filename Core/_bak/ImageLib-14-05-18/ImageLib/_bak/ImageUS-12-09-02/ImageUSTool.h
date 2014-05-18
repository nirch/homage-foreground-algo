/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#ifndef         _IMAGE_US_TOOL_
#define         _IMAGE_US_TOOL_


#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"



	// ImageUSTool.h"
image_type *	imageUS_from( image_type *sim, image_type *im );



void	imageUS_minmax( image_type *im, int *min,	int *max );

void	imageUS_max( image_type *im, int *max );


image_type * imageUS3_to_y( image_type *sim, image_type *im );

//image_type *	imageUS3_linear_combination( image_type *sim, float a, float fR, float fG, float fB, image_type *im );



image_type *	imageUS_to_image1( image_type *sim, image_type *im );


int	imageUS_compare( image_type *im1, image_type *im0 );


image_type *	imageUS_to_imageU8( image_type *sim, image_type *im );

image_type *	imageUS_to_U8( image_type *sim, int min, int max, image_type *im );




	// ImageUSInterpolate.c
image_type *	imageAS_interpolation_V( imageA_type *aim, vec2f_type *p, vec2f_type *v, 
						int x0, int width,
						image_type *im );


#ifdef __cplusplus
}
#endif

#endif
