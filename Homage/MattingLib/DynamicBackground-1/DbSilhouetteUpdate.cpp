//  Defines the entry point for the console application.
//
#include	<string.h>
#include	<math.h>

#ifdef _DEBUG
//#define _DUMP
#endif

#include "ImageType/ImageType.h"
#include "ImageDump/ImageDump.h"
#include "ImageMorphology/ImageMorphology.h"
#include "Imagelabel/BwLabel.h"

#define DIFF_THRESH 10// 12


#include	"DynamicBackground.h"

#define		NCC_SMOOTH	0x10
#define		NCC_BG		0x20
#define		NCC_FR		0x40
#define		NCC_EDGE	0x48


//static image_type *dEim = NULL;
//static image_type *gNim = NULL;


static image_type *	image3_ncc( image_type *sim, image_type *bim, image_type *mim, image_type *nim );

static image_type *	image1_ncc( image_type *sim, image_type *bim, image_type *mim, image_type *nim );

static image_type *	image1_ncc_T( image_type *sim, image_type *im );

static image_type *	image1_ncc_T1( image_type *sim, image_type *im );

static void	image1_ncc_T1_SMOOTH( image_type *sim, image_type *nim );


static void	image1_ncc_open( image_type *sim );

static image_type *	image1_maskT( image_type *sim, image_type *mim );

static image_type *	image1_mask1( image_type *sim, image_type *mim );

static void	image1_ncc_neighbor( image_type *sim );

static void	image1_ncc_end( image_type *gnim, image_type *nim );




static void	image1_ncc_update_edge( image_type *sim, image_type *bim, image_type *nim );

static void	image1_ncc_neighbor_BG( image_type *sim );

static void	image1_ncc_update_edgeN( image_type *gim, image_type *gNim );



static void	image1_ncc_0x4_dilate_1( image_type *sim );


static void	image1_ncc_final( image_type *sim, image_type *nccIm );





#define		F0	300
#define		F1	305


void
CDynamicBackground::produceSilhouetteUpdate( image_type *rgbSim, image_type *sim, image_type *sim4, image_type *mim )
{
image_type *gNim = NULL;

	if( m_rgbBim == NULL )
		return;

	m_nccIm = image3_ncc( rgbSim, m_rgbBim, mim, m_nccIm );


	gNim = image1_ncc_T1( m_nccIm, gNim );


	image1_ncc_T1_SMOOTH( gNim, m_nccIm );


	image1_ncc_neighbor( gNim );


//	image1_ncc_update_edge(  sim, m_bim, gNim );
	if( m_gim != NULL ){
		image1_ncc_update_edgeN(  m_gim, gNim );
		image1_ncc_neighbor_BG( gNim );
		image1_ncc_neighbor_BG( gNim );
	}



	if( m_iFrame > F0  && m_iFrame < F1 ){
		IMAGE_DUMP_DUP( m_nccIm, 8, 1, "E", m_iFrame, "nim" );
	}




	image1_ncc_end( gNim, m_nccIm );


	if( m_iFrame > F0  && m_iFrame < F1 ){
		IMAGE_DUMP_DUP( m_nccIm, 8, 1, "E", m_iFrame, "nim-end" );
		IMAGE_DUMP_DUP( gNim, 8, 2, "E", m_iFrame, "gnim-end" );
	}


//	image1_ncc_open( m_nccIm );
//


	image1_ncc_0x4_dilate_1( m_nccIm );
	image1_ncc_0x4_dilate_1( m_nccIm );


	image1_ncc_final( mim, m_nccIm );

	image_destroy( gNim, 1 );
}



