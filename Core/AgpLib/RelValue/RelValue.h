/**********************
 ***   RelValue.h   ***
 **********************/
#ifndef		_REL_VALUE_
#define		_REL_VALUE_

#include	"Uigp/igp.h"
#include	"Uprm/prm.h"

#include	"GpType/GpType.h"

#include	"EpnType/EpnType.h"


	// RelValue.c
void	rel_value_agp( gp_array *agp, ep_narray *aep, int Fwidth );


	// AbsVAlue.c
void	abs_value_agp( gp_array *agp, ep_narray *aep );


	// SetWidth.c
void	set_width_get_prm(GP_prm  **prm, int  *prm_no, void  (**check)());
void	set_width_agp( gp_array *agp );

void	set_width_init( char *file );



	// AbsValueO.c
// use only in agpColor/agp_color_F1.c
void	abs_value_agpO( gp_array *agp, struct ep_array *aep );


#endif
