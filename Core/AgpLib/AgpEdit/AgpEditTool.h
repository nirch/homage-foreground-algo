/**************************
 ***	AgpEditTool.h	***
 **************************/

#ifndef         AGP_EDIT_TOOL
#define         AGP_EDIT_TOOL

#include "AgpEdit.h"

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#include	"GpType/GpType.h"
//
//
//#include	"AgpSelect.h"
//
//
//
//	/* AgpLink2Jnt.c */
//jnt_type * agp_link_to_jnt( gp_array *agp, vec2d *ctr, link_type *link );
//
//jnt_type *	agp_link_to_jnt_t( gp_array *agp,
//							  vec2d *ctr, link_type *link, float t, float d );
//
//
//
//	/* AgpLinkSplit.c */
//void	agp_link_split( gp_array *agp, vec2d *ctr, link_type *link, vec2d *p );
//
//
//	/* AgpLinkDelete.c */
//void	agp_link_delete( gp_array *agp, vec2d *ctr, link_type *link );
//
//void	agp_link_delete_n3( gp_array *agp, vec2d *ctr, link_type *link );
//
//
//	/* AgpLinkN3ToEdge.c */
//void	agp_link_n3_to_edge( gp_array *agp, vec2d *ctr, link_type *link );
//
//	/* AgpLinkN3rToRidge.c */
//void	agp_link_N3R_to_ridge( gp_array *agp, link_type * link );
//
//
//	/* AgpLinkFilter.c */ //Grisha 05.07.01
//link_type *agp_link_filter( gp_array *agp, vec2d *ctr, 
//		link_type *link, float min_width );
//
//
//	/* SgpLinkInverse.c */
//void	agp_link_inverse( gp_array *agp, link_type *link );
//
//
//
//	/* AgpJnt.c */
//void    agp_jnt_insert( gp_array *agp, jnt_type *jnt );
//
//void    agp_jnt_untied( gp_array *agp, jnt_type *jnt );
//
//void    gp_jnt_untied( gp_type *gp, jnt_type *jnt );
//
//void	agp_jnt_untied_brn( gp_array *agp, jnt_type *jnt, int bno );
//
//
//		// remove jnt and change the end point of the link
//int		agp_jnt_reconect_link( gp_array *agp, jnt_type *jnt, int bno, jnt_type *njnt, int nbno );
//
//int		agp_jnt_connect_to_jnt( gp_array *agp, jnt_type *jnt, int bno, jnt_type *njnt, int nbno );
//
//int		agp_jnt_connect_to_link( gp_array *agp, jnt_type *jnt, vec2d *ctr, link_type *link, float t );
//
//int		agp_jnt_reposition( gp_array *agp, jnt_type *jnt, vec2d *ctr );
//
//int		agp_jnt_merage( gp_array *agp, jnt_type *jnt, jnt_type *njnt );
//
//
//	/* AgpJntN3.c */
//jnt_type *	agp_jnt_n3_split( gp_array *agp, jnt_type *jnt );
//
//void		agp_jnt_n3_delete_in( jnt_type *jnt, int bno );
//
//
//	// AgpJntN3ReplaceEdge.c
//void	agp_jnt_n3_replace_edge( gp_array *agp, jnt_type *sjnt, int sbno, jnt_type *jnt, int bno );
//
//	// AgpJntN3ReplaceIn.c
//int	agp_jnt_n3_replace_in( gp_array *agp, jnt_type *jnt, int bno );
//
//
//
//	/* AgpJntN3.c */
//int	agp_jnt_cut_brn( gp_array *agp, jnt_type *jnt, int bno );
//
//
//
//
//
//	/* AgpPolylinkDelete.c */
//int	agp_polylink_delete( gp_array *agp, link_type *link );
//
//	/* AgpPolylinkSelect.c */
//link_type *	agp_polylink_select( gp_array *agp, vec2d *p, float d );
//
//int	agp_polylink_select_jnt( gp_array *agp, vec2d *p, float d, link_type *alink[], int EMjnt, jnt_type *ignore_jnt );
//
//
//
//
//
//
//	/* AgpJntEdgeReorder.c */
//void	agp_jnt_edge_reorder( gp_array *agp, jnt_type *jnt );
//
//	/* AgpJntN3Reposition.c */
//void	agp_jnt_n3_reposition( gp_array *agp, jnt_type *jnt );
//
//
//	/* AgpJntConnect.c */
//int	agp_jnt_connect( gp_array *agp, jnt_type *jnt );
//
//int	agp_jnt_edge_connect( gp_array *agp, gp_type *gp, jnt_type *jnt );
//int	agp_jnt_ridge_connect( gp_array *agp, gp_type *gp, jnt_type *jnt );
//int	agp_jnt_rn3_connect( gp_array *agp, gp_type *gp, jnt_type *jnt );
//
//
//
//	/* AgpDefaultProfile.c */
//void	agp_default_profile_set( int color[], float width, float len );
//
//void	agp_default_profile_setF( float color[], float width, float len );
//
//void	agp_default_profile( gp_array *agp,
//		vec2d *ctr, link_type *link, int direct, float t, int Falloc );
//
//void	agp_default_hunch( gp_array *agp, vec2d *p, vec2d *v );
//
//
//	/* AgpProfile.c */
//int	agp_profile_load_from_jnt( link_type *link, int direct );
//
//int	agp_profile_load_from_jnt_n3( link_type *link, int direct );
//
//
//	/* AgpPolylinkInsert.c */
//link_type *	agp_polylink_insertA( gp_array *agp,
//								vec2d *ctr, link_type *link, int Fclose );
//
//void	agp_polylink_insert( gp_array *agp,
//								vec2d *ctr, link_type *link, int Fclose );
//
//
//void	agp_polylink_default_profile( gp_array *agp,
//										vec2d *ctr, link_type *link, int Falloc );
//
//#ifdef __cplusplus
//}
//#endif
#endif
