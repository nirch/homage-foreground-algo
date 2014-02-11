
/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#ifndef         _IMAGE_READ_
#define         _IMAGE_READ_



#if defined _DEBUG || defined DEBUG
#pragma comment( lib, "ImageCodecD.lib" )
#else
#pragma comment( lib, "ImageCodec.lib" )
#endif



#include	"Uigp/igp.h"
#include	"ImageType/ImageType.h"


	// ImageRead.c
image_type *	image_read_file( char *file );

image_type *	image3_read_file( char *file );

image_type *	image1_read_file( char *file );

image_type *	imageS_read_file( char *file );

image_type *	imageS3_read_file( char *file );

image_type *	image_read_buffer( char *data, int bytes, char *sextension );


#endif
