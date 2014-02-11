/**********************
 ***	BgpType.h   ***
 **********************/

#ifndef         _BGP_TYPE_
#define         _BGP_TYPE_

#include	"Uigp/igp.h"


#include	"Uvec/Vec2d.h"




typedef struct bgp_type {	// 32 bytes
	vec2d	ctr;

	float	depth;
	s_char	br;
	s_char	Sbr;

	qcolor_type	val[SP_NO];

	struct bgp_type	*p;



	/* Rendering AUX */
	struct bgp_type *rp;

#ifdef RENDER_AUX_LOCAL	
	struct pl_type       *pl;
#endif

}	bgp_type;

#define         BGP_ALLOC()	( (bgp_type *)malloc( sizeof( bgp_type ) ) )


#endif
