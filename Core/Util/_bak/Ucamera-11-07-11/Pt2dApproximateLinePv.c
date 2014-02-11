/***********************************
 ***    Pt2ApproximateLinePn.c   ***
 ***********************************/


#include	<string.h>
#include	<stdio.h>
#include	<math.h>
#include	"Uigp/igp.h"

#include	"Umath/Matrix2Type.h"

#include	"Ucamera/Pt2dType.h"


//typedef struct linePv_type {
//	vec2f_type	p;
//
//	vec2f_type	v;
//
//	float	t0,	t1;
//
//	float	r;
//
//} linePn_type;



int
pt2d_approximate_line_pv( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v )
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

	if( t1 < t0 ){
		v->x = -v->x;
		v->y = -v->y;
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

//int
//pt2d_approximate_line_pn_aplit( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v )
//{
//float	rMax;
//int		iMax;
//int	i;
//
//
//
//
//	iMax = -1;
//	rMax = 0;
//
//	for( i = i0+1 ; i < i1-1 ; i++ ){
//		pt2d_type	*pt = &apt->p[i];
//
//		if( pt->r > 0 ){
//			if( apt->p[i-1].r > pt->r ||  apt->p[i+1].r > pt->r )
//				continue;
//		}
//		else	{
//			if( apt->p[i-1].r < pt->r ||  apt->p[i+1].r < pt->r )
//				continue;
//		}
//
//
//		if( ABS( pt->r) > rMax ){
//			rMax = ABS( pt->r );
//			iMax = i;
//		}
//	}
//
//	return( iMax );
//}




int
pt2d_approximate_line_pv_split( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v )
{
pt2d_type	*pt;
vec2d_type	u;
int	i;

float	d0;
float	r0,	r1,	r2,	rMax;
int		iMax;


	VEC2D_LEFT( *v, u );

	d0 = p->x * u.x + p->y * u.y;


	pt = &apt->p[i0+1];
	r0 = pt->p.x * u.x + pt->p.y * u.y - d0;


	pt = &apt->p[i0+2];
	r1 = pt->p.x * u.x + pt->p.y * u.y - d0;


	iMax = -1;
	rMax = 0;

	for( i = i0+2 ; i < i1-1 ; i++ ){
		pt2d_type	*pt = &apt->p[i];

		r2 = pt->p.x * u.x + pt->p.y * u.y - d0 ;

		if( r1 > r0 && r1 > r2 && r0 > 0 && r2 > 0  || r1 < r0 && r1 < r2 && r0 < 0 && r2 < 0){
			r1 = ABS(r1);
			if( r1 > rMax || iMax - i0 < i1 - i && r1 > 2.5 ){
				rMax = r1;
				iMax = i-1;
			}
		}

		r0 = r1;
		r1 = r2;

	}

	return( iMax );
}