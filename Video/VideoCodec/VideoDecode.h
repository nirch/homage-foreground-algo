#ifndef __VIDEO_DECODE_H__
#define __VIDEO_DECODE_H__

#include "Ugio/GioType.h"

#ifndef VF_I
#define VF_I		1 /* Intra */
#define VF_P		2 /* Predicted */
#define VF_B		3 /* Bi-dir predicted */
#endif

class CVideoDecode 
{
public:

	CVideoDecode();

	virtual ~CVideoDecode();


	virtual int Init( u_char *buffer=NULL, int bufferSize=0 ) = 0;

	virtual void Close() = 0;


	virtual int Decode( u_char *inData, int inSize, struct image_type **im, int fSkip=0 ) = 0;


	void SetUseAssembler( int use_assembler )	{ m_useAssembler = use_assembler; }

	void SetImageFormat( int imageFormat )	{ m_imageFormat = imageFormat; }

//	void SetWidth( int width )	{ m_width = width; }

//	void SetHeight( int height )	{ m_height = height; }

	int GetWidth()		{ return( m_width ); }

	int GetHeight()	{ return( m_height ); }


//	int GetBitrate()	{ return m_bitrate; }


//	virtual int  GetCodecName( char *codec, int codecLen ) = 0;

	int	GetFrameType()	{ return m_frameType; }


	virtual int ComputeBitrate( u_char *inData, int inBytes )	{ return 0; }

protected:
	int	m_useAssembler;

	int	m_frameType;

	int	m_imageFormat;

	int m_width;
	int m_height;

//	int	m_channels;

//	int	m_bitsPerSample;

//	int	m_sampleRate;

//	int	m_bitrate; 
};


#endif