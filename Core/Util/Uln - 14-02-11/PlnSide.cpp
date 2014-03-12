/*******************
 ***  PlnTool.c  ***
 *******************/
#include <string.h>
#include <math.h>
#include "Uigp/igp.h"

#ifdef _WIN32
#define _GPMEMORY_LEAK 
#endif
#include "Uigp/GpMemoryLeak.h"


#include "Uln/PlnType.h"


void	
pln_interior_force_right( pln_type *pl )
{
	if( pln_interior_side( pl ) == 0 )
		pln_inverse( pl );
}



// if the interior of the close contour pl is on right  return 1 otherwise  0
int 
pln_interior_side( pln_type *pl )
{
	ln_type	*l, *lr;
	float		len;
	vec2d		gctr, p;


	// find the longest link
	len = -1.0;
	for ( l = pl->link, gctr = pl->ctr; l; l= LN_NEXT( l ) ) {
		if ( l->len > len ) {
			len	= l->len;
			lr	= l;
			p	= gctr;
		}

		gctr.x += l->v.x;
		gctr.y += l->v.y;
	}

	p.x += lr->v.x/2.0 + lr->u.x;
	p.y += lr->v.y/2.0 + lr->u.y;

	return pln_point_side( pl, &p );

}



// if the point  is in the right side of the close contour pl  return 1  otherwise 0
int 
pln_point_side( pln_type *pl, vec2d *p )
{
	ln_type *l;
	vec2d gctr;
	vec2d v1, v2;
	float d1, d2, dd, scal, vect, cos_delta, sin_delta;
	float al, sum;

	sum = 0;

	for ( l = pl->link, gctr = pl->ctr; l != NULL; l = LN_NEXT(l) ) {
		v1.x = gctr.x - p->x;
		v1.y = gctr.y - p->y;

		gctr.x += l->v.x;
		gctr.y += l->v.y;
		v2.x = gctr.x - p->x;
		v2.y = gctr.y - p->y;

		d1 = v1.x*v1.x + v1.y*v1.y;
		d2 = v2.x*v2.x + v2.y*v2.y;
		dd = sqrt(d1*d2);
		scal = v1.x*v2.x + v1.y*v2.y;
		cos_delta = scal/dd;
		vect = v1.x*v2.y - v1.y*v2.x;
		sin_delta = vect/dd;

		al = atan2( sin_delta, cos_delta );
		sum += al;
	}

	return ( ABS(sum) > M_PI );
}

