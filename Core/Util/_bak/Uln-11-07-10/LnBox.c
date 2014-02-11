/***************************
 ***   AgpCopyBranch.c   ***
 ***************************/

#include	<stdio.h>
#include	<math.h>

#include	"Uigp/igp.h"
#include "Ubox/Box2d.h"



#include	"LnType.h"



static void	ln_update_box( vec2d *ctr, ln_type *link, box2d *box );


void
lnL_box( vec2d *ctr, ln_type *link, ln_type *last, box2d *box )
{
ln_type	*l;
vec2d	v;

	BOX2D_INIT( *box, ctr->x, ctr->y );

	for( l = link, v = *ctr ; l != last ; l = LN_NEXT(l) ){
		ln_update_box( &v, l, box );

		v.x += l->v.x;
		v.y += l->v.y;
	}
}




static void
ln_update_box( vec2d *ctr, ln_type *link, box2d *box )
{
vec2d	v,	p;
float	t;



	v.x = ctr->x + link->v.x;
	v.y = ctr->y + link->v.y;
	BOX2D_UPDATE( *box, v.x, v.y );



	if( ln_tanget_point_10( link, ctr, &t, &p ) )
		BOX2D_UPDATE( *box, p.x, p.y );



	if( ln_tanget_point_01( link, ctr, &t, &p ) )
		BOX2D_UPDATE( *box, p.x, p.y );

}
