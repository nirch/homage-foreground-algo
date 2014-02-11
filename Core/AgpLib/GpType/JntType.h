/***********************
 ***    JntType.h    ***
 ***********************/

#ifndef		_JNT_TYPE_
#define		_JNT_TYPE_

#include	"Uigp/igp.h"

#include	"Uvec/Vec2d.h"
#include	"NfType.h"

#define		MAX_BRN		5



#define		BRN_NULL		0x00
#define		BRN_IN			0x01
#define		BRN_RIDGE		0x02
#define		BRN_EDGE		0x03
#define		BRN_N3			0x04
#define		BRN_N3R			0x06

#define		BRN_N3_P		0x09
#define		BRN_N3_J		0x11




#define		BRN_RIGHT( jnt, bno )	(( bno < jnt->brn_no -1 )? bno+1 : 0 )
#define		BRN_LEFT( jnt, bno )	(( bno > 0 )? bno-1 : jnt->brn_no -1 )

#define		IS_BRN_NULL( type )	( (type & 0xf ) == BRN_NULL )


typedef  struct  brn_type {
	int	type;
	int	direction;	/* BRN_BEGIN or BRN_END	*/
	vec2d	ctr;

	link_type	*link;

	in_type	*in;



	/* AUX */
	struct jnt_type	*pj;	/* JNT_N3_P */

} brn_type;


	/* for jnt->type */
#define		JNT_NULL	0
#define		JNT_N3		1
#define		JNT_EDGE	2
#define		JNT_RIDGE	3
#define		JNT_RN3		4

#define		JNT_N3_P	6


	/* for jnt->Fborder */
#define		JNT_IN		0
#define		JNT_BRODER	1
#define		JNT_STATIC	2


typedef  struct  jnt_type {
	int	type;
	int	Fborder;
	vec2d	ctr;


	vec2d	gctr;	/* global center */
	vec2d	u;

	float	rwidth,	lwidth;

	int	brn_no;
	brn_type	*brn[MAX_BRN];



	/* N3Prime */
	struct jnt_type	*pj[2];


	/*	Aux	*/

	int	jnt_no;	/* have to meaning - after D2gp and in Coding */


	struct jnt_type  *nj;	/* next jnt in the same gp_type cell */
	
	struct jnt_type  *cjnt;	/* copy for Rendering */


} jnt_type;



#define		BRN_ALLOC()	( (brn_type *)malloc( sizeof( brn_type )) )

#define		JNT_ALLOC()	( (jnt_type *)malloc( sizeof( jnt_type )) )

jnt_type *	jnt_alloc();
jnt_type *	jnt_alloc_1( int type, vec2d *ctr );

brn_type *	brn_alloc();

void		jnt_free( jnt_type *jnt );

void		jnt_insert_brn( int type, vec2d *ctr, link_type *link,
			jnt_type *jnt, int bno, jnt_type *njnt, int nbno,
			int flag );

void		jnt_free_brn( jnt_type *jnt, int bno );

void		jnt_untied_brn( jnt_type *jnt, int bno, int Fn3 );

int		jnt_connet_link( jnt_type *jnt, int bno,
					link_type *link, int direct );


void		jnt_set_aux( jnt_type *jnt );

void 		jnt_brn_ctr( jnt_type *jnt, int bno, vec2d *ctr );



void		link_get_jnt_and_brn_no( link_type *link, int direct,
					jnt_type **jnt, int *bno );

void		link_get_jnt( link_type *link, int direct,
						 jnt_type **jnt, int *bno, int *no );

void		jnt_n3_pvector( jnt_type *jnt, vec2d *p );
void		jnt_n3_uvector( jnt_type *jnt, vec2d *p );

void		jnt_load_nf_end_link( link_type *link );

/*
void		jnt_set_depth( jnt_type *jnt );
*/




	/* JntN3.c */
void	jnt_n3_load_u( jnt_type *jnt );

void	jnt_n3_load_from_link( jnt_type *jnt );

void	jnt_n3_set_aux( jnt_type *jnt );


int	jnt_n3_from_jnt_rn3( jnt_type *jnt );

int	jnt_n3_to_jnt_rn3( jnt_type *jnt );

void	jnt_n3_set_in_direct( jnt_type *jnt, int bno );


	/* JntN3In.c */
void	jnt_n3_in_set( jnt_type *jnt, int bno );

void	jnt_n3_in_delete( jnt_type *jnt, int bno );

void	jnt_n3_in_replace( jnt_type *jnt, int bno, jnt_type *njnt );

void	jnt_n3_in_replace_link( jnt_type *jnt, int bno, link_type *link, int direction );

int	jnt_n3_in_delete_segment( jnt_type *jnt, int bno );

int	jnt_n3_in_get_mate( jnt_type *jnt, int bno,
					jnt_type **njnt, int *nbno );


	/* JntRN3.c */
void	jnt_rn3_load_from_link( jnt_type *jnt );
void	jnt_rn3_set_aux( jnt_type *jnt );


	/* JntEdge.c */
void	jnt_edge_set_aux( jnt_type *jnt );


#endif
