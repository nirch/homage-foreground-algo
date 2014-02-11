/************************************************************************/
/*									*/
/*           RlType2.h   	         				*/
/*									*/
/************************************************************************/

#ifndef         RL_TYPE2
#define         RL_TYPE2


#include	"UGeoApp/GeoApp.h"
#include	"GpType/GpType.h"



//Grisha 31.05.01 ...

extern	gapp_prm Qgprm;
extern	float	Cang;

extern  int	Frl;
extern	float Clen_d;

	/* RlLink2.c */
void	rl_link_agp_2( gp_array *agp );

void	rl_link_brn_2( jnt_type *jnt, int bno, gp_array *agp );

	/* RlTool2.c */
void	rl_approximate_2( gapp_type *gapp, int i0, int i1,
			vec2d *p0, vec2d *p1, gapp_prm *gprm, rl_type *rl );

	/* RlCornerArc.c */
void	rl_link_corner_arc( rl_aux laux[], int lno, gapp_type *gapp );

void	rllink_find_arcs( link_type *link, vec2d *gctr,
				int *n_arcs_groupe, link_type **links_arcs_groupe);

void	rllink_find_arcs_union(int *n_arcs_groupe, 
				link_type **links_arcs_groupe );

void	rllink_find_corners( link_type *link, vec2d *gctr,
				int *n_corners, link_type **links_corners );

//... Grisha 31.05.01



#endif
