 /*****************************
 ***   Image3KlTransform.c  ***
 ******************************/
#include	<string.h>
#include    <math.h>

#include	 "Umath/Matrix3Type.h"
#include	"ImageType/ImageType.h"
#include	"ImageTransform.h"



static image_type *	image3_averageF( image_type *sim, image_type *im );

static float	image3_band_cv( image_type *sim, int b0, int b1, image_type *aim );



int
image3_KL_transform( image_type *sim, matrix3_type *em, double ev[3] )
{
image_type	*aim;
matrix3_type	m;
int	i,	j;

	aim = 	image3_averageF( sim, NULL );

	for( i = 0; i < 3 ; i++ )
		for( j = 0 ; j < 3 ; j++ ){
			m.a[i][j] = image3_band_cv( sim, i, j, aim );
		}


	image_destroy( aim, 1 );

	if( matrixS3_eigen( &m, em, ev ) < 0 )
		return( -1 );

	return( 1 );
}


static float
image3_band_cv( image_type *sim, int b0, int b1, image_type *aim )
{
u_char	*sp0,	*sp1;
float	*ap;
int	i,	j;
double	av;



	sp0 = sim->data + b0;
	sp1 = sim->data + b1;

	ap = aim->data_f;

	av = 0;
	for( i = 0 ; i < sim->row ; i++ ){
		for( j = 0 ; j < sim->column ; j++, sp0 += 3, sp1 += 3, ap++ ){
			av += ( *sp0 - *ap) * ( *sp1 - *ap ); 
		}
	}

	
	av /= ( sim->width * sim->height);

	return( av );
}


static image_type *
image3_averageF( image_type *sim, image_type *im )
{
u_char	*sp;
float	*tp;
int	i,	j;

int	R,	G,	B;


	im = image_recreate( im, sim->height, sim->width, IMAGE_FORMAT_F, 1 );

	sp = sim->data;
	tp = im->data_f;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++ ){
			R = *sp++;
			G = *sp++;
			B = *sp++;

			*tp++ = (R + G + B)/3;
		}
	}


	return( im );
}


image_type *
image3_KL_component( image_type *sim, image_type *im )
{
matrix3_type em;
double ev[3];

u_char	*sp,	*tp;
int	i,	j;
double	rF,	gF,	bF;
int	R,	G,	B;
float	tmp,	m;



	image3_KL_transform( sim, &em, ev );

	rF = em.a[0][0];
	gF = em.a[1][0];
	bF = em.a[2][0];


	im = image_recreate( im, sim->height, sim->width, 1, 1 );

	sp = sim->data;
	tp = im->data;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++ ){
			R = *sp++;
			G = *sp++;
			B = *sp++;

			m = (R + G + B)/3;

			tmp = rF*(R-m) + gF*(G-m) + bF*(B-m) + m;

			*tp++ = PUSH_TO_RANGE( tmp, 0, 255 );

		}
	}


	return( im );
}