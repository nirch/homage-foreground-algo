/***************************
 ***	ImageAverage.c   ***
 ***************************/

#include	<stdlib.h>
#include	"Uigp/igp.h"

#include	"ImageType/ImageType.h"





image_type * 
image_average( image_type *images[], int nImage )
{
image_type	*im;
int	i, j,	n;
u_int	*p[100],	*tp;
int	sR,	sG,	sB;



	im = image_create( images[0]->row, images[0]->column, images[0]->depth, 1, NULL );

//	p = ( u_int ** )malloc( sizeof(u_int *) * nImage );


	for( n = 0 ; n < nImage ; n++ )
		p[n] = (u_int *)images[n]->data;

	


	tp = (u_int *)im->data;
	for( i = 0; i < im->row; i++){
		for( j = 0; j < im->column; j++ ){

			sR = sG = sB = 0;
			for( n = 0 ; n < nImage ; n++ ){
				sR += IMAGE4_RED(*p[n]);
				sG += IMAGE4_GREEN(*p[n]);
				sB += IMAGE4_BLUE(*p[n]);
				p[n] ++;
			}

			sR /= nImage;
			sG /= nImage;
			sB /= nImage;

			*tp++ = IMAGE4_RGB( sR, sG, sB );
		}
	}

//	free( p );

	return( im );

}

