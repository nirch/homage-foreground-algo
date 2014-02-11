/**************************
 ***	DmPlaneType.h   ***
 **************************/

#ifndef		_DM_PLANE_TYPE_
#define		_DM_PLANE_TYPE_

#include	"Uigp/igp.h"
#include	"Uvec/Vec3d.h"
#include	"Umath/Plane/Plane3d.h"
#include	"Uview/ViewType.h"




typedef struct dmPlane_type {
	int type;

	int	iLayer;	

	vec3d	N;//,	P;

	float	d;

	//Aux
	plane3f_type pl;

}	dmPlane_type;



	// DmPlane.c
dmPlane_type *	dmPlane_alloc();

void	dmPlane_destroy( dmPlane_type *dmPlane );

dmPlane_type *	dmPlane_create(vec3d *n, float d );

dmPlane_type *	dmPlane_make_copy( dmPlane_type *plane );


void	dmPlane_aux( dmPlane_type *dmPlane, view_type *vw );

float	dmPlane_depth( dmPlane_type *dmPlane, vec2d *v );


void	dmPlane_to_plane3d( view_type *vw, dmPlane_type *dmPlane, plane3f_type *plane );


void	dmPlane_flipH( view_type *vw, dmPlane_type *dmPlane );

void	dmPlane_flipV( view_type *vw, dmPlane_type *dmPlane );

float	dmPlane_depth_value( view_type *vw, dmPlane_type *dmPlane, vec2d *v );


#endif
