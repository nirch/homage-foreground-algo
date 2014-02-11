/****************************
 ***   XtrBgRemoval.cpp   ***
 ****************************/
#include	<stdlib.h>
#include	<string.h>


#include	"Uigp/igp.h"
#include	"ImageType/ImageType.h"

#include <math.h>

#include	"XtrBgRemoval.h"

#include "Image2\BwLabel.h"


//#define _ILYA_ 


static void	image_background_removal( image_type *bim, image_type *im, int T0, int T1, image_type *mim );

static void	image_background_removalABS( image_type *bim, image_type *im, int T0, int T1, image_type *mim );

static void	image1_background_removalABS( image_type *bim, image_type *im, int T0, int T1, image_type *mim );


static void	image_background_removal_ilya( image_type *bim, image_type *im, image_type *mim );



static void	image_background_update( image_type *im, image_type *wim, image_type *bim );

static void	image_background_update_foreground( image_type *im );


static void	image_background_removal_grad( image_type *im,
							image_type *imx, image_type *imy,
							int T0, int T1, image_type *mim );





static void	image_background_update_foreground_hole( image_type *im );

static void	image1_cleaner( image_type *sim );


void	image1_MM( image_type *sim );

void	image1_remove_blobe( image_type *sim );




CXtrBgRemoval::CXtrBgRemoval()
{
	m_mim = NULL;
	m_var = NULL;
	m_xim = NULL;
	m_yim = NULL;

	m_sbim = NULL;
	m_svar = NULL;

	m_bgFrame = 0;

	m_T0 = 16;
	m_T1 = 32;


	m_mode = BR_COLOR;

}



CXtrBgRemoval::~CXtrBgRemoval()
{
	if( m_mim != NULL ){
		image_destroy( m_mim, 1 );
		m_mim = NULL;
	}

	if( m_var != NULL ){
		image_destroy( m_var, 1 );
		m_var = NULL;
	}

	if( m_xim != NULL ){
		image_destroy( m_xim, 1 );
		m_xim = NULL;
	}

	if( m_yim != NULL ){
		image_destroy( m_yim, 1 );
		m_yim = NULL;
	}
}


void CXtrBgRemoval::DeleteContent()
{
	if( m_mim != NULL ){
		image_destroy( m_mim, 1 );
		m_mim = NULL;
	}

	if( m_var != NULL ){
		image_destroy( m_var, 1 );
		m_var = NULL;
	}

	if( m_xim != NULL ){
		image_destroy( m_xim, 1 );
		m_xim = NULL;
	}

	if( m_yim != NULL ){
		image_destroy( m_yim, 1 );
		m_yim = NULL;
	}
}




void CXtrBgRemoval::SetThreshold( float t0, float t1 )
{
	m_T0 = t0;
	m_T1 = 2*t1 -t0;
}



void	image1_closeBit( image_type *im, int n );




void CXtrBgRemoval::ProcessFrame( image_type *im, image_type **mim )
{



	if( *mim == NULL ){
		*mim = image_create( im->row, im->column, 1, 1, NULL );
	}
	
	image1_const( *mim, 0 );



	
	if( m_mode & BR_COLOR )
		image_background_removalABS( m_mim, im, m_T0, m_T1, *mim );


	if( m_mode & BR_GRAD )
		image_background_removal_grad( im,
							m_xim, m_yim,
							m_T0, m_T1, *mim );



//	image_background_update_foreground_hole( *mim );
//	image1_close( *mim, 2 );


	if( im->width < 400 )
			image1_closeBit( *mim, 1 );
	else		image1_closeBit( *mim, 2 );


	image1_cleaner( *mim );

	//image1_closeBit( *mim, 2 );

	
	image1_MM( *mim );


//	image1_remove_blobe( *mim );




	if( m_mode & BR_UPDATE_FOREGROUND )
		image_background_update_foreground( *mim );


	if( m_mode & BR_UPDATE )
		image_background_update( im, *mim, m_mim );
}




