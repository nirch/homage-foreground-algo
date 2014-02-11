/***********************************
 ***    Pt2ApproximateLinePn.c   ***
 ***********************************/


#include	<string.h>
#include	<stdio.h>
#include	<math.h>
#include	"Uigp/igp.h"

#include	"Umath/Matrix2Type.h"

#include	"Ucamera/Pt2dType.h"





int
pt2d_approximate_line_pv( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v, float *d )
{
matrix2_type	m;
vec2d_type	D;
float	x,	y;
double	sx,	sy,	sxx,	sxy,	syy;
int	i,	n;

float	e1,	e2;
float	t0,	t1;


	matrix2_zero( &m );
	D.x = D.y = 0;


	if( i0 < 0 )
		i0 = 0;

	if( i1 > apt->nP )
		i1 = apt->nP;

	sx = sy = sxx = sxy = syy = 0;


	for( i = i0, n = 0 ; i < i1 ; i++ ){


		x = apt->p[i].p.x;
		y = apt->p[i].p.y;


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


	p->x = sx;
	p->y = sy;



	matrix2S_eigen( &m, &e1, v, &e2 );


	// direction
	t0 = (apt->p[i0].p.x - p->x)*v->x + (apt->p[i0].p.y - p->y)*v->y;
	t1 = (apt->p[i1-1].p.x - p->x)*v->x + (apt->p[i1-1].p.y - p->y)*v->y;

	*d = 0.5*(t1 - t0);

	if( t1 < t0 ){
		v->x = -v->x;
		v->y = -v->y;

		*d = - *d;
	}


	return( n );
}



float
pt2d_approximate_line_pv_test( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v, float D, int *nD )
{
vec2d_type	u;
int	i;

float	d0,	d,	dMax;



	VEC2D_LEFT( *v, u );

	d0 = p->x * u.x + p->y * u.y;

	*nD = 0;
	dMax = 0;
	for( i = i0 ; i < i1 ; i++ ){
		pt2d_type	*pt = &apt->p[i];

		d = pt->p.x * u.x + pt->p.y * u.y - d0;
	
		pt->r = d;

		if( ABS(d) > D )	(*nD)++;

		if( ABS(d) > ABS(dMax) ){
			dMax = d;
		}
	}

	return( dMax );
}






typedef struct slT_type {
	int	i0;
	int	i1;

	float m;
	int	iM;
} slT_type;

int
pt2d_approximate_line_pv_split( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v )
{
	pt2d_type	*pt;
	vec2d_type	u;
	int	i;

	float	d0;
	float	d;
	int		iMax;

	slT_type	aS[100],	*sl;
	int	nS;


	VEC2D_LEFT( *v, u );

	d0 = p->x * u.x + p->y * u.y;


	nS = 0;
	sl = &aS[nS++];

	pt = &apt->p[i0];
	sl->m = pt->p.x * u.x + pt->p.y * u.y - d0;
	sl->i0 = sl->i1 = sl->iM = i0;


	for( i = i0+2 ; i < i1-1 ; i++ ){
		pt2d_type	*pt = &apt->p[i];

		d = pt->p.x * u.x + pt->p.y * u.y - d0 ;

		if( (sl->m < 0) == ( d < 0 ) ){

			if( ABS(d) > ABS(sl->m) ){
				sl->m = d;
				sl->iM = i;
			}

			sl->i1 = i;
			continue;
		}

	
		sl = &aS[nS++];
		sl->m = d;
		sl->i0 = sl->i1 = sl->iM = i;
	}


	if( nS == 1 )
		return( aS[0].iM );


	if( nS == 2 ){
		iMax = (aS[0].i1 + aS[1].i0)>> 1;
		return( iMax );


		if(  ABS(aS[0].m) > ABS(aS[1].m) )
			return( aS[0].iM );
		return( aS[1].iM );
	}
	
	iMax = 1;
	for( i = 2 ; i < nS -1 ; i++ ){
		if( ABS(aS[i].m) > ABS(aS[iMax].m) )
			iMax = i;
	}


	return( aS[iMax].iM );
}