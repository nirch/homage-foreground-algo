#include	<string.h>
#include	<stdio.h>


#include	"Uigp/igp.h"
#include	"ImageType/ImageType.h"

#include	"ImageRead.h"

#define _JPEG
//#define _ALL
//
#define _TIFF

#include	"Uigp/igp.h"


#if defined _DEBUG || defined DEBUG
#pragma comment( lib, "ImageD.lib" )
#pragma comment( lib, "TiffCoderD.lib" )
#else
#pragma comment( lib, "Image.lib" )
#pragma comment( lib, "Util.lib" )
#endif


#include	"ImageType/ImageType.h"
#include	"Bmp/ImageBmp.h"

#define _ALL
#ifdef _ALL
extern "C" {
#include	"Gif/ImageReadGif.h"
#include	"Ems/ImageEms.h"
#include	 "Npm\ImageNpm.h"
#include	"wbmp\ImageWbmp.h"
};
#include	"Targa/ImageTarga.h"


#include	"Png/PngCodec/Png/ImageReadPng.h"

#endif

#ifdef _JPEG
#include	"Jpeg\JpegCodec/ImageReadJpeg.h"
#endif

#ifdef _TIFF
#include	"Tiff\TiffCoder\ImageReadTiff.h"
#endif



image_type *
image_read_file( char *file )
{
char	extension[256];
image_type	*im;

	gp_filename_extract_extension( file, extension, 256 );


	gp_strlwr( extension );

	if( strcmp( extension, ".bmp") == 0 ){
		im = image_read_bmp_file( file );
		return( im );
	}

#ifdef _JPEG
	if( strcmp( extension, ".jpg") == 0 || strcmp( extension, ".jpeg") == 0 ){
		im = image_read_jpeg( file );
		return( im );
	}
#endif


#ifdef _ALL



	if( strcmp( extension, ".png") == 0 ){
		im = image_read_png_file( file );
		return( im );
	}


	if( strcmp( extension, ".gif") == 0 ){	
		im = image_read_gif_file( file );
		return( im );
	}

	if( strcmp( extension, ".npm") == 0 ){
		im = image_read_npm_file( file );
		return( im );
	}

	if( strcmp( extension, ".wbmp") == 0 ){
		im = image_read_wbmp_file( file );
		return( im );
	}

	if( strcmp( extension, ".ems") == 0 ){
		im = image_read_ems_file( file );
		return( im );
	}


#ifdef _TIFF
	if( strcmp( extension, ".tif") == 0 || strcmp(extension,".tiff") == 0){
		im = image_read_tiff_file( file );
		return( im );
	}
#endif

#endif

	return( NULL );
}



image_type *
image1_read_file( char *file )
{
image_type	*sim,	*im;

	if( (sim = image_read_file( file )) == NULL )
		return( NULL );


	im = image4_to_y( sim, NULL );


	image_destroy( sim, 1 );


	return( im );
}


image_type *
imageS_read_file( char *file )
{
	image_type	*sim,	*im;

	if( (sim = image1_read_file( file )) == NULL )
		return( NULL );


	im = image2_from_image1( sim, NULL );


	image_destroy( sim, 1 );


	return( im );
}

image_type *
imageS3_read_file( char *file )
{
	image_type	*sim,	*im;

	if( (sim = image3_read_file( file )) == NULL )
		return( NULL );


	im = image6_from_image3( sim, NULL );


	image_destroy( sim, 1 );


	return( im );
}

image_type *
image3_read_file( char *file )
{
image_type	*sim,	*im;
char	extension[256];


	gp_filename_extract_extension( file, extension, 256 );

	if( strcmp( extension, ".bmp" ) == 0 ){
		im = image3_read_bmp_file( file );
		return( im );
	}



	if( (sim = image_read_file( file ) ) == NULL )
		return( NULL );


	im = image3_from_image4( sim, NULL );
	image_destroy( sim, 1 );
	return( im );
}




image_type *
image_read_buffer( char *data, int bytes, char *sextension )
{
image_type *im,	*im1;
char	extension[256];



	gp_filename_extract_extension( sextension, extension, 256 );
	gp_strlwr( extension );


	if( strcmp( extension, ".bmp") == 0 ){
		im = image_read_bmp_buffer( data, bytes, 0 );
		return(im);
	}


#ifdef _JPEG
	if( strcmp( extension, ".jpg") == 0 || strcmp( extension, ".jpeg") == 0 ){
		im = image_read_jpg_buffer( data, bytes, 0 );
		if( im == NULL )	return( NULL );

		if( im->depth == 1){
			im1 = image4_from_y( im );
			image_destroy( im, 1 );
			im = im1;
		}

		return( im );
	}
#endif


#ifdef _ALL
	if( strcmp( extension, ".jpg") == 0 || strcmp( extension, ".jpeg") == 0 ){
		im = image_read_jpg_buffer( data, bytes, 0 );
		if( im == NULL )	return( NULL );

		if( im->depth == 1){
			im1 = image4_from_y( im );
			image_destroy( im, 1 );
			im = im1;
		}

		return( im );
	}


	if( strcmp( extension, ".wbmp") == 0 ){
		im = image_read_wbmp_buffer( data, bytes, 0 );
		return(im);
	}


	if( strcmp( extension, ".ems") == 0 ){
		im = image_read_ems_buffer( data, bytes, 0 );
		return(im);
	}


	if( strcmp( extension, ".npm") == 0 ){
		im = image_read_npm_buffer( data, bytes, 0 );
		return(im);
	}




	if( strcmp( extension, ".gif") == 0 ){
		im = image_read_gif_buffer(data,bytes,0);
		return(im);
	}

	if( strcmp( extension, ".png") == 0 ){
		im = image_read_png_buffer(data,bytes,0);
		return(im);
	}
#endif

	return( NULL );
}