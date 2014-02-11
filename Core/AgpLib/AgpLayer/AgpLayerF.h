#ifndef		_AGP_LAYER_FILL_
#define		_AGP_LAYER_FILL_

#include	"Uigp/igp.h"

#include	"GpType/GpType.h"
#include	"EpType/EpType.h"


	/* AgpLayerFill.c */
int	agp_layer_F_test_boundary( ep_array *aep, ep_type *ep );


	/* AgpLayerFill_1.c */
void	agp_layer_F1( gp_array *agp, ep_array *aep, int br );

void	agp_layer_F1_st_clear();

void	agp_layer_F1_st_add( ep_type *ep, int cont );



// new fill algorithm
	/* AgpLayerFC.c */
int	agp_layer_FC_test_boundary( ep_array *aep, ep_type *ep );


	/* AgpLayerFC1.c */
void	agp_layer_FC1( gp_array *agp, gp_array *baseAgp, ep_array *aep, int br );

void	agp_layer_FC1_st_clear();

void	agp_layer_FC1_st_add( ep_type *ep, int cont );



#endif
