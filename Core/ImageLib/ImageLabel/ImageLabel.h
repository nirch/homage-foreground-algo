#ifndef         _IMAGE_LABEL_
#define         _IMAGE_LABEL_


#ifdef __cplusplus
extern "C" {
#endif

#include	"Uigp/igp.h"
#include	"Uln/Cln/ClnType.h"

#include "BwLabel.h"


		// ImageLabel.c
imageLabel_type *imageLabel_alloc();

void imageLabel_destroy( imageLabel_type *abw );

int imageLabel_no( imageLabel_type *abw );

int	imageLabel_bigest( imageLabel_type *abw, int color );


int	imageLabel_print( imageLabel_type *abw, FILE *fp );


void	bwLabel_merge( bwLabel_type *abw, int nBw, int id1, int id );

int		bwLabel_printA( bwLabel_type *bw, int nBw, FILE *fp );

int		bwLabel_no( bwLabel_type *bw, int nBw, int T );

void	bwLabel_order( bwLabel_type *abw, int nBw, int NI, int aI[], int *nI );

void	bwLabelA_order( imageLabel_type *abw, int color, int NI, int aI[], int *nI );


	// ImageLabelUI.c
imageLabel_type *imageLabelUI( image_type *sim, imageLabel_type *abw );

imageLabel_type *imageLabelUI_T( image_type *sim, int T, int margin, imageLabel_type *abw );

image_type *	image1_label( image_type *sim, bwLabel_type **tbw, int *tnBw, image_type *im );

void	imageLabelUI_filter( image_type *sim, image_type *lim, bwLabel_type *aBw, int nBw, int nT );


void	imageLabelUI_set_id( imageLabel_type *abw );

void	imageLabelUI_set_aux( image_type *im, bwLabel_type *aBw, int nBw );

void	imageLabelUI_set_box( imageLabel_type *abw );


int		imageLabelUI_eigen2d( image_type *im, int id, box2i_type *b, struct eigen2d_type *e );



	// ImageLabelUS.cpp
imageLabel_type *imageLabelUS( image_type *sim, int T, int inv, int margin, imageLabel_type *abw );

imageLabel_type *imageLabelUS_N( image_type *sim, int T, int inv, int margin, imageLabel_type *abw );

void	imageLabelUS_set_id( imageLabel_type *abw );

int		imageLabelUS_set_pixel( image_type *sim, imageLabel_type *abw, int value );

void	imageLabelUS_create( image_type *im, bwLabel_type **tbw, int *tnBw );

void	imageLabelUS_value( imageLabel_type *abw, image_type *sim );

int		imageLabelUS_eigen2d( imageLabel_type *abw, int id,  struct eigen2d_type *e );

image_type *	imageLabelUS_image( imageLabel_type *abw, image_type *im );

int	imageLabelUS_unoin( imageLabel_type *abw, int d, int size );

int	imageLabelUS_unoinCorner( imageLabel_type *abw );

void	imageLabel_merge( imageLabel_type *abw, int id, int id1 );




	// Image1InletFilter.c
int		imageLabel_inlet_filter( image_type *sim, int n );





	// Image1Blob.c
void	image1_remove_blob( image_type *sim, int nP, int nT, int value );

void	image1_remove_blobM( image_type *sim, int nP, int pT, int bT, int value );


//void	image1_fill_blob( image_type *sim, int nP, int nT, int value );
void	image1_fill_blob( image_type *sim, int nP, int pT, int bT, int value );

void	image1_fill_blobV( image_type *vim, image_type *sim, int nP, int pT, int bT, int vT, int value );


	// ImageLabelUIContour.cpp
cln_type *	imageLabelUI_contour( image_type *im, int id );

	// ImageLabelUSContour.cpp
cln_type *	imageLabelUS_contour( image_type *im, int id );

#ifdef __cplusplus
}
#endif

#endif
