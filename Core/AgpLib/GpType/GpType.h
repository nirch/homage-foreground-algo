/**********************
 ***    GpType.h    ***
 **********************/
 
#ifndef         _GP_TYPE_
#define         _GP_TYPE_

#ifdef __cplusplus
extern "C" {
#endif



#include	"NfType.h"
#include	"HunchType.h"
#include	"LinkType.h"
#include	"JntType.h"
#include	"BgpType.h"


#include	"MbrType.h"
#include	"AdepthType.h"

#include	"LayerType.h"




#define		MAX_LAYER	MAX_LAYER_BIT


#define		MAX_LINK	16


#define		MAX_GP		48
#define		AGP_MAX_JNT	4000


//	for agp.type
#define		AGP_NORMAL		0
#define		AGP_DEPTH		1
#define		AGP_RENDER		2
#define		AGP_TRANSPARENT		3



//	for agp.color_type
#define		AGP_YCrCb	0
#define		AGP_RGB		1
 

 


typedef struct gp_type {
	vec2d		ctr;

	hunch_type	*hunch;

	jnt_type	*jnt;

	link_type	*link;

	bgp_type	*bgp;

} gp_type;




typedef struct	gp_array {

	int	type;

	int	Lcoding;


	int	color_type;
	int	Fn3_prime;
	int	Fin;			// 1 if link->in is set



	adepth_type	*ad;

	int	subLayer_no;
	mbr_type	Mbr;

	int	layer_no;
	layer_type	*layer[MAX_LAYER];

	struct renderAux_type	*renderAux;
	struct n3Aux_type	*n3Aux;


	int	row,	column;

	int	bgp;
	float	inv_bgp;
	int	rowR,	columnR;

	int	Ni,	Nj;
	int	Lni,	Lnj;

	/* Aux for local compress */
	float	X0,	Y0;
	int	Ni0,	Ni1;
	int	Nj0,	Nj1;

	gp_type		**gp;

}	gp_array;




gp_array * agp_alloc();
void	agp_init( gp_array *agp, int bgp, int ni, int nj, int lni, int lnj);

void	agp_init_data( gp_array *agp );


void	agp_clear( gp_array *agp, int bgp, int ni, int nj, int lni, int lnj );
void    gp_clear( gp_type *gp );

void	agp_destroy( gp_array *agp );


void	gp_array_realloc( gp_array *agp, int ni, int nj );

void	gp_array_alloc( gp_array *agp, int ni, int nj );

void	gp_array_free( gp_array *agp );

void	agp_geomtric_aux( gp_array *agp );





void	agp_clear_jnt( gp_array *agp, jnt_type *jnt );
void	agp_untied_jnt( gp_array *agp, jnt_type *jnt );
void	gp_untied_jnt( gp_type *gp, jnt_type *jnt );

void	agp_untied_link( gp_array *agp, vec2d *ctr, link_type *link );
void	gp_untied_link( gp_type *gp, link_type *link );

void	gp_clear_hunch( gp_type *gp, hunch_type *hunch );


int	agp_nf_no( gp_array *agp, int nf_type );



	// AgpNfArray
int	agp_get_hunchs_array( gp_array *agp, hunch_type *ahunch[] );

int	agp_get_ridge_array( gp_array *agp, link_type *link[] );

int	agp_get_hunch_array( gp_array *agp, int type, hunch_type *ahunch[] );

int	agp_get_link_type_array( gp_array *agp, int type, link_type *link[] );




	// AgpBox
void	agp_set_box( gp_array *agp, int row, int col );

void	agp_set_box_ij( gp_array *agp, int ni0, int nj0 );
 
int		agp_set_next_box( gp_array *agp );



int	agp_Fborder_xy( gp_array *agp, vec2d *ctr );

int	agp_Fborder_ij( gp_array *agp, int i, int j );



	// AgpInsert
void	agp_insert_hunch( gp_array *agp, hunch_type *hunch );

jnt_type *	agp_insert_jnt( gp_array *agp, jnt_type *jnt );




	// AgpLnf.c */
//void	agp_lnf_box( gp_array *agp );
//void	agp_lnf_clear_box( gp_array *agp );

void	agp_lnf( gp_array *agp );
void	agp_lnf_clear( gp_array *agp );


void	agp_lnf_link( vec2d *ctr, link_type *link, gp_array *agp );
void    agp_lnf_clear_link( vec2d *ctr, link_type *link, gp_array *agp );

void	agp_lnf_add_link_1( vec2d *ctr, link_type *link, gp_array *agp );
void	agp_lnf_clear_link_1( vec2d *ctr, link_type *link, gp_array *agp );

void	agp_lnf_clear_brn( jnt_type *jnt, int bno, gp_array *agp );
void	agp_lnf_add_brn( jnt_type *jnt, int bno, gp_array *agp );







	// AgpIn.c
void	agp_in_rebuild( gp_array *agp );

void	agp_in_clear( gp_array *agp );



	/* LinkIn.c */
void	agp_link_in_reorder( gp_array *agp );

void	link_in_reorder( jnt_type *jnt, int side );


	/* AgpClear.c */
void	agp_clear_box( gp_array *agp );



#ifdef __cplusplus
}
#endif

#endif