static void
image_background_removal( image_type *bim, image_type *im, int T0, int T1, image_type *mim )
{
u_char	*sp;
short	*bp;
u_char	*mp;
int	i,	j;
int	R,	G,	B; 
int	bR,	bG,	bB;
int	dR,	dG,	dB;
int	m;
float	fT;
	T0 *= 16;
	T1 *= 16;

	fT = 255.0/T1;



	sp = (u_char *)im->data;
	bp = (short *)bim->data;
	mp = (u_char *)mim->data;

	for( i = 0 ; i < im->row ; i++, sp += im->pad ){

		for( j = 0 ; j < im->column ; j++ ){

			R = *sp++;
			G = *sp++;
			B = *sp++;

			bR = *bp++;
			bG = *bp++;
			bB = *bp++;

			R <<= 4;
			G <<= 4;
			B <<= 4;


			if( ( dR = R - bR) < 0 )	dR = -dR;
			if( ( dG = G - bG) < 0 )	dG = -dG;
			if( ( dB = B - bB) < 0 )	dB = -dB;





			m = (dR + dG + dB)/3;

			if( m <= T0 )
				m = 0;
			else	if( m >= T1+T0 )	m = 255;
			else m = 255*(m - T0)/(T1);



			*mp++ = m;
		}
	}
}




static void
image_background_removalABS( image_type *bim, image_type *im, int T0, int T1, image_type *mim )
{
u_char	*sp;
short	*bp;
u_char	*mp;
int	i,	j;
int	R,	G,	B; 
int	bR,	bG,	bB;
int	dR,	dG,	dB;
int	m;
float	fT;
int	aT[256];
	fT = 255.0/T1;

	if( im->depth == 1 ){
		image1_background_removalABS( bim, im, T0, T1, mim );
		return;
	}


	for( i = 0 ; i <= T0 ; i++ )
		aT[i] = 0;

	for(; i < T0+T1 ; i++ )
		aT[i] = fT*(i-T0);

	for(; i < 256 ; i++ )
		aT[i] = 255;


	sp = (u_char *)im->data;
	bp = (short *)bim->data;
	mp = (u_char *)mim->data;

	for( i = 0 ; i < im->row ; i++, sp += im->pad ){

		for( j = 0 ; j < im->column ; j++ ){

			R = *sp++;
			G = *sp++;
			B = *sp++;

			bR = *bp++;
			bG = *bp++;
			bB = *bp++;


			if( ( dR = R - (bR>>4)) < 0 )	dR = -dR;
			if( ( dG = G - (bG>>4)) < 0 )	dG = -dG;
			if( ( dB = B - (bB>>4)) < 0 )	dB = -dB;


			
			m = dR;
			if( m < dG )	m = dG;
			if( m < dB )	m = dB;


			//if( m <= T0 )
			//	m = 0;
			//else	if( m >= T1+T0 )	m = 255;
			//else m = fT*(m - T0);


//			*mp++ = m;
			*mp++ = aT[m];
		}
	}
}



static void
image1_background_removalABS( image_type *bim, image_type *im, int T0, int T1, image_type *mim )
{
u_char	*sp;
short	*bp;
u_char	*mp;
int	i,	j;
int	R; 
int	bR;
int	dR;
int	m;
float	fT;
int	aT[256];
fT = 255.0/T1;


	for( i = 0 ; i <= T0 ; i++ )
		aT[i] = 0;

	for(; i < T0+T1 ; i++ )
		aT[i] = fT*(i-T0);

	for(; i < 256 ; i++ )
		aT[i] = 255;


	sp = (u_char *)im->data;
	bp = (short *)bim->data;
	mp = (u_char *)mim->data;

	for( i = 0 ; i < im->row ; i++, sp += im->pad ){

		for( j = 0 ; j < im->column ; j++ ){

			R = *sp++;

			bR = *bp++;


			if( ( dR = R - (bR>>4)) < 0 )	dR = -dR;


			m = dR;

			*mp++ = aT[m];
		}
	}
}



