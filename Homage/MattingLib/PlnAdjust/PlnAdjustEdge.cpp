
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<string.h>


#ifdef _DEBUG
#define _DUMP 
#endif


#include	"Uigp/igp.h"
#include	"Utime\GpTime.h"
#include	"Ulog/Log.h"


#include "Uln/PlnType.h"

#include "PlnAdjust.h"


typedef struct seg_type {
	int i0;
	int i1;

	int	id;
	float d;

	float dt;
} seg_type;


int	pln_adjust_edge( pln_type *pl, plnA_type *eapl, float height, int iFrame );

static int	pt2dA_distane_plnA( pt2dA_type *apt, plnA_type *apl );

static int	pln_range( pln_type *pl, float h, float *gt0, float *gt1 );


static int	pt2dA_seg( pt2dA_type *apt, seg_type as[], int *nS );

static void	seg_printf( char *title, seg_type *as, int nS, FILE *fp  );

static int	pt2dA_seg_ended( pt2dA_type *apt, seg_type as[], int *nS );

static int	pt2dA_seg_finish( pln_type *pl, pt2dA_type *apt, plnA_type *eapl, seg_type as[], int nS );

static int	pt2dA_seg_finish1( pln_type *pl, pt2dA_type *apt, plnA_type *eapl, seg_type as[], int nS );

static int	pt2dA_seg_union( pt2dA_type *apt, seg_type as[], int *nS );


static int	pt2dA_seg_filter_order( pt2dA_type *apt, seg_type as[], int *nS );
static int	pt2dA_seg_filter_order( pt2dA_type *apt, seg_type *s );







static int	pt2dA_seg_filter_overlap( pt2dA_type *apt, seg_type as[], int *nS );

static int	pt2dA_seg_filter_overlap( pt2dA_type *apt, seg_type as[], int nS, int i0 );

static int	pt2dA_seg_union2( pt2dA_type *apt, seg_type as[], int *nS );



int
plnA_adjust_edge( plnA_type *apl, plnA_type *eapl, float height, int iFrame )
{
	if( apl->nA <= 0 )	return( 1 );

	int ret = pln_adjust_edge( apl->a[0], eapl, height, iFrame );

	return( ret );
}


int
pln_adjust_edge( pln_type *pl, plnA_type *eapl, float height, int iFrame )
{
float gt0, gt1;

	pln_range( pl, height, &gt0, &gt1 );

	pt2dA_type *apt = pln_sampleP( pl, gt0, gt1, 1.0, NULL );

	pt2dA_distane_plnA( apt, eapl );

	apt->type = PT2D_4V;
	PT2DA_DUMP( apt, "edge", iFrame, "aa" );

	seg_type	as[100];
	int nS;

	pt2dA_seg( apt, as, &nS );
#ifdef _DUMP
	seg_printf( "seg", as, nS, stdout );
#endif

	pt2dA_seg_filter_overlap( apt, as, &nS );
#ifdef _DUMP
	seg_printf( "overlap", as, nS, stdout );
#endif


	pt2dA_seg_union( apt, as, &nS );
#ifdef _DUMP
	seg_printf( "union", as, nS, stdout );
#endif





	pt2dA_seg_ended( apt, as, &nS );
#ifdef _DUMP
	seg_printf( "end", as, nS, stdout );
#endif

	pt2dA_seg_filter_order( apt, as, &nS );
#ifdef _DUMP
	seg_printf( "order", as, nS, stdout );
#endif


	pt2dA_seg_union2( apt, as, &nS );
#ifdef _DUMP
	seg_printf( "union2", as, nS, stdout );
#endif



	pt2dA_seg_finish1( pl, apt, eapl, as, nS );


//	PLN_DUMP( pl, "pl",1, NULL );

	return( 1 );

}

