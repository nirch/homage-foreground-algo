#ifndef		_AGP_SELECT_H_
#define		_AGP_SELECT_H_

#ifdef __cplusplus
extern "C" {
#endif


#include        <stdio.h>
#include        "GpType/GpType.h"


float	agp_select_hunch( gp_array *agp, vec2d *v,
					vec2d *s_ctr, hunch_type **s_hunch );



float	agp_select_link( gp_array *agp, vec2d *v, int Fridge,
				vec2d *s_ctr, link_type **s_link );


float	agp_select_linkN( gp_array *agp, vec2d *v, int Mnf, link_type *ignore_link, 
				vec2d *s_ctr, link_type **s_link );


float	agp_select_plink( gp_array *agp, vec2d *v,
			int Fridge, link_type *link0,
			vec2d *s_ctr, link_type **s_link, int *s_direct );


float	agp_select_point( gp_array *agp, vec2d *v,
					int Fridge, link_type *elink, jnt_type *ejnt,
					vec2d *s_ctr, link_type **s_link, jnt_type **s_jnt );



int	agp_select_find_link( gp_array *agp, vec2d *ctr0, link_type *link,
					vec2d *s_ctr );

float   agp_select_jnt( gp_array *agp, vec2d *v, int Fridge,
					jnt_type **s_jnt, int *s_bno );

float	agp_select_jntN( gp_array *agp, vec2d *v, int EMjnt, jnt_type *ignore_jnt,
					jnt_type **s_jnt, int *s_bno );

float	agp_select_jntD( gp_array *agp, vec2d *v, int EMjnt, jnt_type *ignore_jnt, float Td,
					jnt_type **s_jnt, int *s_bno );



float agp_select_bgp(gp_array *agp, vec2d *v,vec2d *s_ctr, bgp_type **s_bgp);


#ifdef __cplusplus
}
#endif


#endif
