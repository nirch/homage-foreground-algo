#ifndef		_AGP_COLOR_F_
#define		_AGP_COLOR_F_

#include        "Uigp/igp.h"
#include        "GpType/GpType.h"

#include        "EpType/EpType.h"




	/* AgpColorF.c */
int     agp_color_F_test_boundary( ep_array *aep, ep_type *ep, int bno );


	/* AgpColorF1.c */
void    agp_color_F1_set( int fill_op, int Fprofile, float color[] );
 
void    agp_color_F1_ep( gp_array *agp, ep_array *aep, box2d *box );
 
void    agp_color_F1_st_clear();
 
void    agp_color_F1_st_add( ep_type *ep, int bno );


#endif
