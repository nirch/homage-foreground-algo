/***************************
 ***	DmCornerType.h   ***
 ***************************/

#ifndef		_DM_CORNER_TYPE_
#define		_DM_CORNER_TYPE_

#include	"Uigp/igp.h"
#include	"Uvec/Vec2d.h"

#include	"Uview/ViewType.h"



#define	CORNER90_CONVEX			0
#define	CORNER90_CONCAVE		1


typedef struct dmCorner_type {

	int type;

	int	iLayer;	

	vec2d	p;
	vec2d	v[3];	// can be big

	float	depth;	
	float	d[3];	// depth of corener at dis 10


	// Aux
	plane3f_type pl[3];

}	dmCorner_type;



	// DmCorner.c
dmCorner_type	* dmCorner_alloc();

void	dmCorner_destroy( dmCorner_type	*corner );


void	dmCorner_init( dmCorner_type *c, float x, float y );

dmCorner_type *	dmCorner_make_copy( dmCorner_type *sp );




void	dmCorner_aux( dmCorner_type *c, view_type *vw );

int		dmCorner_plane( view_type *vw, dmCorner_type *c, plane3f_type pl[3] );


float	dmCorner_depth( dmCorner_type *c, vec2d *v );



	//DmCorner90View.c
int		dmCorner90_compute_depth( view_type *vw, vec2d *p0, vec2d V[3], float depth, int flag,
									float radius, float d[3] );




#endif
