#ifndef		_FILTER_

#define		_FILTER_
#ifdef __cplusplus
extern "C" {
#endif

#include	"Uprm/prm.h"
#include	"GpType/GpType.h"


	/* FilterAgp.c */

void	filter_get_prm( GP_prm **prm, int *prm_no,void (**check)() );

void	filter_init( char *dir, int Lfilter );

void	filter_set_lprm();

void	filter_agp( gp_array *agp );

void	filter_percent_agp( gp_array *agp, box2d *box,
					float Phunch, float Pridge );



	/* FilterRh2Hunch.c */
void	filter_rhunch_to_hunch_get_prm( GP_prm **prm,
					int *prm_no,void (**check)() );

void	filter_rhunch_to_hunch_agp( gp_array *agp );



	/* FilterEdge.c */
void	filter_edge_get_prm(GP_prm **prm, int *prm_no, void (**check)() );

int	filter_edge( gp_array *agp );


	/* FilterN3.c */
void	filter_n3( gp_array *agp );



	/* FilterHunch.c */
void	filter_hunch_agp( gp_array *agp, box2d *box,
                        float rval_t, float lm_t, float len_t );

int	filter_hunch_agp_aux( gp_array *agp, box2d *box, int val[256] );


	/* FilterRidge.c */
void	filter_ridge_agp( gp_array *agp, box2d *box, float rval_t );
int	filter_ridge_agp_aux( gp_array *agp, box2d *box, int val[256] );


	/* FilterLinkLen.c */
void filter_len_edge( gp_array *agp, float len_min );
void filter_len_n3_to_edge( gp_array *agp, float len_min );

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _FILTER_ */		
 		
