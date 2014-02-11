/**************************
 ***	AgpTexture.h	***
 **************************/

#ifndef         AGP_TEXTURE
#define         AGP_TEXTURE

#define	L_SIZE		5
#define	EX_BOX		0.2F

// ***  CopyHunchTexture.c ***
gp_array *agp_texture_copy_hunch_box( gp_array *agp, box2d *box );
gp_array *agp_texture_copy_hunch_pos( gp_array *agp, int i0, int j0, int i1, int j1 );
void agp_texture_copy_hunch1( gp_type *ngp, hunch_type *hunch );
void agp_texture_copy_bgp( gp_type *ngp, bgp_type *bgp );

// ***  CopyTexture.c ***
gp_array *agp_texture_copy_pos( gp_array *agp, int i0, int j0, int i1, int j1 );
gp_array *agp_texture_copy_box( gp_array *agp, box2d *box );
void agp_texture_copy_jnt_link_pos( gp_array *agp, gp_array *nagp, 
		int i0, int j0, int ni0, int nj0, int NiC, int NjC, box2d *boxEx );

char agp_texture_test_jntN3_box( gp_array *agp, jnt_type *jnt, box2d *boxEx );
void agp_texture_clear( gp_array *agp );
void agp_texture_cross_box( gp_array *agp, box2d *boxEx );

// ***  PasteHunchTexture.c ***
int agp_texture_paste_hunch_box( gp_array *agp, gp_array *nagp, box2d *box, int iAdd, float fStir );
int agp_texture_paste_hunch_point( gp_array *agp, gp_array *nagp, vec2d *point, int iAdd, float fStir );
//int agp_texture_stir_hunch_box( gp_array *agp, box2d *box, int iStir );
//int agp_texture_midle_hunch( gp_array *agp, box2d *box );

// ***  PasteTexture.c ***
int agp_texture_paste_box( gp_array *agp, gp_array *nagp, box2d *box );
int agp_texture_paste_point( gp_array *agp, gp_array *nagp, vec2d *point );
void  agp_texture_delete( gp_array *agp, int i0, int j0, int i1, int j1 );

#endif //AGP_TEXTURE