static void
image_background_update( image_type *im, image_type *wim, image_type *bim )
{
u_char	*sp,	*wp;
short	*tp;
int	i,	j;
int	R,	G,	B,	c;
int	w;


	sp = (u_char *)im->data;

	wp = (u_char *)wim->data;

	tp = (short *)bim->data;
	

	for( i = 0 ; i < im->row ; i++ ){

		for( j = 0 ; j < im->column ; j++ ){
			
			R = *sp++;
			G = *sp++;
			B = *sp++;

			w = *wp++;
			w = 255 - w;
//			w >>= 5;
			w >>= 6;

			if( w == 0 ){
				tp += 3;
				continue;
			}




			c = *tp;
			*tp++ = ( c * (256 - w) + w*R*16 )>>8;	// ( ((15*(c/16) + R )/16 )*16

			c = *tp;
			*tp++ = ( c * (256 - w) + w*G*16 )>>8;

			c = *tp;
			*tp++ = ( c * (256 - w) + w*B*16 )>>8;

		}
	}
}




static void
image_background_removal_grad( image_type *im,
							image_type *imx, image_type *imy,
							int T0, int T1, image_type *mim )
{
u_char	*sp,	*sp0,	*sp2;
short	*tpx,	*tpy;
u_char	*mp;
int	i,	j;
int	R[3][3],	G[3][3],	B[3][3],	c,	cx,	cy;
int	sm,	m;
short	g,	g0,	g1;
int	bx,	by;

	T0 *= 4;
	T1 *= 4;


	sp = (u_char *)im->data;

	tpx = (short *)imx->data;
	tpy = (short *)imy->data;
	mp = ( u_char *)mim->data;

	
	sp += 3*im->column+3;
	tpx += 3*im->column+3;
	tpy += 3*im->column+3;

	mp += imx->column+1;

	for( i = 1 ; i < im->row-1 ; i++ ){

		sp0 = sp - 3*im->column;
		sp2 = sp + 3*im->column;
		for( j = 1 ; j < im->column-1 ; j++, sp+=3, sp0+=3, sp2+=3, mp++ ){
			

			R[0][0] = *(sp0-3);
			G[0][0] = *(sp0-3+1);
			B[0][0] = *(sp0-3+2);

			R[0][1] = *(sp0);
			G[0][1] = *(sp0+1); 
			B[0][1] = *(sp0+2);

			R[0][2] = *(sp0+3);
			G[0][2] = *(sp0+3+1);
			B[0][2] = *(sp0+3+2);


			R[1][0] = *(sp-3);
			G[1][0] = *(sp-3+1);
			B[1][0] = *(sp-3+2);

			R[1][1] = *(sp);
			G[1][1] = *(sp+1); 
			B[1][1] = *(sp+2);

			R[1][2] = *(sp+3);
			G[1][2] = *(sp+3+1);
			B[1][2] = *(sp+3+2);



			R[2][0] = *(sp2-3);
			G[2][0] = *(sp2-3+1);
			B[2][0] = *(sp2-3+2);

			R[2][1] = *(sp2);
			G[2][1] = *(sp2+1); 
			B[2][1] = *(sp2+2);

			R[2][2] = *(sp2+3);
			G[2][2] = *(sp2+3+1);
			B[2][2] = *(sp2+3+2);



//#define A
			cx = ((R[0][2] - R[0][0]) + 2*(R[1][2] - R[1][0]) + (R[2][2] - R[2][0]));
			cy = ((R[2][0] - R[0][0]) + 2*(R[2][1] - R[0][1]) + (R[2][2] - R[0][2]));

			bx = (*tpx++ >> 4) - 128;
			by = (*tpy++ >> 4) - 128;
#ifdef A
			cx -= bx;
			cy -= by;
			c = ABS( cx) + ABS( cy );
#else
			g0 = ABS(bx) + ABS(by );
			g1 = ABS( cx) + ABS(cy);
			g = MAX( g1, g0 );

			cx -= bx;
			cy -= by;
			c = ABS( cx) + ABS( cy );

			if( g > 0 )	c = c*c/g;
#endif


			sm = 0;
			if( c < T0 )
				m = 0;
			else	if( c > T1 )	m = 255;
					else m = 255*(c - T0)/(T1-T0);
			if( m > sm )	sm = m;


			cx = ((G[0][2] - G[0][0]) + 2*(G[1][2] - G[1][0]) + (G[2][2] - G[2][0]));
			cy = ((G[2][0] - G[0][0]) + 2*(G[2][1] - G[0][1]) + (G[2][2] - G[0][2]));

			bx = (*tpx++ >> 4) - 128;
			by = (*tpy++ >> 4) - 128;

#ifdef A
			cx -= bx;
			cy -= by;
			c = ABS( cx) + ABS( cy );
#else
			g0 = ABS(bx) + ABS(by );
			g1 = ABS( cx) + ABS(cy);
			g = MAX( g1, g0 );

			cx -= bx;
			cy -= by;
			c = ABS( cx) + ABS( cy );

			if( g > 0 )	c = c*c/g;
#endif

			if( c < T0 )
				m = 0;
			else	if( c > T1 )	m = 255;
					else m = 255*(c - T0)/(T1-T0);
//			if( m > sm )	sm = m;
			sm += m;

			cx = ((B[0][2] - B[0][0]) + 2*(B[1][2] - B[1][0]) + (B[2][2] - B[2][0]));
			cy = ((B[2][0] - B[0][0]) + 2*(B[2][1] - B[0][1]) + (B[2][2] - B[0][2]));
			bx = (*tpx++ >> 4) - 128;
			by = (*tpy++ >> 4) - 128;

#ifdef A
			cx -= bx;
			cy -= by;
			c = ABS( cx) + ABS( cy );
#else
			g0 = ABS(bx) + ABS(by );
			g1 = ABS( cx) + ABS(cy);
			g = MAX( g1, g0 );

			cx -= bx;
			cy -= by;
			c = ABS( cx) + ABS( cy );

			if( g > 0 )	c = c*c/g;
#endif

			if( c < T0 )
				m = 0;
			else	if( c > T1 )	m = 255;
					else m = 255*(c - T0)/(T1-T0);
			sm += m;
//			if( m > sm )	sm = m;

			if( sm > 255 )	sm = 255;
			if( *mp < sm )	*mp = sm;
		}

		sp += 6;
		tpx += 6;
		tpy += 6;
		mp += 2;

	}
}




	




