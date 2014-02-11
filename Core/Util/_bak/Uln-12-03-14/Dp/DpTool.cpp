
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<string.h>


#include	"Uigp/igp.h"


#include "Uln/PlnType.h"
#include "Uln/CrPlnType.h"

#include	"DpType.h"



static void	pt2dA_group_nv( pt2dA_type *apt, int iGroup, vec2f_type *nv );


static int	dpA_set( dp_type *dr, plnA_type *al, float R, pt2dA_type *apt );

static void	dpA_clear( dpA_type *ad, float angle );




dpA_type *
dpA_alloc( box2i *b, int dxy )
{
dpA_type *ad;
int	ni,	nj;
int	i,	j;
vec2f_type	p0,	p;
dp_type	*dr;

	ad = (dpA_type * )malloc( sizeof(dpA_type));

	nj = ( b->x1 - b->x0)/dxy + 3;
	ni = ( b->y1 - b->y0)/dxy + 3;

	ad->Ni = ni;
	ad->Nj = nj;

	ad->a = ( dp_type *) malloc( ad->Ni*ad->Nj*sizeof(dp_type));

	ad->dxy = dxy;
	ad->inv_dxy = 1.0/ ad->dxy;

	ad->p0.x = b->y0 - dxy;
	ad->p0.y = b->x0 - dxy;

	p0.x = b->y0 - 0.5*dxy;
	p0.y = b->x0 - 0.5*dxy;

//	for( i = 0, p.x = p0.x + 0.5*dxy ; i < ad->Ni ; i++, p.x += dxy ){
//		dr = dp( ad, i, 0 );
//		for( j = 0, p.y = p0.y + 0.5*dxy ; j < ad->Nj ; j++, p.y += dxy, dr++ ){

	for( i = 0, p.x = ad->p0.x + 0.5*dxy ; i < ad->Ni ; i++, p.x += dxy ){
			dr = DPA( ad, i, 0 );
			for( j = 0, p.y = ad->p0.y + 0.5*dxy ; j < ad->Nj ; j++, p.y += dxy, dr++ ){

			dr->p = p;
			dr->no = 0;
		}
	}

	return( ad );
}


void
dpA_clear( dpA_type *ad )
{
dp_type	*dr;
int	i,	j;

	for( i = 0; i < ad->Ni ; i++ ){
		dr = DPA( ad, i, 0 );
		for( j = 0 ; j < ad->Nj ; j++, dr++ ){
			dr->no = 0;
		}
	}
}

void
dpA_destroy( dpA_type *ad )
{
	free( ad->a );
	free( ad );
}


void
dpA_set( dpA_type *ad,  plnA_type *al, float R )
{
dp_type	*dr;
int	i,	j;
pt2dA_type	*apt;

	apt = pt2dA_alloc( 256 );

	for( i = 0; i < ad->Ni ; i++ ){
		dr = DPA( ad, i, 0 );
		for( j = 0 ; j < ad->Nj ; j++, dr++ ){
			dpA_set(  dr, al, R, apt );
		}
	}

	pt2dA_destroy( apt );



	dpA_clear( ad, 15 );
}

//void	pln_tangetS( pln_type *pl, float gt, vec2f_type *v );

static int
dpA_set( dp_type *dr, plnA_type *al, float R, pt2dA_type *apt )
{
pln_type	*pl;
dPln_type	d;
int	i;

pt2d_type	*pt;
vec2f_type	n;
float	t;


	apt->nP = 0;

	for( i = 0 ; i < al->nA ; i++ ){
		pl = al->a[i];

		if( pl->link == NULL )	continue;


		if( ln_distance( &pl->ctr, pl->link, NULL, &dr->p, &d.l, &d.u, &d.t, &d.gt ) < 0 )
			continue;

		if( ABS(d.u) > R )	continue;

		t = PUSH_TO_RANGE( d.t, 0, d.l->len );

		pt = &apt->p[apt->nP++];
		ln_tanget( d.l, t, &pt->n );


		pln_tangetS( pl, d.gt, &n );
		pt->n = n;

	}

	if( apt->nP < 0 )
		return( -1 );



	pt2dA_group_n( apt, 0.5*22.5 );

	int iGroup,	no;
	pt2dA_group_max( apt, &iGroup, &no );

	if( no <= 1 )
		return( -1 );

	pt2dA_group_nv( apt, iGroup, &dr->v );
	dr->no = no;

	return( 1 );
}