static image_type *
image3_ncc( image_type *sim, image_type *bim, image_type *mim, image_type *nim )
{
	u_char	*mp,	*sp,	*bp,	*np;
	int	i,	j,	n,	k,	align;

	int	av[3];

	align = 3*(sim->width - 8);


	nim = image_recreate( nim, mim->height, mim->width, 1, 1 );


	for( i = 0 ; i < mim->height ; i++ ){

		mp = IMAGE_PIXEL( mim, i, 0 );
		np = IMAGE_PIXEL( nim, i, 0 );

		for( j = 0 ; j < mim->width ; j++, mp++, np++ ){
			if( *mp == 0 ){
				*np = 0;
				continue;
			}


			sp = IMAGE_PIXEL( sim, i*8, j*8 );
			bp = IMAGE_PIXEL( bim, i*8, j*8 );

			av[0] = av[1] = av[2] = 0;
			for( k = 0 ; k < 8 ; k++, sp += align, bp += align ){
				for( n = 0 ; n < 8 ; n++ ){
					av[0] += *sp++ - *bp++;
					av[1] += *sp++ - *bp++;
					av[2] += *sp++ - *bp++;
				}
			}

			av[0] = av[0] >> 6;
			av[1] = av[1] >> 6;
			av[2] = av[2] >> 6;


			int	a0,	a1,	a2,	a,	d;

			a0 = av[0] - 8;
			a1 = -av[0]  - 24;
			a = MAX( a0, a1 );
			d = av[0];


			a0 = av[1] - 8;
			a1 = -av[1]  - 24;
			a2 = MAX( a0, a1 );
			if( a2 > a ){
				d = av[1];
				a = a2;
			}


			a0 = av[2] - 8;
			a1 = -av[2]  - 24;
			a2 = MAX( a0, a1 );
			if( a2 > a ){
				d = av[2];
				a = a2;
			}

//			int d = av[0];
//			if( av[1] > d )	d = av[1];
//			if( av[2] > d )	d = av[2];


			*np = d + 128;
		}
	}


	return( nim );
}



static image_type *
image1_ncc( image_type *sim, image_type *bim, image_type *mim, image_type *nim )
{
	u_char	*mp,	*sp,	*bp,	*np;
	int	i,	j,	n,	k,	align;
	int	av;

	align = sim->width - 8;


	nim = image_recreate( nim, mim->height, mim->width, 1, 1 );


	for( i = 0 ; i < mim->height ; i++ ){

		mp = IMAGE_PIXEL( mim, i, 0 );
		np = IMAGE_PIXEL( nim, i, 0 );

		for( j = 0 ; j < mim->width ; j++, mp++, np++ ){
			if( *mp == 0 ){
				*np = 0;
				continue;
			}


			sp = IMAGE_PIXEL( sim, i*8, j*8 );
			bp = IMAGE_PIXEL( bim, i*8, j*8 );

			av = 0;
			for( k = 0 ; k < 8 ; k++, sp += align, bp += align ){
				for( n = 0 ; n < 8 ; n++ ){
					av += *sp++ - *bp++;
				}
			}

			av = av >> 6;

			*np = av + 128;
		}
	}


	return( nim );
}




static void
image1_ncc_open( image_type *sim )
{
image_type	*mim;

	mim = image1_maskT( sim, NULL );


	image1_dilate( mim, 3 );

	image1_mask( sim, mim, sim );

}


static image_type *
image1_maskT( image_type *sim, image_type *mim )
{
	u_char	*sp,	*mp;
	int	i,	j;

	mim = image_recreate( mim, sim->height, sim->width, 1, 1 );

	sp = (u_char *)sim->data;
	mp = mim->data;

	for( i = 0 ; i < sim->row ; i++ ){
		for( j = 0 ; j < sim->column ; j++, sp++, mp++ ){

			*mp = ( *sp < 255)? 0 : 1;
		}
	}

	return( mim );
}



