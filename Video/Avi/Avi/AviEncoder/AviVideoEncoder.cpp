/*******************************
 ***   AviVideoEncoder.cpp   ***
 *******************************/

#include	"Uigp/igp.h"


#include "AviVideoEncoder.h"
#include "AviVideoStreamEncoder.h"
#include "AviAudioStreamEncoder.h"
#include "errno.h"


CVideoEncoder *GetAviEncoder()
{
	CVideoEncoder *encoder;
	encoder = new CAviVideoEncoder();
	return encoder;
}



CAviVideoEncoder::CAviVideoEncoder()
{
	AVIFileInit();
	m_afFile = NULL;
}

CAviVideoEncoder::~CAviVideoEncoder()
{
	if ( m_afFile != NULL ){
		Close();
		m_afFile = NULL;
	}

	if ( m_sFilename != NULL ){
		free(m_sFilename);
		m_sFilename = NULL;
	}

	AVIFileExit();
}


int CAviVideoEncoder::Open() 
{
	return -1;
}

int CAviVideoEncoder::GetData( char **data, int *bytes, int DetauchData )
{
  return -1;
}

int CAviVideoEncoder::Open(const char *filename ) 
{
			
	
	HRESULT hr = AVIFileOpen(&m_afFile, (char *)filename, OF_WRITE | OF_CREATE , NULL);// truncates an old file if existed
	//
	if ( NULL == m_afFile || hr != AVIERR_OK )
		return -1;

	// get info struct
	hr = AVIFileInfo(m_afFile,&m_fiInfo,sizeof(AVIFILEINFO));	
	if ( hr != AVIERR_OK || !(m_fiInfo.dwCaps & AVIFILECAPS_CANWRITE))
	{
		AVIFileRelease(m_afFile);		
		return -1;
	}	

	m_sFilename = strdup(filename);
	return 1;	
}


int CAviVideoEncoder::Close()
{
	CloseAllStreams();

	HRESULT hr = AVIERR_OK;
	if (NULL != m_afFile)
		hr = AVIFileRelease(m_afFile);

	m_afFile = NULL;
	
	return( 1 );
}



int CAviVideoEncoder::CloseAllStreams()
{
	if ( NULL != m_AudioStream)
	{
		m_AudioStream->Close();
//		delete m_AudioStream;
	}



	if ( NULL != m_VideoStream)
	{
		m_VideoStream->Close();
//		delete m_VideoStream;
	}

	return true;

}



CVideoStreamEncoder *
CAviVideoEncoder::CreateVideoStream(int frameRate, int width, int height, int codec/*=0*/, int quality/*=0*/)
{
CAviVideoStreamEncoder *stEncoder;

	if( m_VideoStream != NULL )
		return( NULL );
	

	stEncoder = new CAviVideoStreamEncoder(codec, frameRate, width, height, quality);

	if( stEncoder->Create( m_afFile ) < 0 ){
		delete stEncoder;
		return( NULL );
	}

	
	m_VideoStream = stEncoder;
	return stEncoder;
}




