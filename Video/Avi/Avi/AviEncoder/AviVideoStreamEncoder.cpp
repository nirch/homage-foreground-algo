/*************************************
 ***   AviVideoStreamEncoder.cpp   ***
 *************************************/

#include	"windows.h"
#include	"vfw.h"
//#include	"AviUtil/Cdib.h"

#include "Wutil/UWdib/Cdib.h"

#include	"Uigp/igp.h"
#include	"ImageType/ImageType.h"


#include "AviVideoStreamEncoder.h"


CAviVideoStreamEncoder::CAviVideoStreamEncoder(int codec, float frameRate,
											   int width, int height, int bitrate ) 
{
	m_numberOfFrames = 0;
	m_quality = 0;


	m_codec = codec;
	m_frameRate = frameRate;
	m_width = width;
	m_height = height;
	m_bitRate = bitrate;


	if( m_bitRate < 0 || m_bitRate > 10000 )
		m_bitRate = 10000;

	
	
	
	if( m_quality == 0  )
		m_quality = 75;


	if ( m_codec < AVI_CODEC_RAW || m_codec >= AVI_CODEC_CVID)
		m_codec = AVI_CODEC_MSVC;



	m_psStream = NULL;
	m_psCurrent = NULL;
	m_psCompressed = NULL;
	
	m_pDib = NULL ;	
}





CAviVideoStreamEncoder::~CAviVideoStreamEncoder()
{
	Close();
}



int CAviVideoStreamEncoder::Create( PAVIFILE m_afFile )
{
AVISTREAMINFO    strhdr;


	memset(&strhdr, 0, sizeof(strhdr));	
	SetRect(&strhdr.rcFrame, 0, 0, m_width, m_height); 	
//	strhdr.dwQuality = m_quality * 100;
	strhdr.dwQuality = m_bitRate;
	strhdr.dwSuggestedBufferSize  = 0;
	strhdr.dwRate = m_frameRate*1000;
	strhdr.dwScale = 1000;
	strhdr.fccHandler = 0;//mmioFOURCC('M','S','V','C');
	strhdr.fccType = streamtypeVIDEO;// stream type		

	HRESULT hr = AVIFileCreateStream(m_afFile, &m_psStream, &strhdr); 
    if (hr != AVIERR_OK )
		return -1; 
 

	
	m_psCurrent =  m_psStream;




	if( m_codec != AVI_CODEC_RAW ){
		AVICOMPRESSOPTIONS opts;
		AVICOMPRESSOPTIONS FAR * aopts[1] = {&opts};
		memset(&opts, 0, sizeof(opts));		
		opts.fccHandler=FOURCC_from_codecType( m_codec);  
//		opts.dwQuality = m_quality;
		opts.dwQuality = m_bitRate;
		opts.dwKeyFrameEvery = 5;
		opts.dwFlags = AVICOMPRESSF_KEYFRAMES ;
		opts.fccType = streamtypeVIDEO;
		
		
		BITMAPINFOHEADER hdr;
		memset(&hdr, 0, sizeof(hdr));
		hdr.biSize = sizeof(hdr);
		hdr.biBitCount = 24;
		hdr.biWidth = m_width;
		hdr.biHeight = m_height; 
		hdr.biSizeImage = m_width * m_height * (24/3);
		hdr.biPlanes = 1;
		

		//SetAviVideoCompression(avi,hbm,&opts,true,hwnd);
		HRESULT hr = AVIMakeCompressedStream(&m_psCompressed, m_psStream, aopts[0], NULL);
		AVISaveOptionsFree(1,aopts);
		if (AVIERR_OK == hr ) 
		{
			
			hr = AVIStreamSetFormat(m_psCompressed, 0, &hdr, hdr.biSize+hdr.biClrUsed*sizeof(RGBQUAD));
			if (hr == AVIERR_OK )
			{
				m_psCurrent = m_psCompressed;
			}
		}		
	}



	return( 1 );
}


int CAviVideoStreamEncoder::Open() 
{
	return(1);
}


int CAviVideoStreamEncoder::Close() 
{	


	if ( NULL != m_pDib ){
		delete m_pDib ;
		m_pDib = NULL;
	}

	if ( m_psStream ){
		AVIStreamRelease( m_psStream );	
		m_psStream = NULL;
	}


	if ( m_psCompressed ){
		AVIStreamRelease( m_psCompressed );
		m_psCompressed = NULL;
	}

	return 1;
}





void CAviVideoStreamEncoder::CreateDib(int row,int col, int bits)
{


	
	m_pDib = new CDib(row, col, 24);		
	m_pDib->CreateSection();
	
	HRESULT hr = m_psCurrent->SetFormat(0,m_pDib->m_lpBMIH,	    // stream format
				m_pDib->m_lpBMIH->biSize +   // format size
				m_pDib->m_lpBMIH->biClrUsed * sizeof(RGBQUAD));	
#ifdef _DEBUG_PRINT
	if ( AVIERR_OK != hr )
		printf("%s\n",TranslateAVIERR_to_string(hr));
#endif
	
	
}






int CAviVideoStreamEncoder::WriteFrame( image_type *frame, int SetKeyFrame)
{
	LPBITMAPINFOHEADER alpbi;
	
	image_type *im = NULL;
//	if ( frame->depth == 1 ){
////		im = image_1to4(frame);
//		im = image4_from_y( frame );
//		frame = im;
//	}
//	if ( frame->depth == 3 ){
//		im = image3_to_image4( frame, NULL );
//		frame = im;
//	}

	if( frame->depth != 4 ){
		im = image4_from( frame, NULL );
		frame = im;
	}




	DWORD flags = 0;
	if ( 1 == SetKeyFrame )
		flags = AVIIF_KEYFRAME;
	
	if ( m_pDib == NULL ) 
		CreateDib(frame->row, frame->column, 24);
		
	alpbi = m_pDib->m_lpBMIH;
	m_pDib->data_image(frame, TRUE );
	

	HRESULT hr = AVIStreamWrite(m_psCurrent,//m_psCompressed,	// stream pointer
		m_numberOfFrames,// time of this frame	
		1,	// number to write
		(LPBYTE)m_pDib->m_lpImage,
		alpbi->biSizeImage,	// size of this frame
		flags,			 // flags....
		NULL,
		NULL);


	if( im != NULL )
		image_destroy(im,1);
	
	if (hr != AVIERR_OK)
	{		
#ifdef _DEBUG_PRINT
		printf("%s\n",TranslateAVIERR_to_string(hr));
#endif
		return -1;
	}
	
	m_numberOfFrames++;
	return 1;
	
}

