// WndInner.cpp : implementation file
//

#include <stdio.h>
#include <math.h>

#ifdef _DEBUG
#define _DUMP
#endif

#include "Uigp/igp.h"
#include "Umath/Matrix2Type.h"
#include "Umath/EigenType.h"


#include "PlnType.h"


int
pln_eigen( pln_type *pl, float dt, eigen2d_type *e )
{
	matrix2_type	m;
	vec2f_type	p;
	float	x,	y;
	double	sx,	sy,	sxx,	sxy,	syy;
	int	n;
	float	t;



	sx = sy = sxx = sxy = syy = 0;


	for( t = 0, n = 0 ; t < pl->len ; t += dt ){

		pln_gt2p( pl, t, &p );


		x = p.x;
		y = p.y;


		sx += x;
		sy += y;

		sxx += x*x;
		sxy += x*y;
		syy += y*y;
		n++;
	}

	sx /= n;
	sy /= n;

	m.a00 = sxx / n - sx*sx;
	m.a01 = sxy / n - sx*sy;
	m.a11 = syy / n - sy*sy;
	m.a10 = m.a01;


	e->p.x = sx;
	e->p.y = sy;



	matrix2S_eigen( &m, &e->e1, &e->v1, &e->e2 );

	VEC2D_RIGHT( e->v1, e->v2 );


	e->r = e->e2/ e->e1;



	return( n );
}




pt2dA_type *
pln_apt( pln_type *pl, float dt )
{

	vec2f_type	p;
	float	t;



	pt2dA_type *apt = pt2dA_alloc( pl->len /dt + 1 );



	for( t = 0 ; t < pl->len ; t += dt ){

		pln_gt2p( pl, t, &p );




		pt2d_type *pt = &apt->a[apt->nA++];

		pt->p = p;

	}


	return( apt );


}
