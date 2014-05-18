/**************************
 ***	ImageSubtruct.c	***
 *************************/

#include	"ImageType/ImageType.h"

static image_type *	image1_subtract( image_type *sim1, image_type *sim0 );





image_type *
image1_interpolation( image_type *sim,
					 float x0, float y0, int width, int height,
					 image_type *im )
{
u_char	*sp0,	*sp,	*tp;
int	i,	j;
float	x,	y,	dx,	dy;
int	ix,	iy;
float	s1,	s2;
int	s;

	if( im != NULL && (im->column != width || im->row != height) ){
		image_destroy( im, 1 );
		im = NULL;
	}
	if( im == NULL )
		im = image_create( height, width, 1, 1, NULL );



	tp = (u_char *)im->data;
	for( i = 0, y = y0 ; i < im->row ; i++, y++ ){

		if( y < 0 || y > sim->row-1){
			for( j = 0 ; j < im->column ; j++ )
				*tp++ = 0;
			continue;
		}


		iy = y;
		dy = y - iy;

		sp0 = IMAGE_PIXEL( sim, iy, 0 );

		for( j = 0, x = x0 ; j < im->column ; j++, x++ ){
			if( x < 0 || x > sim->column-1 ){
				*tp++ = 0;
				continue;
			}

			ix = x;
			dx = x - ix;

			sp = sp0 + ix;

			s1 = (1-dx)* (*sp) + dx * (*(sp+1));
			sp += sim->column;
			s2 = (1-dx)* (*sp) + dx * (*(sp+1));

			s = (1-dy)*s1 + dy * s2 + 0.5;
			*tp++ = PUSH_TO_RANGE(s, 0, 255 );
		}
	}

	return( im );
}

image_type *
image1_interpolation_1( image_type *sim,
					 float x0, float y0, int width, int height,
					 image_type *im )
{
u_char	*sp0,	*sp,	*tp;
int	i,	j;
float	x,	y,	dx,	dy;
int	ix,	iy;
float	s1,	s2;
int	s;

	if( im != NULL && (im->column != width || im->row != height) ){
		image_destroy( im, 1 );
		im = NULL;
	}
	if( im == NULL )
		im = image_create( height, width, 1, 1, NULL );



	dy = y0 - (int)y0;
	if( y0 < 0 )	dy = -dy;

	dx = x0 - (int)x0;
	if( x0 < 0 )	dx = -dx;


	tp = (u_char *)im->data;
	for( i = 0, y = y0 ; i < im->row ; i++, y++ ){

		if( y < 0 || y > sim->row-1){
			for( j = 0 ; j < im->column ; j++ )
				*tp++ = 0;
			continue;
		}


		iy = y;
//		dy = y - iy;

		sp0 = IMAGE_PIXEL( sim, iy, 0 );

		for( j = 0, x = x0 ; j < im->column ; j++, x++ ){
			if( x < 0 || x > sim->column-1 ){
				*tp++ = 0;
				continue;
			}

			ix = x;
//			dx = x - ix;

			sp = sp0 + ix;

			s1 = (1-dx)* (*sp) + dx * (*(sp+1));
			sp += sim->column;
			s2 = (1-dx)* (*sp) + dx * (*(sp+1));

			s = (1-dy)*s1 + dy * s2 + 0.5;
			*tp++ = PUSH_TO_RANGE(s, 0, 255 );
		}
	}

	return( im );
}