static void
image_background_update_foreground( image_type *im )
{
u_char	*sp,	*sp0,	*sp2;
int	i,	j;
int	sum;

	sp = (u_char *)im->data;


	
	sp += im->column+1;


	for( i = 1 ; i < im->row-1 ; i++ ){

		sp0 = sp - im->column;
		sp2 = sp + im->column;
		for( j = 1 ; j < im->column-1 ; j++, sp++, sp0++, sp2++ ){
			
			sum = *(sp0-1) + *(sp0) + *(sp0+1) +
				*(sp-1) + *(sp+1) +
				*(sp2-1) + *(sp2) + *(sp2+1);
			sum >>= 3;
			if( sum < 164 )	continue;

			if( sum > *sp )
				*sp = sum;
		}
	}
}



static void
image_background_update_foreground_hole( image_type *im )
{
u_char	*sp,	*at,	*tp,	*sp0,	*sp1;
int	i,	j;
int	sum;

	sp = (u_char *)im->data;
	
	sp += im->column+1;


	at = (u_char *) malloc( MAX( im->row, im->column )+6 );

	*at = 0;

	for( i = 1 ; i < im->row-1 ; i++, sp += 2 ){
		tp = at+2;
		*(tp-2) = 0;
		*(tp-1) = *(sp-1);
		*tp = *sp;
		sum = *(sp-1) + *sp;
		
		for( j = 1 ; j < im->column-1 ; j++, sp++, tp++ ){
			*(tp+1) = *(sp+1);
			sum -= *(tp-2);
			sum += *(tp+1);
			*sp = sum * ( 1.0 / 3 );
		}
	}

	sp0 = (u_char *)im->data + 1;
	for( j = 1 ; j < im->column-1 ; j++, sp0++ ){
		sp = sp0 + im->column;
		sp1 = sp + im->column;

		tp = at+2;
		*(tp-2) = 0;
		*(tp-1) = *sp0;
		*tp = *sp;
		sum = *(tp-1) + *tp;
		for( i = 1 ; i < im->row-1 ; i++, sp++, sp1++, tp++ ){
		
			*(tp+1) = *sp1;
			sum -= *(tp-2);
			sum += *(tp+1);
			*sp = sum * ( 1.0 / 3 );
		}
	}

	free( at );
}



