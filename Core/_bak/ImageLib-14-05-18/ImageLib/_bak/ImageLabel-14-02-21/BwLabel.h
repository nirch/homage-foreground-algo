#ifndef         _BW_LABEL_
#define         _BW_LABEL_


#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"
#include "Ubox/Box2d.h"



	// Image2BwLabel.c
typedef struct bwLabel_type {
	short	color;
	int	id;
	int	no;

	vec2d	p;

	float	e1,	e2;
	vec2d	v1;

	box2i	b;
}	bwLabel_type;



void	image2_bwLabel( image_type *im, bwLabel_type **tbw, int *tnBw );

int		bwLabel_no( bwLabel_type *bw, int nBw, int T );

void	image2_bwLabel_remove_boundary( image_type *im, bwLabel_type *bw );


void	image2_bwLabel_set_id( image_type *im, bwLabel_type *bw );

void	image2_bwLabel_set_aux( image_type *im, bwLabel_type *aBw, int nBw );


void	image2_bwLabel_set_direction( image_type *im, bwLabel_type *bw, int nBw );


int		bwLabel_gesture_id( bwLabel_type *bw, int nBw, int T );


void	bwLabel_order( bwLabel_type *abw, int nBw, int aI[], int *nI );



image_type *	image1_connect_component( image_type *sim, int T, bwLabel_type **abw, int *nBw, image_type *im );



#ifdef __cplusplus
}
#endif

#endif
