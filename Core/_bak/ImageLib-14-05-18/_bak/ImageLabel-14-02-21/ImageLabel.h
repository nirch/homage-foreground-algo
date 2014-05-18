#ifndef         _IMAGE1_LABEL_
#define         _IMAGE1_LABEL_


#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"

#include "BwLabel.h"

	// Image1Label.c
image_type *	image1_label( image_type *sim, bwLabel_type **tbw, int *tnBw, image_type *im );

void	imageLabel_filter( image_type *sim, image_type *lim, bwLabel_type *aBw, int nBw, int nT );

int		imageLabel_print( bwLabel_type *bw, int nBw, FILE *fp );


	// Image1InletFilter.c
int		imageLabel_inlet_filter( image_type *sim, int n );



void	imageLabelUS_set_aux( image_type *im, bwLabel_type *aBw, int nBw );


	// Image1Blob.c
void	image1_remove_blob( image_type *sim, int nP, int nT, int value );

void	image1_fill_blob( image_type *sim, int nP, int nT, int value );


#ifdef __cplusplus
}
#endif

#endif
