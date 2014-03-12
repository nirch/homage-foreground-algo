
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


void	image3_histogram_RGB( image_type *sim, image_type *mim, int *r, int *g, int *b );


typedef	struct bImage_type {
	int n;
	int	r;
	int g;
	int b;
} bImage_type;	


image_type *	bImage_realloc(  box2i_type *b, int n, image_type *bim );

image_type *	bImage_set( image_type *sim, image_type *mim, box2i_type *b, int n, image_type *bim );

image_type *	bImage_set( image_type *sim, box2i_type *b, int N, image_type *bim );


image_type *	bImage_to_image( image_type *bim, image_type *im );

image_type *	bImage_diff( image_type *sim, box2i_type *b, int N, image_type *bim, int T, image_type *im );

void		bImage_dump( image_type *bim, int N, char *prefix, int index, char *suffix );

void		bImage_clear( image_type *bim );

int			bImage_update( image_type *bim, image_type *cim, float T );


int			bImage_bnMask( image_type *bim, image_type *bnIm );


int	bImage_complete( image_type *bim );




CUniformBackground::CUniformBackground()
{


	m_cim = NULL;

	m_dim = NULL;

	m_bim = NULL;

	m_bimC = NULL;

	m_N = 8;

	m_T = 24;

	m_bT = 8;
	m_bnT = 12;
	

	m_yim = NULL;
	m_eim = NULL;
	m_bnIm = NULL;
	m_bnImD = NULL;

	m_cim8 = NULL;

	m_abw = NULL;

	m_abwC = NULL;

	m_cln = NULL;

	m_fpl = plnF_alloc( 1000 );

	gpTime_init( &m_rTime );
	gpTime_init( &m_tCompare );
	gpTime_init( &m_tUpdate );
	gpTime_init( &m_gTime );

	gpTime_init( &m_tBn );
	gpTime_init( &m_tCln );
}


CUniformBackground::~CUniformBackground()
{
	DeleteContents();

}



void CUniformBackground::DeleteContents()
{

	//if( m_him != NULL ){
	//	image_destroy( m_him, 1 );
	//	m_him = NULL;
	//}

	if( m_cln != NULL ){
		cln_destroy( m_cln );
		m_cln = NULL;
	}
}



void	CUniformBackground::SetRoi( box2i_type *b )
{
	m_roi = *b;
}


int	CUniformBackground::ProcessHistogram( image_type *sim, image_type *mim )
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






int	CUniformBackground::Process( image_type *sim, int iFrame, image_type **cim )
{
	m_iFrame = iFrame;

	gpTime_start( &m_gTime );


#ifdef EXCEPTION
	try {
#endif


	m_yim = image1_from( sim, m_yim );

	ProcessCompare( sim, cim );

	ProcessNN( 8 );
//	ProcessNN( 4 );


	image1_convolution_guasian( m_cim, 0.75, m_cim );
	*cim = m_cim;

	ProcessContour();


	ProcessBn( sim, m_bnT );

	gpTime_start( &m_tUpdate );
	ProcessUpdate( sim );
	gpTime_stop( &m_tUpdate );



	gpTime_stop( &m_gTime );


#ifdef EXCEPTION
	}

	catch (...) {
		return( -1 );
	}
#endif


	return( 1 );
}



int	CUniformBackground::ProcessCompare( image_type *sim, image_type **cim )
{

	gpTime_start( &m_tCompare );


//	m_cim = image_realloc( m_cim, sim->width, sim->height, 1, IMAGE_TYPE_U8, 1 );

	m_dim = bImage_diff( sim,  &m_roi, m_N, m_bim, m_T, m_dim );

//	m_cim = bImage_diff( sim,  &m_roi, m_N, m_bim, m_T, m_cim );
	m_cim = image1_binaryM( m_dim, m_T, m_cim );



	if( m_iFrame == m_dFrame ){
		bImage_dump( m_bim, m_N, "bim", m_iFrame, "B" );
		IMAGE_DUMP( sim, "m", m_iFrame, "SIM" );
		IMAGE_DUMP( m_cim, "m", m_iFrame, "1" );
	}




	image1_remove_blobM( m_cim, 255, 100*100, 1, 0 );

//	image1_close( m_cim, 2, 255 );

	if( m_iFrame == m_dFrame ){
		IMAGE_DUMP( m_cim, "m", m_iFrame, "3" );
	}



//	image1_fill_blobV( m_dim, m_cim, 255, 100*100, 4, m_T*0.5, 255 );

	ProcessFillHole();

	if( m_iFrame == m_dFrame ){
		IMAGE_DUMP( m_cim, "m", m_iFrame, "4" );
	}



	image1_open( m_cim, 1, 0 );


	if( m_iFrame == m_dFrame ){
		IMAGE_DUMP( m_cim, "m", m_iFrame, "2" );
	}



	gpTime_stop( &m_tCompare );


	return( 1 );
}




