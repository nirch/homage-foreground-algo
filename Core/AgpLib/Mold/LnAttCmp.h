/***********************
 ***    LnAttCmp.h   ***
 ***********************/
#ifndef		_LN_ATTCMP_H_
#define		_LN_ATTCMP_H_


#include	"Uigp/igp.h"


#include	"AttPrm.h"
#include	"LnAttcType.h"




typedef struct lnAttCmp_type {

	int	id;	// componnet id

	lnAttc_type	*at0;
	lnAttc_type *at1;
	int	i0,	i1;


	float	cgt0,	cgt1;
	float	clen;
	float	gap;


	float	contourLen;


	// aux
	int	use;


	struct lnAttCmp_type	*next;
} lnAttCmp_type;


lnAttCmp_type *	lnAttCmp_alloc();

lnAttCmp_type *	lnAttCmp_make_copy( lnAttCmp_type *c0 );

void	lnAttCmpL_destroy( lnAttCmp_type *cmpL );

void	lnAttCmpL_insert( lnAttCmp_type **cmpL, lnAttCmp_type *cmp );

void	lnAttCmpL_Oinsert( lnAttCmp_type **cmpL, lnAttCmp_type *c0 );


int		lnAttCmp_gt( lnAttCmp_type *c, lnAttCmp_type *nc, float *gt );






lnAttCmp_type *	lnAttCmpL_get( lnAttCmp_type *cmpL, int iCmp );


void	lnAttCmp_connect( lnAttc_type *aAt[], int nAt,
								lnAttCmp_type **cmpL,
								lnAttCmp_type *c, lnAttCmp_type *c1 );

void	lnAttCmpL_delete( lnAttCmp_type **cmpL, lnAttCmp_type *c0 );


void	lnAttCmpL_clen( lnAttCmp_type *cmpL );

void	lnAttCmp_len( lnAttCmp_type *c );


float	lnAttCmpL_cover_len( lnAttCmp_type *cmpL );





void	lnAttCmpL_union1( lnAttc_type *aAt[], int nAt, lnAttCmp_type **cmpL );


void	lnAttCmpL_clear_use( lnAttCmp_type *cmpL );



int		lnAttCmpL_get_polylink_copy( lnAttCmp_type  *cmpL, link_type *contour,
									link_type ***alink  );

int		lnAttCmp_polylink_copy( lnAttCmp_type  *cmp, link_type *contour,
									vec2d *ctr, link_type **link  );

int		lnAttCmpL_tied( lnAttCmp_type *cmpL, link_type *contour,
									vec2d *ctr, link_type **link  );


void	lnAttCmp_pos( lnAttCmp_type *cmp );

void	lnAttCmp_print( lnAttCmp_type *c, char *file );



		// LnAttCmpBuild.c
void	lnAttCmp_build( lnAttc_type *aAt[], int nAt, float contourLen, lnAttCmp_type **lnCmp );




		// LnAttCmpFinal.c
lnAttCmp_type *	lnAttCmp_final_best( lnAttCmp_type *cmpL, link_type *contour, struct  attPrm_type *attPrm );

lnAttCmp_type *	lnAttCmp_final( lnAttCmp_type *cmpL, struct attPrm_type *attPrm );

lnAttCmp_type *	lnAttCmp_final_from( lnAttCmp_type *cmpL, lnAttCmp_type *c0 );

void	lnAttCmpL_filter_overlap( lnAttCmp_type *cmpL );



		// LnAttCmpStep.c
int	lnAttCmp_step( lnAttCmp_type *cmpL, link_type *contour, float X[] );


	/* LnAttCmpStep4.c */
int	lnAttCmp_step4( lnAttCmp_type *cmpL, link_type *contour, float X[] );


	// LnAttCmpStepN.c
int	lnAttCmp_stepN( lnAttCmp_type *cmpL, link_type *contour, float X[] );

float	lnAttCmp_disN( lnAttCmp_type *cmpL, link_type *contour );


	// LnAttCmpStepW.c
int	lnAttCmp_stepW( lnAttCmp_type *cmpL, link_type *contour, float X[] );


	/* LnAttCmpStepNS.c */
int	lnAttCmp_stepNS( lnAttCmp_type *cmpL, link_type *contour, float X[] );


void	lnAttCmpL_pos( lnAttCmp_type *cmpL, link_type *contour );

#endif