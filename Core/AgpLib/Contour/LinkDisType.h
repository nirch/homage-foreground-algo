/**************************
 ***	LinkDisType.h	***
 **************************/

#ifndef		_LINK_DIS_TYPE_
#define		_LINK_DIS_TYPE_

#include	<stdlib.h>

#include	"Uvec/Vec2d.h"

#include	"GpType/LinkType.h"




typedef struct linkDis_type {
	vec2d	ctr;

	vec2d	v;

	float	a;
	
	/*	AUX	*/
	float	len;
	vec2d	u;		
	float   c_prb;	



	float	t0,	t1; 

} linkDis_type;



typedef struct linkDisArray_type {
		int		size;

        int     nLd;
		linkDis_type	*ld;

}  linkDisArray_type;



#define		LINK_DIS_ALLOC()	\
			( (linkDis_type *)malloc( sizeof( linkDis_type ) ) )



linkDisArray_type *	linkDisArray_alloc( int size );

void	linkDisArray_destroy( linkDisArray_type * ald );

linkDisArray_type *	linkDis_create( vec2d *ctr, link_type *link, int Fclose );


void	linkDisArray_bes( linkDisArray_type *ald, int Fclose );


float	linkDis_distance( linkDisArray_type *ald, vec2d  *v,
						linkDis_type **sl, float *u, float *t, float *gt );


#endif