static image_type *
image1_ncc_T1( image_type *sim, image_type *im )
{
	u_char	*sp,	*tp;
	int	i,	j;



	im = image_recreate( im, sim->height, sim->width, 1, 1 );

	sp = sim->data;
	tp = im->data;
	for( i = 0 ; i < im->height ; i++ ){

		for( j = 0 ; j < im->width ; j++, sp++, tp++ ){

			if( *sp == 0 ){
				*tp = 0x01;
				continue;
			}

			if( *sp >  128 + 8 || *sp < 128 - 24 ){
				*tp = 0x04;
				continue;
			}

			*tp = 0x02;
		}
	}

	return( im );
}


static void
image1_ncc_T1_SMOOTH( image_type *sim, image_type *nim )
{
u_char	*sp,	*sp0,	*sp1,	*np;
int	i,	j;
int	no;


	for( i = 1, no = 0 ; i < sim->row-1 ; i ++ ){
		sp = IMAGE_PIXEL( sim, i, 1 );
		sp0 = sp - sim->width;
		sp1 = sp + sim->width;

		np = IMAGE_PIXEL( nim, i, 1 );


		for( j = 1 ; j < sim->column-1 ; j ++, sp++, sp0++, sp1++, np++ ){ 
			if( (*sp & 0x04) == 0  )	continue;

			if( *np >  128 + 12 || *np < 128 - 32 )
				continue;

			int flag =	*(sp0-1) | *(sp0) | *(sp0+1) | 
				*(sp0-1) | *(sp+1) | 
				*(sp1-1) | *(sp1) | *(sp1+1);



			if( (flag & 0x4 ) == 0 )
				*sp = (*sp & (~0x04) ) | 0x2;
		}
	}
}


static void
image1_ncc_neighbor( image_type *sim )
{
u_char	*sp,	*sp0,	*sp1;
int	i,	j;
int	no;


	for( i = 1, no = 0 ; i < sim->row-1 ; i ++ ){
		sp = IMAGE_PIXEL( sim, i, 1 );
		sp0 = sp - sim->width;
		sp1 = sp + sim->width;

	
		for( j = 1 ; j < sim->column-1 ; j ++, sp++, sp0++, sp1++ ){ 
			if( *sp == 0x01 )	continue;
		
			int flag =	*(sp0-1) | *(sp0) | *(sp0+1) | 
					*(sp0-1) | *(sp+1) | 
					*(sp1-1) | *(sp1) | *(sp1+1);



			if( *sp == 0x4 && (flag & (0x02|0x01)) )
				*sp |= 0x8;

			if( *sp == 0x2 && (flag & (0x04|0x01)) )
				*sp |= 0x8;
		}
	}
}



static void
image1_ncc_neighbor_BG( image_type *sim )
{
	u_char	*sp,	*sp0,	*sp1;
	int	i,	j;
	int	no;


	for( i = 1, no = 0 ; i < sim->row-1 ; i ++ ){
		sp = IMAGE_PIXEL( sim, i, 1 );
		sp0 = sp - sim->width;
		sp1 = sp + sim->width;

		for( j = 1 ; j < sim->column-1 ; j ++, sp++, sp0++, sp1++ ){ 
			if( *sp == 0x01 )	continue;

			int flag =	*(sp0-1) | *(sp0) | *(sp0+1) | 
				*(sp0-1) | *(sp+1) | 
				*(sp1-1) | *(sp1) | *(sp1+1);


			if( (*sp & NCC_SMOOTH) && (*sp & 0x02 ) && (flag & NCC_BG) )
				*sp |= 0x80;
		}
	}


	for( i = 1 ; i < sim->row-1 ; i ++ ){
		sp = IMAGE_PIXEL( sim, i, 1 );

	
		for( j = 1 ; j < sim->column-1 ; j ++, sp++, sp0++, sp1++ ){ 
			if( *sp & 0x80 ){
//				*sp = (*sp & 0x7F ) | NCC_BG;
				*sp = NCC_BG;

			}
		}
	}

}



