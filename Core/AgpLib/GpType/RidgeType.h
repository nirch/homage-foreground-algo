/************************
 ***	RidgeType.h   ***
 ************************/

#ifndef         RIDGE_TYPE
#define         RIDGE_TYPE

#include	"Uigp/igp.h"

#include	"ColorType.h"



typedef  struct  ridge_type {
	float	depth;
//	float	rdepth;
 
	float	width;

	qcolor_type	mval[SP_NO];
	qcolor_type	lm[SP_NO];

	qcolor_type	rval[SP_NO]; 

}  ridge_type;  



#define         RIDGE_ALLOC()	( (ridge_type *)malloc( sizeof(ridge_type) ) )
#define         RIDGE_CALLOC()	( (ridge_type *)calloc( 1, sizeof(ridge_type)) )

void	ridge_afine( ridge_type *r0, ridge_type *r1, float t, ridge_type *r );

#endif
