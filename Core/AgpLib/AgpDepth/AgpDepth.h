/***********************
 ***	AgpDepth.h   ***
 ***********************/
#ifndef		_AGP_DEPTH_
#define		_AGP_DEPTH_

#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"
#include	"GpType/GpType.h"



	// AgpDepthDefault.c
void	agp_depth_default( gp_array *agp, float depth );


	// AgpDepthSet.c 
void	agp_depth_set( gp_array *agp );


	// AgpDepthSetL.c 
void	agp_depth_setL( gp_array *agp, int mbr );


	// AgpDepthAdd.c 
void	agp_depth_add( gp_array *agp, int Fadd );




	// AgpDepthRange.c
void	agp_depth_range( gp_array *agp, float *depth0, float *depth1 );


	// AgpDepthSmooth.c
void	agp_depth_smooth0x4( gp_array *agp );



	// AgpDepthValue.c
float	agp_depth_value( gp_array *agp, int layer, vec2d *p );



#ifdef __cplusplus
}
#endif

#endif