CAudioStreamEncoder *CAviVideoEncoder::CreateAudioStream( int sampleRate,
	int bitRate,int bitPerSample, int codecType, int channels) 
{
CAviAudioStreamEncoder *stEncoder;

	if (m_AudioStream != NULL ) 		
		return NULL;
	
	stEncoder = new CAviAudioStreamEncoder( sampleRate, bitRate, bitPerSample, channels, codecType);


	if( stEncoder->Create( m_afFile ) < 0 ){
		delete stEncoder;
		return( NULL );
	}

	
	
	m_AudioStream = stEncoder;
	return stEncoder;
}





	/*
	#define AVIERR_UNSUPPORTED      MAKE_AVIERR(101)
#define AVIERR_BADFORMAT        MAKE_AVIERR(102)
#define AVIERR_MEMORY           MAKE_AVIERR(103)
#define AVIERR_INTERNAL         MAKE_AVIERR(104)
#define AVIERR_BADFLAGS         MAKE_AVIERR(105)
#define AVIERR_BADPARAM         MAKE_AVIERR(106)
#define AVIERR_BADSIZE          MAKE_AVIERR(107)
#define AVIERR_BADHANDLE        MAKE_AVIERR(108)
#define AVIERR_FILEREAD         MAKE_AVIERR(109)
#define AVIERR_FILEWRITE        MAKE_AVIERR(110)
#define AVIERR_FILEOPEN         MAKE_AVIERR(111)
#define AVIERR_COMPRESSOR       MAKE_AVIERR(112)
#define AVIERR_NOCOMPRESSOR     MAKE_AVIERR(113)
#define AVIERR_READONLY		MAKE_AVIERR(114)
#define AVIERR_NODATA		MAKE_AVIERR(115)
#define AVIERR_BUFFERTOOSMALL	MAKE_AVIERR(116)
#define AVIERR_CANTCOMPRESS	MAKE_AVIERR(117)
#define AVIERR_USERABORT        MAKE_AVIERR(198)
#define AVIERR_ERROR            MAKE_AVIERR(199)
	*/



const char *TranslateAVIERR_to_string(HRESULT avierr_code)
{

	switch( avierr_code )
	{
	case AVIERR_UNSUPPORTED:
		return "AVIERR_UNSUPPORTED";
		break;
	case AVIERR_BADFORMAT:
		return "AVIERR_BADFORMAT";
		break;
	case AVIERR_MEMORY:
		return "AVIERR_MEMORY";
		break;
	case AVIERR_INTERNAL:
		return "AVIERR_INTERNAL";
		break;
	case AVIERR_BADFLAGS:
		return "AVIERR_BADFLAGS";
		break;
	case AVIERR_BADPARAM:
		return "AVIERR_BADPARAM";
		break;
	case AVIERR_BADSIZE:
		return "AVIERR_BADSIZE";
		break;
	case AVIERR_BADHANDLE:
		return "AVIERR_BADHANDLE";
		break;
	case AVIERR_FILEREAD:
		return "AVIERR_FILEREAD";
		break;
	case AVIERR_FILEWRITE:
		return "AVIERR_FILEWRITE";
		break;
	case AVIERR_FILEOPEN:
		return "AVIERR_FILEOPEN";
		break;
	case AVIERR_COMPRESSOR:
		return "AVIERR_COMPRESSOR";
		break;
	case AVIERR_NOCOMPRESSOR:
		return "AVIERR_NOCOMPRESSOR";
		break;
	case AVIERR_READONLY:
		return "AVIERR_READONLY";
		break;
	case AVIERR_NODATA:
		return "AVIERR_NODATA";
		break;
	case AVIERR_BUFFERTOOSMALL:
		return "AVIERR_BUFFERTOOSMALL";
		break;
	case AVIERR_CANTCOMPRESS:
		return "AVIERR_CANTCOMPRESS";
		break;
	case AVIERR_USERABORT:
		return "AVIERR_USERABORT";
		break;
	case AVIERR_ERROR:
		return "AVIERR_ERROR";
		break;
	default:
		return "unknown error";
		break;
	}
}



int FOURCC_from_codecType(int codecType)
{
	switch (codecType)
	{
	case AVI_CODEC_IV32 :
		return mmioFOURCC('I','V','3','2'); 
		break;
	case AVI_CODEC_IV50 :
		return mmioFOURCC('I','V','5','0'); 
		break;
	case AVI_CODEC_MSVC :
		return mmioFOURCC('M','S','V','C'); 
		break;
	case AVI_CODEC_MP42 :
		return mmioFOURCC('M','P','4','2'); 
		break;
	case AVI_CODEC_CVID :
		return mmioFOURCC('C','V','I','D'); 
		break;	
	}
	return 0;
}


int CAviVideoEncoder::GetMIMEType( char *mime, int mimeLen )
{
	strncpy( mime, "video/avi", mimeLen );
	return( 1 );
}

int CAviVideoEncoder::GetExtension( char *extension, int extensionLen )
{
	strncpy( extension, ".avi", extensionLen );
	return( 1 );
}