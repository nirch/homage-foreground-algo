#ifndef		_AGP_LAYER_H_
#define		_AGP_LAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"

#include	"GpType/GpType.h"




	/* AgpLayer.c */

void	agp_layer_changh_no( gp_array *agp, int br, int nbr );

void 	agp_layer_add_const( gp_array *agp, int cosnt );

int		agp_layer_no( gp_array *agp, int *layer0, int *layer1 );

int		agp_layer_id( gp_array *agp, int iLayer );

int		agp_layer_index( gp_array *agp, int layerId );

int		agp_layer_index_by_name( gp_array *agp, char *layerName );

int		agp_is_layer_index_valid( gp_array *agp, int index );



	/* AgpLayerRenumbering.c */
int	agp_layer_renumbering( gp_array *agp, int id0, int aId[] );



	/* AgpLayerCopy.c */
gp_array *	agp_layer_copy( gp_array *agp, int mbr, int Fbox );

int	agp_layer_copy_test( gp_array *agp, int br, vec2d *p );



	/* AgpCopyLayerContour.c */
gp_array *agp_layer_copy_contour( gp_array *agp, int mbr, int Fbox );


	/* AgpLayerCut.c */
int	agp_layer_cut( gp_array *agp, int br );



	/* AgpLayerInit.c */
void	agp_layer_init( gp_array *agp, int Fdepth );
void	agp_layer_reset( gp_array *agp );

	/* AgpLayerClear.c */
void	agp_layer_clear( gp_array *agp, int layer );


#ifdef AD_ABR
	/* AgpLayerDepth.c */
void	agp_layer_depth( gp_array *agp, int br );
#endif


	/* AgpLayerDepth.c */
void	agp_layer_depth_base( gp_array *agp, int mbr );



	/* AgpLayerBox.c */
void	agp_layer_box( gp_array *agp, int mbr, box2d *box );
void	agp_layer_alink_box( link_type *link[], int no, box2d *box );



	/* AgpLayerF.c */
void	agp_layer_F( gp_array *agp, int branch, vec2d *p, int flag );

	/* AgpLayerFC.c  */
void	agp_layer_FC( gp_array *baseAgp, int branch, vec2d *p, int step_no );

	/* AgpLayerFillN3.c */
void	agp_layer_F_n3_prime_load( gp_array *agp );


	/* AgpLayerHole.c */
int	agp_layer_hole( gp_array *agp, int br, vec2d p[] );


	/* AgpLayerSelect.c */
int	agp_layer_select( gp_array *agp, mbr_type Lmbr, vec2d *p, float d,
					vec2d *s_ctr, float *s_depth );



	/* AgpLayerSphere.c */
void	agp_layer_sphere( gp_array *agp, int mbr,
					float depthMax,float depthMin );


	/* AgpLayerMiddle.c */
float	agp_layer_middle_distance( gp_array *agp, int mbr );


	/* AgpLayerColor.c */
void agp_layer_color( gp_array *agp ,int color ,int mbr);


	
/*
	// AgpLayerCountor.c	old coutout
int	agp_layer_contour( gp_array *agp, vec2d *ctr, link_type *link,
			int layer, float depth, vec2d *mp, int step );

gp_array *	agp_layer_contour_copy( gp_array *agp, vec2d *ctr, link_type *link, 
			     int layer, float depth, vec2d *mp );


gp_array *	agp_layer_contour_copyT( gp_array *agp, vec2d *ctr, link_type *link, 
						int layer, float depth, vec2d *mp );
*/

	// AgpLayerContourPolylink.c
int	agp_layer_contour_polylink( gp_array *agp, int layerId, struct contour_type **c );

int	agp_layer_contour_polylinkO( gp_array *agp, int br, vec2d *ctr, link_type **link );


	/* AgpLayerBorder.c */
void	agp_layer_border( gp_array *agp );

	/* AgpLayerFlattening.c */
void agp_layer_flattening( gp_array *agp );


#ifdef __cplusplus
}
#endif

#endif
