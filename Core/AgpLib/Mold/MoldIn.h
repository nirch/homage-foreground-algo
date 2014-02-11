/**********************
 ***    MoldIn.h    ***
 **********************/
 
#ifndef         _MOLD_IN_H_
#define         _MOLD_IN_H_

#ifdef __cplusplus
extern "C" {
#endif


#include        "Uigp/igp.h"
#include		"ImageType/ImageType.h"
#include        "GpType/GpType.h"

#include    "LnAttType.h"
#include	"LnAttCType.h"
#include	"LnAttType.h"
#include	"LnAttCmp.h"







	// MoldCrossSeg.c
gp_array *	mold_cross_agp( gp_array *agp0 );


int	mold_cross_lnSeg( gp_array *agp,
						vec2d *ctr, link_type *link, float radius,
						lnSeg_type **lsL );

link_type *	mold_contour( vec2d *ctr, link_type *link, float max_len );



	// MoldParallelSeg.c



		// MoldAttachSeg.c
int	mold_fitting_parallel_lnSeg( lnSeg_type *lsL_in, link_type *contour,
						lnSeg_type **lsL, lnAttc_type **attcL  );




		// LnAttCConnect.c
void	lnAttc_connect( lnAttc_type *atL, link_type *contour, lnAttCmp_type **lnCmp );

  

#ifdef __cplusplus
}
#endif


#endif //_MOLD_IN_H_
