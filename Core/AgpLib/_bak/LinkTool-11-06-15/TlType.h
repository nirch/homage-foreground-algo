/*********************
 ***	TlType.h   ***
 *********************/
#ifndef         _TL_TYPE_
#define         _TL_TYPE_

#include	"Uigp/igp.h"
#include	"GpType/LinkType.h"


typedef struct tl_type {
	vec2d	ctr;   

	link_type	*l;

	int	mbr;

}	tl_type;


#define         TL_ALLOC()	( (tl_type *)malloc( sizeof( tl_type ) ) );


int	tl_array_select( tl_type  tlink[], int no, vec2d  *v, int mbr,
                                tl_type **sl, float *u, float *t );


int	tl_array_set( vec2d *ctr, link_type *link, link_type *elink,
											tl_type  atl[], int *no );
	

#endif