void CUniformBackground::Trace( FILE *fp )
{
	gpTime_print( fp, "Calibrate", &m_rTime );
	gpTime_print( fp, "Compare", &m_tCompare );
	gpTime_print( fp, "Update", &m_tUpdate );

	gpTime_print( fp, "Bn-dd", &m_tBn );

	gpTime_print( fp, "Contour", &m_tCln );

	gpTime_print( fp, "UniformBackground", &m_gTime );


}



int	CUniformBackground::ProcessBn( image_type *sim, float bnT )
{

	gpTime_start( &m_tBn );

//	m_yim = image1_from( sim, m_yim );
	m_bnIm = bnImage_average4( m_yim, m_bnIm );

	m_bnImD = bnImage_dd( m_bnIm, bnT, m_bnImD );

	gpTime_stop( &m_tBn );

	return( 1 );
}

int	bImage_fill_1( image_type *bim );

int	CUniformBackground::ProcessUpdate( image_type *sim )
{
	m_bimC = bImage_set( sim, m_cim, &m_roi, m_N, m_bimC );


	if( m_bnImD != NULL )
		bImage_bnMask( m_bimC, m_bnImD );

//	bImage_fill_1( m_bimC );

	bImage_update( m_bim, m_bimC, m_bT );

	if( m_iFrame >= m_dFrame-2 && m_iFrame <= m_dFrame +2)
		bImage_dump( m_bim, m_N, "bim", m_iFrame, NULL );


//	bImage_complete( m_bim );

	return( 1 );
}





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


	// bImage_clear( bim );


	//bImage_type *bp = (bImage_type *)bim->data;

	//for( i = 0 ; i < bim->height ; i++ ){
	//	for( j = 0 ; j < bim->width ; j++, bp++ ){
	//		bp->n= 0;
	//		bp->r = bp->g = bp->b = 0;
	//	}
	//}

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



