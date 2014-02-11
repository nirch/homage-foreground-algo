/**************************
 ***	EmbedLinkIn.h	***
 **************************/

#ifndef		EMBED_LINK_IN
#define		EMBED_LINK_IN


#include	"GpType/GpType.h"

#include	"RlLink/RlType.h"

#include	"UGeoApp/GeoApp.h"

typedef struct  dis_type {
	vec2d	ctr;
	link_type	*l;
	float	u;
}	dis_type;



typedef struct  tjnt_type {
	jnt_type	*jnt;
	int	b0;
	int	b1;

	int	i1;

	struct  tjnt_type	*ntj;

}	tjnt_type;



typedef struct  seg_type {

	int	i0;
	int	i1;

	float	min,	max;

	int	cuts;
	int	cut_i;
	int	cut_i1;

	int	type;
	jnt_type	*jnt0,	*jnt1;
	int	bno0,	bno1;
	int		si0,	si1;

	int	direct0,	direct1;
	tjnt_type	*tj;

	int	bound;

	float	dt;	// for determine direction	t1 - t0

}	seg_type;




#define         TJNT_ALLOC()	( (tjnt_type *)malloc( sizeof( tjnt_type ) ) )


	/* EmbedLink.c */
void	embed_link( vec2d *ctr, link_type *link, gp_array *agp );


	/* EmbedN3.c */
void	embed_link_n3( vec2d *ctr, link_type *link, gapp_type *gapp, gp_array *agp );


	/* EmbedLinkFinal.c */
void	embed_link_final( vec2d *ctr, link_type *link, gp_array *agp,
		seg_type aseg[], int seg_no, gapp_type *gapp, rl_aux laux[],
		link_type *ln[], int *ln_no );


	/* EmdebMarkBr.c */
void 	emded_mark_br( seg_type *s, int br, int Fbr );
void	emded_mark_br_cycle( seg_type *s, int br, int Fbr, dis_type ads[], gapp_type *gapp );

	/* EmdebRlink.c */
void 	emded_rlink( gp_array *agp, seg_type *s, float d );

	/* EmbedLinkRidge.c */
void	embed_link_ridges( vec2d ctr[], link_type *link[], int link_no,
							gp_array *agp );

void	embed_link_ridge( vec2d *ctr, link_type *link,
		vec2d actr[], link_type *alink[], int alink_no, gp_array *agp );



	/* EmbedSelect.c */
float	embed_select_link( gp_array *agp, vec2d *v, int type,
				link_type *aln[], int aln_no,
				vec2d *s_ctr, link_type **s_link );

void	embed_find_links( gp_array *agp, vec2d *v, int Mtype, float dis,
				link_type *aln[], int aln_no,
				vec2d actr[], link_type *alink[], int *no );

float	embed_dis_form_link( vec2d *ctr, link_type *link, vec2d *v );

float	embed_dis_form_link1( vec2d *ctr, link_type *link, vec2d *v );



	/* EmbedGapp.c */
void	embed_link_gapp( vec2d *ctr, link_type *link, link_type *elink,
			gapp_type *gapp, rl_aux laux[], int *lno );



	/* EmbedSegment.c */
int	embed_link_segment( dis_type ads[], int ds_no,
					seg_type seg[], float Td );

void	embed_link_segment_union( seg_type a[], int *no, dis_type ads[],
						int Tno, float Tfd );


int	embed_link_segment_cycle( seg_type a[], int seg_no,
				int no, dis_type ads[], int Tno, float Tfd );

int	embed_link_segment_cycle_nieg( seg_type aseg[], int no,
				dis_type ads[], gapp_type *gapp, int Tno );


void	embed_link_segment_cut( seg_type *seg, dis_type ads[] );

void	embed_link_segment_filter1( seg_type aseg[], int *no,
				dis_type ads[], int pno, float Tcd, int Tcno );

void	embed_link_segment_direct( seg_type *seg,
					dis_type ads[], gapp_type *gapp );


void	embed_link_segment_union_nieg( seg_type a[], int *no,
				dis_type ads[], gapp_type *gapp, int Tno );


void	embed_link_segment_free( seg_type *seg );



	/* EmbedJntN3.c */
void	embed_link_JNT_N3_filter(gp_array *agp, vec2d *ctr, link_type *link, float Tu );


#endif
