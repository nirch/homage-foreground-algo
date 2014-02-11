/*********************
 ***	RlType.h   ***
 *********************/

#ifndef         RL_LINK
#define         RL_LINK

#ifdef __cplusplus
extern "C" {
#endif

#include	"GpType/GpType.h"



	/* RlLink.c */
void	rl_link_get_prm(GP_prm **prm, int *prm_no, void (**check)() );
void	rl_link_get_group( GP_prm_group **prm_group, int *prm_group_no );

void	rl_link_init( char *file );

void	rl_link_agp( gp_array *agp );

void	rl_link_1( gp_array *agp, link_type *link );

void	rl_link_countor_agp( gp_array *agp );

void	rl_link_brn( jnt_type *jnt, int bno, gp_array *agp );


#ifdef __cplusplus
}
#endif

#endif