#ifdef _AA_
static int
pt2dA_seg_finish( pln_type *pl, pt2dA_type *apt, plnA_type *eapl, seg_type as[], int nS )
{
int	i;

	for( i = nS-1 ; i >=0  ; i-- ){
		seg_type *s = &as[i];

		pln_type *epl;
		if( apt->a[s->i0].r > apt->a[s->i1].r ){
			epl = pln_copy_sub( eapl->a[s->id], apt->a[s->i1].r, apt->a[s->i0].r );
			pln_inverse( epl );
		}
		else
			epl = pln_copy_sub( eapl->a[s->id], apt->a[s->i0].r, apt->a[s->i1].r );


		
		pln_type *pl1 = pln_copy_sub( pl, apt->a[s->i1].f, pl->len );

		pln_trim( pl, F_END, pl->len - apt->a[s->i0].f );
		pln_append( pl, epl );
		pln_append( pl, pl1 );

		//break;
	}

	return( 1 );
}
#endif

static int
pt2dA_seg_finish1( pln_type *pl, pt2dA_type *apt, plnA_type *eapl, seg_type as[], int nS )
{
int	i;
pln_type	*apl[128];
seg_type *s;

	int n = 0;
	

	for( i = 0 ; i < nS  ; i++ ){
		s = &as[i];
		
		pln_type *epl;
		if( apt->a[s->i0].r > apt->a[s->i1].r ){
			epl = pln_copy_sub( eapl->a[s->id], apt->a[s->i1].r, apt->a[s->i0].r );
			pln_inverse( epl );
		}
		else
			epl = pln_copy_sub( eapl->a[s->id], apt->a[s->i0].r, apt->a[s->i1].r );

		apl[n++] = epl;

		if( i < nS-1 ){
			int i0 = s->i1;
			int i1 = ( as[i+1].i0 < as[i+1].i1 )? as[i+1].i0 : as[i+1].i1;


			 if( apt->a[i1].f - apt->a[i0].f > 10 )
				 apl[n++] = pln_copy_sub( pl, apt->a[i0+5].f, apt->a[i1-5].f );
		}
		else
			apl[n++] = pln_copy_sub( pl, apt->a[s->i1+5].f, pl->len );

//			apl[n++] = pln_copy_sub( pl, 0, apt->a[s->i0].f-5 );




		
	}

//	s = &as[nS-1];
//	apl[n++] = pln_copy_sub( pl, apt->a[s->i1].f, pl->len );

	s = &as[0];
	float t = apt->a[s->i0].f - 5;
	if( t < 1.0 )	t = 1.0;
	pln_trim( pl, F_END, pl->len - t );

	for( i = 0 ; i < n ; i++ )
		pln_append(pl, apl[i] );


	return( 1 );
}
		

static int
pt2dA_distane_plnA( pt2dA_type *apt, plnA_type *apl )
{
int	i;
vec2f_type p;
dPln_type d;
pln_type *spl;

	for( i = 0 ; i < apt->nA ; i++ ){
		pt2d_type *pt = &apt->a[i];

		p.x = pt->p.y;
		p.y = pt->p.x;
	

		pt->group = plnA_distance( apl, &p, 10.0, &spl, &d );
		pt->n.x = 1.0;
		pt->n.y = 0;
//		pt->f = d.u;
		pt->n.y = d.u;

		if( pt->group < 0 )	continue;

		pt->r = d.gt;
	}

	return( 1 );
}


static int
pln_range( pln_type *pl, float h, float *gt0, float *gt1 )
{

	vec2f_type v;
	ln_type *l;

	*gt0 = 0;
	*gt1 = 0;

	for( l = pl->link, v = pl->ctr ; l != NULL ; l = LN_NEXT(l) ){

		*gt1 += l->len;
		v.x += l->v.x;
		v.y += l->v.y;

		if( v.x > h - 0.1 && *gt1 > 10.0 )
			break;
	}


	return( 1 );
}


static int	pt2dA_seg_ended( pt2dA_type *apt, seg_type *s );

static int
pt2dA_seg_ended( pt2dA_type *apt, seg_type as[], int *nS )
{
int	i,	j;

	for( i =0, j =0 ; i < *nS ; i++ ){
		pt2dA_seg_ended( apt, &as[i] );
		if( as[i].i1 - as[i].i0 > 8 )
			as[j++] = as[i];
	}

	*nS = j;

	return( 1 );
}


