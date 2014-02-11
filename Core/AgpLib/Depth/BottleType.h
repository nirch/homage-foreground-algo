/************************
 ***	BottleType.h  ***
 ************************/

#ifndef		_BOTTLE_TYPE_
#define		_BOTTLE_TYPE_

#include	"Uigp/igp.h"
#include	"Uvec/Vec2d.h"

#include	"Uview/ViewType.h"



#define	BOTTLE_CONVEX		0
#define	BOTTLE_CONCAVE		1


typedef struct bottle_type {

	int type;

	int	iLayer;	

	vec2d	p;
	vec2d	v[3];	// can be big

	float	depth;	
	float	d[3];	// depth of bottle at dis 10

}	bottle_type;



	// Bottle.c
bottle_type	* bottle_alloc();

void	bottle_destroy( bottle_type	*bottle );

void	bottle_init( bottle_type *b, float x, float y );


//int		view_plane90_depth( view_type *vw, vec2d *p0, vec2d V[3], float depth, int flag,
//									float radius, float d[3] );

int		bottle_plane( view_type *vw, bottle_type *b, plane3d pl[3] );

float	bottle_depth( bottle_type *b, plane3d pl[], vec2d *v );



#endif
