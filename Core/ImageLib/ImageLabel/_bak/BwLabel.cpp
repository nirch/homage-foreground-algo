/*************************
 ***   Image1Label.c   ***
 *************************/
#include <math.h>
#include "Uigp/igp.h"
#include "ImageType/ImageType.h"

#ifdef _DEBUG
//#define _DUMP
#endif

#include "Umath/Matrix2Type.h"
#include "Umath/EigenType.h"

#include "ImageLabel/ImageLabel.h"

#include "ImageDump/ImageDump.h"





int
bwLabel_printA( bwLabel_type *bw, int nBw, FILE *fp )
{
	int	i,	no;

	for( i = 0, no = 0 ; i < nBw ; i++ ){
		if( bw[i].id != i )	continue;

		fprintf( fp, "%d  -   color: %d   no: %d\n", (int)bw[i].id, (int)bw[i].color, bw[i].no );
	}

	return( no );
}




void
bwLabel_merge( bwLabel_type *abw, int nBw, int id1, int id )
{
	int	i;

	abw[id].no += abw[id1 ].no;

	for( i = id1 ; i < nBw ; i++ ){
		if( abw[i].id == id1 )
			abw[i].id = id;
	}
}