/*************************
 ***   Image1Label.c   ***
 *************************/
#include <math.h>
#include "Uigp/igp.h"
#include "ImageType/ImageType.h"

#include "Umath/Matrix2Type.h"
#include "Umath/EigenType.h"

#include "ImageLabel/ImageLabel.h"


static void	imageUI_lebal_set_id( image_type *im, bwLabel_type *bw, int nBw );

static image_type *	imageLabelUI_create( image_type *sim, bwLabel_type **tbw, int *tnBw, image_type *im );





imageLabel_type *
imageLabel_alloc()
{
	imageLabel_type *abw;

	abw = ( imageLabel_type *)malloc( sizeof(imageLabel_type) );

	abw->mim = NULL;

	abw->im = NULL;
	abw->a = NULL;
	abw->nA = 0;

	return( abw );
}

void
imageLabel_destroy( imageLabel_type *abw )
{
	if( abw->a != NULL )
		free( abw->a );


	if( abw->im != NULL )
		image_destroy( abw->im, 1 );


	if( abw->mim != NULL )
		image_destroy( abw->mim, 1 );


	free( abw );
}





imageLabel_type *
imageLabelUI( image_type *sim, imageLabel_type *abw )
{
	if( abw == NULL )
		abw = imageLabel_alloc();


	abw->im = imageLabelUI_create( sim, &abw->a, &abw->nA, abw->im );

	return( abw );
}



imageLabel_type *
imageLabelUI_T( image_type *sim, int T, imageLabel_type *abw )
{
	if( abw == NULL )
		abw = imageLabel_alloc();

	abw->mim = image1_binary( sim, T, abw->mim );

	abw->im = imageLabelUI_create( abw->mim, &abw->a, &abw->nA, abw->im );

	return( abw );
}


image_type *
image1_label( image_type *sim, bwLabel_type **tbw, int *tnBw, image_type *im )
{
	*tbw = NULL;

	im = imageLabelUI_create(  sim, tbw, tnBw, im );
	
	return( im );
}



static image_type *
imageLabelUI_create( image_type *sim, bwLabel_type **tbw, int *tnBw, image_type *im )
{
bwLabel_type	*bw;
int	nBw;

int	i,	j,	k;
u_char	*sp,	*sp0,	*sp1;
u_int	*tp,	*tp0,	*tp1;
int	id1,	id;


//	im  = image_recreate( im, sim->height, sim->width, 4, 1 );
	im = image_realloc( im, sim->width, sim->height, 4, IMAGE_TYPE_U8, 1 );

	bw = *tbw;
	if( bw == NULL )
		bw = (bwLabel_type *)malloc( sim->row*sim->column*sizeof(bwLabel_type)/16 );

	nBw = 0;

	sp = sim->data ;
	tp = im->data_ui;
//	if( *sp != 0 ){
		bw[nBw].id = nBw;
		bw[nBw].no = 1;
		bw[nBw].color = *sp;

		*tp = nBw++;
//	}

	sp++;
	sp0 = sp-1;
	tp++;
	tp0 = tp-1;


	for( j = 1 ; j < sim->column ; j++, sp++, sp0++, tp++, tp0++ ){
//		if( *sp == 0 )	continue;

		if( *sp0 == *sp ){
			*tp = *tp0;
			bw[*tp].no++;
			continue;
		}

		bw[nBw].id = nBw;
		bw[nBw].no = 1;
		bw[nBw].color = *sp;

		*tp = nBw++;
	}

		
	for( i = 1 ; i < sim->row ; i++ ){
		sp = IMAGE_PIXEL( sim, i, 0 );
		sp1 = sp - sim->column;

		tp = (u_int*)IMAGE_PIXEL( im, i, 0 );
		tp1 = tp - im->column;


		if( *sp1 == *sp){
			*tp = *tp1;
			bw[*tp].no++;
		}
		else	{
			bw[nBw].id = nBw;
			bw[nBw].no = 1;
			bw[nBw].color = *sp;
			*tp = nBw++;
		}



		sp++;
		sp1++;
		sp0 = sp-1;

		tp++;
		tp1++;
		tp0 = tp-1;
		for( j = 1 ; j < sim->column ; j++, sp++, sp1++, sp0++, tp++, tp0++, *tp1++ ){
//			if( *sp == 0 )	continue;
			if( *sp0 == *sp ){

				*tp = bw[*tp0].id;
				bw[*tp].no++;
				if( *sp1 != *sp || bw[*tp].id == bw[*tp1].id )	continue;



				if( bw[*tp].id < bw[*tp1].id ){
					id1 = bw[*tp1].id;
					id = bw[*tp].id;
				}
				else {
					id = bw[*tp1].id;
					id1 = bw[*tp].id;
				}

				for( k = id1 ; k < nBw ; k++ ){
					if( bw[k].id == id1 )
						bw[k].id = id;
				}

				bw[id].no += bw[id1].no;


				continue;
			}

			if( *sp1 == *sp ){
				*tp = bw[*tp1].id;
				bw[*tp].no++;

				continue;
			}

			bw[nBw].id = nBw;
			bw[nBw].color = *sp;
			bw[nBw].no = 0;
			*tp = nBw++;
			bw[*tp].no++;
		}
	}

	*tbw = bw;
	*tnBw = nBw;


	imageUI_lebal_set_id( im, bw, nBw );

	return( im );
}


void
imageUI_lebal_set_id( image_type *im, bwLabel_type *bw, int nBw )
{
int	i,	j;
u_int	*tp;

	tp = im->data_ui;
	for( i = 0 ; i < im->height ; i++ )
		for( j = 0 ; j < im->width ; j++, tp++ )
			*tp = bw[*tp].id;
}




