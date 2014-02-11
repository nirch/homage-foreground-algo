/************************
 *** WbmapDecoder.cpp ***
 ***********************/

#include "WbmapDecoder.h"


extern "C"
{
#include "ImageType/ImageType.h"
#include "ImageType/PaletteType.h"
#include "Uigp/igp.h"
#include "Ugio/GioType.h"

#include "ImageWbmp.h"
}


CWbmapDecoder::CWbmapDecoder() : CImageDecoder()
{

}

CWbmapDecoder::~CWbmapDecoder()
{
}
	






int CWbmapDecoder::Decode(const char *filename, image_type **im) 
{
	
	if( (m_image = image_read_wbmp_file((char*)filename)) == NULL )
		return( IMAGE_CODEC_CORRUPTED_INPUT_STREAM );

	*im = m_image;

	return( 1 );
	
}



	
int CWbmapDecoder::Decode(char *data, int bytes, image_type **im )
{
	if( (m_image = image_read_wbmp_buffer(data, bytes, 0)) == NULL )
		return( IMAGE_CODEC_CORRUPTED_INPUT_STREAM );

	*im = m_image;

	return( 1 );
	

}


