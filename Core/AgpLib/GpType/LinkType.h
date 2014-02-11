/************************
 ***    LinkType.h    ***
 ************************/

#ifndef         LINK_TYPE
#define         LINK_TYPE

#ifdef __cplusplus
extern "C" {
#endif

#include	"NfType.h"

#include	"ProfileType.h"
#include	"WidthType.h"

#include	"Uvec/Vec2d.h"
#include	"Ubox/Box2d.h"





typedef struct link_ptr {
	int	bno;
	union {
		union	{
			struct link_type *l;
			struct jnt_type *jnt;
		} p; 
		struct link_type *l;
		struct jnt_type *jnt;
	};


}	link_ptr;


typedef struct in_type {
	float	t;

	u_char	type;
	u_char	direct;

	u_char	use;

	s_char	bno;
	struct jnt_type *jnt;

	struct in_type	*p;
}	in_type;


	/* in.type */
#define		IN_NULL		0
#define		IN_N3		1
#define		IN_EDGE		2


	


typedef struct link_type {		// 96
	
	
	int	type;

	vec2d	ctr;

	
    
	vec2d	v;
	
	float	a;		// maximal height of parabola



	// AUX
	float	len;	//  length of the link on v 

	
	vec2d	u;		// unit right normal to v 
	
	float   c_prb;	// 2-nd order coefficient of parabola



	profile_type	pr[2];		/* F_BEGIN and F_END */


#ifdef LIN
	in_type		*in[2];		/* F_RIGHT and F_LEFT */
#endif

	
   
	link_ptr	p[2];		/* F_BEGIN and F_END */



	// for Depth
	u_char	br,	Fbr,	br1;
	u_char	side;



	struct link_type	*nl;	// next link in the same gp_type cell

	struct link_type	*cln;	// for xp_type cell


	// Rendering AUX
	struct link_type	*rnl;	// for xp_type cell
#ifdef RENDER_AUX_LOCAL
	struct pl_type	*pl[2];		// F_BEGIN and F_END
#endif

} link_type;




#define		LINK_ALLOC()	\
			( (link_type *)malloc( sizeof( link_type ) ) )


#define		IN_TYPE_ALLOC()	\
			( (in_type *)malloc( sizeof( in_type ) ) )



#define		LINK_NEXT( link )	\
		(( (link)->p[F_END].bno != -1 )? NULL : (link)->p[F_END].p.l )

#define		LINK_PREV( link )	\
		(( (link)->p[F_BEGIN].bno != -1 )? NULL : (link)->p[F_BEGIN].p.l )


#define		LINK_NEXT_JNT( link )	\
		(( (link)->p[F_END].bno < 0 )? NULL : (link)->p[F_END].p.jnt )

#define		LINK_PREV_JNT( link )	\
		(( (link)->p[F_BEGIN].bno < 0 )? NULL : (link)->p[F_BEGIN].p.jnt )


link_type *	link_alloc( int type, int ino );

link_type *	link_1_alloc();

void		link_alloc_width( link_type *link );

link_type *	link_make_copy( link_type *plink );

void		link_free( link_type *link );
void		link_1_free( link_type *l );



void	link_width_bes( link_type *link );

void	link_t2xy( vec2d *vm, link_type *link, float t, vec2d *p );
void	link_tu2xy( vec2d *vm, link_type *link, float t, float u, vec2d *p );


void	link_set_aux( link_type *l );



void	link_tanget( link_type *l, float t, vec2d *tanget );

void	link_Ntanget( link_type *l, float t, vec2d *nt );

void	link_Ntanget_beg( link_type *l, vec2d *t );
void	link_Ntanget_end( link_type *l, vec2d *t );

void	link_tanget_beg( link_type *l, vec2d *t );
void	link_tanget_end( link_type *l, vec2d *t );

	/* point with tanget ( 1, 0 ), if exist, set p and return 1 else 0 */
int	link_tanget_point_10( link_type *l, vec2d *vm, float *t, vec2d *p );

int	link_tanget_point_01( link_type *l, vec2d *vm, float *t, vec2d *p );

void	link_box2d( link_type *l, box2d *b );

void	polylink_box2d(link_type *l, box2d *b, link_type **lx0, link_type **lx1, link_type **ly0, link_type **ly1);


link_type *	link_inverse( link_type *link );
void	link_1_inverse( link_type *l );

void	link_set_br( link_type *link, int br, int Fbr );

link_type *	link_make_copyG( link_type *plink, link_type *elink );

void	link_get_ctr( link_type *link, vec2f_type *ctr );


	/* LinkTool1.c */
 
int	links_distance( vec2d *ctr, link_type  *link, link_type *elink,
			vec2d  *p,
			link_type **sl, float *u, float *t );

int	links_distance_n3( vec2d *ctr, link_type  *link, link_type *elink,
			vec2d  *p,
			link_type **sl, float *u, float *t );




	/* NfAux.o */
void	link_set_geo_aux( link_type *link );
void	link_1_set_geo_aux( link_type *link );


	/* LinkIn.c */
void	link_in_reposition( link_type *l0, link_type *l1 );

void	link_in_get( link_type *link, int side, link_type *ln[2] );

void	link_delete_in( link_type *link, int side );



	// LinkN3.c
void	linkN3_bes( link_type *link, vec2d bes[] );
void	linkN3_bes_1( link_type *link, int direct, vec2d *bes );


void	linkN3_width( link_type *link, width_type width[] );
void	linkN3_width_1( link_type *link, int direct, width_type *width );


#ifdef __cplusplus
}
#endif

#endif