static void
image1_ncc_end( image_type *gnim, image_type *nim )
{
	u_char	*sp,	*tp;
	int	i,	j;


	sp = gnim->data;
	tp = nim->data;
	for( i = 0 ; i < nim->height ; i++ ){

		for( j = 0 ; j < nim->width ; j++, sp++, tp++ ){

			if( *sp & NCC_BG ){
				*tp = 0;
				*sp = 0;
				continue;
			}

			if( *sp >= NCC_FR ){
				*tp = 2 * *sp;
				continue;
			}
			if( *sp & 0x04 ){
				*tp = 0x40;
				continue;
			}

			if( *sp & 0x02 ){
				*tp = 0x10;
				continue;
			}

//			*tp = *sp & 0x02;
		}
	}
}




static void
image1_ncc_update_edgeN( image_type *gim, image_type *gNim )
{
u_char	*sp,	*np;	
int	i,	j;

	for( i = 0 ; i < gNim->height ; i++ ){
		sp = IMAGE_PIXEL( gim, i, 0 );

		np = IMAGE_PIXEL( gNim, i, 0 );

		for( j = 0 ; j < gNim->width ; j++,  np++, sp++ ){

			if( (*np & (0x02|0x4) ) == 0 )
				continue;


			if( *sp == ECC_0 ){
				*np |= 0x10;
				continue;
			}


			if( *sp & ECC_BG ){
				*np = NCC_BG;
				continue;
			}




			if( *sp & ECC_FR ){
				*np = NCC_EDGE;
				continue;
			}


			if( *sp & ECC_MIX ){
				*np = NCC_FR;
				continue;
			}
		}
	}

}


static void
image1_ncc_update_edge( image_type *sim, image_type *bim, image_type *gNim )
{
u_char	*np,	*sp,	*bp,	*dp;	
int	i,	j,	align;
int	k,	n,	tmp;
	image_type *ebim = image1_gridient_sobol_value( bim, NULL );

	image_type *eim = image1_gridient_sobol_value( sim, NULL );

//	image_type *dim = image1_subtract_g( eim, ebim, NULL );

	image_type *dEim = NULL;
	dEim = image_recreate( dEim, sim->height, sim->width, 1, 1 );
	image1_const( dEim, 0 );


	align = sim->width - 8;


	for( i = 0 ; i < gNim->height ; i++ ){
		np = IMAGE_PIXEL( gNim, i, 0 );

		for( j = 0 ; j < gNim->width ; j++,  np++ ){
//			if( *np == 0 || *np == 255 ){
//				continue;
//			}

//			if( (*np & (0x02|0x8) ) == 0 )
			if( (*np & (0x02|0x4) ) == 0 )


				continue;



			sp = IMAGE_PIXEL( eim, i*8, j*8 );
			bp = IMAGE_PIXEL( ebim, i*8, j*8 );
			dp = IMAGE_PIXEL( dEim, i*8, j*8 );


			int	nS,	nB,	nSB,	nSB_w;
			nS = nB = nSB = nSB_w = 0;
			for( k = 0 ; k < 8 ; k++, sp += align, bp += align, dp += align ){
				for( n = 0 ; n < 8 ; n++ ){
					tmp = (*sp) - (*bp);

					if( *sp > 10 )	nS++;
					if( *bp > 10 )	nB++;

					if( !(*sp > 10 && *bp > 10 && ABS(tmp) < 24 || ABS( tmp) < 10) ){
						*dp = tmp + 128;

						if( tmp > 0 )	nSB_w++;
						nSB++;
					}


					sp++;
					bp++;

					dp++;
				}
			}

			if( nS < 2 && nB < 2 ){
				*np |= 0x10;
				continue;
			}

			if( nS > 16 && nSB < 5 ){
				*np = NCC_BG;
				continue;
			}



//			if( nS > 16 && nSB_w > 10 ){
//			if( nS > 16 && nSB_w > 10 ){
			if( nSB_w > 10 ){


				*np = NCC_EDGE;
				continue;
			}


			if( nSB > 5 )
				*np = NCC_FR;




		}
	}

	//if( m_iFrame > F0  && m_iFrame < F1 ){
	//	IMAGE_DUMP( eim, "E", m_iFrame, "eim" );
	//	IMAGE_DUMP( ebim, "E", m_iFrame, "ebim" );
	//	IMAGE_DUMP( dEim, "E", m_iFrame, "dEim" );

	//	IMAGE_DUMP_DUP( gNim, 8, 2, "E", m_iFrame, "gnim" );

	//}


	image_destroy( ebim, 1 );
	image_destroy( eim, 1 );
	image_destroy( dEim, 1 );


}



