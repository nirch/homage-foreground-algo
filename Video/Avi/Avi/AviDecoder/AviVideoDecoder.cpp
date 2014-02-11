#include <windows.h>
//#include <wmsysprf.h>
#include <vfw.h>
//#include "dib.h"




#include	"Uigp/igp.h"
#include	"ImageType/ImageType.h"


#include	"AviUtil/DibToImage.h" // sits localy in this library.
#include "AviCodec.h"



#include "AviGetDecoder.h"

#include "AviVideoDecoder.h"



CVideoDecoder *GetAviDecoder()
{
	CVideoDecoder *decoder;
	decoder = new CAviVideoDecoder();
	return decoder;
}



//#define MOTION_JPEG


CAviVideoDecoder::CAviVideoDecoder()
{
	m_sFilename = NULL;
	m_bFileOpen = false;

	m_bTempFile = false;

	m_image = NULL;


	m_lLength = 0;
	m_jpgBuf = NULL;
	m_codec = AVI_CODEC_UNKNOEN;
	m_aviFrame = NULL;
	m_pStream = NULL;
}




CAviVideoDecoder::~CAviVideoDecoder()
{
	Close();
	
}


int CAviVideoDecoder::Open( char *data, int bytes )
{
char	filename[2056];
int	ret;

	gp_filename_get_temporary( "ain", 0, ".avi", filename );

	gp_file_create( data, bytes, filename );

	ret =  Open( filename );

	m_bTempFile = true;
	return( ret );
}


int CAviVideoDecoder::ReOpen()
{

	if( m_bFileOpen == false)
		return -1;
	m_iFrameToDecode = 0;
	return 1;
}


int CAviVideoDecoder::Close()
{
	
	if( m_bFileOpen == true ){

		if ( m_aviFrame )
			AVIStreamGetFrameClose(m_aviFrame);
		m_aviFrame = NULL;

		if ( m_pStream )
			AVIStreamRelease(m_pStream);
		m_pStream = NULL;

		AVIFileExit();
	}
	if ( m_jpgBuf )
		free (m_jpgBuf);
	m_jpgBuf = NULL;
	m_bFileOpen = false;

	if( m_bTempFile == true )
		unlink( m_sFilename );
	m_bTempFile = false;

	if( m_sFilename != NULL )
	{
		free(m_sFilename);
		m_sFilename = NULL;
	}

	if( m_image != NULL ){
		image_destroy( m_image, 1 );
		m_image = NULL;
	}
	

	return 1;
}



//***********************************
bool CAviVideoDecoder::CheckMJPEG()
{
	LONG lFmtLength;
	m_lLength = 0;
	/*AVIStreamOpenFromFile(&m_pStream, filename,
        streamtypeVIDEO, 0,
		OF_READ | OF_SHARE_DENY_NONE, //OF_SHARE_EXCLUSIVE,
        NULL);
	*/
	AVIStreamFormatSize(m_pStream, 0, &lFmtLength);
	

	LPBITMAPINFOHEADER lpSrcFmt = (LPBITMAPINFOHEADER)malloc(lFmtLength);

    AVIStreamReadFormat(m_pStream, 0, lpSrcFmt, &lFmtLength);
	if ((lpSrcFmt->biCompression != mmioFOURCC('M', 'J', 'P', 'G')) &&
		(lpSrcFmt->biCompression != mmioFOURCC('m', 'j', 'p', 'g')) &&
		(lpSrcFmt->biCompression != mmioFOURCC('d', 'm', 'b', '1')) &&
		(lpSrcFmt->biCompression != mmioFOURCC('j', 'p', 'e', 'g')))
	{
	    if (lpSrcFmt)
			free(lpSrcFmt);			
		return false;
	}


	AVISTREAMINFO si;
    m_lLength = (ULONG)lpSrcFmt->biSizeImage;
    AVIStreamInfo(m_pStream, &si, AVIStreamInfo(m_pStream, NULL, 0));

	if (si.dwSuggestedBufferSize)
        if ((LONG)si.dwSuggestedBufferSize > m_lLength)
            m_lLength = (LONG)si.dwSuggestedBufferSize;

	if (!m_lLength)
	    m_lLength = (ULONG)(lpSrcFmt->biHeight * lpSrcFmt->biWidth * ((lpSrcFmt->biBitCount / 8) + (lpSrcFmt->biBitCount % 8)));

	m_jpgBuf = (LPBYTE)malloc((m_lLength / 16) * 16 + 16);


	free(lpSrcFmt);
	m_codec = AVI_CODEC_MJPG;
	return( true );
}
//***********************************

