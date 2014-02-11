//  Defines the entry point for the console application.
//
#include	<string.h>
#include	<math.h>

#ifdef _DEBUG
#define _DUMP
#endif

#include "ImageType/ImageType.h"
#include "ImageDump/ImageDump.h"

#include "BnImage.h"

#include	"DynamicBackground.h"


static int	bnImage_update_edge( image_type *eim, image_type *eim1, image_type *gvar );

static image_type *	bnImage_edge_compare( image_type *eim, image_type *ebim, image_type *gim );



void
CDynamicBackground::DbEdgeMotion( image_type *sim )
{

	imageA_icycle( m_eIm, m_tNo+1 );
	m_eIm[0] = image1_gridient_sobol_value( sim, m_eIm[0] );


	m_eBim = image1_gridient_sobol_value( m_bim, m_eBim );


	if( m_eIm[m_tNo] != NULL )
		bnImage_update_edge( m_eIm[0], m_eIm[m_tNo], m_gvar );


	m_gim = bnImage_edge_compare( m_eIm[0], m_eBim, m_gim );
}


image_type *
CDynamicBackground::GetDbEdgeImage( image_type *im )
{

	im = image1_sub( m_eIm[0], m_eBim, NULL );

	return( im );
}


static int
bnImage_update_edge( image_type *eim, image_type *eim1, image_type *gvar )
{
bn_type	*gv;
int	i,	j,	i0,	j0,	k,	n;
int	sum,	no,	d;



	int	align = eim->width - 10;

	gv = ( bn_type*)gvar->data;

	for( i = 1, i0 = 8, no = 0 ; i < gvar->height-1 ; i++, i0 += 8 ){
		gv = ( bn_type*)IMAGE_PIXEL( gvar, i, 1 );
		
	
		for( j = 1, j0 = 8 ; j < gvar->width-1 ; j++, j0 += 8, gv++ ){

			if( gv->flag == 0 ){
				continue;
			}

			
			u_char *sp0 = (u_char *)IMAGE_PIXEL( eim, i0-1, j0-1 );
			u_char *sp1 = (u_char *)IMAGE_PIXEL( eim1, i0-1, j0-1 );

			no = 0;
			sum = 0;
			for( k = 0 ; k < 10 ; k++, sp0 += align, sp1 += align )
				for( n = 0 ; n < 10 ; n++, sp0++, sp1++ ){
					d = *sp0 - *sp1;
					if( d < 0 )	d = -d;
					if( d > 10 ){
						sum += d;
						no++;
					}
				}

			if( no > 4 )
				gv->flag = 0;
		}
	}

	return( no );
}

//#define ECC_0		0x00
//#define ECC_BG		0x01
//#define ECC_FR		0x02
//#define ECC_MIX		0x04

static image_type *
bnImage_edge_compare( image_type *eim, image_type *ebim, image_type *gim )
{
int	i,	j,	align;
int	k,	n,	tmp;

	gim = image_recreate( gim, eim->height/8, eim->width/8, 1, 1 );

	align = eim->width - 8;


	for( i = 0 ; i < gim->height ; i++ ){
		u_char *gp = IMAGE_PIXEL( gim, i, 0 );

		for( j = 0 ; j < gim->width ; j++,  gp++ ){

			u_char *sp = IMAGE_PIXEL( eim, i*8, j*8 );
			u_char *bp = IMAGE_PIXEL( ebim, i*8, j*8 );
	


			int	nS,	nB,	nSB,	nSB_w;
			nS = nB = nSB = nSB_w = 0;
			for( k = 0 ; k < 8 ; k++, sp += align, bp += align ){
				for( n = 0 ; n < 8 ; n++ ){
					tmp = (*sp) - (*bp);

					if( *sp > 10 )	nS++;
					if( *bp > 10 )	nB++;

					if( !(*sp > 10 && *bp > 10 && ABS(tmp) < 24 || ABS( tmp) < 10) ){

						if( tmp > 0 )	nSB_w++;
						nSB++;
					}


					sp++;
					bp++;
				}
			}


			if( nS < 2 && nB < 2 ){
				*gp = ECC_0;
				continue;
			}

			int nM = MAX( nS, nB );
//			if( (nS > 16 || nB > 16 ) && nSB < 5 || (nS > 10 || nB > 10 ) && nSB < 3 ){
//			if( nM > 16 && nSB < 5 || nM > 10 && nSB < 3 || nM > 5 && nSB < 0 ){
			if( nM >= 4 && nM > 3 * nSB ){


				*gp = ECC_BG;
				continue;
			}



			if( nSB_w > 10 || nSB - nSB_w < 2 && nSB_w > 5 ){
				*gp = ECC_FR;
				continue;
			}


			if( nS < 4 && nB < 4 ){
				*gp = ECC_0;
				continue;
			}


			*gp = ECC_MIX;

		}
	}


	return( gim );
}