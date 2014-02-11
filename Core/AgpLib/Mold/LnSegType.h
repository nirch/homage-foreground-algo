/************************
 ***    LnSegType.h   ***
 ************************/
 
#ifndef         _LN_SEG_H_
#define         _LN_SEG_H_


#include        "Uigp/igp.h"
#include		"GpType/LinkType.h"
#include		"UGeoApp/GeoApp.h"

#include	"Contour/LinkDisType.h"

#include	"LnDisType.h"



#ifdef __cplusplus
extern "C" {
#endif




struct lnAtt_type;


typedef struct lnSeg_type {

	link_type	*link;

	link_type	*l0,	*l1;
	float		t0,	t1;


	// AUX
	float	gt0,	gt1;
	float	len;


	struct lnAtt_type	*att;

	struct lnSeg_type	*next;

} lnSeg_type;


typedef lnSeg_type lnSec_type;


lnSeg_type *	lnSeg_alloc();

lnSeg_type *	lnSeg_create( vec2d *ctr, link_type *link );
lnSeg_type *	lnSeg_createN( link_type *link, link_type *l0, float t0, link_type *l1, float t1 );


void	lnSegL_destroy( lnSeg_type *lsL, int Flink );

void	lnSeg_destroy( lnSeg_type *ls, int Flink );


void	lnSeg_set( lnSeg_type *ls, vec2d *ctr, link_type *link );
void	lnSeg_setN( lnSeg_type *ls, link_type *link, link_type *l0, float t0,
										link_type *l1, float t1 );
void	lnSeg_setG( lnSeg_type *ls, link_type *link, float gt0, float gt1 );


void	lnSeg_setG_begin( lnSeg_type *ls, float gt0 );

void	lnSeg_setG_end( lnSeg_type *ls, float gt1 );


lnSeg_type *	lnSeg_make_copy( lnSeg_type *ls0, int Flink );


void	lnSeg_inverse( lnSeg_type *ls );


void	lnSeg_set_aux( lnSeg_type *ls );


void	lnSegL_insert( lnSeg_type **lsL, lnSeg_type *ls );


int		lnSegL_get_polylink_copy( lnSeg_type *lsL, link_type ***alink  );

int		lnSeg_polylink_copy( lnSeg_type *ls, vec2d *ctr, link_type **link  );

int		lnSeg_gt_polylink_copy( lnSeg_type *ls, float gt0, float gt1,
								vec2d *ctr, link_type **link  );


void	lnSeg_gapp( lnSeg_type *ls, gapp_type *gapp );


void	lnSegL_quantize( lnSeg_type *lsL, float dt );



float	lnSeg_gt_dist( lnSeg_type *ls, float gt, vec2d *ctr, link_type *link );



void	lnSeg_dis( lnSeg_type *ls, vec2d *ctr, link_type *link, lnDisA_type *ad );

void	lnSeg_disA( lnSeg_type *ls,linkDisArray_type *ald, lnDisA_type *ad );


lnSeg_type *	lnSegL_select( lnSeg_type *lsL, vec2d *p );


// for Debug
char lnSeg_check( lnSeg_type *ls );



#ifdef __cplusplus
}
#endif


#endif 