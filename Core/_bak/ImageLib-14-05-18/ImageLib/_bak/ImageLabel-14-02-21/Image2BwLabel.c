/***************************
 ***   Image2BwLabel.c   ***
 ***************************/
#include <math.h>
#include "Uigp/igp.h"
#include "ImageType/ImageType.h"
#include "BwLabel.h"



static int	math_linear_equation2_symtric_eigenvalue( float xx, float xy, float yy,
							  float *e1, vec2d *v1, float *e2 );



void
image2_bwLabel( image_type *im, bwLabel_type **tbw, int *tnBw )
{
bwLabel_type	*bw;
int	nBw;

int	i,	j,	k;
short	*sp,	*sp0,	*sp1;
int	id,	id1;



	bw = (bwLabel_type *)malloc( im->row*im->column*sizeof(bwLabel_type) );
	nBw = 0;

	bw[nBw].id = nBw;
	bw[nBw].no = 0;
	nBw++;

	sp = (short*)im->data ;
	if( *sp != 0 ){
		bw[nBw].id = nBw;
		bw[nBw].no = 0;
		*sp = nBw++;
		bw[*sp].no++;
	}

	sp++;
	sp0 = sp-1;
	for( j = 1 ; j < im->column ; j++, sp++, sp0++ ){
		if( *sp == 0 )	continue;

		if( *sp0 != 0 ){
			*sp = bw[*sp0].id;
			bw[*sp].no++;
			continue;
		}

		bw[nBw].id = nBw;
		bw[nBw].no = 0;
		*sp = nBw++;
		bw[*sp].no++;
	}

		
	for( i = 1 ; i < im->row ; i++ ){
		sp = (short*)IMAGE_PIXEL( im, i, 0 );
		sp1 = sp - im->column;
		if( *sp != 0 ){
			if( *sp1 != 0 ){
				*sp = bw[*sp1].id;
				bw[*sp].no++;
			}
			else	{
				bw[nBw].id = nBw;
				bw[nBw].no = 0;
				*sp = nBw++;
				bw[*sp].no++;
			}
		}


		sp++;
		sp1++;
		sp0 = sp-1;
		for( j = 1 ; j < im->column ; j++, sp++, sp1++, sp0++ ){
			if( *sp == 0 )	continue;
			if( *sp0 != 0 ){
				*sp = bw[*sp0].id;
				bw[*sp].no++;
//				if( *sp1 == 0 || *sp1 == *sp || bw[*sp].id == bw[*sp1].id )	continue;
				if( *sp1 == 0 || bw[*sp].id == bw[*sp1].id )	continue;



				if( bw[*sp].id < bw[*sp1].id ){
					id1 = bw[*sp1].id;
					id = bw[*sp].id;
				}
				else {
					id = bw[*sp1].id;
					id1 = bw[*sp].id;
				}

				for( k = id1 ; k < nBw ; k++ ){
					if( bw[k].id == id1 )
						bw[k].id = id;
				}

				bw[id].no += bw[id1].no;



				//if( bw[*sp].id < bw[*sp1].id ){

				//	for( k = 0 ; k < nBw ; k++ ){
				//		if( bw[k].id == bw[*sp1].id )
				//			bw[k].id = bw[*sp].id;
				//	}

				//	bw[*sp].no += bw[*sp1].no;
				//	bw[*sp1].id = bw[*sp].id;

				//}
				//else {
				//	for( k = 0 ; k < nBw ; k++ ){
				//		if( bw[k].id == bw[*sp].id )
				//			bw[k].id = bw[*sp1].id;
				//	}
				//	bw[*sp1].no += bw[*sp].no;
				//	bw[*sp].id = bw[*sp1].id;
				//}
				continue;
			}

			if( *sp1 != 0 ){
				*sp = bw[*sp1].id;
				bw[*sp].no++;

				continue;
			}

			bw[nBw].id = nBw;
			bw[nBw].no = 0;
			*sp = nBw++;
			bw[*sp].no++;
		}
	}

	*tbw = bw;
	*tnBw = nBw;
}

