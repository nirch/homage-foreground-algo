/*************************
 ***	AgpDepthIn.h   ***
 *************************/
#ifndef		_AGP_DEPTH_IN_
#define		_AGP_DEPTH_IN_

#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"
#include	"GpType/GpType.h"
#include	"Depth/DepthModelType.h"


	// AgpDepthSetCorner.c 
void	agp_depth_set_corner( gp_array *agp, dmCorner_type *c );


	// AgpDepthSetBottle.c 
void	agp_depth_set_bottle( gp_array *agp, dmBottle_type *c );



#ifdef __cplusplus
}
#endif

#endif
