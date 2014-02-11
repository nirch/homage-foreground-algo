/************************
 ***    PlinkType.h   ***
 ************************/
 
#ifndef		_PLINK_TYPE_H_
#define		_PLINK_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif



#include	"Uigp/igp.h"
#include	"Umath/LT2Type.h"
#include	"GpType/LinkType.h"



#define	PL_EMPTY	0
#define	PL_OPEN		1
#define	PL_CLOSE	2
#define	PL_TRANSPARENT	4

typedef	struct plink_type {
	int	state;

	int	range;

	vec2d		ctr;

	link_type	*link;

	float	len;

} plink_type;




plink_type *	plink_alloc();

plink_type *	plink_make_copy( plink_type *p );

void	plink_destroy( plink_type *p );


plink_type *	plink_create( vec2d *ctr, link_type *link, int state, int Fdata );


void	plink_set_state( plink_type *p );

link_type *		plink_next_link( plink_type *pl, link_type *link );

link_type *		plink_prev_link( plink_type *pl, link_type *link );




	// anchor
void	plink_clear_anchor( plink_type *p );

int		plink_anchor_no( plink_type *p );

link_type *		plink_next_anchor( plink_type *pl, link_type *link );

link_type *		plink_prev_anchor( plink_type *pl, link_type *link );



void	plink_affine( plink_type *p, float a, float b, float s, float t );

void	plink_affine_lt2( plink_type *p, lt2_type *lt );


void	plink_simplify( plink_type *p );

void	plink_simplify_len( plink_type *p, float minLen, float maxLen );


// return 1 if dirrection is OK
int		plink_check_dirrection( plink_type *p );

void	plink_change_dirrection( plink_type *p );

// return 1 if p inside p2, else 0
int		plink_inside_plink( plink_type *p, plink_type *p2 );

	// return 1 if p inside pl ( acording to the direction )
int		plink_is_point_inside( plink_type *pl, vec2f_type *p );


// return <0 if p cross p2, else 0
int		plink_check_cross( plink_type *p, plink_type *p2, float d_min, vec2f_type *mp );


	// PlinkUnion.c
int	plink_union( plink_type *pl, plink_type *pl0, float dT );



#ifdef __cplusplus
}
#endif


#endif 
