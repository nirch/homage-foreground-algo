/****************************
 ***   XtrBgRemoval.cpp   ***
 ****************************/
#include	<stdlib.h>
#include	<string.h>


#include	"Uigp/igp.h"
#include	"ImageType/ImageType.h"

#include <math.h>

#include	"XtrBgRemoval.h"




static void	image_background_sum( image_type *im, image_type *mim, image_type *vim );

static void	image1_background_sum( image_type *im, image_type *mim, image_type *vim );


static void	image_background_grad( image_type *im, image_type *imx, image_type *imy, int n );






void CXtrBgRemoval::UpdateBgImage( image_type *im )
{
	if( m_mim == NULL ){
		m_bgFrame = 0;
		if( im->depth == 3 )
				m_mim = image6_from_image3( im );
		else	m_mim = image2_from_image1( im, NULL );

		m_var = image_create( im->row, im->column, 4, 1, NULL );
		image4_const( m_var, 0 );

		if( m_mode & BR_GRAD ){
			m_xim = image_create( im->row, im->column, 6, 1, NULL );
			m_yim = image_create( im->row, im->column, 6, 1, NULL );


			image_background_grad( im, m_xim, m_yim, m_bgFrame );
		}
		m_bgFrame = 1;

		return;
	}


	image_background_sum( im, m_mim, m_var );
	if( m_mode & BR_GRAD ){
		image_background_grad( im, m_xim, m_yim, m_bgFrame );
	}


	m_bgFrame++;
}








static void
image_background_sum( image_type *im, image_type *mim, image_type *vim )
{
u_char	*sp;
short	*tp,	*vp;
int	i,	j;
int	R,	G,	B,	c;
int	d[3],	var;

	if( im->depth == 1 ){
		image1_background_sum( im, mim, vim );
		return;
	}

	sp = (u_char *)im->data;

	tp = (short *)mim->data;
	vp = (short *)vim->data;

	for( i = 0 ; i < im->row ; i++, sp += im->pad ){

		for( j = 0 ; j < im->column ; j++ ){
			
			R = *sp++;
			G = *sp++;
			B = *sp++;

			if( ( d[0] = (R<<4) - *tp )     < 0 )	d[0] = -d[0];
			if( ( d[1] = (G<<4) - *(tp+1) ) < 0 )	d[1] = -d[1];
			if( ( d[2] = (B<<4) - *(tp+2) ) < 0 )	d[2] = -d[2];

			c = *tp;
			*tp++ = ( c - (c>>4) + R);	// ( ((15*(c/16) + R )/16 )*16

			c = *tp;
			*tp++ = ( c - (c>>4) + G);

			c = *tp;
			*tp++ = ( c - (c>>4) + B);



			var = (d[0] + 2*d[1] + d[2])>>2;

			c = *vp;
			*vp++ = ( c - ((c-var)>>4) );
			*vp++ += 1;

		}
	}
}




static void
image1_background_sum( image_type *im, image_type *mim, image_type *vim )
{
u_char	*sp;
short	*tp,	*vp;
int	i,	j;
int	R,	c;
int	d,	var;



	sp = (u_char *)im->data;

	tp = (short *)mim->data;
	vp = (short *)vim->data;

	for( i = 0 ; i < im->row ; i++, sp += im->pad ){

		for( j = 0 ; j < im->column ; j++ ){

			R = *sp++;

			if( ( d = (R<<4) - *tp )     < 0 )	d = -d;

			c = *tp;
			*tp++ = ( c - (c>>4) + R);	// ( ((15*(c/16) + R )/16 )*16


			var = d;

			c = *vp;
			*vp++ = ( c - ((c-var)>>4) );
			*vp++ += 1;

		}
	}
}


static void
image_background_grad( image_type *im, image_type *imx, image_type *imy, int n )
{
u_char	*sp,	*sp0,	*sp2;
short	*tpx,	*tpy;
int	i,	j;
int	R[3][3],	G[3][3],	B[3][3],	c,	cx,	cy;


	sp = (u_char *)im->data;

	tpx = (short *)imx->data;
	tpy = (short *)imy->data;
	
	sp += 3*im->column+3;
	tpx += 3*im->column+3;
	tpy += 3*im->column+3;

	for( i = 1 ; i < im->row-1 ; i++ ){

		sp0 = sp - 3*im->column;
		sp2 = sp + 3*im->column;
		for( j = 1 ; j < im->column-1 ; j++, sp += 3, sp0 += 3, sp2 += 3 ){
			

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




			cx = ((R[0][2] - R[0][0]) + 2*(R[1][2] - R[1][0]) + (R[2][2] - R[2][0]));
			cy = ((R[2][0] - R[0][0]) + 2*(R[2][1] - R[0][1]) + (R[2][2] - R[0][2]));
			cx += 128;
			cy += 128;

			if( n > 0 ){
				c = *tpx;
				*tpx++ = ( c - (c>>4) + cx);
				c = *tpy;
				*tpy++ = ( c - (c>>4) + cy);
			}
			else	{
				*tpx++ = cx<<4;
				*tpy++ = cy <<4;
			}



			cx = ((G[0][2] - G[0][0]) + 2*(G[1][2] - G[1][0]) + (G[2][2] - G[2][0]));
			cy = ((G[2][0] - G[0][0]) + 2*(G[2][1] - G[0][1]) + (G[2][2] - G[0][2]));
			cx += 128;
			cy += 128;
			if( n > 0 ){
				c = *tpx;
				*tpx++ = ( c - (c>>4) + cx);
				c = *tpy;
				*tpy++ = ( c - (c>>4) + cy);
			}
			else	{
				*tpx++ = cx<<4;
				*tpy++ = cy <<4;
			}


			cx = ((B[0][2] - B[0][0]) + 2*(B[1][2] - B[1][0]) + (B[2][2] - B[2][0]));
			cy = ((B[2][0] - B[0][0]) + 2*(B[2][1] - B[0][1]) + (B[2][2] - B[0][2]));
			cx += 128;
			cy += 128;
			if( n > 0 ){
				c = *tpx;
				*tpx++ = ( c - (c>>4) + cx);
				c = *tpy;
				*tpy++ = ( c - (c>>4) + cy);
			}
			else	{
				*tpx++ = cx<<4;
				*tpy++ = cy <<4;
			}
		}

		sp += 6;
		tpx += 6;
		tpy += 6;

	}
}