image_type *
bImage_diff( image_type *sim, box2i_type *b, int N, image_type *bim, int T, image_type *im )
{
	int	i,	j,	k,	n,	i0;
	u_char	*sp,	*tp;
	bImage_type *bp,	*bp0;


	im = image_realloc( im, sim->width, sim->height, 1, IMAGE_TYPE_U8, 1 );
	image1_const( im, 0 );


	for( i = 1, i0 = b->y0 ; i < bim->height-1 ; i++ ){
		bp0 = ( bImage_type *)IMAGE_PIXEL( bim, i, 1 );

		for( k = 0 ; k < N ; k++, i0 += 1 ){

			if( i0 >= sim->height )
				break;

			sp = IMAGE_PIXEL( sim, i0, b->x0 );
			tp = IMAGE_PIXEL( im, i0, b->x0 );


			for( j = 1, bp = bp0 ; j < bim->width-1 ; j++, bp++ ){
				for( n = 0 ; n < N ; n++, tp++ ){
	
					int dr = *sp++ - bp->r;
					int dg = *sp++ - bp->g;
					int db = *sp++ - bp->b;

					int d = ABS(dr);
					if( dg < 0 )	dg = -dg;
					if( d < dg )	d = dg;

					if( db < 0 )	db = -db;
					if( d < db )	d = db;


					//if( d < T )
					//	*tp = 0;
					//else *tp = 255;

					*tp = d;
				}
			}
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


int	bImage_update_1( image_type *bim, image_type *cbim );


int
bImage_update( image_type *bim, image_type *cim, float T )
{
	int	i,	j,	no;
	bImage_type *bp,	*cp;




	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	cp = ( bImage_type *)IMAGE_PIXEL( cim, 1, 1 );
	for( i = 1 ; i < bim->height-1 ; i++, bp += 2, cp += 2 ){

		for( j = 1 ; j < bim->width-1 ; j++, bp++, cp++ ){
			if( cp->n == 0 )		continue;

			int dr = cp->r - bp->r;
			int dg = cp->g - bp->g;
			int db = cp->b - bp->b;

			int d = ABS(dr);
			if( dg < 0 )	dg = -dg;
			if( d < dg )	d = dg;

			if( db < 0 )	db = -db;
			if( d < db )	d = db;


			if( d < T )
				cp->n = 1;
			else	cp->n = 0;

		}
	}



	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	cp = ( bImage_type *)IMAGE_PIXEL( cim, 1, 1 );
	for( i = 1, no = 0 ; i < bim->height-1 ; i++, bp += 2, cp += 2 ){
		bImage_type *cp0 = cp - bim->width;
		bImage_type *cp1 = cp + bim->width;

		for( j = 1 ; j < bim->width-1 ; j++, bp++, cp++, cp0++, cp1++ ){
			if( cp->n  == 0 )		continue;

			//int n =  (cp0-1)->n + (cp0)->n + (cp0+1)->n +
			//	     (cp-1)->n  + (cp)->n  + (cp+1)->n  +
			//	     (cp1-1)->n + (cp1)->n + (cp1+1)->n;

			//
			//if( n != 9 )	continue;

			bp->r = cp->r;
			bp->g = cp->g;
			bp->b = cp->b;

			bp->n = 1;

			no++;
		}
	}



	bImage_update_1( bim, cim );
	
//	fprintf( stdout, "%d", no );
	return( no );
}



int
bImage_bnMask( image_type *bim, image_type *bnIm )
{
	int	i,	j;
	bImage_type *bp;



	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	u_char	*mp = bnIm->data;
	for( i = 1 ; i < bim->height-1 ; i++, bp += 2 ){

		for( j = 1 ; j < bim->width-1 ; j++, bp++, mp++ ){
			if( *mp != 0 )
				bp->n = 0;
		}
	}

	return( 1 );
}


int
bImage_update_1( image_type *bim, image_type *cbim )
{
	int	i,	j,	n,	k,	no;
	bImage_type *bp,	*cp;



	no = 0;
	bp = ( bImage_type *)IMAGE_PIXEL( bim, 1, 1 );
	cp = ( bImage_type *)IMAGE_PIXEL( cbim, 1, 1 );
	for( i = 1 ; i < bim->height-1 ; i++, bp += 2, cp += 2 ){


		for( j = 1 ; j < bim->width-1 ; j++, bp++, cp++ ){
			if( cp->n > 0 )		continue;

			bImage_type p;
			p.n = p.r = p.g = p.b = 0;

			bImage_type *sp = cp - bim->width -1;
			for( k = 0; k < 3 ; k++, sp += bim->width-3 ){
				for( n = 0; n < 3 ; n++, sp++ ){
					if( sp->n == 0 )
						continue;

					p.n += 1;
					p.r += sp->r;
					p.g += sp->g;
					p.b += sp->b;
				}
			}


			if(p.n == 0 )
				continue;

			p.r /= p.n;
			p.g /= p.n;
			p.b /= p.n;

			bp->r = p.r;
			bp->g = p.g;
			bp->b = p.b;
			



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



static image_type *	image1_nn( image_type *sim, int N, image_type *im );

static void	image1_nn1( image_type *im, int N );

static void	image1_nn2( image_type *im );

static void	image1_nn_clear( image_type *sim, int N, image_type *im );



int	CUniformBackground::ProcessNN( int N )
{
//int	N;
//	N = 8;

	m_cim8 = image1_nn( m_cim, N, m_cim8 );

	if( m_iFrame == m_dFrame ){
		IMAGE_DUMP_DUP( m_cim8, N, 1, "m", m_iFrame, "d2-1" );
	}


	image1_nn1( m_cim8, N );

	if( m_iFrame == m_dFrame ){
		IMAGE_DUMP_DUP( m_cim8, N, 1, "m", m_iFrame, "d2-2" );
	}

	if( N == 4 ){
//		image1_nn2( m_cim8 );
		image1_remove_blobM( m_cim8, 0x40, 10, 1, 0x40 );
	}
	else
		image1_remove_blobM( m_cim8, 0x80, 10, 1, 0x40 );

	if( m_iFrame == m_dFrame ){
		IMAGE_DUMP_DUP( m_cim8, N, 1, "m", m_iFrame, "d2-3" );
	}
	
	image1_nn_clear( m_cim, N, m_cim8 );

	if( m_iFrame == m_dFrame ){
		IMAGE_DUMP( m_cim, "m", m_iFrame, "d2" );
	}



	return( 1 );
}



static image_type *
image1_nn( image_type *sim, int N, image_type *im )
{
	u_char	*sp;
	int	i,	j,	k,	n,	s;


	int width = (sim->width+N-1)/N ;
	int	height = ( sim->height+N-1)/N;


	im = image_realloc( im, width, height, 1, IMAGE_TYPE_U8, 1 );
	image1_const( im, 0 );


	u_char *tp = im->data;
	for( i = 0 ; i < sim->row ; i += N ){
		

		u_char *sp0 = IMAGE_PIXEL( sim, i, 0 );
		int k1 = ( i + N < sim->height )? N : sim->height - i;
		for( j = 0 ; j < sim->column ; j += N, sp0 += N, tp++ ){

			int n1 = ( j + N < sim->width )? N : sim->width - j;
			int align = sim->width - n1;
			for( k = 0, sp = sp0, s = 0 ; k < k1 ; k++, sp += align )
				for( n = 0 ; n < n1 ; n++, sp++ ){
					if( *sp != 0 )	s++;
				}

			*tp = s;
		}
	}


	return( im );
}



static void
image1_nn1( image_type *im, int N )
{

	int	i,	j;


	int	N1 = 0.75*N*N;
	int	N2 = 0.75 *N *N;
	u_char *sp = IMAGE_PIXEL( im, 1, 1 );
	for( i = 1 ; i < im->row-1 ; i++, sp += 2 ){
		u_char *sp0 = sp - im->width;
		u_char *sp1 = sp + im->width;

		for( j = 1 ; j < im->column-1 ; j ++, sp++, sp0++, sp1++ ){
			if( *sp == 0 )	continue;

			if( (*sp&0x7F) < N2 )	continue;
				
			int n = ((*(sp0-1)&0x7F) > N1)  +   ((*(sp0)&0x7F) > N1) + ((*(sp0+1)&0x7F) > N1 ) + 
				 ((*(sp-1 )&0x7F) > N1)  +   ((*(sp )&0x7F) > N1) + ((*(sp+1 )&0x7F) > N1 ) + 
				 ((*(sp1-1)&0x7F) > N1)  +   ((*(sp1)&0x7F) > N1) + ((*(sp1+1)&0x7F) > N1 ) ;

			if( n < 5 )
				continue;

			if( *(sp0-1) != 0 )
				*(sp0-1) |= 0x80;
			if( *(sp0) != 0 )
				*(sp0  ) |= 0x80;
			if( *(sp0+1) != 0 )
				*(sp0+1) |= 0x80;
			
			if( *(sp-1) != 0 )
				*(sp-1) |= 0x80;
			if( *(sp) != 0 )
				*(sp  ) |= 0x80;
			if( *(sp+1) != 0 )
				*(sp+1) |= 0x80;

			if( *(sp1-1) != 0 )
				*(sp1-1) |= 0x80;
			if( *(sp1) != 0 )
				*(sp1  ) |= 0x80;
			if( *(sp1+1) != 0 )
				*(sp1+1) |= 0x80;
		}
	}
}

static void
image1_nn2( image_type *im )
{
	int	i,	j;

	u_char *sp = IMAGE_PIXEL( im, 1, 1 );
	for( i = 1 ; i < im->row-1 ; i++, sp += 2 ){
		u_char *sp0 = sp - im->width;
		u_char *sp1 = sp + im->width;

		for( j = 1 ; j < im->column-1 ; j ++, sp++, sp0++, sp1++ ){
			if( *sp == 0 || *sp >= 0x80 )	continue;

			int n = *(sp0-1) | *(sp0) | *(sp0+1) | 
				 *(sp-1) | *(sp+1) |
				  *(sp1-1) | *(sp1) | *(sp1+1);

			if( n & 0x80 )
				*sp |= 0x40;
		}
	}
}



static void
image1_nn_clear( image_type *sim, int N, image_type *im )
{
	u_char	*sp;
	int	i,	j,	k,	n;




	u_char *tp = im->data;
	for( i = 0 ; i < sim->row ; i += N ){

		u_char *sp0 = IMAGE_PIXEL( sim, i, 0 );
		int k1 = ( i + N < sim->height )? N : sim->height - i;
		for( j = 0 ; j < sim->column ; j += N, sp0 += N, tp++ ){

			if( *tp == 0 || (*tp >= 0x80 ) )
				continue;

			*tp = 0;

			int n1 = ( j + N < sim->width )? N : sim->width - j;
			int align = sim->width - n1;
			for( k = 0, sp = sp0 ; k < k1 ; k++, sp += align )
				for( n = 0 ; n < n1 ; n++, sp++ ){
					*sp = 0;
				}
		}
	}
}