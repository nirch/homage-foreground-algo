
#include	<string.h>
#include	<math.h>

#include	"Ulog/Log.h"

//#ifdef _DEBUG
#define _DUMP 
//#endif

#include	"ImageType/ImageType.h"
#include	"ImageDump/ImageDump.h"
#include	"ImageMark/ImageMark.h"
#include	"ImageLabel/ImageLabel.h"
#include	"BnImage/BnImage.h"

#include "UniformBackground.h"

#include "ImageMorphology/ImageMorphology.h"


#define EXCEPTION



void	bImage_smoothTT( image_type *sim, box2i_type *b, int N );





image_type *	bImage_realloc(  box2i_type *b, int n, image_type *bim );

image_type *	bImage_set( image_type *sim, image_type *mim, box2i_type *b, int N, image_type *bim );

image_type *	bImage_set( image_type *sim, box2i_type *b, int N, image_type *bim );


static void	bImage_mask( image_type *bim, image_type *mim, box2i_type *b, int N );



void		bImage_dump( image_type *bim, int N, char *prefix, int index, char *suffix );
image_type *bImage_to_image( image_type *bim, image_type *im );

void		bImage_clear( image_type *bim );


int	bImage_complete( image_type *bim );

image_type *	bImage_grad_x( image_type *bim, image_type *im );

void	bImage_grad_xTT( image_type *bim );


int	bImage_fill( image_type *bim, int a0[], int a1[] );

int	bImage_row( image_type *bim, int a0[], int a1[] );

int	bImage_protraction( image_type *bim, image_type *eim, int a0[], int a1[] );

int	bImage_seg( image_type *bim, image_type *eim, int a[] );


 int	bImage_segC_L( image_type *bim, image_type *eim, int a[], int n );

  int	bImage_segC_R( image_type *bim, image_type *eim, int a[], int n );



int	CUniformBackground::ProcessInitBackground( image_type *sim, image_type *mim )
{
	
	gpTime_start( &m_rTime );

	m_yim = image1_from( sim, m_yim );


//	m_bim = bImage_set( sim, mim,&m_roi, m_N, m_bim );


	m_bim = bImage_set( sim, &m_roi, m_N, m_bim );
	bImage_mask( m_bim, mim, &m_roi, m_N );


	bImage_dump( m_bim, m_N, "bg", 1, "A" );	
	
	//bImage_grad_xTT( m_bim );

	m_bimDx = bImage_grad_x( m_bim, m_bimDx );

#ifdef _DUMP
	image_type *im = image1S_axb(  m_bimDx, 1, 128, NULL );
	IMAGE_DUMP_DUP( im, 8, 1, "bg", 1, "D" );
	image_destroy( im, 1 );
#endif


	int	a0[128],	a1[128];

	bImage_row( m_bim, a0, a1 );

	bImage_segC_L( m_bim, m_bimDx, a0, -5 );
	bImage_segC_R( m_bim, m_bimDx, a1, 5 );

	bImage_protraction( m_bim, m_bimDx, a0, a1 );

	bImage_dump( m_bim, m_N, "bg", 1, "E" );

	bImage_fill( m_bim, a0, a1 );



	bImage_dump( m_bim, m_N, "bg", 1, "F" );


	ProcessBn( sim, 2*m_bnT );
	IMAGE_DUMP_DUP( m_bnImD, 8, 1, "bg", 1, "bn" );

	gpTime_stop( &m_rTime );



	return( 1 );
}










int	bImage_fill_1( image_type *bim );






