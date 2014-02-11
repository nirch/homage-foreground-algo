/*******************
 ***   vec2d.h   ***
 *******************/
#ifndef	_PT2D_GROUP_TYPE_
#define _PT2D_GROUP_TYPE_

#ifdef __cplusplus
extern "C" {
#endif

#include "Pt2dType.h"

//#define MAX_GROUP	4096

	// p2d	-  2d point

typedef struct pt2dGroup_type {
	int	group;

	int	no;

	vec2d	p;

} pt2dGroup_type ;




typedef struct pt2dGroupA_type {
	int	nG;
	pt2dGroup_type	*g;

} pt2dGroupA_type;


   

	/* V2c2dTool.c */
pt2dGroupA_type *	pt2dGroupA_alloc();

void	pt2dGroupA_destroy( pt2dGroupA_type *av );


pt2dGroupA_type *	pt2dGroupA_set( pt2dGroupA_type *ag, pt2dA_type *apt );

int	pt2dGroupA_filter( pt2dGroupA_type *ag, int tNo );



#ifdef __cplusplus
}
#endif

#endif
