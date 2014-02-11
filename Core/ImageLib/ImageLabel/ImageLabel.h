#ifndef         _IMAGE1_LABEL_
#define         _IMAGE1_LABEL_


#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"

#include "BwLabel.h"


	// Image1Label.c
imageLabel_type *imageLabelUI( image_type *sim, imageLabel_type *abw );

imageLabel_type *imageLabelUI_T( image_type *sim, int T, imageLabel_type *abw );

image_type *	image1_label( image_type *sim, bwLabel_type **tbw, int *tnBw, image_type *im );

void	imageLabel_filter( image_type *sim, image_type *lim, bwLabel_type *aBw, int nBw, int nT );

int		imageLabel_print( bwLabel_type *bw, int nBw, FILE *fp );


void	imageLabelUS_set_aux( image_type *im, bwLabel_type *aBw, int nBw );

int		imageLabelUI_eigen2d( image_type *im, int id, box2i_type *b, struct eigen2d_type *e );




	// Image1InletFilter.c
int		imageLabel_inlet_filter( image_type *sim, int n );





	// Image1Blob.c
void	image1_remove_blob( image_type *sim, int nP, int nT, int value );

void	image1_remove_blobM( image_type *sim, int nP, int pT, int bT, int value );


void	image1_fill_blob( image_type *sim, int nP, int nT, int value );


#ifdef __cplusplus
}
#endif

#endif
