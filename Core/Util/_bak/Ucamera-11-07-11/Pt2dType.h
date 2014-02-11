/***
 ***    author:		Yoram Elichai   yorame@gmail.com
 ***    Copyright (C) 2000 - All Rights Reserved
 ***/

/**********************
 ***   Pt2dType.h   ***
 **********************/

#ifndef	_PT2D_TYPE_
#define _PT2D_TYPE_

#ifdef __cplusplus
extern "C" {
#endif

#include "Uvec/vec2d.h"
#include "Uln/LnType.h"
#include "Ubox/Box2d.h"

#include "UPoly/Poly1d4Type.h"


#define	PT2D_2		0

#define	PT2D_4		1

#define	PT2D_4V		2


#define PT2D_AXIS_XY	0
#define PT2D_AXIS_YX	1


	// p2d	-  2d point

typedef struct pt2d_type {
	vec2f_type	p;

	vec2f_type	n;

	float	r;	// radius

	// aux
	int	id;
	int	group;

	int	i[2];

	struct pt2d_type	*np;
} pt2d_type ;



typedef struct pt2dA_type {
	int	nP,	NP;

	int	type;

	int	axis;

	int	nGroup;
	int	mGroup;

	box2f_type	box;

	struct pt2dG_type	*gpt;

	pt2d_type	*p;

} pt2dA_type;



typedef struct pt2dG_type {
	int	Ni,	Nj;

	float	d;
	float	inv_d;

	box2f_type	box;

	pt2d_type	**p;

} pt2dG_type;




	// Pt2dATool.c
pt2dA_type *	pt2dA_alloc( int n );

pt2dA_type *	pt2dA_realloc( pt2dA_type*apt, int n );

void	pt2dA_destroy( pt2dA_type *av );

pt2dA_type *pt2dA_set( pt2dA_type *apt, vec2fA_type *av );


int	pt2dA_write_to_file( pt2dA_type *av, char *file );

int	pt2dA_read_from_file( pt2dA_type **av, char *file );


void	pt2dA_dump( pt2dA_type *apt, char *prefix, int index, char *suffix );

pt2dA_type *	pt2dA_copy( pt2dA_type *apt, pt2dA_type *capt );

pt2dA_type *	pt2dA_copy_box( pt2dA_type *apt, box2i *box, pt2dA_type *capt );


pt2dA_type *	pt2dA_copy_group( pt2dA_type *apt, int group, int no );

pt2dA_type *	pt2dA_copy_neighbor ( pt2dA_type *apt, vec2f_type *p, float D, pt2dA_type *capt );

pt2dA_type *	pt2dA_copy_neighbor_id( pt2dA_type *apt, vec2f_type *p, float D, int mId, pt2dA_type *capt );

void	pt2dA_nGroup( pt2dA_type *apt );

void	pt2dA_set_default_group( pt2dA_type *apt );

int		pt2dA_select( pt2dA_type *apt, vec2f_type *p, float dis );

int		pt2dA_neighbor ( pt2dA_type *apt, vec2f_type *p, float D );

int		pt2dA_neighbor_remove( pt2dA_type *apt, vec2f_type *p, float D );

void	pt2dA_remove_box( pt2dA_type *apt, box2i *box );

void pt2dA_remove_group( pt2dA_type *apt, int group );

int		pt2dA_no( pt2dA_type *apt, box2f_type *b );
int		pt2dA_nCircle( pt2dA_type *apt, vec2f_type *p, float r );


void	pt2dA_translate( pt2dA_type *apt, float x, float y );

void	pt2d_tanget_line( pt2d_type *pt0, pt2d_type *pt1, vec2f_type *p0, vec2f_type *p1, vec2f_type *v );

void	pt2dA_moment( pt2dA_type *apt, vec2f_type *p, vec2f_type *v, float *e1, float *e2 );

pt2dA_type	*	pt2dA_append( pt2dA_type *apt, pt2dA_type *sapt );

void	pt2dA_set_groupId( pt2dA_type *apt, int iGroup );

void	pt2dA_box( pt2dA_type *apt );




	// Pt2dGroup.cpp
void	pt2dA_groupM( pt2dA_type *apt, float dis );

void	pt2dA_group( pt2dA_type *apt, float dis );

void	pt2dA_group_n( pt2dA_type *apt, float angle );

int		pt2dA_group_max( pt2dA_type *apt, int *iG, int *no );



	// Pt2dMask.cpp
void	pt2dA_mask( pt2dA_type *apt, pt2dA_type *mapt, float dis );


	// Pt2dTriangleFilter.cpp
pt2dA_type *	pt2d_triangle_filter( pt2dA_type *apt, float R, float T );


#include "Pt2dGroupType.h"


	//Pt2dApproximateLine.c
int	pt2d_approximate_line( pt2dA_type *apt, int i0, int di, vec2f_type *p0, float dis, vec2f_type *p, vec2f_type *v );

int	pt2d_approximate_line3( pt2dA_type *apt, int i0, int di, vec2f_type *p0, vec2f_type *u0, float dis, vec2f_type *p, vec2f_type *v );

	
//Pt2dApproximateAxB.c
int	pt2d_approximate_Ax_B( pt2dA_type *apt, int i0, int i1, float *a, float *b );


	//Pt2dApproximatePn.c
int		pt2d_approximate_line_pv( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v );

float	pt2d_approximate_line_pv_test( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v, float D, int *nD );

int		pt2d_approximate_line_pv_split( pt2dA_type *apt, int i0, int i1, vec2f_type *p, vec2f_type *v );


	//Pt2dApproximateLink.c
void	pt2d_approximate_linkO( pt2dA_type *apt, vec2f_type *ctr, ln_type **link );

//void	pt2d_approximate_link( pt2dA_type *apt, vec2f_type *ctr, ln_type **gelm );
void	pt2d_approximate_link( pt2dA_type *apt, int i0, int i1, vec2d *ctr, ln_type **link );

pt2dA_type *	pt2d_from_polylink(vec2f_type *ctr, ln_type *link, float d );


void pt2d_distance_from_polylink( pt2dA_type *apt, vec2f_type *ctr, ln_type *link );


	// Pt2ApproximatyePolynim.c
int	pt2d_approximate_polynom_1( pt2dA_type *apt, int i0, int di, vec2d *p0, vec2d *v0, float maxDv, poly1d4_type *pl );

int	pt2d_approximate_polynom_2( pt2dA_type *apt, vec2f_type *p0, vec2f_type *v0, int i0, int i1, poly1d4_type *pl );

int	pt2d_approximate_polynom_2O( pt2dA_type *apt, int i0, int di, vec2f_type *p0, vec2f_type *u0, float dis, poly1d4_type *pl );



	// Pt2dCurvtur.c
void	pt2dA_curvtur( pt2dA_type *apt );

float	pt2dA_curvtur_1( pt2dA_type *apt, vec2f_type *p0,int i0, int i1, vec2f_type *n, float *curvtur );

pt2dA_type *	pt2dA_smooth( pt2dA_type *apt, float r, pt2dA_type	*tapt );


	// Pt2dLine.c
pt2dA_type *	pt2dA_get_pt( pt2dA_type *apt, int i0, pt2dA_type *capt );

int				pt2dA_get_ptN( pt2dA_type *apt, int i0, int i1, int nP, pt2dA_type *capt );

int	pt2dA_get_prev( pt2dA_type *apt, int i0 );

int	pt2dA_get_next( pt2dA_type *apt, int i0 );

int	pt2dA_get_nextN( pt2dA_type *apt, int i0, int prev );





	//   Pt2dApproximateAb.c

// y = 0*x + b
int	pt2dA_app_b( pt2dA_type *apt, int i0, int i1, float a0, float b0, float maxY, float *b );

// y = a*x + b
int	pt2dA_app_ab( pt2dA_type *apt, int i0, int i1, float a0, float b0, float maxY, float *a, float *b );




#ifdef __cplusplus
}
#endif

#endif
