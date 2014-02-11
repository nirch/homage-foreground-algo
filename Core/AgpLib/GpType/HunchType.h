/**************************
 ***	HunchType.h	***
 **************************/

#ifndef		_HUNCH_TYPE_
#define		_HUNCH_TYPE_

#include        "Uigp/igp.h"

#include	"ColorType.h"
     

#include	"Uvec/Vec2d.h"


typedef  struct  hunch_gtype {	// 20
	float      theta;

	/*** aux ***/
	vec2d      u;
	float	width,	len;

} hunch_gtype;


typedef  struct  hunch_type {	// 76 bytes
	int	type;		/* NF_HUNCH or NF_RH */
	vec2d	ctr;


	float	depth;
	u_char	br;


	hunch_gtype	g;

	qcolor_type	gval[SP_NO] ;
	qcolor_type	rval[SP_NO];

	qcolor_type	lm1[SP_NO];
	qcolor_type	lm2[SP_NO];



	struct  hunch_type	*nh;


	/* Rendering AUX */
	struct  hunch_type	*rnh;
#ifdef RENDER_AUX_LOCAL
	struct pl_type	*pl;
#endif

}  hunch_type;



#define		HUNCH_ALLOC( no )  \
			( (hunch_type *)malloc( no*sizeof( hunch_type )) )
#define		HUNCH_COPY( h, nh, no )  \
				memcpy( nh, h, no*sizeof( hunch_type ) )


#define		HUNCH_FREE( h )		free( h )

	
hunch_type      *hunch_alloc();

hunch_type *	hunch_make_copy( hunch_type *hunch );

void		hunch_copy( hunch_type *h, hunch_type *nh );

void		hunch_inverse_copy( hunch_type *h, hunch_type *nh, int dno );



void		rhunch_set_aux( hunch_type  *rh );

void		hunch_set_aux( hunch_type  *h );

#endif