static image_type *
image1_subtract_g( image_type *sim1, image_type *sim0, image_type *im )
{
	u_char	*sp0,	*sp1;
	u_char	*tp;
	int	i,	j;
	int	tmp;


	im = image_recreate( im, sim1->height, sim1->width, 1, 1 );

	tp = (u_char *)im->data;
	for( i = 0 ; i < im->row ; i++ ){
		sp0 = IMAGE_PIXEL( sim0, i, 0 );
		sp1 = IMAGE_PIXEL( sim1, i, 0 );
		for( j = 0 ; j < im->column ; j++ ){

			tmp = (*sp1) - (*sp0);

			if( *sp0 > 10 && *sp1 > 10 && ABS(tmp) < 24 )
				tmp = 0;
			else	if( ABS( tmp) < 10 )	tmp = 0;

			*tp++ = tmp + 128;


			sp0++;
			sp1++;
		}
	}

	return( im );
}


static image_type *
image1_ncc_mask( image_type *nim, image_type *sIm )
{
u_char	*sp,	*np;
int	i,	j,	n,	k,	align;
int	no;

	align = sIm->width - 8;


	for( i = 0 ; i < nim->height ; i++ ){

		np = IMAGE_PIXEL( nim, i, 0 );

		for( j = 0 ; j < nim->width ; j++,np++ ){
			if( *np == 0 )
				continue;


			sp = IMAGE_PIXEL( sIm, i*8, j*8 );
	
			no = 0;
			for( k = 0 ; k < 8 ; k++, sp += align ){
				for( n = 0 ; n < 8 ; n++ ){
					if( *sp != 0 )	no++;
				}
			}

			if( no == 0	)	*np = 0;
		}
	}


	return( nim );
}



static void
image1_ncc_0x4_dilate_1( image_type *sim )
{
	u_char	*sp,	*sp0,	*sp1;
	int	i,	j;
	int	no;


	for( i = 1, no = 0 ; i < sim->row-1 ; i ++ ){
		sp = IMAGE_PIXEL( sim, i, 1 );
		sp0 = sp - sim->width;
		sp1 = sp + sim->width;

		for( j = 1 ; j < sim->column-1 ; j ++, sp++, sp0++, sp1++ ){ 
			if( *sp != 0x10 )	continue;

			int flag =	*(sp0-1) | *(sp0) | *(sp0+1) | 
				*(sp0-1) | *(sp+1) | 
				*(sp1-1) | *(sp1) | *(sp1+1);


			if( flag & 0x40 )
				*sp |= 0x80;
		}
	}


	for( i = 1 ; i < sim->row-1 ; i ++ ){
		sp = IMAGE_PIXEL( sim, i, 1 );


		for( j = 1 ; j < sim->column-1 ; j ++, sp++, sp0++, sp1++ ){ 
			if( *sp & 0x80 ){
				*sp = 0x50;
			}
		}
	}
}



static void
image1_ncc_final( image_type *sim, image_type *nccIm )
{
	u_char	*sp,	*np;
	int	i,	j;


	sp = sim->data;
	np = nccIm->data;

	for( i = 0 ; i < sim->row ; i++ ){
		for( j = 0 ; j < sim->column ; j++, sp++, np++ ){

			if( *np == 0x10  )
				*sp = 0;
		}
	}
}