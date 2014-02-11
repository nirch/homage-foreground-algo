
#include	<string.h>
#include	"Uigp/igp.h"





#include "AviEncoder/AviGetEncoder.h"

#include "AviEncoder/AviVideoEncoder.h"
#include "AviEncoder/AviVideoStreamEncoder.h"

#include "ImageType/ImageType.h"


#include "AviWriter.h"




CAviWriter::CAviWriter( int synchron )
{
	m_videoEncoder = NULL;
	m_videoStream = NULL;
	
	m_nIm = 0;
	m_iIm = 0;
	for (int i = 0; i < MAX_IM ; i++ )
		m_aIm[i] = NULL;


	m_synchron = synchron;


}

CAviWriter::~CAviWriter( void )
{
	if( m_videoEncoder != NULL ){
		delete m_videoEncoder;
		m_videoEncoder = NULL;
	}


	for( int i = 0 ; i < m_nIm; i++ ){
		image_destroy(m_aIm[i], 1);
	}

}

int CAviWriter::Open( int width, int height, int frameRate, int codec, char *outFile )
{
	m_videoEncoder = GetAviEncoder();
	
	if( m_videoEncoder == NULL )
		//error( "CAviWriter", "VideoEncoder not found" );
		return -1;
	
	if ( m_videoEncoder->Open(outFile) < 0 ){
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



	if( m_videoStream->Open() < 0 )
		//error( "CAviWriter", "videoStream->open failed" );
		return -1;


	char  file[256];
	gpFilename_force_extension( outFile, ".log", file );
	m_fp = fopen( file, "wb" );
	m_time0 = vTime();

	if( m_synchron == AW_ASYNCHRONY_THREAD ){
		m_semIn.Create( NULL, 0, MAX_IM, NULL);
		m_semOut.Create( NULL, 0, MAX_IM, NULL);
		StartThread();
	}

	return 1;
}

int CAviWriter::WriteFrame( image_type *im )
{
	if( m_synchron == AW_SYNCHRONY ){
		m_videoStream->WriteFrame( im, 0 );


		if( m_fp != NULL ){
			int dt = m_aIm[m_iIm]->timeStamp - m_time0;
			fprintf( m_fp, "%d    %d\n", m_iIm, dt );
		}

		m_iIm++;

		return( 1 );
	}


	if( m_nIm >= MAX_IM )
		return( -1 );
	m_aIm[m_nIm++] = image_make_copy( im, NULL );

	if( m_synchron == AW_ASYNCHRONY_THREAD )
		m_semIn.Release( 1 );

	return 1;
}

int CAviWriter::Close()
{
int	i;
	if( m_synchron == AW_ASYNCHRONY ){
		for( int i = 0; i < m_nIm; i++ ){
			m_videoStream->WriteFrame( m_aIm[i], 0 );

			if( m_fp != NULL ){
				int dt = m_aIm[m_iIm]->timeStamp - m_time0;
				fprintf( m_fp, "%d    %d\n", m_iIm, dt );
			}

			image_destroy( m_aIm[i], 1 );
			m_aIm[i] = NULL;
		}
	}
	else {
		if( m_synchron == AW_ASYNCHRONY_THREAD ){
			for( i = 0 ; i < m_nIm ; i++ )
				m_semOut.WaitForSingleObject();
		}
	}


	m_videoEncoder->Close();

	delete m_videoEncoder;
	m_videoEncoder = NULL;


	if( m_fp != NULL )
		fclose( m_fp );

	return 1;
}

//void CAviWriter::SetSynchrony( int flag ) 
//{ 
//	m_synchron = flag; 
//}


	


void CAviWriter::Run()
{

	while( 1 ) {
		m_semIn.WaitForSingleObject();

		if( m_videoStream == NULL )	continue;

		m_videoStream->WriteFrame(m_aIm[m_iIm], 0 );

		if( m_fp != NULL ){
			int dt = m_aIm[m_iIm]->timeStamp - m_time0;
			fprintf( m_fp, "%d    %d\n", m_iIm, dt );
		}



		image_destroy( m_aIm[m_iIm], 1 );
		m_aIm[m_iIm] = NULL;

		m_iIm++;

		m_semOut.Release( 1 );
	}
}



	


int CAviWriter::Write( imageA_type *aim, int frameRate, int codec, char *outFile )
{
int	i;
	CVideoEncoder *videoEncoder  = GetAviEncoder();

	if( videoEncoder == NULL )
		return -1;

	if ( videoEncoder->Open(outFile) < 0 ){
		delete videoEncoder;
		return -1;
	}

	if( codec <= 0 )	codec = AVI_CODEC_INDEO50;
	if( frameRate <= 0 )	frameRate = 10;


	for( i = 0 ; i < aim->nA ; i++ )
		if( aim->a[i] != NULL )	break;

	CVideoStreamEncoder *videoStream = videoEncoder->CreateVideoStream( frameRate,
		aim->a[i]->width,
		aim->a[i]->height,
		codec,
		10000 );



	if( videoStream->Open() < 0 ){
		delete videoEncoder;
		return -1;
	}


	
	for( int i = 0 ; i < aim->nA ; i++ ){
		if( aim->a[i] != NULL )
			videoStream->WriteFrame( aim->a[i], 0 );
	}


	videoEncoder->Close();

	delete videoEncoder;


	return 1;
}