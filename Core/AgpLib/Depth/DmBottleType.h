/***************************
 ***	DmBottleType.h   ***
 ***************************/

#ifndef		_DM_BOTTLE_TYPE_
#define		_DM_BOTTLE_TYPE_

#include	"Uigp/igp.h"
#include	"Uvec/Vec2d.h"

#include	"Uview/ViewType.h"

#include	"GpType/LinkType.h"



typedef struct dmBottle_type {

	int type;

	int	iLayer;	


	float	depth0;	// depth on the contour

	float	depth1;	// depth on the middle

	float	Mu;		// max deistance from the contour

	// Aux
	vec2d ctr;
	link_type	*link;

}	dmBottle_type;



	// DmCorner.c
dmBottle_type	* dmBottle_alloc();

void	dmBottle_destroy( dmBottle_type	*corner );


void	dmBottle_init( dmBottle_type *c, float depth0, float depth1, float Mu  );


dmBottle_type *	dmBottle_make_copy( dmBottle_type *sp );



void	dmBottle_aux( dmBottle_type *c, view_type *vw, vec2d *ctr, link_type *link );



float	dmBottle_depth( dmBottle_type *c, vec2d *v );




#endif
