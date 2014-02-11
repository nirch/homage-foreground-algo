/**********************
 ***    LayerIn.h    ***
 **********************/
 
#ifndef         _LAYER_AUX_H_
#define         _LAYER_AUX_H_


#include        "Uigp/igp.h"
#include        "GpType/GpType.h"
#include		"EpnType/EpnType.h"




#define		BST_SIZE	8000
#define		ST_SIZE		8000


typedef struct layerAuxB_type {
	int		visit;
	int		no;

	u_char		*top;
	u_char		*buttom;
	u_char		*right;
	u_char		*left;

}	layerAuxB_type;



typedef struct layerAuxR_type {
		int	i,	j;
}	layerAuxR_type;




typedef struct layerAuxBound_type {
		ep_ntype	*ep;
		int	bmask;
}	layerAuxBound_type;





typedef struct layerAux_type {

	int	N;
	int	Ni,	Nj;

	layerAuxB_type	*bp;

	// block
	layerAuxR_type	Bst[BST_SIZE];
	int	Bst_b,	Bst_e;

	// bound 
	layerAuxBound_type	St[ST_SIZE];
	int	St_b,	St_e;

} layerAux_type;




#define	LAYER_AUX_BLOCK( lAux, i, j )		( &lAux->bp[ i * lAux->Nj + j] )



layerAux_type *	layerAux_alloc( gp_array *agp, int ni );

void	layerAux_destroy( layerAux_type	*lAux );


	// block
void	layerAux_set_visit( layerAux_type *lAux, int i, int j );

int		layerAux_is_visit( layerAux_type *lAux, int i, int j );


int		layerAux_test_boundary( layerAux_type *laux, ep_narray *aep, ep_ntype *ep );

layerAuxR_type *	layerAux_get_next_block( layerAux_type *laux );

void	layerAux_blockQU_add( layerAux_type *laux, int i, int j );

int	layerAux_blockQU_is_empty( layerAux_type *laux );








	// bound
void	layerAux_boundQU_clear( layerAux_type *laux );

int	layerAux_boundQU_is_empty( layerAux_type *laux );


void	layerAux_boundQU_add( layerAux_type *laux, ep_ntype *ep, int cont );

layerAuxBound_type *	layerAux_boundQU_get( layerAux_type *laux );

void	layerAux_boundQU_add_from_point( layerAux_type *laux, ep_narray *aep, vec2d *p );

void	layerAux_set_boundQU_add_boundary( layerAux_type *laux, layerAuxB_type *bp,
										  ep_narray *aep );

void	layerAux_set_boundQU_add_link( layerAux_type *laux, ep_narray *aep, int layerId );


	// Aep
void	layerAux_mark_boundary( ep_narray *aep );

  
	// AgpLayerIdF1.c
void	agp_layerId_expand( layerAux_type *laux, gp_array *agp, gp_array *baseAgp, ep_narray *aep, int branch );


#endif
