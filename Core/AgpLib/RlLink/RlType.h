/********************
 ***   RlType.h   ***
 *******************/

#ifndef _RL_TYPE_
#define _RL_TYPE_


#include	<stdlib.h>
#include	"UGeoApp/GeoApp.h"
#include	"GpType/GpType.h"



typedef struct rl_type {

	vec2d	ctr;
	vec2d	v;		/* len* ( cos(angle) , sin(angle) )	*/
	float	len;

	float	a;		/* parabola height */

	float	da;

	int	Fsplit;
	int	i0,	i1;


	struct rl_type	*p[2];		/* F_BEGIN and F_END */
} rl_type;



#define		RL_NULL		0
#define		RL_CORNER	1


typedef struct rl_aux {
	int	type;
	vec2d	ctr;
	link_type	*link;

	int	i0,	i1;

	float	t0;
} rl_aux;



typedef struct rlAux_type {

	int		size;	// alocate size of laux;
	int		no; 
	rl_aux	*laux;

	rl_type	*rl;

}	rlAux_type;



#define		RL_ALLOC()	\
			( (rl_type *)malloc( sizeof( rl_type ) ) )


#define		RL_NEXT( rl )	( rl->p[F_END] )

#define		RL_PREV( rl )	( rl->p[F_BEGIN] )




	/* RlLink.c */
void	rl_link_get_prm(GP_prm **prm, int *prm_no, void (**check)() );
void	rl_link_get_group( GP_prm_group **prm_group, int *prm_group_no );

void	rl_link_init( char *file );

void	rl_link_agp( gp_array *agp );

void	rl_link_1( gp_array *agp, link_type *link );

void	rl_link_brn( jnt_type *jnt, int bno, gp_array *agp );


void    rl_link_app( gapp_type *gapp, rl_aux laux[],
                vec2d *ctr0, vec2d *ctr1, int i0, int i1,
                link_type **l0, link_type **l1 );
 


	/* RlGapp.c */
void	rl_link_gapp( vec2d *ctr, link_type *link, link_type *elink,
				gapp_type *gapp, rl_aux laux[], int *lno );
 


	/* RlTool.c */
rlAux_type *	rlAux_alloc( int size );

void	rlAux_realloc( rlAux_type *rla, int size );\

void	rlAux_destroy( rlAux_type *rla );

rl_type *	rl_alloc();
void	rl_destroy( rl_type *rl );




void	rl_approximate( gapp_type *gapp, int i0, int i1,
			vec2d *p0, vec2d *p1, gapp_prm *gprm, rl_type *rl );

void	rl_to_link( int type, rl_type *rl, rl_aux qa[], int ino,
				link_type **l0, link_type **l1 );


	/* RlCorner.c */
void	rl_link_corner_get_prm(GP_prm **prm, int *prm_no, void (**check)() );

void	rl_link_corner_set_lprm();

void	rl_link_corner( rl_aux laux[], int lno, gapp_type *gapp );


	/* LinkReplace.c */
void	link_replace( link_type *link0, link_type *link1,
				link_type *l0, link_type *l1 );

#endif
