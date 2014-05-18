
#include	<math.h>

#include	"ImageType/ImageType.h"
#include	"ImageUSTool.h"

void
imageUS_minmax( image_type *im, int *min,	int *max )
{
u_short	*sp;
int	i,	j;
int	channel;


	channel = im->depth / 2;

	sp = im->data_us;
	*min = *max = *sp;

	for( i = 0 ; i < im->row ; i++ )
		for( j = 0 ; j < channel*im->column ; j++, sp++ ){

			if( *sp < *min )
				*min = *sp;
			else	if( *sp > *max )
				*max = *sp;
		}
}

void
imageUS_max( image_type *im, int *max )
{
u_short	*sp;
int	i,	j;
int	channel;



	channel = im->depth / 2;

	sp = im->data_us;

	*max = *sp;

	for( i = 0 ; i < im->row ; i++ )
		for( j = 0 ; j < channel*im->column ; j++, sp++ ){

			if( *sp > *max )
				*max = *sp;
		}
}



image_type *
imageUS_to_image1( image_type *sim, image_type *im )
{
u_short	*sp;
u_char	*tp;
int	i,	j;



	im = image_recreate( im, sim->height, sim->width, 1, 1 );

	sp = sim->data_us;
	tp = im->data;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++ ){


			*tp++ = *sp++;
		}
	}

	return( im );
}




image_type *
imageUS3_to_y( image_type *sim, image_type *im )
{
u_short	*sp,	*tp;
int	i,	j;
int	R,	G,	B;

int	Y;


	im = image_recreate( im, sim->height, sim->width, IMAGE_FORMAT_US, 1 );

	sp = sim->data_us;
	tp = im->data_us;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++ ){
			R = *sp++;
			G = *sp++;
			B = *sp++;

			Y  =  0.29900 * R + 0.58700 * G + 0.11400 * B + 0.5;
			*tp++ = PUSH_TO_RANGE( Y, 0, ((1<<16)-1) );
		}
	}

	return( im );
}

image_type *
imageUS3_linear_combination( image_type *sim, float a, float fR, float fG, float fB, image_type *im )
{
	u_short	*sp;
	u_short	*tp;
	int	i,	j;

	int	R,	G,	B;

	int	Y;




	im = image_recreate( im, sim->height, sim->width, IMAGE_FORMAT_US, 1 );

	sp = sim->data_us;
	tp = im->data_us;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++ ){
			R = *sp++;
			G = *sp++;
			B = *sp++;


			Y  =  a + fR * R + fG * G + fB * B + 0.5;
			*tp++ = PUSH_TO_RANGE( Y, 0, ((1<<16)-1) );
		}
	}

	return( im );
}


int
imageUS_compare( image_type *im1, image_type *im0 )
{
float	*sp0,	*sp1;
int	i,	j;
float	tmp,	peak;

	sp1 = (float *)im1->data;
	sp0 = (float *)im0->data;


	peak = 0;

	for( i = 0 ; i < im0->row ; i++ )
		for( j = 0 ; j < im0->column ; j++ ){

			tmp = *sp1++ - (float)*sp0++;
			if( tmp < 0 )	tmp = - tmp;
			if( peak < tmp )	peak = tmp;
		}

	return( peak );
}