static void
pt2dA_group_nv( pt2dA_type *apt, int iGroup, vec2f_type *nv )
{
pt2d_type	*pt;
vec2f_type	v,	n;
float	t;
int	i;

	int nV = 0;
	v.x = v.y = 0;
	for( i = 0 ; i < apt->nP ; i++ ){
		pt = &apt->p[i];
		if( pt->group != iGroup )
			continue;

		if( nV == 0 ){
			v = pt->n;
			nV = 1;

			n = pt->n;
			continue;
		}

		if( n.x * pt->n.x +  n.y * pt->n.y > 0 ){
			v.x += pt->n.x;
			v.y += pt->n.y;
		}
		else	{
			v.x -= pt->n.x;
			v.y -= pt->n.y;
		}
		nV++;
	}

	t = hypot( v.x, v.y );

	v.x /= t;
	v.y /= t;

	*nv = v;
}






static void	dpA_clear_1( dpA_type *ad, int i00, int j00, float aT );


static void
dpA_clear( dpA_type *ad, float angle )
{
int	i,	j;
float	aT;

	aT = cos( ANGLE_D2R(angle) );

	for( i = 0; i < ad->Ni ; i++ ){
		for( j = 0 ; j < ad->Nj ; j++ ){
			dpA_clear_1( ad, i, j, aT );
		}
	}
}

static void
dpA_clear_1( dpA_type *ad, int i00, int j00, float aT )
{
	dp_type	*dr,	*dr0;
	int	i,	j,	i0,	i1,	j0,	j1,	n;
	float	t;


	dr0 = DPA( ad, i00, j00 );
	if( dr0->no == 0 )	return;

	i1 = i00 + 2;
	i0 = i00 - 1;

	j1 = j00 + 2;
	j0 = j00 - 1;

	if( i0 < 0 )	i0 = 0;
	if( i1 > ad->Ni )	i1 = ad->Ni;
	if( j0 < 0 )	j0 = 0;
	if( j1 > ad->Nj )	j1 = ad->Nj;


	
	for( i = i0, n = 0 ; i < i1 ; i++ ){
		dr = DPA( ad, i, j0 );
		for( j = j0 ; j < j1 ; j++, dr++ ){
			if( dr == dr0 || dr->no == 0 )	continue;
			
		
			t = dr->v.x * dr0->v.x + dr->v.y * dr0->v.y;
			if( ABS(t) >= aT ){
				n++;
				continue;
			}

			if( dr->no <= dr0->no )	continue;

//			t = dr->v.x * dr0->v.x + dr->v.y * dr0->v.y;

			if( ABS(t) < aT ){
				dr0->no = 0;
				return;
			}
			

		}
	}

	if( n == 0 )
		dr0->no = 0;

}


#ifdef _AA_
void
dpA_draw( gpw_type *gpw, dpA_type *ad )
{
	dp_type	*dr;
	int	i,	j;
	vec2f_type	p1;


	for( i = 0; i < ad->Ni ; i++ ){
		dr = DPA( ad, i, 0 );
		for( j = 0 ; j < ad->Nj ; j++, dr++ ){
			if( dr->no <= 1 )	continue;

			p1.x = dr->p.x + 20 * dr->v.x;
			p1.y = dr->p.y + 20 * dr->v.y;


			gpw_line( gpw, dr->p.x, dr->p.y, p1.x, p1.y, GREEN ); 
			gpw_marker_rectangle( gpw, dr->p.x, dr->p.y, 1, BLUE ); 

		}
	}
}
#endif



//void
//pln_tangetS( pln_type *pl, float gt, vec2f_type *v )
//{
//	pt2dA_type	*apt;
//	vec2f_type	pd;
//	float	t0,	t1,	dt,	d;
//	int	n;
//
//	apt = pt2dA_alloc( 100 );
//
//
//	gt = PUSH_TO_RANGE( gt, 10, pl->len-10 );
//
//	dt = 2.0;
//	n = pl->len / dt;
//	if( n > 20 )	n = 20;
//
//	t0 = gt - 5*dt;
//	if( t0 < 0 )	t0 = 0;
//	t1 = gt + 5*dt;
//	if( t1 > pl->len )	t1 = pl->len;
//
//	n = (t1 - t0)/dt;
//	pln_sample( pl, t0, dt, n, 0, apt );
//
//	pt2d_approximate_line_pv( apt, 0, apt->nP, &pd, v, &d );
//
//	VEC2D_SWAP( *v );
//
//
//	pt2dA_destroy( apt );
//}