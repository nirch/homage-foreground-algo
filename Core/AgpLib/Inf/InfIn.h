#ifndef _INF_IN_

#define _INF_IN_

#define D2B_STEP        0.5 
#define D2B_LEVELS      8


#include	<float.h>

#include	"Uinf/uinf.h"

#include	"Inf.h"

#include	"GpType/GpType.h"


	/*  InfJnt.c */

void	inf_jnt_init();

void	inf_jnt( jnt_type *jnt, vec2d *v );

void	inf_jnt_print( FILE *fp );


	/* InfBgp.c */

void	inf_bgp_init();

void	inf_bgp( gp_array *agp );

void	inf_bgp_print( FILE *fp );


	/* InfProfile.c */

void	inf_profile_init();

void	inf_profile( link_type *link, int type, int side );

void	inf_profile_print ( FILE *fp );


	/*  InfEdge.c */

void	inf_edge_init();

void	inf_edge( vec2d *ctr, link_type *link );

void	inf_edge_print ( FILE *fp );

void	inf_edge_print_total( FILE *fp );



	/* InfN3.c  */

void	inf_n3_init();

void	inf_n3( vec2d *ctr, link_type *link );

void	inf_n3_print ( FILE *fp );

void	inf_n3_print_total( FILE *fp );



	/* InfRidge.c  */

void	inf_ridge_init();

void	inf_ridge( vec2d *ctr, link_type *link );

void	inf_ridge_print ( FILE *fp );

void	inf_ridge_print_total( FILE *fp );




	/* inf_hunch.c */

void	inf_hunch_init();

void	inf_hunch( hunch_type *h );

void	inf_hunch_print ( FILE *fp );

void	inf_hunch_print_total( FILE *fp );



	/* inf_rhunch.c */

void	inf_rhunch_init();
 
void	inf_rhunch( hunch_type *h );
 
void	inf_rhunch_print ( FILE *fp );

void	inf_rhunch_print_total( FILE *fp );
 
 

 		
#endif /* #ifndef _INF_IN_ */
