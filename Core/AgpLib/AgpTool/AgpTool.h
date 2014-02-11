#ifndef		_AGP_TOOL_
#define		_AGP_TOOL_

#ifdef __cplusplus
extern "C" {
#endif

#include        "Uigp/igp.h"
#include	"Umath/LT2Type.h"
#include        "ImageType/ImageType.h"

#include        "GpType/GpType.h"


#include        "LinkTool/TlType.h"


	/* AgpCopy.c */
void	agp_copy( gp_array *agp, gp_array *nagp, int row, int column, int bgp);

gp_array *	agp_make_copy( gp_array *agp );


	/* AgpExtend.c */
gp_array *	agp_extend( gp_array *agp, int row, int column, int bgp );


	/* AgpZoom.c */
gp_array *	agp_zoom( gp_array *agp, float Zf, int bgp );
int		agp_zoom_move_layer( gp_array *nagp, gp_array *agp,
                                float Zf, link_type *links[], vec2d gctr[] );


	// AgpLt2.c
gp_array *	agp_lt2( gp_array *agp, lt2_type *lt, int bgp );


	// AgpRescale.c
gp_array *	agp_rescale( gp_array *agp, float A, float B, int bgp );


	/* AgpZoomP.c */
gp_array *	agp_zoomP( gp_array *agp, float zf, int bgp );
gp_array *	agp_zoomP_layer(gp_array *agp,
				int mbr, float zf, int bgp, int step );


	/* AgpUnion.c */
void	agp_union( gp_array *agp, vec2d *gctr, gp_array *uagp );


	/* AgpMakeUnion.c */
gp_array *	agp_make_union( gp_array *Agp[], int no );

gp_array *	agp_make_union2( gp_array *agp0, gp_array *agp1 );


	/* AgpConst.c */
gp_array *	agp_const( int row, int column, int bgp,
                        int red, int green, int blue );

void	agp_const1( gp_array *agp,
			int red, int green, int blue );

gp_array *agp_const_2( int height, int width, int bgp, int color, float depth );


	/* AgpFlipV.c */
gp_array * agp_flipV( gp_array *agp, int Fview );

	/* AgpFlipH.c */
gp_array * agp_flipH( gp_array *agp, int Fview  );


	/* AgpMold.c */
gp_array *	agp_make_mold( gp_array *agp );

	/* AgpCleare.c */
gp_array *	agp_make_cleare( gp_array *agp, int moldColorInLayers );






	/* AgpProfile.c */
void	agp_profile_get_prm( GP_prm **prm, int *prm_no, void (**check)() );

void	agp_profile_init( char *file );

void	agp_profile( gp_array *agp );


	/* AgpProfileWidth.c */
void	agp_profile_width(gp_array *agp,float width,int mbr );



	/* AgpBgValue.c */
int	agp_bg_value( gp_array *agp, vec2d *p, qcolor_type val[SP_NO] );

int		agp_bg_valueL( gp_array *agp, int layer, vec2d *p, qcolor_type val[SP_NO] );


	/* AgpBgpFill.c */
void	agp_bgp_fill( gp_array *agp, int layer_no );

void	agp_bgp_fill_layer( gp_array *agp, int layer_no );


	/* AgpBgpFill.c */
void	agp_bgp_fillN( gp_array *agp, int layer_no );

void	agp_bgp_fill_layerN( gp_array *agp, int layer_no );


	// AgpBgpFillHole.c
void	agp_bgp_fill_hole( gp_array *agp );





	/* AgpLinkLen.c */
int	agp_link_len( gp_array *agp, int max_len );


	/* AgpLinkForceMaxLA.c */
int	agp_link_force_max_LA( gp_array *agp, float maxLen, float maxA );


	/* AgpLinkNo.c */
int	agp_link_no( gp_array *agp, int max_no );

int	agp_link_force_max_diff( gp_array *agp, float maxDiff );


	/* AgpConnectJnt.c */
void	agp_connect_jnt( gp_array *agp );


	/* AgpDelete.c */
void	agp_delete( gp_array *agp, int Mnf, box2d *box );

void	agp_delete_bgp( gp_array *agp, box2d *box );




	/* AgpAddConstLayer.c */
void	agp_add_const_layer( gp_array *agp,
			int br, float depth, float r, float b, float g );


	/* AgpBrList.c */
void	agp_br_mask( gp_array *agp, int *Mnf, int *Mbg, int *Fbr );

void	agp_br_list( gp_array *agp );


	/* AgpNf.c */
int	agp_nf( gp_array *agp, box2d *box, int nf[NF_TYPES] );

int	agp_polylink_no( gp_array *agp, int type );

void	agp_data_size( gp_array *agp, int *data_size, int *alloc_no );



	/* AgpJntBrn4.c */
void	agp_jnt_brn4( gp_array *agp );



	/* AgpImage.c */
image_type *	agp_to_image( gp_array *agp, int color, image_type *im );

image_type *	agp_to_imageS( gp_array *agp, int i0, int j0,
					int row, int col, image_type *im );

	/* AgpCloseHole.o */
int	agp_close_hole( gp_array *agp, float max_u );


	/* AgpAppend.c */
void	agp_append( gp_array *agp, vec2d *gctr, gp_array *uagp );



	/* AgpNormalView.c */
void	agp_normal_view( gp_array *agp );


	/* AgpBorder.c */
void	agp_border_add( gp_array *agp );

void	agp_border_clear( gp_array *agp );


	/* AgpDumpWrite.c */
void	agp_dump_write( gp_array *agp, char *path, char *name, char dump_type_binary );

	/* AgpDumpRead.c */
gp_array *agp_dump_read( char *path, char *name );


	/* AgpScriptWrite.c */
void	agp_script_write( gp_array *agp, char *path, char *name, char dump_type_binary );

	/* AgpScriptRead.c */
gp_array *agp_script_read( char *path, char *name, int bgp );

	/* AgpCheckLinkFbr.c */
int agp_check_link_fbr( gp_array *agp);


	/* AgpDither.c */
image_type *	agp_dither( gp_array *agp, float zf, float bf, float len, float dis );


	/* AgpCountorLink.c */
int	agp_countor_link( gp_array *agp, int mbr, tl_type tlink[] );



	/* AgpMoveLayer.c */
gp_array *	agp_reposition_layer( gp_array *sagp, int iLayer, vec2d *dp );


	/* AgpBgpTest.c */
int	agp_bgp_test( gp_array *agp, int iLayer );

	/* AgpCheckIn.c */
int	agp_check_in( gp_array *agp, vec2d *p );


	/* AgpTransparent2Flat.c */
gp_array *	agp_transparent2flat_Extand( gp_array *agp, int color );

int	agp_transparent2flat( gp_array *agp, int color );


	// AgpN3ToEdge.c
void	agp_n3_to_edge( gp_array *agp, int FjntLink );

	// AgpN3ToEdge.c
void	agp_edge_to_n3( gp_array *agp );


	/* AgpN3InProfile.c */
int	agp_n3_in_profile( gp_array *agp );


	// AgpUpgrate06.c

int	agp_upgrade06( gp_array *agp, int Renumbring );

	// AgpRemoveN3R06.c 
void	agp_remove_N3R_06( gp_array *agp );


	// AgpSetBr1_06.c
void	agp_set_br1_06( gp_array *agp );




	// AgpTransparentWidth.c 
void	agp_transparent_width( gp_array *agp, float width );

void	agp_transparent_width_force_max( gp_array *agp, float width );



	// AgpJnt.c
int	agp_jnt_get_array( gp_array *agp, jnt_type ***aJnt, int *nJnt );

int	agp_jnt_no( gp_array *agp );


#ifdef __cplusplus
}
#endif
				 
#endif
