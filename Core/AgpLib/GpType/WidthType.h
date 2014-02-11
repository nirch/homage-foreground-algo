/************************
 ***	WidthType.h   ***
 ************************/

#ifndef         WIDTH_TYPE
#define         WIDTH_TYPE

#include	"Uvec/Vec2d.h"




typedef struct width_type {
	float	w[2];

	/* AUX	*/
	vec2d	bes;


	/* for Depth */
//	float	depth[2];

}	width_type;
	


#define		WDITH_TYPE_ALLOC()      \
                        ( (width_type *)malloc( sizeof( width_type ) ) );


width_type      * width_alloc();

width_type      * width_make_copy( width_type *w );

void	width_afine( width_type *w0, width_type *w1, float t, width_type *w );

void	width_inverse( width_type *w );
#endif