void
image2_bwLabelV( image_type *im, bwLabel_type **tbw, int *tnBw )
{
bwLabel_type	*bw;
int	nBw;

int	i,	j,	k;
short	*sp,	*sp0,	*sp1;



	bw = (bwLabel_type *)malloc( im->row*im->column*sizeof(bwLabel_type) );
	nBw = 0;

	sp = (short*)im->data ;
	if( *sp != 0 ){
		bw[nBw].id = nBw;
		bw[nBw].no = 1;
		bw[nBw].color = *sp;

		*sp = nBw++;
	}

	sp++;
	sp0 = sp-1;
	for( j = 1 ; j < im->column ; j++, sp++, sp0++ ){
		if( *sp == 0 )	continue;

		if( *sp0 != 0 && bw[*sp0].color == *sp ){
			*sp = bw[*sp0].id;
			bw[*sp].no++;
			continue;
		}

		bw[nBw].id = nBw;
		bw[nBw].no = 1;
		bw[nBw].color = *sp;

		*sp = nBw++;
	}

		
	for( i = 1 ; i < im->row ; i++ ){
		sp = (short*)IMAGE_PIXEL( im, i, 0 );
		sp1 = sp - im->column;
		if( *sp != 0 ){
			if( *sp1 != 0 && bw[*sp1].color == *sp){
				*sp = bw[*sp1].id;
				bw[*sp].no++;
			}
			else	{
				bw[nBw].id = nBw;
				bw[nBw].no = 1;
				bw[nBw].color = *sp;
				*sp = nBw++;
			}
		}


		sp++;
		sp1++;
		sp0 = sp-1;
		for( j = 1 ; j < im->column ; j++, sp++, sp1++, sp0++ ){
			if( *sp == 0 )	continue;
			if( *sp0 != 0 ){
				*sp = bw[*sp0].id;
				bw[*sp].no++;
				if( *sp1 == 0 || *sp1 == *sp )	continue;

				if( bw[*sp].id < bw[*sp1].id ){

					for( k = 0 ; k < nBw ; k++ ){
						if( bw[k].id == bw[*sp1].id )
							bw[k].id = bw[*sp].id;
					}

					bw[*sp].no += bw[*sp1].no;
					bw[*sp1].id = bw[*sp].id;

				}
				else {
					for( k = 0 ; k < nBw ; k++ ){
						if( bw[k].id == bw[*sp].id )
							bw[k].id = bw[*sp1].id;
					}
					bw[*sp1].no += bw[*sp].no;
					bw[*sp].id = bw[*sp1].id;
				}
				continue;
			}

			if( *sp1 != 0 ){
				*sp = bw[*sp1].id;
				bw[*sp].no++;

				continue;
			}

			bw[nBw].id = nBw;
			bw[nBw].no = 0;
			*sp = nBw++;
			bw[*sp].no++;
		}
	}

	*tbw = bw;
	*tnBw = nBw;
}


int
bwLabel_no( bwLabel_type *bw, int nBw, int T )
{
int	i,	no;

	for( i = 0, no = 0 ; i < nBw ; i++ ){
		if( bw[i].id != i )	continue;
		if( T <= 0 || bw[i].no > T )	no++;
	}

	return( no );
}


void
image2_bwLabel_set_id( image_type *im, bwLabel_type *bw )
{
short	*sp;
int	i,	j;

	sp = (short *)im->data;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++, sp++ )
			*sp = bw[*sp].id;
	}
}