int CAviVideoDecoder::Open(const char *filename)
{


	if ( filename != m_sFilename )// if called from ReOpen!!!
	{
		if ( m_sFilename != NULL ) 
			free (m_sFilename);
		m_sFilename = strdup(filename);
	}



	
	m_pStream = 0;	
	// first - initialize the AVIFILE library
	AVIFileInit();	
	
	PAVIFILE pfile;
	AVIFILEINFO pfi;
	// second - open the file
	AVIFileOpen(&pfile, (char *)m_sFilename,OF_READ,NULL);

	
	if ( pfile == NULL ) 
	{
		m_pStream = 0;
		if ( m_bTempFile == true )
			unlink(m_sFilename);
		m_bTempFile = false;
		free (m_sFilename);
		m_sFilename = NULL;
		m_codec = AVI_CODEC_UNKNOEN;
		return( -1 );
	}

	// get info struct
	AVIFileInfo(pfile,&pfi,sizeof(AVIFILEINFO));
	// get the video stream (what if there are more than one stream?
	int res = AVIFileGetStream(pfile,&m_pStream,streamtypeVIDEO,0);
	AVIFileRelease(pfile);
	if ( res != 0 )
	{
		// **** error ! 
		m_pStream = 0;
		if ( m_bTempFile == true )
			unlink(m_sFilename);
		m_bTempFile = false;
		free (m_sFilename);
		m_sFilename = NULL;
		m_codec = AVI_CODEC_UNKNOEN;
		return( -1 );
	}
	

	// set codec info
	
	


	m_dFrameRate = pfi.dwRate/pfi.dwScale;
//	m_iFrameDelay = 1000 / m_dFrameRate;
	m_iWidth = pfi.dwWidth;
	m_iHeight = pfi.dwHeight;
	m_iNumberOfFrames = AVIStreamLength(m_pStream);


	SetCodecName();

	//check if mjpeg:
#ifdef MOTION_JPEG
	if (true == CheckMJPEG())
	{			
		m_bFileOpen = true;		
		return( 1 );
	}
#endif
	// get 
	

	BITMAPINFOHEADER bimapInfo;
	memset( &bimapInfo, 0, sizeof( BITMAPINFOHEADER) );
	bimapInfo.biBitCount = 32;
	bimapInfo.biHeight = pfi.dwHeight;
	bimapInfo.biWidth = pfi.dwWidth;
	bimapInfo.biSize = 40;
	bimapInfo.biPlanes = 1;


	

	m_aviFrame = AVIStreamGetFrameOpen(m_pStream, &bimapInfo );
	if( m_aviFrame == NULL )
		m_aviFrame = AVIStreamGetFrameOpen(m_pStream, NULL);

	
	if ( m_aviFrame == NULL )
	{
		if ( m_bTempFile == true )
			unlink(m_sFilename);
		m_bTempFile = false;
		free (m_sFilename);
		m_sFilename = NULL;
		return( VD_UNSUPPORTED_INPUT_CODEC );
	}

	AVISTREAMINFO si;
    AVIStreamInfo(m_pStream, &si, AVIStreamInfo(m_pStream, NULL, 0));
	m_codec = si.fccHandler;
	
	m_bFileOpen = true;
	
	return( 1 );
}









int CAviVideoDecoder::ReadFrame( int frame, image_type **im )
{	
	if( m_iFrameToDecode - 1 == frame && m_image != NULL ){
		*im = m_image;
		return( 1 );
	}
	
	
	//if ( m_image != NULL )
	//	image_destroy(m_image, 1);
	//m_image = NULL;
	
	if( frame < 0 || frame >= m_iNumberOfFrames )	
		return( -1 );

#ifdef MOTION_JPEG
	if ( AVI_CODEC_MJPG ==  m_codec ){
		m_image = MJPEG_Frame(frame);
		if( m_image == NULL )	return( -1 );

		*im = m_image;
		return( 1 );
	}
#endif

	if( frame < m_frameIndex || frame > m_frameIndex +1 ){
		AVIStreamGetFrame(m_aviFrame, (frame ==0)? 0 : frame-1 );
	}

	void *pDib = AVIStreamGetFrame(m_aviFrame,frame);
	
	// check if we succeded
	if (pDib == NULL)	
		return -1;



	image_type *tim = DibToImage( pDib );
	switch( m_imageFormat ){
	case IMAGE_FORMAT_Y:
		m_image = image4_to_y( tim, m_image );
		image_destroy( tim, 1 );
		break;

	case IMAGE_FORMAT_RGB:
		m_image = image3_from_image4( tim, m_image );
		image_destroy( tim, 1 );
		break;

	case IMAGE_FORMAT_RGB4:
		if( m_image != NULL )
			image_destroy( m_image, 1 );
		m_image = tim;
		break;
	}
//	m_image = DibToImage( pDib );


	m_frameTimeStamp = ComputeTimeStampFromFrameIndex( m_iFrameToDecode );
	m_frameIndex = frame;
	m_frameType = 0;

	m_iFrameToDecode =  frame + 1;// had success with this one, wait for next

	*im = m_image;

	return 1;

}


void CAviVideoDecoder::SetCodecName()
{
LONG lFmtLength;

	AVIStreamFormatSize(m_pStream, 0, &lFmtLength);


	LPBITMAPINFOHEADER lpSrcFmt = (LPBITMAPINFOHEADER)malloc(lFmtLength);

	AVIStreamReadFormat(m_pStream, 0, lpSrcFmt, &lFmtLength);


	m_codecName[0] = lpSrcFmt->biCompression & 0xFF;
	m_codecName[1] = (lpSrcFmt->biCompression>>8) & 0xFF;
	m_codecName[2] = (lpSrcFmt->biCompression>>16) & 0xFF;
	m_codecName[3] = (lpSrcFmt->biCompression>>24) & 0xFF;
	m_codecName[4] = 0;


	free(lpSrcFmt);
}


int CAviVideoDecoder::GetCodecName( char *codec, int codecLen )
{
	strncpy( codec, m_codecName, codecLen );
	return( 1 );
}



int CAviVideoDecoder::GetMIMEType( char *mime, int mimeLen )
{
	strncpy( mime, "video/avi", mimeLen );
	return( 1 );
}

int CAviVideoDecoder::GetExtension( char *extension, int extensionLen )
{
	strncpy( extension, ".avi", extensionLen );
	return( 1 );
}