image_type *
	bImage_set( image_type *sim, image_type *mim, box2i_type *b, int N, image_type *bim )
{
	int	i,	j,	k,	n,	i0,	j0;
	u_char	*sp,	*mp;
	bImage_type *bp,	*bp0;


	bim = bImage_realloc( b, N,  bim );

	bImage_clear( bim );




	for( i = 1, i0 = b->y0 ; i < bim->height-1 ; i++ ){
		bp0 = ( bImage_type *)IMAGE_PIXEL( bim, i, 1 );

		for( k = 0 ; k < N ; k++, i0 += 1 ){

			if( i0 >= sim->height-1 )
				break;

			sp = IMAGE_PIXEL( sim, i0, b->x0 );
			mp = IMAGE_PIXEL( mim, i0, b->x0 );



			for( j = 1, j0 = b->x0, bp = bp0 ; j < bim->width-1 ; j++, j0 += N, bp++ ){
				int n1 = N;
				if( j0 + n1 > sim->width )	n1 = sim->width - j0;

				for( n = 0 ; n < n1 ; n++, sp += 3, mp++ ){
					if( *mp != 0 )
						continue;

					bp->r += sp[0];
					bp->g += sp[1];
					bp->b += sp[2];
					bp->n++;
				}
			}
		}
	}


	bp = ( bImage_type *)bim->data;
	for( i = 0 ; i < bim->height ; i++ ){

		for( j = 0 ; j < bim->width ; j++, bp++ ){
			if( bp->n < 0.5*n*n ){
				bp->n = 0;
				continue;
			}

			bp->r /= bp->n;
			bp->g /= bp->n;
			bp->b /= bp->n;
		}
	}

	return( bim );
}


image_type *
bImage_set( image_type *sim, box2i_type *b, int N, image_type *bim )
{
	int	i,	j,	k,	n,	i0,	j0;
	u_char	*sp;
	bImage_type *bp,	*bp0;


	bim = bImage_realloc( b, N,  bim );

	bImage_clear( bim );



	for( i = 1, i0 = b->y0 ; i < bim->height-1 ; i++ ){
		bp0 = ( bImage_type *)IMAGE_PIXEL( bim, i, 1 );

		for( k = 0 ; k < N ; k++, i0 += 1 ){

			if( i0 >= sim->height-1 )
				break;

			sp = IMAGE_PIXEL( sim, i0, b->x0 );
			
			for( j = 1, j0 = b->x0, bp = bp0 ; j < bim->width-1 ; j++, j0 += N, bp++ ){
				int n1 = N;
				if( j0 + n1 > sim->width )	n1 = sim->width - j0;

				for( n = 0 ; n < n1 ; n++, sp += 3 ){
	
					bp->r += sp[0];
					bp->g += sp[1];
					bp->b += sp[2];
					bp->n++;
				}
			}
		}
	}


	bp = ( bImage_type *)bim->data;
	for( i = 0 ; i < bim->height ; i++ ){

		for( j = 0 ; j < bim->width ; j++, bp++ ){
			if( bp->n == 0 )	continue;

			bp->r /= bp->n;
			bp->g /= bp->n;
			bp->b /= bp->n;

			bp->n = N*N;
		}
	}




	return( bim );
}


static void
bImage_mask( image_type *bim, image_type *mim, box2i_type *b, int N )
{
	int	i,	j,	k,	n,	i0,	j0;
	u_char	*mp;
	bImage_type *bp,	*bp0;


	for( i = 1, i0 = b->y0 ; i < bim->height-1 ; i++ ){
		bp0 = ( bImage_type *)IMAGE_PIXEL( bim, i, 1 );

		for( k = 0 ; k < N ; k++, i0 += 1 ){

			if( i0 >= mim->height-1 )
				break;

			mp = IMAGE_PIXEL( mim, i0, b->x0 );

			for( j = 1, j0 = b->x0, bp = bp0 ; j < bim->width-1 ; j++, j0 += N, bp++ ){
				int n1 = N;
				if( j0 + n1 > mim->width )	n1 = mim->width - j0;

				for( n = 0 ; n < n1 ; n++, mp++ ){
					if( *mp != 0 )
						bp->n--;
				}
			}
		}
	}

	bp = ( bImage_type *)bim->data;
	for( i = 0 ; i < bim->height ; i++ ){

		for( j = 0 ; j < bim->width ; j++, bp++ ){
			if( bp->n != N*N )
				bp->n = 0;
		}
	}
}






image_type *
bImage_realloc(  box2i_type *b, int n, image_type *bim )
{

	int	width,	height,	w,	h;
	width = b->x1 - b->x0;
	w = width/n;
	if( width - w*n > 0.25*n )	w++;

	height = b->y1 - b->y0;
	h = height/n;
	if( height - h*n > 0.25*n )	h++;


	if( bim != NULL && ( bim->width != w + 2 || bim->height != h + 2 )){
		image_destroy( bim, 1 );
		bim = NULL;
	}

	if( bim == NULL )
		bim = image_create( h+2, w+2, sizeof(bImage_type), 1, NULL );




	return( bim );
}



