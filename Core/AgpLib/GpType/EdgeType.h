/***********************
 ***	EdgeType.h   ***
 ***********************/

#ifndef         EDGE_TYPE
#define         EDGE_TYPE

//#ifndef __SYMBIAN32__
#include	<stdlib.h>
//#endif // __SYMBIAN32__

#include	"ColorType.h"



typedef  struct  edge_ltype {

    qcolor_type   val[SP_NO];

    qcolor_type   bval[SP_NO];

} edge_ltype;



typedef  struct  edge_type {

	float depth;
//	float repth;
 
	float	width;

	edge_ltype      side[2];

}  edge_type;  


#define		EDGE_ALLOC()	( (edge_type *)malloc( sizeof(edge_type) ) )
#define		EDGE_CALLOC()	( (edge_type *)calloc( 1, sizeof(edge_type) ))

void	edge_afine( edge_type *e0, edge_type *e1, float t, edge_type *e );

void	edge_copy_inverse( edge_type *se, edge_type *e );

void	edge_inverse( edge_type *e );

#endif
