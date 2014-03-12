
#include	<string.h>
#include	<math.h>

#include	"Ulog/Log.h"

#ifdef _DEBUG
#define _DUMP 
#endif

#include	"ImageType/ImageType.h"
#include	"ImageDump/ImageDump.h"
#include	"ImageMark/ImageMark.h"
#include	"ImageLabel/ImageLabel.h"
#include	"BnImage/BnImage.h"

#include "UniformBackground.h"

#include "ImageMorphology/ImageMorphology.h"


#define EXCEPTION






image_type *	bImage_realloc(  box2i_type *b, int n, image_type *bim );

image_type *	bImage_set( image_type *sim, image_type *mim, box2i_type *b, int N, image_type *bim );




void		bImage_dump( image_type *bim, int N, char *prefix, int index, char *suffix );
image_type *bImage_to_image( image_type *bim, image_type *im );

void		bImage_clear( image_type *bim );


int	bImage_complete( image_type *bim );



int	CUniformBackground::ProcessInitBackground( image_type *sim, image_type *mim )
{
	
	gpTime_start( &m_rTime );

	m_yim = image1_from( sim, m_yim );

	m_bim = bImage_set( sim, mim,&m_roi, m_N, m_bim );



	bImage_dump( m_bim, m_N, "cc", 1, "S" );

	bImage_complete( m_bim );

	bImage_dump( m_bim, m_N, "cc", 1, "C" );


	ProcessBn( sim, 2*m_bnT );
	IMAGE_DUMP_DUP( m_bnImD, 8, 1, "cc", 1, "bn" );

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
		}
	}

	return( bim );
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



int	bImage_fill_1( image_type *bim );
int	bImage_fill_row( image_type *bim );



int
bImage_complete( image_type *bim )
{

	//bImage_dump( bim, "aa", 1, "1" );

	//	while( bImage_fill_1( bim ) > 0 );

	bImage_fill_row( bim );


//	bImage_dump( bim, 8, "aa", 1, "fill" );

	return( 1 );
}

int
bImage_fill_1( image_type *bim )
{
	int	i,	j,	n,	k,	no;
	bImage_type *bp;



	no = 0;
	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	for( i = 1 ; i < bim->height-1 ; i++, bp += 2 ){


		for( j = 1 ; j < bim->width-1 ; j++, bp++ ){
			if( bp->n > 0 )		continue;
			bp->r = bp->g = bp->b = 0;
			bImage_type *sp = bp - bim->width -1;
			for( k = 0; k < 3 ; k++, sp += bim->width-3 ){
				for( n = 0; n < 3 ; n++, sp++ ){
					if( sp == bp || sp->n == 0 || sp->n & 0x10000 )
						continue;

					bp->n += sp->n;
					bp->r += sp->n*sp->r;
					bp->g += sp->n*sp->g;
					bp->b += sp->n*sp->b;
				}
			}


			if( bp->n == 0 )
				continue;

			bp->r /= bp->n;
			bp->g /= bp->n;
			bp->b /= bp->n;
			bp->n = 0x10001;

			no++;
		}
	}



	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	for( i = 1 ; i < bim->height-1 ; i++, bp += 2 ){
		for( j = 1 ; j < bim->width-1 ; j++, bp++ )
			bp->n &= 0xffff;
	}

	return( no );
}



int
	bImage_fill_row( image_type *bim )
{
	int	i,	j,	k,	no;
	bImage_type *bp;



	no = 0;
	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	for( i = 1 ; i < bim->height-1 ; i++, bp += 2 ){


		for( j = 1 ; j < bim->width-1 ; j++, bp++ ){
			if( bp->n > 0 )		continue;

			int j0 = j-1;
			bImage_type *bp0 = bp-1;
			for( ; j < bim->width-1 ; j++, bp++ )
				if( bp->n >  0 )		break;
			

			bImage_type *bp1 = bp;
			if( j >= bim->width-1 )
				bp1 = bp0;

			if( j0 == 0 )
				bp0 = bp1;

			bImage_type *cp;
			for( k = j0 + 1, cp = bp0+1 ; k < j ; k++, cp++ ){
				float f = (k - j0)/(float)( j - j0 ); 
				cp->r = (1-f) * bp0->r + f* bp1->r;
				cp->g = (1-f) * bp0->g + f* bp1->g;
				cp->b = (1-f) * bp0->b + f* bp1->b;
				cp->n = 1;

			}
		}
	}


	return( no );
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





