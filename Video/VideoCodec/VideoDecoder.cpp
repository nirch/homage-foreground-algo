/****************************
 ***   VideoDecoder.cpp   ***
 ****************************/
#include	<string.h>
#include	"VideoDecoder.h"

extern "C"
{
#include "ImageType/ImageType.h"
}

#include "stdlib.h"




CVideoDecoder::CVideoDecoder()
{
	m_bFileOpen = false;
	m_bTempFile = false;
	m_sFilename = NULL;


	m_vimatixData = NULL;


	//
	m_iNumberOfFrames = 0;
	m_dFrameRate = 0.0;

	m_iWidth = -1;
	m_iHeight = -1;

	m_bitRate = -1;

	m_duration = -1;

	m_codec = 0;

	m_frameType = -1;


	m_imageFormat = IMAGE_FORMAT_RGB4;//IMAGE_TYPE_RGB4;



    //
	m_iFrameToDecode = 0;
	m_image = NULL;
	m_frameIndex = 0;
	m_frameTimeStamp = 0;


    memset(&m_sNextFrame, 0, sizeof(frame_type));
	m_sNextFrame.index = -1;
    memset(&m_sPrevFrame, 0, sizeof(frame_type));


	m_rangeStart = 0;		// from start
	m_rangeDuration = -1;	// to end

}


CVideoDecoder::~CVideoDecoder()
{


	if( m_image != NULL ){
		image_destroy( m_image, 1 );
		m_image = NULL;
	}

    if (m_sNextFrame.im != 0) {
      image_destroy(m_sNextFrame.im, 1);
    }

    if (m_sPrevFrame.im != 0) {
      image_destroy(m_sPrevFrame.im, 1);
    }


	if( m_vimatixData != NULL ){
		free( m_vimatixData );
		m_vimatixData = NULL;
	}

	if( m_sFilename != NULL ){
		free( m_sFilename );
		m_sFilename = NULL;
	}
}



void CVideoDecoder::SetVimatixData( const char *data )
{
	if( data == NULL || data[0] == 0 )	return;

	if( m_vimatixData != NULL )
		free( m_vimatixData );

	m_vimatixData = strdup( data );
}


int CVideoDecoder::ReadFrameByTimeStamp( int timestamp, image_type **im )
{
image_type	*im1;

	if (timestamp < m_frameTimeStamp && ( m_sPrevFrame.im == NULL || timestamp < m_sPrevFrame.timeStamp )){
		if (m_sNextFrame.im != 0) {
			image_destroy(m_sNextFrame.im, 1);
		}
    
		if (m_sPrevFrame.im != 0) {
			image_destroy(m_sPrevFrame.im, 1);
		}
    
		memset(&m_sNextFrame, 0, sizeof(frame_type));		
		memset(&m_sPrevFrame, 0, sizeof(frame_type));
		m_sNextFrame.index = -1;
	}


	while (true){

		if (m_sNextFrame.im != 0) {
			if (m_sNextFrame.timeStamp >= timestamp) {
				if (m_sPrevFrame.im != 0) {
					if ((timestamp - m_sPrevFrame.timeStamp) < (m_sNextFrame.timeStamp - timestamp)) {
						m_frameIndex = m_sPrevFrame.index;
						m_frameTimeStamp = m_sPrevFrame.timeStamp;
						m_frameType = m_sPrevFrame.type;
/*
						if( m_image != NULL )
								image_destroy(m_sPrevFrame.im, 1);
						m_image = image_make_copy( m_sPrevFrame.im );

						*im = m_image;
*/
						*im = m_sPrevFrame.im;
						return( 1 );
					}
				}

				m_frameIndex = m_sNextFrame.index;
				m_frameTimeStamp = m_sNextFrame.timeStamp;
				m_frameType = m_sNextFrame.type;
/*
				if( m_image != NULL )
					image_destroy(m_sNextFrame.im, 1);
				m_image = image_make_copy( m_sNextFrame.im );

				*im = m_image;
*/
				*im = m_sNextFrame.im;
				return( 1 );
			}
		}

		if (m_sPrevFrame.im != 0) {
		  image_destroy(m_sPrevFrame.im, 1);
		}

		m_sPrevFrame.im = m_sNextFrame.im;
		m_sPrevFrame.timeStamp = m_sNextFrame.timeStamp;
		m_sPrevFrame.index = m_sNextFrame.index;
		m_sPrevFrame.type = m_sNextFrame.type;
		m_sNextFrame.im = NULL;


    
		if( ReadFrame( m_sNextFrame.index+1, &im1 ) < 0 )
			return( -1 );


		m_sNextFrame.im = m_image;
		m_image = NULL;

		m_sNextFrame.timeStamp = GetFrameTimeStamp();
		m_sNextFrame.index = m_frameIndex;
		m_sNextFrame.type = m_frameType;
	}


	return -1;
}
 



int
CVideoDecoder::ReadFrame_Y( int frame, image_type **im )
{
image_type	*im0,	*im1;

	if( ReadFrame( frame, &im0 ) < 0 )
		return( -1 );

	im1 = image4_to_green( im0 );

	if( m_image != NULL )
		image_destroy( m_image, 1 );
	m_image = im1;

	*im = m_image;

	return( 1 );
}


int CVideoDecoder::GetDuration()
{
	if( m_duration > 0 )	return( m_duration );

	m_duration = GetNumOfFrames() * 1000 / GetFrameRate();

	return( m_duration );
}


int CVideoDecoder::ComputeTimeStampFromFrameIndex( int frameIndex )
{
	float fCurrentSec = 0;

	if (m_dFrameRate != 0 && frameIndex > 0) 
		fCurrentSec = (float)(frameIndex - 1) * (1.0 / m_dFrameRate);


	return (int)(fCurrentSec * 1000.0); // in msec
}


int CVideoDecoder::GetCodecName( char *codec, int codecLen )
{
	codec[0] = 0;
	return( -1 );
}


int CVideoDecoder::IsMimeTypeSupported( char *smime )
{
char mime[256];

	GetMIMEType( mime,256 );

	if( strcmp( mime, smime ) == 0 )
		return( 1 );

	return( -1 );
}

int CVideoDecoder::IsExtensionSupported( char *file )
{
char extension[256],	cext[256];

	gp_filename_extract_extension( file, cext, 256 );
	strcat( cext, "|" );


	GetExtension( extension, 256 );
	strcat( extension, "|" );


	
	if( gp_strcasestr( extension, cext ) != NULL )
		return( 1 );


	return( -1 );
}