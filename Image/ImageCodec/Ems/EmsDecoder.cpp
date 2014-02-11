/************************
 *** EmsDecoder.cpp ***
 ***********************/

#include "EmsDecoder.h"

extern "C"
{
#include "ImageType/ImageType.h"
#include "ImageType/PaletteType.h"
#include "Uigp/igp.h"
#include "Ugio/GioType.h"

#include "ImageEms.h"
}


CEmsDecoder::CEmsDecoder():CImageDecoder()
{
}

CEmsDecoder::~CEmsDecoder()
{
}
	


	
int CEmsDecoder::Decode(const char *filename, image_type **im)
{
	if( m_image != NULL )	image_destroy( m_image, 1 );

	if( (m_image = image_read_ems_file((char*)filename) ) == NULL )
		return( IMAGE_CODEC_COULD_NOT_OPEN_STREAM );

	*im = m_image;

	return( 1);
}


int CEmsDecoder::Decode( char *data, int bytes, image_type **im)
{
	if( m_image != NULL )	image_destroy( m_image, 1 );

	if( (m_image = image_read_ems_buffer( data, bytes, 0) ) == NULL )
		return( IMAGE_CODEC_COULD_NOT_OPEN_STREAM );

	*im = m_image;
	return( 1);
}









