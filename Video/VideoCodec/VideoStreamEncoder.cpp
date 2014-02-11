
#include "VideoStreamEncoder.h"
extern "C"
{
#include "ImageType/ImageType.h"
#include "ImageType/PaletteType.h"
}


CVideoStreamEncoder::CVideoStreamEncoder()
{
	m_numberOfFrames = 0;


	m_codec = 0;

	m_width = 0;
	m_height = 0;

	m_frameRate = 0;
	m_bitRate = 0;

	m_size = 0;
	m_sizeLimit = 0;
}


CVideoStreamEncoder::CVideoStreamEncoder( int codec, float frameRate,
										 int width, int height, int bitRate )
{
	m_numberOfFrames = 0;


	m_codec = codec;
	m_frameRate = frameRate;
	m_width = width;
	m_height = height;

	m_bitRate = bitRate;
}


CVideoStreamEncoder::~CVideoStreamEncoder()
{
	Close();
}



int CVideoStreamEncoder::Open() 
{
	return( 1 );
}

int CVideoStreamEncoder::Close() 
{	
	return( 1 );
}




