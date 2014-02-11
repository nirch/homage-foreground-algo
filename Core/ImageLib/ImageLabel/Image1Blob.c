/**************************
 ***   Image1Blob.cpp   ***
 **************************/
#include	<math.h>

#ifdef _DEBUG
#define _DUMP
#endif



#include "ImageType/ImageType.h"
#include "ImageLabel.h"

imageLabel_type *
imageLabelUS( image_type *sim, int T, imageLabel_type *abw )
{
int	i,	j;
u_char	*sp;
short	*bp;

	if( abw == NULL )
		abw = imageLabel_alloc();


	abw->im = image_realloc( abw->im, sim->width, sim->height, 1, IMAGE_TYPE_U16, 1 );



	sp = sim->data;
	bp = abw->im->data_s;
	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ )
			*bp = ( *sp < T )? 0 :1;


	image2_bwLabel( abw->im, &abw->a, &abw->nA );
	

	return( abw );
}



image_type *
image1_connect_component( image_type *sim, int T, bwLabel_type **abw, int *nBw, image_type *im )
{
	int	i,	j;
	u_char *sp;
	short *bp;

	im = image_create( sim->height, sim->width, 2, 1, NULL );

	sp = sim->data;
	bp = im->data_s;
	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ )
			*bp = ( *sp < T )? 0 :1;


	image2_bwLabel( im, abw, nBw );
	if( *nBw <= 1 ){
		free( abw );
		image_destroy( im, 1);
		return( NULL );
	}

	image2_bwLabel_set_id( im, *abw );

	image2_bwLabel_set_aux( im, *abw, *nBw );

	return( im );
}




void 
image1_remove_blob( image_type *sim, int nP, int nT, int value )
{
image_type *im;
bwLabel_type *abw;
int nBw; 
int	i,	j;
u_char *sp;
short *bp;

	im = image_create( sim->height, sim->width, 2, 1, NULL );

	sp = sim->data;
	bp = im->data_s;
	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ )
			*bp = ( *sp < nP )? 0 :1;


	image2_bwLabel( im, &abw, &nBw );
	if( nBw <= 1 ){
		free( abw );
		image_destroy( im, 1);
		return;
	}

	image2_bwLabel_set_id( im, abw );



	for( i = 0 ; i < nBw ; i++ ){
		if( abw[i].no < nT )
			abw[i].id = -1;
	}



	sp = sim->data;
	bp = im->data_s;

	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ ){
			if( abw[*bp].id < 0 )
				*sp = value;
		}

		free( abw );
		image_destroy( im, 1 );
}


int	bwLabel_filter( bwLabel_type *bw, int nBw, int pT, int bT );



void 
image1_remove_blobM( image_type *sim, int nP, int pT, int bT, int value )
{
	image_type *im;
	bwLabel_type *abw;
	int nBw; 
	int	i,	j;
	u_char *sp;
	short *bp;


	im = image_create( sim->height, sim->width, 2, 1, NULL );

	sp = sim->data;
	bp = im->data_s;
	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ )
			*bp = ( *sp < nP )? 0 :1;


	image2_bwLabel( im, &abw, &nBw );
	if( nBw <= 1 ){
		free( abw );
		image_destroy( im, 1);
		return;
	}

	image2_bwLabel_set_id( im, abw );



	//for( i = 0 ; i < nBw ; i++ ){
	//	if( abw[i].no < nT )
	//		abw[i].id = -1;
	//}



	bwLabel_filter( abw, nBw, pT, bT );



	sp = sim->data;
	bp = im->data_s;

	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ ){
			if( abw[*bp].id < 0 )
				*sp = value;
		}

		free( abw );
		image_destroy( im, 1 );
}



int
bwLabel_filter( bwLabel_type *bw, int nBw, int pT, int bT )
{
int	i,	i0,	j;
int	ab[64],	 nB;

	nB = 0;
	for( i = 0 ; i < nBw ; i++ ){
//		if( bw[i].id != i )	continue;

		if( bw[i].id != i || bw[i].no < pT ){
			bw[i].id = -1;
			continue;
		}



		if( nB < bT ){
			ab[nB++] = i;
			continue;
		}

		i0 = ab[nB-1];

		if( bw[i0].no > bw[i].no ){
			bw[i].id = -1;
			continue;
		}

		bw[i0].id = -1;

		for( j = nB ; j > 0 ; j-- ){
			if(  bw[ab[j-1]].no > bw[i].no  )
				break;
			ab[j] = ab[j-1];
		}
		ab[j] = i;
	}

	return( nB );
}



void 
image1_fill_blob( image_type *sim, int nP, int nT, int value )
{
image_type *im;
bwLabel_type *abw;
int nBw; 
int	i,	j;
u_char *sp;
short *bp;

	im = image_create( sim->height, sim->width, 2, 1, NULL );

	sp = sim->data;
	bp = im->data_s;
	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ )
			*bp = ( *sp < nP )? 1 :0;


	image2_bwLabel( im, &abw, &nBw );
	if( nBw <= 1 ){
		free( abw );
		image_destroy( im, 1);
		return;
	}

	image2_bwLabel_set_id( im, abw );



	for( i = 0 ; i < nBw ; i++ ){
		if( abw[i].no < nT )
			abw[i].id = -1;
	}



	sp = sim->data;
	bp = im->data_s;

	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ ){
			if( *bp == 0 )	continue;
			if( abw[*bp].id < 0 )
				*sp = value;
		}

		free( abw );
		image_destroy( im, 1 );
}