int
imageLabelUI_eigen2d( image_type *im, int id, box2i_type *b, eigen2d_type *e )
{
int	i,	j,	n;
u_int	*tp;
float	sx,	sy;

	matrix2_type	m;
	matrix2_zero( &m );
	
	sx = sy = 0;

	tp = im->data_ui;
	for( i = b->y0, n = 0 ; i < b->y1 ; i++ ){
		tp = IMAGE4_PIXEL( im, i, b->x0 );
		for( j = b->x0 ; j < b->x1 ; j++, tp++ ){
			if( *tp != id )	continue;

			sx += j;
			sy += i;

			m.a00 += j*j;
			m.a01 += j*i;
			m.a11 += i*i;
			n++;
		}
	}

	sx /= n;
	sy /= n;

	m.a00 = m.a00 / n - sx*sx;
	m.a01 = m.a01 / n - sx*sy;
	m.a11 = m.a11 / n - sy*sy;
	m.a10 = m.a01;


	e->p.x = sx;
	e->p.y = sy;




	matrix2S_eigen( &m, &e->e1, &e->v1, &e->e2 );

	return( 1 );

}






static int	imageUS_label_nieg( image_type *im, bwLabel_type *bw, int g[], int *nG );

static void	imageUS_label_replace( image_type *sim, image_type *im, bwLabel_type *bw, bwLabel_type *nbw );


void
imageLabel_filter( image_type *sim, image_type *lim, bwLabel_type *aBw, int nBw, int nT )
{
int	i,	k,	ik;
bwLabel_type	*bw;
int	g[100],	nG;


	imageLabelUS_set_aux( lim, aBw, nBw );

	for( i = 0 ; i < nBw ; i++ ){
		bw = &aBw[i];

		if( bw->id != i )	continue;
		if( bw->no >= nT )	continue;

		imageUS_label_nieg( lim, bw, g, &nG );

		for( k = 1, ik = 0 ; k < nG ; k++ )
			if( g[k] > g[ik] )	ik = k;

	
		imageUS_label_replace( sim, lim, bw, &aBw[g[ik]] );
	}
}


void
imageLabelUS_set_aux( image_type *im, bwLabel_type *aBw, int nBw )
{
int	i,	j;
u_int	*tp;
bwLabel_type *bw;

	for( i = 0 ; i < nBw ; i++ )
		aBw[i].no = 0;


	tp = im->data_ui;
	for( i = 0 ; i < im->height ; i++ ){
		for( j = 0 ; j < im->width ; j++, tp++ ){
			bw = &aBw[*tp];

			*tp = bw->id;
			bw->no++;

			if( bw->no <= 1 ){
				BOX2D_INIT( bw->b, j, i );
			}
			else	{
				BOX2D_UPDATE( bw->b, j, i );
			}
		}
	}
}


int
imageUS_label_nieg( image_type *im, bwLabel_type *bw, int g[], int *nG )
{
int	i,	j,	k,	id;
u_int	*tp;



	*nG = 0;
	for( i = bw->b.y0 ; i <= bw->b.y1 ; i++ ){
		tp = (u_int *)IMAGE_PIXEL( im, i, bw->b.x0 );

		for( j = bw->b.x0 ; j <= bw->b.x1 ; j++, tp++ ){

			if( *tp != bw->id )	continue;

			if( i > 0 && (id = *(tp-im->width)) != *tp ){
				for( k = 0 ; k < *nG ; k++ ){
					if( g[k] == id )	break;
				}
				if( k == *nG )	g[(*nG)++] = id;
			}

			if( i < im->height-1 && (id = *(tp+im->width)) != *tp ){
				for( k = 0 ; k < *nG ; k++ ){
					if( g[k] == id )	break;
				}
				if( k == *nG )	g[(*nG)++] = id;
			}

			if( j > 0 && (id = *(tp-1)) != *tp ){
				for( k = 0 ; k < *nG ; k++ ){
					if( g[k] == id )	break;
				}
				if( k == *nG )	g[(*nG)++] = id;
			}

			if( j < im->width-1 && (id = *(tp+1)) != *tp ){
				for( k = 0 ; k < *nG ; k++ ){
					if( g[k] == id )	break;
				}
				if( k == *nG )	g[(*nG)++] = id;
			}
		}
	}

	return( *nG );
}




static void
imageUS_label_replace( image_type *sim, image_type *im, bwLabel_type *bw, bwLabel_type *nbw )
{
int	i,	j;
u_int	*tp;
u_char	*sp;


	for( i = bw->b.y0 ; i <= bw->b.y1 ; i++ ){
		sp = (u_char *)IMAGE_PIXEL( sim, i, bw->b.x0 );
		tp = (u_int *)IMAGE_PIXEL( im, i, bw->b.x0 );

		for( j = bw->b.x0 ; j <= bw->b.x1 ; j++, tp++, sp++ ){

			if( *tp != bw->id )	continue;

			*tp = nbw->id;
			*sp = nbw->color;
			nbw->no++;

			BOX2D_UPDATE( nbw->b, j, i );

		}
	}

	bw->id = -1;
}



int
imageLabel_print( bwLabel_type *bw, int nBw, FILE *fp )
{
	int	i,	no;

	for( i = 0, no = 0 ; i < nBw ; i++ ){
		if( bw[i].id != i )	continue;

		fprintf( fp, "%d  -   color: %d   no: %d\n", (int)bw[i].id, (int)bw[i].color, bw[i].no );
	}

	return( no );
}


