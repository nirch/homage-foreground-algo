#ifndef         _LAYER_TYPE_
#define         _LAYER_TYPE_

#include	"Uvec/Vec2d.h"

#define	MAX_LAYER_NAME	32

typedef struct layer_type {

	int	iSl0;		// id of the first sub-layer
	int	nSl;		// number of sub layers

	int	Mbr;		// mask of sub-layres id
	int	i0,	j0;
	int	i1,	j1;

	int	Fdepth_delta;

	char	name[MAX_LAYER_NAME];


	// aux
	vec2d dv; // use by reposition layers

}	layer_type;


#define		LAYER_ALLOC()	( (layer_type *)malloc( sizeof( layer_type )) )

	/* LayerTool.c */
layer_type *layer_alloc();

#endif
