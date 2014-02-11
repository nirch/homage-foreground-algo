/*********************
 ***	N3Type.h   ***
 *********************/

#ifndef         N3_TYPE
#define         N3_TYPE

//#ifndef __SYMBIAN32__
#include	<stdlib.h>
//#endif // __SYMBIAN32__


#include	"ColorType.h"


typedef  struct  n3_ltype {
	qcolor_type   val[SP_NO];
	qcolor_type   bval[SP_NO];

}	n3_ltype;




typedef  struct  n3_type {
	float	depth;
//	float	rdepth;

	float	sdepth[2];
	float	width[2];
    qcolor_type	mval[SP_NO]; 
    n3_ltype	side[2];

}	n3_type;  



#define		N3_ALLOC()	( (n3_type *)malloc( sizeof(n3_type) ) )
#define		N3_CALLOC()	( (n3_type *)calloc( 1, sizeof(n3_type) ) )

void	n3_afine( n3_type *n0, n3_type *n1, float t, n3_type *n );

void	n3_copy( n3_type *se, n3_type *e );

void	n3_copy_inverse( n3_type *se, n3_type *e );

void	n3_inverse( n3_type *e );



int		n3_sign( n3_type *n3 );


#endif