image_type *
image_smooth( image_type *sim, image_type *im )
{
float	cx[3];

	cx[0] = 0.125;
	cx[1] = 0.75;
	cx[2] = 0.125;

	im = image3_convolution_separably( sim, cx, cx, 1,  im );

	return( im );
}




void
image1_cleaner( image_type *sim )
{
int	H[256],	i,	j,	n,	sum;
u_char	*sp;

	for( i = 0 ; i < 256 ; i++ )
		H[i] = 0;


	n = 0;
	for( i = 0.66*sim->height ; i < sim->height ; i++ ){
		sp = IMAGE_PIXEL( sim, i, 0 );
		for( j = 0 ; j < sim->width ; j++, sp++ ){
			if( *sp != 0 ){
				H[*sp]++;
				n++;
			}
		}
	}

	for( i = 0, sum = 0 ; i < 256 ; i++ ){
		sum += H[i];
		if( sum > 0.25 * n )
			break;
	}

	int	T = i;
//	if( T > 96 || sum > 0.65 * n )	return;
	if( T > 48 )	T = 48;
		
	for( i = 0.66*sim->height ; i < sim->height ; i++ ){
		sp = IMAGE_PIXEL( sim, i, 0 );
		for( j = 0 ; j < sim->width ; j++, sp++ ){
			if( *sp != 0 && *sp < T ){
				*sp = 0;
			}
		}
	}

}



void
image1_MM( image_type *sim )
{
u_char	*sp;
int	i,	j;
//int	tmp;

	for( i = 0 ; i < sim->height ; i++ ){
		sp = IMAGE_PIXEL( sim, i, 0 );
		for( j = 0 ; j < sim->width ; j++, sp++ ){
			if( *sp > 170 )
				*sp = 255;
			else
				*sp += (*sp)>>1;

			//tmp = 1.5 * *sp;
			//if( tmp > 255 )	tmp = 255;
			//*sp = tmp;
		}
	}
}


void
image1_remove_blobe( image_type *sim )
{
image_type *im;
bwLabel_type *abw;
int nBw; 
int	nMax,	iMax,	i,	j;

	im = image2_from_image1( sim, NULL );


	image2_bwLabel( im, &abw, &nBw );
	if( nBw <= 1 ){
		free( abw );
		image_destroy( im, 1);
		return;
	}

	image2_bwLabel_set_direction( im, abw, nBw );

	nMax = abw[0].no;
	iMax = 0;
	for( i = 0 ; i < nBw ; i++ ){
		if( abw[i].id != i )	continue;
		if( nMax < abw[i].no ){
			nMax = abw[i].no;
			iMax = i;
		}
	}

	int m = 0;
	for( i = 0 ; i < nBw ; i++ ){
		if( i == iMax )	continue;
		if( abw[i].id == iMax )	continue;

		if( abw[i].p.x < 100 || abw[i].p.x > im->width - 100 )
			abw[i].id = -1;
	}

	for( i = 0 ; i < nBw ; i++ ){
		if( abw[i].id < 0 || abw[i].id == i )
			continue;

		abw[i].id = abw[ abw[i].id].id;
	}

//	free( abw );

	//if( m == 0  ){
	//	image_destroy( im, 1);
	//	return;
	//}


	u_char *sp = sim->data;
	short *bp = im->data_s;

	for( i = 0 ; i < sim->height ; i++ )
		for( j = 0 ; j < sim->width ; j++, sp++, bp++ ){
//			if( abw[*bp].id != iMax )
//			if( m & (1<< *bp ) )
			if( abw[*bp].id < 0 )
				*sp = 0;
		}

	free( abw );
	image_destroy( im, 1 );
}