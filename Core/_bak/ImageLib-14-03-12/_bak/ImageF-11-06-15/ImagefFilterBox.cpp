/************************
 ***   PfDeblur.cpp   ***
 ************************/
#include	<stdlib.h>
#include	<string.h>

#include "Utime/GpTime.h"

//#ifdef _DEBUG
#define _DUMP
//#endif


//#define USE_IPP
#ifdef USE_IPP
#pragma comment( lib, "ippi.lib" )
#include "ippi.h"
#endif


#include "ImageDump/ImageDump.h"




#ifdef USE_IPP
image_type *
imageF_filter_box( image_type *sim, int rC, image_type *im )
{
IppiSize dstSize,	maskSize;
IppiPoint anchor;
IppStatus ret;

	im = image_recreate( im, sim->height, sim->width, 4, 1 );

	dstSize.width = im->width-2*rC;
	dstSize.height = im->height-2*rC;

	maskSize.width = 2*rC+1;
	maskSize.height = 2*rC+1;


//	anchor.x = 25;//rC;
//	anchor.y = 25;//rC;
	anchor.x = rC;
	anchor.y = rC;


	ret = ippiFilterBox_32f_C1R( sim->data_f + rC*(sim->width+1), 4*sim->width,
									im->data_f + rC*(im->width+1), 4*im->width, dstSize,
									maskSize, anchor );


	return( im );
}
#endif

