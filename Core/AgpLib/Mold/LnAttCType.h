/************************
 ***    LnAttCType.h   ***
 ************************/
 
#ifndef		_LN_ATTC_H_
#define		_LN_ATTC_H_


#include	"Uigp/igp.h"

#include	"LnSegType.h"

struct lnAttc_type;

typedef struct lnAttcP_type {
	int	i;

	int	type;	// 1, 2, 3
	float		u;
	float		t;
//	float		dt;

	struct lnAttc_type *at;

} lnAttcP_type;



typedef struct lnAttc_type {
	int	i;

	int	iCmp;

	lnSeg_type	*ls;


	float	 gt0, gt1;	// on the segment


	float cgt0,	cgt1;	// on the contour
	float clen;

	float	contourLen;


	float	avGt;
	float	avU,	avU0,	avU1;
	float	minU,	maxU;

	struct lnAttc_type	*lnext;

	struct lnAttc_type	*next;





	lnAttcP_type	pa,	na;


}	lnAttc_type;


lnAttc_type *	lnAttc_alloc();

void lnAttc_destroy( lnAttc_type *at );

void lnAttcL_destroy( lnAttc_type *atL );



void	lnAttcL_insert( lnAttc_type **atL, lnAttc_type *at );


void	lnAttc_set_cgt( link_type *contour, float lenContour, lnAttc_type *at);


lnAttc_type *	lnAttc_select( lnAttc_type *atL, vec2d *p );

lnAttc_type *	lnAttc_get( lnAttc_type *atL, int i );


void	lnAttc_print( lnAttc_type *at, char *file );
void	lnAttc_print_1( lnAttc_type *at, FILE *fp );


	/* lnAttTied.c */
link_type *lnAttc_tied( link_type *contour, lnAttc_type *at, lnAttc_type *at2 );


	/* LnAttCConnect.c */
//void	lnAttc_connect( lnAttc_type *atL, link_type *contour, lnAttCmp_type **lnCmp );

int		lnAttc_connect_type( lnAttc_type *at, lnAttc_type *nat );

int		lnAttc_connect_du_dt( lnAttc_type *at, lnAttc_type *nat, float *gu, float *gt );

int		lnAttc_gt( lnAttc_type *at, lnAttc_type *nat, float *gt );





	/* lnAttCPos.c */
void	lnAttc_pos( link_type *contour, float lenContour, 
							lnAttc_type *at, lnAttc_type *at2, int tp );



#endif 