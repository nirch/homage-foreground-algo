/*********************************
 ***   ImageVideoDecoder.cpp   ***
 *********************************/
#include <string.h>
#include "Uigp/igp.h"


#include "ImageVideoDecoder.h"


#include "ImageCodec/ImageRead.h"


CVideoDecoder *GetImageVideoDecoder()
{
	CVideoDecoder *decoder;
	decoder = new CImageVideoDecoder();
	return decoder;
}




CImageVideoDecoder::CImageVideoDecoder()
	:CVideoDecoder()
{
int	i;

	m_image = NULL;
	m_imageY = NULL;

	for( i = 0 ; i < MAX_IMAGE ; i++ )
		m_fname[i]= NULL;


	SetImageFormat( IMAGE_FORMAT_RGB );

	m_extendName = 1;
}


CImageVideoDecoder::~CImageVideoDecoder()
{
	Close();
}


int CImageVideoDecoder::Open( char*data, int bytes)
{
int	ret;

	ret = -1;

	return ret;
}



int CImageVideoDecoder::Open(const char* filename)
{

	if( PraseFileName( (char *)filename ) < 0 )
		return( -1 );



	image_type *tim;
	if( (tim = image_read_file( (char *)filename ) ) == NULL )
		return( -1 );


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
		m_image = tim;
		break;
	}


	m_iWidth = m_image->width;
	m_iHeight = m_image->height;

	m_sFilename = strdup( filename );

	return 1;
}



int CImageVideoDecoder::GetPreviewFrameNo()
{
	return( 0 );
}


int CImageVideoDecoder::ReOpen()
{
	return 1;
}


int CImageVideoDecoder::Close()
{
int	i;

	if (m_image != 0) {
		image_destroy( m_image, 1 );
		m_image = 0;
	}

	if( m_imageY != NULL ){
		image_destroy( m_imageY, 1 );
		m_imageY = NULL;
	}


	for( i = 0 ; i < m_iNumberOfFrames ; i++ ){
		if( m_fname[i] != NULL ){
			free( m_fname[i] );
			m_fname[i] = NULL;
		}
	}

	return 1;
}




int
CImageVideoDecoder::ReadFrame( int frame, image_type **im )
{
	if( frame < 0 || frame >= m_iNumberOfFrames || m_fname[frame] == NULL ){
		*im = NULL;
		return( -1 );
	}

	if( m_iFrame == frame ){
		*im = m_image;
		return( 1 );
	}


	if( m_imageY != NULL ){
		image_destroy( m_imageY, 1 );
		m_imageY = NULL;
	}


	//char	file[512];
	//sprintf( file, "%s%s%.2d%s", m_baseName, m_conjuction, frame, m_extension );
	
	
	image_type	*tim;
	if( (tim = image_read_file( m_fname[frame] ) ) == NULL ){
		*im = NULL;
		return( -1 );
	}



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



//	m_image = tim;
	m_iFrame = frame;

	m_frameType = 0;
	m_frameTimeStamp = ComputeTimeStampFromFrameIndex( frame );



	*im = m_image;
	return( 1 );
}


//int
//CImageVideoDecoder::ReadFrame_Y( int frame, image_type **im )
//{
//image_type	*im0,	*im1;
//
//	if( ReadFrame( frame, &im0 ) < 0 )
//		return( -1 );
//
//	im1 = image4_to_green( im0 );
//
//	if( m_imageY != NULL )
//		image_destroy( m_imageY, 1 );
//	m_imageY = im1;
//
//	*im = m_imageY;
//
//	return( 1 );
//}


int CImageVideoDecoder::ReadFrameByTimeStamp( int timestamp, image_type **im )
{
int	frame;

	frame = GetFrameRate() * timestamp / 1000.0;


	return ReadFrame( frame, im );
}



int CImageVideoDecoder::GetMIMEType( char *mime, int mimeLen )
{
	strncpy( mime, "video/image", mimeLen );
	return( 1 );
}

int CImageVideoDecoder::GetExtension( char *extension, int extensionLen )
{
	strncpy( extension, ".bmp|.jpg|.png", extensionLen );
	return( 1 );
}





int CImageVideoDecoder::PraseFileName( char *inFile )
{
char	dir[256],	name[256],	fname[256];
char	*p,	*sp;
int	i;



	if( gpFile_exist( inFile ) != 1 )
		return( -1 );


	if( m_extendName == 0 ){
		m_fname[0] = strdup( inFile );
		m_iNumberOfFrames = 1;

		m_iFrame = 0;

		m_iFrameToDecode = m_iFrame;

		return( 1 );
	}



	m_iNumberOfFrames = 1;
	m_iFrame = 0;

	gp_filename_split( inFile, dir, name, m_extension );




	int len = strlen( name );


	for( p = name, sp = NULL ; *p != 0  ; p++ )
		if( *p == '-' ||  *p == '_' )
			sp = p;


	if( sp == NULL ){
		m_iFrame = 0;
		m_fname[m_iFrame] = strdup( inFile );
		m_iNumberOfFrames = 1;
		return( 1 );
	}


	*sp = 0;

	m_iNumberOfFrames = gpDir_get_files_list(dir, name, m_extension, m_fname, MAX_IMAGE, 1 );


	gp_filename_extract_name( inFile, name, 256 );
	m_iFrame = 0;
	for( i = 0 ; i < m_iNumberOfFrames ; i++ ){
		gp_filename_extract_name( m_fname[i], fname, 256 );
		if( strcmp( fname, name ) == 0 ){
			m_iFrame = i;
			break;
		}
	}

	m_iFrameToDecode = m_iFrame;

	return( 1 );
}


int
CImageVideoDecoder::Append( char *file )
{
int	frame;
image_type	*im;

	frame = m_iNumberOfFrames;

	m_fname[frame] = strdup( file );

	m_iNumberOfFrames++;

	if( ReadFrame( frame, &im ) < 0 ){
		m_iNumberOfFrames--;
		free( m_fname[frame] );
		return( -1 );
	}

	return( frame );
}
