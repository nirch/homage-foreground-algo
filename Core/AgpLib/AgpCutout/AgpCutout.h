#ifndef		_AGP_CUTOUT_H_
#define		_AGP_CUTOUT_H_

#include	"Uigp/igp.h"

#include	"GpType/GpType.h"
#include	"Contour/ContourType.h"


	// AgpCutoutWrapper.c
gp_array *	agp_cutout_wrapper( gp_array *agp,
							 vec2d *ctr, link_type *link,
							 int iLayer, float depth, char *name );


	// AgpCutoutNWrapper.c
gp_array *	agp_cutoutN_wrapper( gp_array *agp, contour_type *c,
							 int iLayer, float depth, char *name, vec2f_type *mp );


	// AgpCutout.c 
gp_array *	agp_contout( gp_array *agp,
						vec2d *ctr, link_type *link, 
						int layer, float depth, vec2d *mp );


int		agp_contout_layer( gp_array *agp, vec2d *ctr, link_type *link, 
			     int layer, float depth, vec2d *mp, int step );


int		agp_contout_layer_side( gp_array *agp, vec2d *ctr, link_type *link, 
			     int layer, float depth, int step );


gp_array *	agp_contoutT( gp_array *agp,
						vec2d *ctr, link_type *link, 
						int layer, float depth, vec2d *mp );



	// AgpCutoutN.c 
gp_array *	agp_contoutN( gp_array *agp, contour_type *c, int layer, float depth, vec2f_type *mp );


int		agp_contoutN_layer( gp_array *agp, contour_type *c,
			     int layer, float depth, int step, vec2f_type *mp );


	// AgpCutoutFit.c
void	agp_contout_fit( gp_array *agp, int layerId );


#endif
