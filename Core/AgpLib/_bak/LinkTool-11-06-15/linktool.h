/***********************
 ***	LinkTool.h   ***
 ***********************/
#ifndef         _LINK_TOOL_
#define         _LINK_TOOL_

#ifdef __cplusplus
extern "C" {
#endif


#include	"Uigp/igp.h"
#include	"Uprm/prm.h"
#include	"Ubox/Box2d.h"

#include	"GpType/LinkType.h"
#include	"UGeoApp/GeoApp.h"




typedef struct dLink_type {

	link_type	*l;

	float	u;
	float	t;
	float	gt;

	float	dis;

} dLink_type;


	/* LinkFromGapp.c */
link_type *		link_from_gapp( gapp_type *gapp, int type, link_type **last );
	
int				link_from_gappN( gapp_type *gapp, int type, vec2f_type *ctr, link_type **link );

	/* LinkFromLine.c */
link_type *		links_from_line( vec2d *point1, vec2d *point2 ,
								float max_dist, int type, link_type **last_link );

link_type *	link_from_points( vec2d p[], int no, int Fclose );

int		link_approximate( vec2f_type av[], int nV, gapp_prm *gPrm, vec2d *ctr,link_type **link );


int	polylink_from_box( box2d *b, vec2f_type *ctr, link_type **link );



float	polylink_length(link_type *link, link_type *endLink);

float	polylink_len_partial( link_type *l0, float t0, link_type *l1, float t1 );

int	polylink_link_no(link_type *link, link_type *endLink);

void	polylink_end_point( vec2d *ctr, link_type *link, vec2d *p );

void	linkL_get_point( vec2d *ctr, link_type *link, link_type *l0, vec2d *p );

int		linkL_g2l( vec2d *ctr, link_type *link, float *gt, vec2f_type *ctr0, link_type **l0, float *t );


//void	polylink_last_link( link_type *link, link_type **last );
void	polylink_last_link( vec2d *ctr, link_type *link, vec2d *p, link_type **last );


link_type * polylink_max_len( link_type *link, float max_len );

link_type *		link_reapproximate( vec2d *ctr,link_type *link, float max_len, link_type **last );



	/* LinkReaproximate.c */
link_type *		polylink_reapproximate( vec2d *ctr,link_type *link, link_type *elink, link_type **last );

gapp_type *	polylink_to_gapp( vec2d *ctr, link_type *link, link_type *elink );


	/* LinkSetProfile.c */
void	link_profile_alloc( link_type *link, int type );

void link_edge_set_profile( link_type *link, int br, int Fbr, float depth,
														float width, int color );


	/* Beizer2Link.c */

void		beizer_to_link_get_prm(GP_prm **prm, int *prm_no, void (**check)() );

void		beizer_to_link_init( char *file );

link_type *		beizer_curve_to_links( vec2d *p, int no );

link_type *		beizer_to_Links( vec2d *p0,vec2d *p1,vec2d *p2,vec2d *p3 );

link_type *		link_from_qubic_bezier(vec2d *p0,vec2d *p1,vec2d *p2,vec2d *p3, link_type **last );

link_type *		link_from_conic_bezier(vec2d *p0,vec2d *p1,vec2d *p2, link_type **last );


	/* LinkFilter.c */  //Grisha 05.07.01

link_type *link_filter( vec2d *ctr, link_type *link, float min_width );


	/* LinkDistance.c */
float	link_distance( vec2d *ctr, link_type *l, vec2d *v, float *u, float *t );

float	link_distance2( vec2d *ctr, link_type *l, vec2d *v, float *u, float *t );

float	linkL_distance(  vec2d *ctr, link_type  *link, link_type *elink, vec2d  *p, dLink_type *d );

float	polylink_distance( vec2d *ctr, link_type  *link, link_type *elink, vec2d  *v,
										link_type **sl, float *u, float *t, float *gt );

int		polylink_select( link_type *plink[], int nPlink, vec2d *p );

void	polylink_filter_short_link( vec2d *ctr, link_type *link, float d );

void	polylink_remove_zero_link( link_type **link );

void	polylink_split_long_link( link_type *link, float tLen );




//LinkClip.c
link_type* link_clip(vec2d *gCtr, link_type *link, box2d *box);

link_type* link_frame_box(int type1, box2d *box);


	/* LinkSimplify.c */
void	polylink_simplify( vec2d *ctr, link_type **link );

void	polylink_append( vec2d *ctr, link_type *link, vec2d *v2, link_type *l2 );

int	polylink_append_point( vec2d *ctr, link_type **link, vec2d *p, float Tlen, int Fsimplify );

void	polylink_close( vec2d *ctr, link_type *link, float Tlen );

void	polylink_split( vec2d *ctr, link_type *link, link_type *sl, float t,
											vec2d *ctr1, link_type **l1 );



	/* LinkSplit.c */
link_type *	link_split( vec2d *ctr, link_type *link, vec2d *p );

link_type *	link_split_t( link_type *link, float t0 );

link_type *	link_ssplit( link_type *link, float t, float dt );



	/* LinkTool2.c */

void	link_connect( link_type *l0, link_type *l1 );

void	polylink_set_ctr( vec2d *ctr, link_type *l );

void	ploylink_get_link_ctr( vec2d *ctr, link_type *link,
									link_type *link0, vec2d *ctr0 );


void	polylink_tanget_end( link_type *link, vec2d *tanget );

void	link_end_point(link_type *l, vec2d *v);

void	link_set_prev_next( link_type *first, link_type *second );

void	link_set_type( link_type *link, int l_type );

link_type *polylink_get_last_link( link_type *link );

link_type *polylink_get_first_link( link_type *link );

void	polylink_get_link( vec2f_type *ctr0, link_type *link0, float gt, vec2f_type *ctr, link_type **link, float *t );


link_type *	polylink_copy( link_type *plink, link_type *elink );

int	polylink_copy_sub( vec2d *pctr, link_type *plink, float gt0, float gt1, 
											vec2d *ctr, link_type **link  );


link_type * polylink_rescale( link_type *plink, vec2d *gCtr, vec2d *point, 
								  float xScale, float yScale);

link_type * polylink_rescale_from_centr( link_type *plink, vec2d *gCtr,
								  float xScale, float yScale);

void	ploylink_gt2lt( link_type *link, float gt, link_type **l0, float *t0 );
void	ploylink_gt2p( vec2f_type *ctr, link_type *link, float gt, vec2d *p );

void	ploylink_tanget( link_type *link, float gt, vec2d *tanget );


void	polylink_force_closed( vec2d *ctr, link_type *link );

int		ploylink_is_close( vec2d *ctr, link_type *link, float d );





	/* LinkSet.c */
void	link_set_begin( vec2d *ctr, link_type *link, vec2d *p );

void	link_set_end( vec2d *ctr, link_type *link, vec2d *p );

void	link_set_a_point( vec2d *ctr, link_type *l, vec2d *p );

void	link_set_a( vec2d *ctr, link_type *l, float a );


	/* LinkBox.c */
void	polylink_box( vec2d *ctr, link_type *link, link_type *last, box2d *box );

void	polylinkA_box( link_type *alink[], int no, box2d *box );

	/* LinkInsidePoint.c */
void	polylink_inside_point( vec2d *ctr, link_type *link, vec2d *p );
		// return point inside the polylink 

int		polylink_around_point( vec2d *ctr, link_type *plink, vec2d *p );

int		polylink_check_dirrection( vec2d *ctr, link_type *plink );


	//	LinkInternalSide.c
int		polylink_internal_side( vec2d *ctr, link_type *link );

	// LinkFromLn.c
link_type *		link_from_ln( struct ln_type *lnL );


	/* LinkIo.o */
int	ploylink_write_to_file( vec2d *ctr, link_type *link, char *file );

int	ploylink_write_to_buffer( vec2d *ctr, link_type *link, char **data, int *bytes );

int	polylink_write( vec2d *ctr, link_type *link, FILE *fp );

int	ploylink_read_from_file( char *file, vec2d *ctr, link_type **link );

int	ploylink_read_from_buffer( char *data, int bytes, vec2d *ctr, link_type **link );
int	ploylink_read_from_buffer2( char *data, int bytes, vec2d *ctr, link_type **link );


int	ploylink_read( FILE *fp, vec2d *ctr, link_type **link );






#ifdef __cplusplus
}
#endif

#endif
