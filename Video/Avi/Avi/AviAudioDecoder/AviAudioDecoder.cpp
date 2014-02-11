#include <windows.h>
#include	"Uigp/igp.h"

#include	"AviAudioDecoder.h"
#include	"Mp3\Mp3Decoder\Mp3GetAudioDecoder.h"



#include "AviGetAudioDecoder.h"



CAudioDecoder *GetAviAudioDecoder()
{
	CAudioDecoder *decoder;
	decoder = new CAviAudioDecoder();
	return decoder;
} 




CAviAudioDecoder::CAviAudioDecoder()
{
	m_samples		= 0;

	m_codec			= 0;
	m_bitrate		= 0;


	m_pStream		= NULL;

	m_Pos			= 0;

	m_tempFile		= NULL;

	m_sec1bytes		= 0;

	m_data			= NULL;

	m_dataSize      = 0;


	m_audioTrackFile = NULL;

	m_aDecoder = NULL;
}


CAviAudioDecoder::~CAviAudioDecoder()
{

	Close();
}



int CAviAudioDecoder::Open(const char *filename )
{
char	Format[512];
long	cbFormat = 512;
int		wFormatTag;
int	ret;


	AVIFileInit();	// initialize the AVIFILE library

	if (AVIStreamOpenFromFile( &m_pStream, filename, 
				streamtypeAUDIO, 0, OF_READ, NULL) != 0)
		return -1;

	m_Pos = 0;
	AVIStreamReadFormat(m_pStream, m_Pos, Format, &cbFormat);
		
	wFormatTag = ((WAVEFORMAT *)Format)->wFormatTag;

	if ( wFormatTag != 1 ){
		ret = OpenMp3( wFormatTag );
		return( ret );
	}


	m_bitsPerSample = ((PCMWAVEFORMAT *)Format)->wBitsPerSample;
	m_sampleRate = ((PCMWAVEFORMAT *)Format)->wf.nSamplesPerSec;
	m_channels = ((PCMWAVEFORMAT *)Format)->wf.nChannels;

	if( m_bitsPerSample == 0 )	m_bitsPerSample = 16;

	return 1;
}


int CAviAudioDecoder::OpenMp3( int formatTag )
{
char	file[512];

	if( ExtractAudio( ".mp3", file ) < 0 )
		return( -1 );

	if( (m_aDecoder = GetMp3AudioDecoder() ) == NULL )
		return( -1 );

	if( m_aDecoder->Open( file ) < 0 ){
		delete m_aDecoder;
		m_aDecoder = NULL;
		return( -1 );
	}

	m_audioTrackFile = strdup( file );



	m_bitsPerSample = m_aDecoder->GetBitsPerSample();
	m_sampleRate = m_aDecoder->GetSampleRate();
	m_channels = m_aDecoder->GetChannels();


	return( 1 );
}



int CAviAudioDecoder::Open( char *data, int bytes )
{
char	filename[256];

	gp_filename_get_temporary( "ain", 0, ".avi", filename );

	gp_file_create( data, bytes, filename );


	m_tempFile = strdup( filename );

	return( Open( filename ) );
}


int CAviAudioDecoder::ReOpen()
{

	return 1;
}

int CAviAudioDecoder::Close()
{
	if( m_pStream != NULL )
	{
		AVIStreamRelease(m_pStream);
		m_pStream = NULL;
	}

	AVIFileExit();


	if( m_data != NULL ){
		free( m_data );
		m_data = NULL;
	}


	if( m_tempFile != NULL ){
		unlink( m_tempFile );
		free( m_tempFile );
		m_tempFile = NULL;
	}



	if( m_aDecoder != NULL ){
		delete m_aDecoder;
		m_aDecoder = NULL;
	}

	if( m_audioTrackFile != NULL ){
		unlink( m_audioTrackFile );
		free( m_audioTrackFile );
		m_audioTrackFile = NULL;
	}



	return 1;
}




int
CAviAudioDecoder::ReadFrame( char **data, int *bytes, int max_bytes  )
{
char	Format[512];
long	cbFormat = 512;
int		wFormatTag;

int		samples, no_bytes;
long	lBytesRez,	lSamplesRez;


	if( m_aDecoder != NULL ){
		return( m_aDecoder->ReadFrame( data, bytes, max_bytes ) );
	}



	*bytes = 0;
	*data = NULL;

	AVIStreamReadFormat(m_pStream, m_Pos, Format, &cbFormat);
		
	wFormatTag = ((WAVEFORMAT *)Format)->wFormatTag;
//	if ( wFormatTag != 1 )
//		return 0;

	m_bitsPerSample = ((PCMWAVEFORMAT *)Format)->wBitsPerSample;
	m_sampleRate = ((PCMWAVEFORMAT *)Format)->wf.nSamplesPerSec;
	m_channels = ((PCMWAVEFORMAT *)Format)->wf.nChannels;

	if( m_bitsPerSample == 0 )	m_bitsPerSample = 16;
	
	m_sec1bytes = m_sampleRate*m_channels*m_bitsPerSample/8;
	
	no_bytes = max_bytes > 0 ?  max_bytes : m_sec1bytes;
		
	if( m_dataSize < no_bytes ){
		m_data = (char *)realloc( m_data, no_bytes );
		m_dataSize = no_bytes;
	}

	samples = no_bytes /( m_channels * m_bitsPerSample / 8 );

	int ret = AVIStreamRead( m_pStream, m_Pos, samples,   
					m_data, no_bytes, &lBytesRez, &lSamplesRez );

	if ( lSamplesRez == 0 )
		return -1;



//	if( fp == NULL )
///		fp = fopen( "d:\\_mbox\\bug\\aa.mp3", "wb" );

//	fwrite( m_data, lSamplesRez, 1, fp );

	m_Pos += lSamplesRez;

	*bytes = lBytesRez;
	*data = m_data;

	return( lSamplesRez );
}



int CAviAudioDecoder::IsMimeSupport( char *mime )
{
	return 0;
}

int CAviAudioDecoder::GetMIMEType( char *mime, int mimeLen )
{
	strncpy( mime, "video/avi", mimeLen );
	return( 1 );
}

int CAviAudioDecoder::GetExtension( char *extension, int extensionLen )
{
	strncpy( extension, ".avi", extensionLen );
	return( 1 );
}



int CAviAudioDecoder::ExtractAudio( char *extension, char *file )
{
FILE	*fp;
//int	ret;
long		bytes,	samples;
char	*data;
	gp_filename_get_temporary( "avi_audio", 0, extension, file );

	if( (fp = fopen( file, "wb" )) == NULL )
		return( -1 );


	data = ( char *)malloc(40000 );



	while(  AVIStreamRead( m_pStream, m_Pos, 40000,   
					data, 40000, &bytes, &samples ) == 0 ){

		if ( bytes == 0 )
			break;

		fwrite( data, bytes, 1, fp );

		m_Pos += samples;
	}

	fclose( fp );

	free( data );
	return( 1 );
}