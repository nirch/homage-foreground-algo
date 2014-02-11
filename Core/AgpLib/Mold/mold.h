/**********************
 ***    Mold.h      ***
 **********************/
 
#ifndef         _MOLD_H_
#define         _MOLD_H_


#ifdef __cplusplus
extern "C" {
#endif

#include        "Uigp/igp.h"
#include		"Uprm/prm.h"
#include        "GpType/GpType.h"

#include	"AttPrm.h"
#include	"LnAttCType.h"
#include	"LnAttCmp.h"

#include	"Contour/ContourType.h"




//typedef struct attPrm_type {
//	int		step;
//	float	radius1;
//	float	radius0;
//	float	radius;
//
//	float	cover;
//
//	float	minLen;
//
//	//float	minDt1;
//} attPrm_type;




typedef struct fitAux_type {

	lnSeg_type		*lnSeg;

	lnAttc_type		*attcL;

	lnAttCmp_type	*lnCmp;

	lnAttCmp_type	*fcmpL;
} fitAux_type;




	// Mold.c
fitAux_type	*	fitAux_alloc();

void	fitAux_destroy( fitAux_type * fitA );

void	fitAux_clear( fitAux_type * fitA );




//void mold_attPrm_init( attPrm_type *attPrm );



int	mold_fitting_attach( gp_array *agp,
						   vec2d *ctr, link_type *link,
						   attPrm_type *attPrm,
						   contour_type **c );




int		mold_fitting_step( gp_array *agp,
				   vec2d *ctr, link_type *link,
				   attPrm_type *attPrm,
				   fitAux_type *fitA, int step );

int		mold_fitting_step_M( gp_array *magp,
				   vec2d *ctr, link_type *link,
				   attPrm_type *attPrm,
				   fitAux_type *fitA, int step );


int	mold_fitting_contour( fitAux_type *fitA, link_type *contour, contour_type **c );



gp_array *	mold_agp( gp_array *agp );



void	mold_attach_filter_get_prm(GP_prm **prm, int *prm_no, void (**check)() );



	// Aux
void	mold_print_dis( link_type *link, link_type *contour, char *file );


void	*lnAttc_choise_select( vec2d *ctr );


#ifdef __cplusplus
}
#endif

#endif //_MOLD_H_
 