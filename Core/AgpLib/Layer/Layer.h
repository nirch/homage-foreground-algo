/*********************
 ***   LayerIn.h   ***
 *********************/
 
#ifndef		_LAYER_H_
#define		_LAYER_H_


#include	"Uigp/igp.h"
#include	"GpType/GpType.h"


	// AgpLAyerIdF.c
void	agp_layerId_F( gp_array *baseAgp, int layerId, vec2d *p, int step_no );

void	agp_layerId_F_side( gp_array *baseAgp, int layerId );



	// AgpLayerValidate.c
void	agp_layer_validate( gp_array *agp, int Fquantize );


	// AgpLayerFilter.c
void	agp_layer_filter_bgp( gp_array *agp, float T );

void	agp_layer_filter_hunch( gp_array *agp, float T );

  
#endif
