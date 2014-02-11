#ifndef __IMAGE_VIDEO_DECODER__
#define __IMAGE_VIDEO_DECODER__

#include	"VideoCodec/VideoDecoder.h"


#define		MAX_IMAGE	10000




class CImageVideoDecoder : public CVideoDecoder
{
public:
	CImageVideoDecoder();
	~CImageVideoDecoder();

	int GetMIMEType( char *mime, int mimeLen );
	int GetExtension( char *extension, int extensionLen );

	int Open(char* data, int bytes);
	int Open(const char* filename);
	int ReOpen();

	int Close();


	int	GetPreviewFrameNo();



	int ReadFrame( int frame, image_type **im );
//	int ReadFrame_Y( int frame, image_type **im );


	int ReadFrameByTimeStamp( int timestamp, image_type **im );

	int	Append( char *file );

	void	SetExtendName( int fExtend )	{ m_extendName = fExtend; }


private:
	int		PraseFileName( char *inFile );



public:
	int	m_extendName;
protected:

	image_type *m_imageY;

	int	m_iFrame;

	char	m_extension[256];

	char	*m_fname[MAX_IMAGE];

};

#endif // __REAL_VIDEO_DECODER__
