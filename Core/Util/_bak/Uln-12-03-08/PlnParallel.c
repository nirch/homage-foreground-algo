/***********************
 ***  PlnParallel.c  ***
 ***********************/
#include <string.h>
#include <math.h>
#include "Uigp/igp.h"


#include "Uln/PlnType.h"



int
pln_parallel( pln_type *bpl, pln_type *pl, int i, float gt, float aT, float T0, float T1, pPln_type *pp )
{
	vec2f_type	p0,	v0;
	vec2f_type	p1,	v1;
	float	d0,	d1;
	dPln_type	d;
	vec2f_type	p;

	float	t,	u;


	pln_gt2p( pl, gt, &p );

	if( pln_distance( bpl, &p, &d ) < 0 )
		return( -1 );

	if( d.gt < 0 || d.gt > bpl->len )
		return( -1 );

	if( ABS(d.u) < T0 || ABS(d.u) > T1 )
		return( -1 );


	pln_pv( pl, gt, 2.0, 10, &p0, &v0, &d0 );

	pln_pv( bpl, d.gt, 2.0, 10, &p1, &v1, &d1 );



	u = (p0.x - p1.x) * v1.y - (p0.y - p1.y) * v1.x;


	t = v0.x*v1.x + v0.y*v1.y;
	if( ABS(t) < aT )
		return( -1 );

	pp->pl = pl;
	pp->iPl = i;

	pp->sgt = gt;

	pp->gt = d.gt;
	pp->u = d.u;
	pp->u = u;
	pp->v = v0;

	pp->p = p;

	pp->d = t;

	return( 1 );
}



int
pln_parallel_distance(  pln_type *bpl, pln_type *pl, float dt, float aT, float *u )
{
float	gt;
pPln_type	p;
float	su;
float	n;



	su = 0;
	n = 0;
	for( gt = 10 ; gt < pl->len ; gt += dt ){
		if( pln_parallel( bpl, pl, 0, gt, aT, 8 , 1.5*196, &p ) > 0 ){
			su += p.u;
			n++;
		}
	}

	if( n <= 0 )	return( -1 );

	*u = su / n;


	return( n );
}



void
pPln_reorder( pPln_type a[], int n )
{
	int	i,	j;

	for( i = 1 ; i < n ; i++ ){

		pPln_type p = a[i];
		for( j = i ; j > 0 ; j-- ){
			if( a[j-1].gt < p.gt )	break;
			a[j] = a[j-1];
		}

		a[j] = p;
	}
}


void
pPln_inverse( pPln_type *p )
{
	p->v.x = -p->v.x;
	p->v.y = -p->v.y;

	p->sgt = p->pl->len - p->sgt;

	p->d = -p->d;
}