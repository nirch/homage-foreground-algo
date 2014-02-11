#ifndef _VIDEO_DECODER_H_
#define _VIDEO_DECODER_H_

#if defined _DEBUG || defined DEBUG
#pragma comment( lib, "VideoCodecD.lib" )
#else
#pragma comment( lib, "VideoCodec.lib" )
#endif


#include	"Uigp/igp.h"


#define VF_I		1 /* Intra */
#define VF_P		2 /* Predicted */
#define VF_B		3 /* Bi-dir predicted */


#define VD_UNSUPPORTED_INPUT_CODEC	-2



extern "C"
{
	struct image_type;
	struct palette_type;
}



class CVideoDecoder
{
public:
	CVideoDecoder();
	virtual ~CVideoDecoder();	

	virtual int GetMIMEType( char *mime, int mimeLen ) = 0;
	virtual int GetExtension( char *extension, int extensionLen ) = 0;
	virtual int IsMimeTypeSupported( char *mime );
	virtual int IsExtensionSupported( char *extension );

	virtual int Open( char *data, int bytes ) = 0;

	virtual int Open(const char *filename ) = 0;

	virtual int ReOpen() = 0;

	virtual int Close() = 0;


	virtual int Append( char *file ) 	{ return( -1 );}

	// feautre of the video . These value need to be set By Open()
	virtual int GetWidth()	{ return m_iWidth; }
	virtual int GetHeight()	{ return m_iHeight; }

	virtual float GetFrameRate() { return m_dFrameRate; }



	virtual int GetBitrate()	{ return m_bitRate; }

	virtual int GetCodecId()		{ return( m_codec<<4 );   }

	virtual int GetDuration();

	virtual int	GetNumOfFrames()	{ return m_iNumberOfFrames; }

	virtual	int	GetPreviewFrameNo()		{ return -1; }




	virtual int ReadFrame(int frameIndex, image_type **im ) = 0;

	virtual int ReadFrame_Y( int frameIndex, image_type **im );

    virtual int ReadFrameByTimeStamp( int timestamp, image_type **im );


	void	SetImageFormat( int imageFormat )	{ m_imageFormat = imageFormat; }


	
  


	// feautre of the current frame. These value need to be set By ReadFrame()
	int GetFrameIndex()			{ return m_frameIndex; }
	int	GetFrameTimeStamp()		{ return m_frameTimeStamp; }
	int	GetFrameType()			{ return m_frameType; }
	bool IsFrameKeyFrame()		{ return ( m_frameType == VF_I  ); }




	int	GetCurrentFrameNo()		{ return m_iFrameToDecode; }
	int ComputeTimeStampFromFrameIndex( int frameIndex );



	virtual char *GetVimatixData()	{ return( m_vimatixData ); }

	
	virtual int  GetCodecName( char *codec, int codecLen );


	
	// input range;  default all clip
	void	SetRange( u_int startTime, u_int duration );
	int		GetRangeStart()	{ return m_rangeStart; }
	int		GetRangeEnd()	{ return (m_rangeDuration < 0)? -1 : m_rangeStart + m_rangeDuration; }
	int		GetRangeDuration()	{ return m_rangeDuration; }




protected:
	void	SetVimatixData( const char *data );


    struct frame_type {
		  image_type* im;
		  int	index;
		  int	timeStamp;
		  int	type;
    };

	int m_iWidth;
	int	m_iHeight;
	int m_iNumberOfFrames;

	float m_dFrameRate;

	int	m_bitRate;

	int	m_duration;			// clip duration in milisecond

	int	m_codec;


	int	m_imageFormat;	// IMAGE_FORMAT_RAGB ; IMAGE_FORMAT_YUV420 ; IMAGE_FORMAT_Y


	char	*m_vimatixData;


	char *m_sFilename;

	bool m_bFileOpen;

	bool m_bTempFile;


	int m_iFrameToDecode;// **** starting from frame 0, and not from frame 1 ***



	// current frame feautre
	int m_frameIndex;
	int	m_frameTimeStamp;
	int	m_frameType;


	// current frame image
	image_type *m_image;


	// input range
	int	m_rangeStart;
	int	m_rangeDuration;

        

	// use by ReadFrameByTimeStamp
    frame_type m_sNextFrame;
    frame_type m_sPrevFrame;
};



#endif
