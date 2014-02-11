
#include	<string.h>
#include	"Uigp/igp.h"





#include "AviEncoder/AviGetEncoder.h"

#include "AviEncoder/AviVideoEncoder.h"
#include "AviEncoder/AviVideoStreamEncoder.h"

#include "ImageType/ImageType.h"


#include "AviWriter.h"




CAviWriter::CAviWriter(void)
{
	m_videoEncoder = NULL;
	m_videoStream = NULL;
	m_synchrony = 0;
	m_nIm = 0;

	for (int i = 0; i < MAX_IM ; i++ )
		m_aIm[i] = NULL;

}

CAviWriter::~CAviWriter(void)
{
	if( m_videoEncoder != NULL )	delete m_videoEncoder;

	for( int i = 0; i < m_nIm; i++ )
		image_destroy(m_aIm[i], 1);

}

int CAviWriter::Open( int width, int height, int frameRate, int codec, char *outFile )
{
	m_videoEncoder = GetAviEncoder();
	
	if( m_videoEncoder == NULL )
		//error( "CAviWriter", "VideoEncoder not found" );
		return -1;
	
	if ( m_videoEncoder->Open(outFile) == FALSE ){
		delete m_videoEncoder;
		//error( "CAviWriter", "videoEncoder->open failed" );
		return -1;
	}

	if( codec <= 0 )	codec = AVI_CODEC_INDEO50;
	if( frameRate <= 0 )	frameRate = 10;

	m_videoStream = m_videoEncoder->CreateVideoStream( frameRate,
							 width,
							 height,
							 codec,
							 10000 );



	if( m_videoStream->Open() == NULL )
		//error( "CAviWriter", "videoStream->open failed" );
		return -1;

	return 1;
}

int CAviWriter::WriteFrame( image_type *im )
{
	if( m_synchrony == 1 )
	{
		m_videoStream->WriteFrame(im, 0 );
	}
	else
	{
		if( m_nIm < MAX_IM )
		{
			m_aIm[m_nIm] = image_make_copy(im, NULL);
			m_nIm++;
		}
	}

	return 1;
}

int CAviWriter::Close()
{
	if( m_synchrony == 0 )
	{
		for( int i = 0; i < m_nIm; i++ )
		{
			m_videoStream->WriteFrame(m_aIm[i], 0 );
		}
	}

	m_videoEncoder->Close();

	return 1;
}

void CAviWriter::SetSynchrony( int flag ) 
{ 
	m_synchrony = flag; 
}


	




	