void
bImage_clear( image_type *bim )
{
	int	i,	j;

	bImage_type *bp = (bImage_type *)bim->data;

	for( i = 0 ; i < bim->height ; i++ ){
		for( j = 0 ; j < bim->width ; j++, bp++ ){
			bp->n= 0;
			bp->r = bp->g = bp->b = 0;
		}
	}

}




image_type *
bImage_to_image( image_type *bim, image_type *im )
{
	int	i,	j;

	
	im = image_realloc( im, bim->width-2, bim->height-2, 3, IMAGE_TYPE_U8, 1 );



	bImage_type *bp = (bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	u_char *tp = im->data;
	for( i = 0 ; i < im->height ; i++, bp += 2 ){
		for( j = 0 ; j < im->width ; j++, bp++ ){
			
			if( bp->n == 0 ){
				*tp++ = 0;
				*tp++ = 0;
				*tp++ = 0;
				continue;
			}
			*tp++ = bp->r;
			*tp++ = bp->g;
			*tp++ = bp->b;
		}
	}

	return( im );
}




void
bImage_dump( image_type *bim, int N, char *prefix, int index, char *suffix )
{
#ifdef _DUMP
	image_type *im = bImage_to_image(  bim, NULL );

	IMAGE_DUMP_DUP( im, N, 1,prefix, index, suffix );

	image_destroy( im, 1 );
#endif
}

image_type *	bImage_smooth( image_type *bim, float dT, image_type *im );


void
bImage_smoothTT( image_type *sim, box2i_type *b, int N )
{
	image_type *bim = bImage_set( sim, b, N, NULL );

	bImage_dump( bim, N, "TT", 1, "C" );

	image_type *im = bImage_smooth( bim, 8, NULL );

	IMAGE_DUMP_DUP( im, N, 255, "TT", 1, NULL );

	image_destroy( bim, 1 );

	image_destroy( im, 1 );

}




image_type *
bImage_smooth( image_type *bim, float dT, image_type *im )
{
	int	i,	j,	k;


	im = image_realloc( im, bim->width-2, bim->height-2, 1, IMAGE_TYPE_U8, 1 );


	bImage_type m0,	m1;

	int	a[9];
	a[1] = -bim->width;
	a[0] = a[1]-1;
	a[2] = a[1] + 1;

	a[4] = 0;
	a[3] = a[4]-1;
	a[5] = a[4] + 1;

	a[7] = bim->width;
	a[6] = a[7]-1;
	a[8] = a[7] + 1;


	bImage_type *bp = (bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	u_char *tp = im->data;
	for( i = 0 ; i < im->height ; i++, bp += 2 ){

	
		for( j = 0 ; j < im->width ; j++, bp++, tp++ ){
			m0 = m1 = *bp;
			for( k = 0 ; k < 9 ; k++ ){
				if( k == 4 )	continue;
				bImage_type *b = bp + a[k];

		
				if( b->r < m0.r )
					m0.r = b->r;
				else if( b->r > m1.r )
					m1.r = b->r;

				if( b->g < m0.g )
					m0.g = b->g;
				else if( b->g > m1.g )
					m1.g = b->g;

				if( b->b < m0.b )
					m0.b = b->b;
				else if( b->b > m1.b )
					m1.b = b->b;
			}
		

			if( m1.r - m0.r > dT || m1.g - m0.g > dT || m1.b - m0.b > dT )
				*tp = 0;
			else *tp = 1;
		}
	}


	return( im );
}



void
bImage_grad_xTT( image_type *bim )
{
	

	image_type *bimDx = bImage_grad_x( bim, NULL );


	image_type *im = image1S_axb(  bimDx, 1, 128, NULL );


	IMAGE_DUMP_DUP( im, 8, 1, "bg", 1, "DX" );

	image_destroy( bimDx, 1 );

	image_destroy( im, 1 );

}


image_type *
bImage_grad_x( image_type *bim, image_type *im )
{
	int	i,	j;


	im = image_realloc( im, bim->width-2, bim->height-2, 1, IMAGE_TYPE_U8, 1 );


	int	y[3];
	bImage_type *bp = (bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	char *tp = (char *)im->data;
	for( i = 0 ; i < im->height ; i++, bp += 2 ){

		
		y[0] = IMAGE_RGB2Y( bp->r, bp->g, bp->b );
		bp++;
		y[1] = IMAGE_RGB2Y( bp->r, bp->g, bp->b );
		*tp++ = y[1] - y[0];
		bp++;

		for( j = 1 ; j < im->width-1 ; j++, bp++ ){

			y[2] = IMAGE_RGB2Y( bp->r, bp->g, bp->b );
			
			*tp++ = y[2] - y[0];

			y[0] = y[1];
			y[1] = y[2];
		}

		*tp++ = y[1] - y[0];
	}

	return( im );
}



int
bImage_row( image_type *bim, int a0[], int a1[] )
{
	int	i,	j,	no;
	bImage_type *bp;



	no = 0;

	a0[0] = a1[0] = -1;
	for( i = 1 ; i < bim->height-1 ; i++ ){
		bImage_type *bp0 = ( bImage_type *)IMAGE_PIXEL( bim, i, 0 );

		bp = bp0+1;
		for( j = 1 ; j < bim->width-1 ; j++, bp++ )
			if( bp->n <= 0 )		break;

		if( j >= bim->width-1 ){
			a0[i] = a1[i] = -1;
			continue;
		}

		if( j == 1 )
			a0[i] = -1;
		else a0[i] = j-1;


		 bp = bp0 + bim->width-2;
		for( j = bim->width-2 ; j >= 0 ; j--, bp-- )
			if( bp->n <= 0 )		break;


		if( j ==  bim->width-2 )
			a1[i] = -1;
		else a1[i] = j+1;
	}

	return( 1 );
}





int
bImage_fill( image_type *bim, int a0[], int a1[] )
{
	int	i,	k,	no;
	bImage_type *bp;



	no = 0;
	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 0 );
	for( i = 1 ; i < bim->height-1 ; i++, bp += bim->width ){

		if( a0[i] == -1 && a1[i] == -1 )
			continue;
		
		int	j0,	j1;
		bImage_type *bp0,	*bp1;

		if( a0[i] < 0 ){
			j0 = 0;
			bp0 = bp + a1[i];
		}
		else {
			j0 = a0[i];
			bp0 = bp + a0[i];
		}



		if( a1[i] < 0 ){
			j1 = bim->width-1;
			bp1 = bp0;
		}
		else {
			j1 = a1[i];
			bp1 = bp + a1[i];
		}



		bImage_type *cp;
		for( k = j0 + 1, cp = bp0+1 ; k < j1 ; k++, cp++ ){
			float f = (k - j0)/(float)( j1 - j0 ); 
			cp->r = (1-f) * bp0->r + f* bp1->r;
			cp->g = (1-f) * bp0->g + f* bp1->g;
			cp->b = (1-f) * bp0->b + f* bp1->b;
			cp->n = 1;
		}
	}


	return( 1 );
}


int
bImage_protraction( image_type *bim, image_type *eim, int a0[], int a1[] )
{
	int	i,	j,	no;
	bImage_type *bp;



	no = 0;
	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 0 );
	for( i = 1 ; i < bim->height-1 ; i++, bp += bim->width ){

		if( a0[i] == -1 && a1[i] == -1 )
			continue;

		int	j0,	j1;
		bImage_type *bp0,	*bp1;

	
		j0 = ( a0[i] < 0) ? 0 :  a0[i];
		j1 = ( a1[i] < 0) ? bim->width-1:  a1[i];

	


		
		bImage_type *cp;

		if( j0 > 20 ){
//			j0 -= 10;
			bp0 = bp + j0;
			char *ep = (char *)IMAGE_PIXEL(eim, i-1, j0-1 );

			for( j = j0+1, cp = bp0+1 ; j < j1 ; j++, ep++, cp++ ){
				if( ABS(*ep) > 4)	break;
				cp->n = 1;
			}

			a0[i] = j-1;

			if( j >=  j1 ){
				a0[i] = a1[i] = -1;
				continue;
			}
		}


	
		if( j1 < bim->width-1 - 20 ){
//			j1 += 10;
			bp1 = bp +j1;
			char *ep = (char *)IMAGE_PIXEL(eim, i-1, j1-1 );
			for( j = j1-1, cp = bp1-1 ; j > j0 ; j--, ep--, cp-- ){
				if( ABS(*ep) > 4)	break;
				cp->n = 1;
			}

			a1[i] = j+1;
		}

	}


	return( 1 );
}




typedef struct seg_type {
	int	i0;
	int i1;
//	int r;
//	int g;
//	int b;
	int	y;
	int n;
} seg_type ;


typedef struct segC_type {
	int	j0;
	int j1;

	int y;

	int type;
	int dx;		// max dx;
	int	j;		// index of max dx
	int	av;

	int	n;
} segC_type;









static int	bImage_seg( image_type *bim, image_type *eim, int a[], int n, segC_type as[] );

static int	bImage_seg( segC_type ac[], int nC, seg_type as[], int *nS );

static int	bImage_segC_L( image_type *bim, image_type *eim, segC_type *s0, int i, segC_type *c0, int dk, segC_type *c );
static int	bImage_segC_R( image_type *bim, image_type *eim, segC_type *s0, int i, segC_type *c0, int dk, segC_type *c );


int
bImage_segC_L( image_type *bim, image_type *eim, int a[], int n )
{
	int	i;

	segC_type ac[100]; 
	seg_type as[100];
	int nS = 0;



	bImage_seg( bim, eim, a,  n, ac);


	bImage_seg( ac, bim->height, as, &nS );




	int	k;
	for( i = 0 ; i < nS ; ){
		int i0 = as[i].i1;

		int i1 = (i < nS-1)? as[i+1].i0 : bim->height-1;
		segC_type	c;
		for( k = i0 + 1; k < i1 ; k++ ){
			if( bImage_segC_L( bim, eim,  &ac[k-1], k,  &ac[k], 10, &c ) < 0 )
				break;
			ac[k] = c;
			as[i].i1 = k;
		}

		if( i < nS-1 && k == i1 ){
			as[i].i1 = as[i+1].i1;
			nS--;
			for( k = i+1 ; k < nS ; k++ )
				as[k] = as[k+1];
			continue;
		}
		
		i++;
	}

	for( i = 1 ; i < bim->height - 1 ; i++ ){
		if( a[i] < 0 )	continue;
		a[i] = ac[i].j0;
	}


	for( i = 0 ; i < nS ; i++ ){
		fprintf( stdout, "%d %d   (%d)\n", as[i].i0, as[i].i1, as[i].y );
	}

	return( 1 );
}


int
bImage_segC_R( image_type *bim, image_type *eim, int a[], int n )
{
	int	i;

	segC_type ac[100]; 
	seg_type as[100];
	int nS = 0;



	bImage_seg( bim, eim, a,  n, ac);


	bImage_seg( ac, bim->height, as, &nS );




	int	k;
	for( i = 0 ; i < nS ; ){
		int i0 = as[i].i1;

		int i1 = (i < nS-1)? as[i+1].i0 : bim->height-1;
		segC_type	c;
		for( k = i0 + 1; k < i1 ; k++ ){
			if( bImage_segC_R( bim, eim,  &ac[k-1], k,  &ac[k], 10, &c ) < 0 )
				break;
			ac[k] = c;
			as[i].i1 = k;
		}

		if( i < nS-1 && k == i1 ){
			as[i].i1 = as[i+1].i1;
			nS--;
			for( k = i+1 ; k < nS ; k++ )
				as[k] = as[k+1];
			continue;
		}

		i++;
	}

	for( i = 1 ; i < bim->height - 1 ; i++ ){
		if( a[i] < 0 )	continue;
		a[i] = ac[i].j0;
	}


	for( i = 0 ; i < nS ; i++ ){
		fprintf( stdout, "%d %d   (%d)\n", as[i].i0, as[i].i1, as[i].y );
	}


	return( 1 );
}




static int
	bImage_seg( segC_type ac[], int nC, seg_type as[], int *nS )
{
	int	i;



	*nS = 0;



	seg_type *s;
	for( i = 1; i < nC-1 ;  ){
		if( ac[i].j0 < 0 ){
			i++;
			continue;
		}

		
		if( ABS( ac[i].dx) > 8 || ABS( ac[i].av) > 4 ){
			i++;
			continue;
		}

		s = &as[(*nS)++];
		s->i0 = s->i1 = i;
		s->y = 0;
		s->n = 0;
		for( i = s->i1 ; i < nC-1 ; i++ ){
			if( ABS( ac[i].dx) > 8 || ABS( ac[i].av) > 4 )
				break;

			s->y += ac[i].y;
			s->n ++;
			s->i1 = i;
		}			

		s->y /= s->n;

		if( s->n <= 3 )
			(*nS)--;


	}

	return( 1 );
}



static int	bImage_segC( image_type *bim, image_type *eim, int i, int j0, int n, segC_type *s );


static int
bImage_seg( image_type *bim, image_type *eim, int a[], int n, segC_type as[] )
{
int	i;

	int dj = ( n < 0 ) ? n+1 : 0;
	n = ABS(n);

	for( i = 1 ; i < bim->height-1 ; i++ ){
		segC_type *s  = &as[i];
		if( a[i] < 0  ){
			s->j0  = s->j1 = -1;
			s->type = 0;
			continue;
		}


		bImage_segC( bim, eim, i, a[i]+dj, n, s );
	}

	return( 1 );
}


static int
bImage_segC_L( image_type *bim, image_type *eim, segC_type *s0, int i, segC_type *c0, int dk, segC_type *c )
{
int	k,	j0;


	int j00 = MIN( s0->j0, c0->j0 );
	j00 -= dk;
	if( j00 + s0->n < s0->j0 )	j00 = s0->j0 - s0->n;
	if( j00 < 0 )	j00 = 0;
	
	for( k = 0 ; ; k++ ){
		j0 = c0->j0 - k;
		if( j0 < j00 )	return( -1 );
		
//		if( j0 < 0 || j0 < s0->j0 - d)
//			return( -1 );

//		if( j0 + s0->n < s0->j0 )
//			return( -1 );
		bImage_segC( bim, eim, i, c0->j0-k, c0->n, c );

		if( ABS( c->dx) > 8 || ABS( c->av) > 4 )
			continue;

		int y = c->y - s0->y;
		if( ABS(y) > 10 )
			continue;

		return( k );
	}

	return( -1 );
}


static int
bImage_segC_R( image_type *bim, image_type *eim, segC_type *s0, int i, segC_type *c0, int dk, segC_type *c )
{
	int	k,	j0;


	int j00 = MAX( s0->j0, c0->j0 );
	j00 += dk;
	if( j00 > s0->j0 +s0->n)	j00 = s0->j0 + s0->n;
	if( j00 +s0->n > bim->width-1 )	j00 = bim->width-1 - s0->n;

	for( k = 0 ; ; k++ ){
		j0 = c0->j0 + k;
		if( j0 > j00 )	return( -1 );

		bImage_segC( bim, eim, i, j0, c0->n, c );

		if( ABS( c->dx) > 8 || ABS( c->av) > 4 )
			continue;

		int y = c->y - s0->y;
		if( ABS(y) > 10 )
			continue;

		return( k );
	}

	return( -1 );
}


static int
bImage_segC( image_type *bim, image_type *eim, int i, int j0, int n, segC_type *s )
{
	int	j;
	char *tp;
	int a;


	s->j0 = j0;
	s->j1 = j0 + n-1;

	s->dx = 0;
	s->y = 0;
	a = 0;

	int	k = 0;
	tp = (char *)IMAGE_PIXEL( eim, i-1, s->j0-1 );
	bImage_type *bp = (bImage_type *)IMAGE_PIXEL( bim, i, s->j0 );
	for( j = s->j0 ; j <= s->j1 ; j++, tp++, bp++ ){
		a += *tp;
		if( ABS(*tp) > ABS(s->dx) ){
			s->dx = *tp;
			s->j = j;
		}

		int y = IMAGE_RGB2Y( bp->r, bp->g, bp->b );
		s->y += y;
		k++;
	}

	s->av = a / n;
	s->y /= n;

	s->n = n;
	if( ABS(s->dx ) < 5 || ABS(s->av) < 4 )
		s->type = 1;

	return( 1 );
}
		

