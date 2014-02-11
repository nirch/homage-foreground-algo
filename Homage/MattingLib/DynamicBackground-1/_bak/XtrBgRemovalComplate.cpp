/****************************
 ***   XtrBgRemoval.cpp   ***
 ****************************/
#include	<stdlib.h>
#include	<string.h>


#include	"Uigp/igp.h"
#include	"ImageType/ImageType.h"

#include <math.h>

#include	"XtrBgRemoval.h"




static void	image_background_complete( image_type *im, image_type *mim, image_type *vim,
					 image_type *sbim, image_type *svim );


static void	image_background_complete_end( image_type *mim, image_type *vim,
										image_type *sbim, image_type *svim );

static void	image_background_complete_print( int frame, image_type *im, image_type *mim, image_type *vim,
					 image_type *sbim, image_type *svim );





void CXtrBgRemoval::CompleteBackground( image_type *im )
{
	if( m_sbim == NULL ){
		m_sbim = image_create( im->row, im->column, 6, 1, NULL );
		m_svar = image_create( im->row, im->column, 4, 1, NULL );
		image4_const( m_svar, 0 );

		m_state = BG_COMPLETE;
	}

	image_background_complete( im, m_mim, m_var, m_sbim, m_svar );

	m_bgFrame++;
}


void CXtrBgRemoval::CompleteBackgroundEnd()
{
	if( m_state = BG_COMPLETE ){
		image_background_complete_end( m_mim, m_var, m_sbim, m_svar );
		m_state = BG_REMOVE;
	}
}





static void
image_background_complete( image_type *im, image_type *mim, image_type *vim,
					 image_type *sbim, image_type *svim )
{
u_char	*sp;
short	*tp,	*vp;
short	*sbp,	*svp;
int	i,	j;
int	R,	G,	B,	c;
int	d[3],	var;


	sp = (u_char *)im->data;

	tp = (short *)mim->data;
	vp = (short *)vim->data;

	sbp = (short *)sbim->data;
	svp = (short *)svim->data;


	for( i = 0 ; i < im->row ; i++ ){//, sp += im->pad ){

		for( j = 0 ; j < im->column ; j++ ){
			
			R = (*sp++ ) << 4;
			G = (*sp++ ) << 4 ;
			B = (*sp++ ) << 4;


			if( *(svp+1) > 0 ){

				if( ( d[0] = R - *sbp )     < 0 )	d[0] = -d[0];
				if( ( d[1] = G - *(sbp+1) ) < 0 )	d[1] = -d[1];
				if( ( d[2] = B - *(sbp+2) ) < 0 )	d[2] = -d[2];
				var = (d[0] + 2*d[1] + d[2])>>2;

				if( (var>> 4) < 16 ){
					c = *sbp;
					*sbp++ = ( c - ((c-R)>>4));	// ( ((15*(c/16) + R )/16 )*16

					c = *sbp;
					*sbp++ = ( c - ((c-G)>>4));

					c = *sbp;
					*sbp++ = ( c - ((c-B)>>4));



					c = *svp;
					*svp++ = ( c - ((c-var)>>4) );
					*svp++ += 1;
				
					tp += 3;
					vp += 2;
					continue;
				}



				if( *(svp+1) > 12 && *svp <= *vp  ){
					*tp++ = *sbp;
					*tp++ = *(sbp+1);
					*tp++ = *(sbp+2);
					*vp++ = *svp;
					*vp++ = *(svp+1);


					*sbp++ = R;
					*sbp++ = G;
					*sbp++ = B;
					*svp++ = 0;
					*svp++ = 1;
					continue;
				}
			}



			if( ( d[0] = R - *tp )     < 0 )	d[0] = -d[0];
			if( ( d[1] = G - *(tp+1) ) < 0 )	d[1] = -d[1];
			if( ( d[2] = B - *(tp+2) ) < 0 )	d[2] = -d[2];
			var = (d[0] + 2*d[1] + d[2])>>2;


			if( (var>> 4) < 16 ){

				c = *tp;
				*tp++ = ( c - ((c-R)>>4));	// ( ((15*(c/16) + R )/16 )*16

				c = *tp;
				*tp++ = ( c - ((c-G)>>4));

				c = *tp;
				*tp++ = ( c - ((c-B)>>4));



				c = *vp;
				*vp++ = ( c - ((c-var)>>4) );
				*vp++ += 1;

				sbp += 3;
				svp++;
				*svp++ = 0;
				

				continue;
			}


			*sbp++ = R;
			*sbp++ = G;
			*sbp++ = B;
			*svp++ = 0;
			*svp++ = 1;

			tp += 3;
			vp += 2;
		}
	}
}


static void
image_background_complete_print( int frame, image_type *im, image_type *mim, image_type *vim,
					 image_type *sbim, image_type *svim )
{
u_char	*sp;
short	*tp,	*vp;
short	*sbp,	*svp;
int	i,	j;

	i = 205;
	j = 250;
	sp = (u_char *)IMAGE_PIXEL( im,i,j); 
	tp = (short *)IMAGE_PIXEL( mim,i,j); 
	vp = (short *)IMAGE_PIXEL( vim,i,j); 
	sbp = (short *)IMAGE_PIXEL( sbim,i,j); 
	svp = (short *)IMAGE_PIXEL( svim,i,j); 

	fprintf( stderr, "%d   sp: %.3d %.3d %.3d   tp: %.3d %.3d, %.3d  vp: %.3d %.3d  sbp: %.3d %.3d, %.3d  svp: %.3d %.3d\n",  
				frame,
				*sp, *(sp+1), *(sp+2),
				*(tp)>>4, (*(tp+1))>>4, (*(tp+2))>>4,
				*(vp)>>4, (*(vp+1)),
				*(sbp)>>4, (*(sbp+1))>>4, (*(sbp+2))>>4,
				*(svp)>>4, (*(svp+1)) );
}




static void
image_background_complete_end( image_type *mim, image_type *vim,
					 image_type *sbim, image_type *svim )
{
short	*tp,	*vp;
short	*sbp,	*svp;
int	i,	j;


	tp = (short *)mim->data;
	vp = (short *)vim->data;

	sbp = (short *)sbim->data;
	svp = (short *)svim->data;


	for( i = 0 ; i < mim->row ; i++ ){//, sp += im->pad ){

		for( j = 0 ; j < mim->column ; j++ ){
			
			if( *(svp+1) > 16 && *svp < *vp  || *svp > *vp-2 && *(svp+1) > *(vp+1)-2){
				*tp++ = *sbp++;
				*tp++ = *sbp++;
				*tp++ = *sbp++;


				*vp++ = *svp++;
				*vp++ = *svp++;
				continue;
			}

			sbp += 3;
			*svp++ = 0;
			*svp++ = 0;

			tp += 3;
			vp += 2;
		}
	}
}