void
image2_bwLabel_set_aux( image_type *im, bwLabel_type *aBw, int nBw )
{
int	i,	j;
short	*sp;
bwLabel_type *bw;

	for( i = 0 ; i < nBw ; i++ )
		aBw[i].no = 0;


	sp = im->data_s;
	for( i = 0 ; i < im->height ; i++ ){
		for( j = 0 ; j < im->width ; j++, sp++ ){
			bw = &aBw[*sp];

			*sp = bw->id;
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



void
image2_bwLabel_remove_boundary( image_type *im, bwLabel_type *bw )
{
short	*sp;
int	i,	j;

	sp = (short *)im->data;
	for( j = 0 ; j < im->column ; j++, sp++ ){
		if( *sp != 0 )
			bw[*sp].id = -1;
	}

	sp = (short *)IMAGE_PIXEL( im, (im->row-1), 0 );
	for( j = 0 ; j < im->column ; j++, sp++ ){
		if( *sp != 0 )
			bw[*sp].id = -1;
	}



	sp = (short *)im->data;
	for( i = 0 ; i < im->row ; i++, sp += im->column ){
		if( *sp != 0 )
			bw[*sp].id = -1;
	}

	sp = (short *)IMAGE_PIXEL( im, 0, im->column-1 );
	for( i = 0 ; i < im->row ; i++, sp += im->column ){
		if( *sp != 0 )
			bw[*sp].id = -1;
	}
}

typedef	struct bwAux_type	{
	int	n;

	vec2d	p;

	float	xx,	xy,	yy;

}	bwAux_type;

void
image2_bwLabel_set_direction( image_type *im, bwLabel_type *bw, int nBw )
{
short	*sp;
int	i,	j;
bwAux_type	*baw,	*ba;
bwLabel_type	*b;
float	x,	y;


	baw = ( bwAux_type *)malloc( nBw * sizeof( bwAux_type) );

	for( i = 0 ; i < nBw ; i++ ){
		ba = &baw[i];
		ba->p.x = ba->p.y = ba->xx = ba->xy = ba->yy = 0;
		ba->n = 0;
	}

	sp = (short *)im->data;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++, sp++ ){
			if( *sp == 0 )	continue;
			ba = &baw[*sp];

			ba->n++;
			ba->p.x += j;
			ba->p.y += i;
		}
	}

	for( i = 0 ; i < nBw ; i++ ){
		ba = &baw[i];
		if( ba->n == 0 )	continue;

		ba->p.x /= ba->n;
		ba->p.y /= ba->n;
	}
			

	sp = (short *)im->data;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++, sp++ ){
			if( *sp == 0 )	continue;
			ba = &baw[*sp];

			x = j - ba->p.x;
			y = i - ba->p.y;
			ba->xx += x*x;
			ba->xy += x*y;
			ba->yy += y*y;
		}
	}


	for( i = 0 ; i < nBw ; i++ ){
		ba = &baw[i];
		if( ba->n == 0 )	continue;

		ba->xx /= ba->n;
		ba->xy /= ba->n;
		ba->yy /= ba->n;

		b = &bw[i];
		math_linear_equation2_symtric_eigenvalue( ba->xx, ba->xy, ba->yy,
							  &b->e1, &b->v1, &b->e2 );

		b->p = ba->p;
	}

	free( baw );
}





// A[0][1] = A[1][0]
int
math_linear_equation2_symtric_eigenvalue( float xx, float xy, float yy,
							  float *e1, vec2d *v1, float *e2 )
{
float	a,	b,	c;
float	desc,	t;


	a = xx;
	b = xy;
	c = yy;


	desc = hypot( a-c, 2*b );
	*e1 = ((a+c) + desc ) * 0.5;
	*e2 = ((a+c) - desc ) * 0.5;

	v1->x = -b;
	v1->y = a - *e1;

	t = hypot( v1->x, v1->y);
	v1->x /= t;
	v1->y /= t;

	return( 1 );
}



int
bwLabel_gesture_id( bwLabel_type *bw, int nBw, int T )
{
int	i,	no;
bwLabel_type	*b;

	for( i = 0, no = 0 ; i < nBw ; i++ ){
		b = &bw[i];
		if( b->id != i )	continue;
		if( b->no < T )		continue;

		if( ABS(b->e2) < 60 )	continue;

		if( ABS( b->v1.x ) > ABS(b->v1.y) )
			no += 6;
		else no += 1;
	}

	return( no );
}