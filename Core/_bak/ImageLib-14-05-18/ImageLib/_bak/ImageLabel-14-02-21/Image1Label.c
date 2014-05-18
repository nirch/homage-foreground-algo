/*************************
 ***   Image1Label.c   ***
 *************************/
#include <math.h>
#include "Uigp/igp.h"
#include "ImageType/ImageType.h"


#include "ImageLabel/ImageLabel.h"






void	imageUS_lebal_set_id( image_type *im, bwLabel_type *bw, int nBw );



image_type *
image1_label( image_type *sim, bwLabel_type **tbw, int *tnBw, image_type *im )
{
bwLabel_type	*bw;
int	nBw;

int	i,	j,	k;
u_char	*sp,	*sp0,	*sp1;
u_int	*tp,	*tp0,	*tp1;
int	id1,	id;


	im  = image_recreate( im, sim->height, sim->width, 4, 1 );

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
//						bw[k].id = bw[*tp].id;
						bw[k].id = id;


				}

				bw[id].no += bw[id1].no;


				//if( bw[*tp].id < bw[*tp1].id ){

				//	id1 = bw[*tp1].id;
				//	id = bw[*tp].id;

				//	for( k = id1 ; k < nBw ; k++ ){
				//		if( bw[k].id == id1 )
				//			bw[k].id = bw[*tp].id;
				//	}

				//	bw[id].no += bw[id1].no;
				//}
				//else {

				//	id1 = bw[*tp].id;
				//	id = bw[*tp1].id;
				//	for( k = id1 ; k < nBw ; k++ ){
				//		if( bw[k].id == id1 )
				//			bw[k].id = bw[*tp1].id;
				//	}
				//	bw[id].no += bw[id1].no;
				//}


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

//	imageLabel_print( bw, nBw, stdout );

	imageUS_lebal_set_id( im, bw, nBw );
	return( im );
}


void
imageUS_lebal_set_id( image_type *im, bwLabel_type *bw, int nBw )
{
int	i,	j;
u_int	*tp;

	tp = im->data_ui;
	for( i = 0 ; i < im->height ; i++ )
		for( j = 0 ; j < im->width ; j++, tp++ )
			*tp = bw[*tp].id;
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


