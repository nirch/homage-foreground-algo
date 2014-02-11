/************************
 *** NpmDecoder.cpp ***
 ***********************/

#include "NpmDecoder.h"

extern "C"
{
#include "ImageType/ImageType.h"
#include "ImageType/PaletteType.h"
#include "Uigp/igp.h"
#include "Ugio/GioType.h"

#include "ImageNpm.h"
}


CNpmDecoder::CNpmDecoder():CImageDecoder()
{
}

CNpmDecoder::~CNpmDecoder()
{
}
	


int CNpmDecoder::Decode(const char *filename, image_type **im) 
{
	if( (m_image = image_read_npm_file((char*)filename)) == NULL )
		return( IMAGE_CODEC_CORRUPTED_INPUT_STREAM );

	*im = m_image;
	return( 1);
	
}





int CNpmDecoder::Decode(char *data, int bytes, image_type **im )
{
	if( (m_image = image_read_npm_buffer( data, bytes, 0)) == NULL )
		return( IMAGE_CODEC_CORRUPTED_INPUT_STREAM );

	*im = m_image;
	return( 1);
}






