/**************************
 ***	Image4Sample.c	***
 *************************/

#include "ImageType/ImageType.h"


image_type *	image3_sample3( image_type *sim, image_type *im );


image_type *	
image_sample( image_type *sim, int d, image_type *im )
{
	if( sim->depth == 4 ){
		im = image4_sample( sim, d, im );

		return( im );
	}


	if( sim->depth == 3 ){

		if( d == 3 ){
			im = image3_sample3( sim, im );
			return( im );
		}

		im = image3_sample( sim, d, im );

		return( im );
	}

	if( sim->depth == 1 ){
		im = image1_sample( sim, d, im );

		return( im );
	}

	if( im != NULL )
		image_destroy( im, 1 );
	return( NULL );
}



image_type *
image4_sample( image_type *sim, int d, image_type *im )
{
u_int	*sp,	*p;
int	i,	j,	i1,	j1;
int	r,	g,	b,	n,	k,	algin;
float	dup2 = 1.0F / (d*d);

	im = image_recreate( im, sim->row/d, sim->column/d, 4, 1 );

	algin = sim->column - d;
	
	p = (u_int *)im->data;
	for( i = 0, i1 = 0 ; i < im->row ; i++, i1 += d )
	    for( j = 0, j1 = 0 ; j < im->column ; j++, j1 += d ){

		sp = IMAGE4_PIXEL( sim, i1, j1 );
		r = g = b = 0;
		for( k = 0 ; k < d ; k++, sp += algin )
			for( n = 0 ; n < d ; n++, sp++ ){
/*
				r += ((*sp)&0xff0000);
*/
				r += ((*sp) >> 16);
				g += ((*sp)&0x00ff00);
				b += ((*sp)&0x0000ff);
			}

		r *= dup2;
		g *= dup2;
		b *= dup2;

		*p++ = (r<<16) | (g&0x00ff00) | (b&0x0000ff);
	    }


	return( im );
}



image_type *
image4_dup( image_type *sim, int d, image_type *im )
{
u_int	*sp,	*tp,	*sp0;
int	i,	j,	i1,	j1;

	im = image_recreate( im, sim->row*d, sim->column*d, 4, 1 );

	
	tp = (u_int *)im->data;
	sp0 = (u_int *)sim->data;
	for( i = 0 ; i < sim->row ; i++, sp0 += sim->column ){


		for( i1 = 0 ; i1 < d ; i1++ ){
			sp = sp0;
			for( j = 0 ; j < sim->column ; j++, sp++ )
				for( j1 = 0 ; j1 < d ; j1++ )
					*tp++ = *sp;
		}
	}

	return( im );
}










image_type *	
image_sample2( image_type *sim, image_type *im )
{
	if( sim->depth == 4 ){
		im = image4_sample2( sim, im );

		return( im );
	}


	if( sim->depth == 3 ){
		im = image3_sample2( sim, im );

		return( im );
	}

	if( sim->depth == 1 ){
		im = image1_sample2( sim, im );

		return( im );
	}

	if( im != NULL )
		image_destroy( im, 1 );
	return( NULL );
}


#ifdef _AA_
image_type *
image1_sample2( image_type *sim, image_type *im )
{
	u_char	*sp0,	*sp1, *sp2,	*sp3,	*tp;
	int	i,	j;


	im = image_realloc( im, sim->width/2, sim->height/2, 1, IMAGE_TYPE_U8, 1 );


	tp = im->data;
	for( i = 0 ; i < im->row ; i++ ){
		sp0 = IMAGE_PIXEL( sim, 2*i, 0 );
		sp1 = sp0+1;
		sp2 = sp0 + sim->width;
		sp3 = sp2 + 1;

		for( j = 0 ; j < im->column ; j++ ){

			*tp++ = ( *(sp0++) + *(sp1++) + *(sp2++) + *(sp3++) ) >>2;


			sp0 += 1;
		}
	}

	return( im );
}
#endif

image_type *
image3_sample2( image_type *sim, image_type *im )
{
	u_char	*sp0,	*sp1, *sp2,	*sp3,	*tp;
	int	i,	j;


	im = image_realloc( im, sim->width/2, sim->height/2, 3, IMAGE_TYPE_U8, 1 );


	tp = im->data;
	for( i = 0 ; i < im->row ; i++ ){
		sp0 = IMAGE_PIXEL( sim, 2*i, 0 );
		sp1 = sp0+3;
		sp2 = sp0 + 3*sim->width;
		sp3 = sp2 + 3;

		for( j = 0 ; j < im->column ; j++ ){

			*tp++ = ( *(sp0++) + *(sp1++) + *(sp2++) + *(sp3++) ) >>2;
			*tp++ = ( *(sp0++) + *(sp1++) + *(sp2++) + *(sp3++) ) >>2;
			*tp++ = ( *(sp0++) + *(sp1++) + *(sp2++) + *(sp3++) ) >>2;

			sp0 += 3;
			sp1 += 3;
			sp2 += 3;
			sp3 += 3;
		}
	}

	return( im );
}



image_type *
image3_sample3( image_type *sim, image_type *im )
{
	u_char	*sp0,	*sp1, *sp2,	*tp;
	int	i,	j;
	float	tmp;


	

	tmp = 1.0/(3.0*3.0 );

	im = image_realloc( im, sim->width/3, sim->height/3, 3, IMAGE_TYPE_U8, 1 );


	tp = im->data;
	for( i = 0 ; i < im->row ; i++ ){
		sp0 = IMAGE_PIXEL( sim, 3*i, 0 );
		sp1 = sp0 + 3*sim->width;
		sp2 = sp1 + 3*sim->width;

		for( j = 0 ; j < im->column ; j++ ){

			*tp++ = (sp0[0] + sp0[3] + sp0[6] + sp1[0] + sp1[3] + sp1[6] + sp2[0] + sp2[3] + sp2[6]) * tmp;
			*tp++ = (sp0[1] + sp0[4] + sp0[7] + sp1[1] + sp1[4] + sp1[7] + sp2[1] + sp2[4] + sp2[7]) * tmp;
			*tp++ = (sp0[2] + sp0[5] + sp0[8] + sp1[2] + sp1[5] + sp1[8] + sp2[2] + sp2[5] + sp2[8]) * tmp;

			sp0 += 9;
			sp1 += 9;
			sp2 += 9;
		}
	}

	return( im );
}

image_type *
image4_sample2( image_type *sim, image_type *im )
{
	u_char	*sp0,	*sp1, *sp2,	*sp3,	*tp;
	int	i,	j;


	im = image_realloc( im, sim->width/2, sim->height/2, 4, IMAGE_TYPE_U8, 1 );


	tp = im->data;
	for( i = 0 ; i < im->row ; i++ ){
		sp0 = IMAGE_PIXEL( sim, 2*i, 0 );
		sp1 = sp0+4;
		sp2 = sp0 + 4*sim->width;
		sp3 = sp2 + 4;

		for( j = 0 ; j < im->column ; j++ ){

			*tp++ = ( *(sp0++) + *(sp1++) + *(sp2++) + *(sp3++) ) >>2;
			*tp++ = ( *(sp0++) + *(sp1++) + *(sp2++) + *(sp3++) ) >>2;
			*tp++ = ( *(sp0++) + *(sp1++) + *(sp2++) + *(sp3++) ) >>2;
			*tp++ = ( *(sp0++) + *(sp1++) + *(sp2++) + *(sp3++) ) >>2;

			sp0 += 4;
			sp1 += 4;
			sp2 += 4;
			sp3 += 4;
		}
	}

	return( im );
}



