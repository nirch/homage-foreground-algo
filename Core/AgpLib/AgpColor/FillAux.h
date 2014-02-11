/**********************
 ***    FillAux.h   ***
 **********************/
 
#ifndef		_FILL_AUX_H_
#define		_FILL_AUX_H_


#include	"Uigp/igp.h"
#include	"GpType/GpType.h"
#include	"EpnType/EpnType.h"


typedef struct	fillBound_type {
	int	i,	j;
	link_type	*link;
	char	side;

	struct fillBound_type	*next;

}	fillBound_type;



typedef struct fillAep_type {
	int		visit;
	int		no;

	fillBound_type		*fb;

}	fillAep_type;



typedef struct fillAep_st {
		int	i,	j;
}	fillAep_st;




typedef struct fillEp_st {
		ep_ntype	*ep;
		int	bmask;
}	fillEp_st;





typedef struct fillAux_type {

	int	op;
	int	Fprofile;
	qcolor_type	color[SP_NO];

	int	N;
	int	Ni,	Nj;

	fillAep_type	*bp;	//	2D array

	// block	
	fillAep_st	*stAep;		
	int	stAep_b,	stAep_e;



	// bound; for the current Aep
	fillEp_st	*stEp;
	int	stEp_b,	stEp_e;
	int	stEp_size;

} fillAux_type;




#define	FILL_AUX_BLOCK( lAux, i, j )		( &lAux->bp[ i * lAux->Nj + j] )



fillAux_type *	fillAux_alloc( gp_array *agp, int ni );

void	fillAux_destroy( fillAux_type	*lAux );

//void	fillAep_clear( fillAep_type *bp );

void	fillBound_destory( fillBound_type *fb );


	// aep block
void	fillAux_set_visit( fillAux_type *lAux, int i, int j );

int		fillAux_is_visit( fillAux_type *lAux, int i, int j );

int		fillAux_aepST_get( fillAux_type *laux, int *i, int *j );

void	fillAux_aepST_add( fillAux_type *laux, int i, int j );

int		fillAux_aepST_is_empty( fillAux_type *laux );


int		fillAux_test_boundary( fillAux_type *laux, ep_narray *aep, ep_ntype *ep, int bno );






	// bound
void	fillAux_epST_clear( fillAux_type *laux );

int		fillAux_epST_is_empty( fillAux_type *laux );


void	fillAux_epST_add( fillAux_type *laux, ep_ntype *ep, int cont );

int		fillAux_epST_get( fillAux_type *laux, ep_ntype **ep, int *bmask );




void	fillAux_epST_add_from_point( fillAux_type *laux, ep_narray *aep, vec2d *p );

void	fillAux_set_epST_add_boundary( fillAux_type *laux, fillAep_type *bp, ep_narray *aep );


#endif