static int
pt2dA_seg_ended( pt2dA_type *apt, seg_type *s )
{
int	i;

	for( i = s->i0 ; i < s->i1 - 4 ; i++ ){
		float t1 = apt->a[i+2].r - apt->a[i+1].r;
		float t0 = apt->a[i+1].r - apt->a[i].r;

		float t2 = t0 + t1;
		if( ABS( t2 ) > 1.5 )	break;
	}

	s->i0 = i;

	for( i = s->i1 ; i > s->i0 + 4 ; i-- ){
		float t1 = apt->a[i-2].r - apt->a[i-1].r;
		float t0 = apt->a[i-1].r - apt->a[i].r;

		float t2 = t0 + t1;
		if( ABS( t2 ) > 1.5 )	break;
	}

	s->i1 = i;

	return( 1  );
}





static int
pt2dA_seg_union( pt2dA_type *apt, seg_type as[], int *nS )
{
	int	i,	j;

	for( i =1, j =0 ; i < *nS ; i++ ){
		if( as[j].id != as[i].id ){
			as[++j] = as[i];
			continue;
		}

		int i1 = as[i].i0;
		int i0 = as[j].i1;


		float dt = apt->a[i1].r - apt->a[i0].r;


		
		if( ABS(dt) < 20 ){
			as[j].i1 = as[i].i1;
			continue;
		}

		as[++j] = as[i];
	}

	*nS = j+1;

	return( 1 );
}


static int	pt2dA_seg_union2( pt2dA_type *apt, seg_type as[], int *nS, int i0 );

static int
pt2dA_seg_union2( pt2dA_type *apt, seg_type as[], int *nS )
{
	int	i;

	for( i = 0 ; i < *nS ;  ){

		if( pt2dA_seg_union2( apt, as, nS, i ) < 0 )
			i++;
	}

	return( 1 );
}


static int
pt2dA_seg_union2( pt2dA_type *apt, seg_type as[], int *nS, int i0 )
{
	int	i;

	for( i = i0 + 1 ; i < *nS ; i++ )
		if( as[i0].id == as[i].id )	break;

	if ( i >= *nS )	return( -1 );



	int k1 = as[i].i0;
	int k0 = as[i0].i1;


	float dt = apt->a[k1].r - apt->a[k0].r;

	if( ABS(dt) > 20 )
		return( -1 );


	as[i0].dt = ( as[i0].dt*(as[i0].i1 - as[i0].i0 + 1)   + as[i].dt*(as[i].i1 - as[i].i0 + 1) )/( as[i].i1 - as[i0].i0 + 1 );
	as[i0].i1 = as[i].i1;


	int di = i - i0;
	(*nS) -=  di;

	for( i = i0 +1 ; i < *nS ; i++ )
		as[i] = as[i+di];



	return( 1 );
}



static int	pt2dA_seg_filter_orderN( pt2dA_type *apt, seg_type *s );


static int
pt2dA_seg_filter_order( pt2dA_type *apt, seg_type as[], int *nS )
{
	int	i,	j;

	for( i =0, j =0 ; i < *nS ; i++ ){


		if( pt2dA_seg_filter_orderN( apt, &as[i] ) < 0 )
			continue;

		as[j++] = as[i];
	}

	*nS = j;

	return( 1 );
}




static int
pt2dA_seg_filter_order( pt2dA_type *apt, seg_type *s )
{
int	i,	iMax;

	iMax = s->i0;
	for( i = s->i0+1 ; i <= s->i1 ; i++ ){
		if( apt->a[iMax].r < apt->a[i].r )
			iMax = i;
	}

	if( apt->a[iMax].r < 6 )
		return( -1 );


	float av0 = 0;
	for( i = s->i0 ; i <= iMax ; i++ )
		av0 += apt->a[i].n.y;

	av0 = av0 / ( iMax- s->i0+1);

	float av1 = 0;
	for( i = iMax ; i <= s->i1 ; i++ )
		av1 += apt->a[i].n.y;

	av1 = av1 / ( s->i1 - iMax + 1);


	if( iMax > 0.5*( s->i0 + s->i1) )
		s->i1 = iMax;
	else s->i0 = iMax;

	return( 1 );
}



static int
pt2dA_seg_filter_orderN( pt2dA_type *apt, seg_type *s )
{
int	i,	iMax;
seg_type as[2];

	iMax = s->i0;
	for( i = s->i0+1 ; i <= s->i1 ; i++ ){
		if( apt->a[iMax].r < apt->a[i].r )
			iMax = i;
	}



	if( iMax < s->i0 + 2 ){
		s->i0 = iMax;
		return( 1 );
	}

	if( iMax > s->i1 - 2 ){
		s->i1 = iMax;
		return( 1 );
	}


	as[0].i0 = s->i0;
	as[0].i1 = iMax;
	as[0].id = s->id;
	as[0].dt = 0;
	for( i = as[0].i0 ; i <= as[0].i1 ; i++ )
		as[0].dt += ABS( apt->a[i].n.y );
	as[0].dt = as[0].dt / ( as[0].i1 - as[0].i0 +1 );


	as[1].i0 = iMax;
	as[1].i1 = s->i1;
	as[1].id = s->id;
	as[1].dt = 0;
	for( i = as[1].i0 ; i <= as[1].i1 ; i++ )
		as[1].dt += ABS( apt->a[i].n.y );
	as[1].dt = as[1].dt / ( as[1].i1 - as[1].i0 +1 );


	if( as[0].dt < as[1].dt )
		*s = as[0];
	else *s = as[1];


	float dt = apt->a[s->i1].r - apt->a[s->i0].r;
	if( s->i1 - s->i0 < 6 || dt < 10 )
		return( -1 );



	return( 1 );
}




static int
pt2dA_seg_filter_overlap( pt2dA_type *apt, seg_type as[], int *nS )
{
	int	i,	j;

	for( i =0, j = 0 ; i < *nS ; i++ ){
		if( as[i].id < 0 )	continue;

		if( pt2dA_seg_filter_overlap( apt, as, *nS, i  ) < 0 )
			continue;

		as[j++] = as[i];
	}

	*nS = j;

	return( 1 );
}


static int
pt2dA_seg_filter_overlap( pt2dA_type *apt, seg_type as[], int nS, int i0 )
{
	int	i;
	seg_type	*s0 = &as[i0];
	for( i = i0+1 ; i < nS ; i++ ){
		seg_type	*s = &as[i];
		if( s->id != s0->id )	continue;

		float t0 = apt->a[s->i0].r;
		float t1 = apt->a[s->i1].r;
		if( t0 > t1 )	{
			float tmp = t0;
			t0 = t1;
			t1 = tmp;
		}


		float t00 = apt->a[s0->i0].r;
		float t01 = apt->a[s0->i1].r;
		if( t00 > t01 )	{
			float tmp = t00;
			t00 = t01;
			t01 = tmp;
		}


		if( t1 < t00 || t01 < t0 )
			continue;


		if( s0->dt > s->dt ){
			s0->id = -1;
			return( -1 );
		}


		s->id = -1;
	}


	return( 1 );
}



static int
pt2dA_seg( pt2dA_type *apt, seg_type as[], int *nS )
{
int	i;
seg_type	*s;

	
	*nS = 0;

	s = NULL;
	for( i = 0 ; i < apt->nA ;  ){

		for( ; i < apt->nA ; i++ ){
			if( apt->p[i].group >= 0 )
				break;
		}

		s = &as[*nS];
		s->i0 = s->i1 = i;
		s->id = apt->a[i].group;
		s->dt = ABS( apt->a[i].n.y );

		for( ; i < apt->nA ; i++ ){
			if( apt->p[i].group != s->id )
				break;

			s->dt += ABS( apt->a[i].n.y );
			s->i1 = i;
		}
		
		if( s->i1 - s->i0 > 4 ){
			s->dt = s->dt / ( s->i1 - s->i0 + 1 );
			*nS += 1;
		}

		s = NULL;
	}

	if( s != NULL && s->i1 - s->i0 > 4 )
		*nS += 1;

	return( *nS );
}

static void
seg_printf( char *title, seg_type *as, int nS, FILE *fp  )
{
int i;
	
	fprintf( fp, "%s\n", title );

	for( i = 0 ; i < nS ; i++ )
		fprintf( fp, "%d %d %d\n", as[i].id, as[i].i0, as[i].i1 );
}