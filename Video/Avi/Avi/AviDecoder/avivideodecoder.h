/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#if	defined WIN32 || defined _WINDOWS 

#ifndef __CAviVideoDecoder__
#define __CAviVideoDecoder__

extern "C"
{
	struct image_type;
	struct palette_type;
}
#include	<windows.h>
#include	<vfw.h>

#include "VideoCodec/VideoDecoder.h"
//#include "AviUtil/AviInclude.h"



class CAviVideoDecoder: public CVideoDecoder
{
public:
	CAviVideoDecoder();
	~CAviVideoDecoder();
	
	int GetMIMEType( char *mime, int mimeLen );
	int GetExtension( char *extension, int extensionLen );

	virtual int	ReadFrame( int frame, image_type **im );

	virtual int Open( char *data, int bytes );

	virtual int Open(const char *filename );

	virtual int ReOpen();

	virtual int Close();

	int GetCodecName( char *codec, int codecLen );


	int OpenFfmpeg( char*data, int bytes, char *extension );

	int OpenFfmpeg( char *inFile );
	
protected:
	bool CheckMJPEG();
	image_type *MJPEG_Frame(int frame);

	void SetCodecName();

private:	
	PAVISTREAM  m_pStream;
	PGETFRAME	m_aviFrame;
	
	//CVideoDecoder *mjpegDecoder;
	int m_codec;// if mjpeg, use other technique
	LONG m_lLength;
	LPBYTE m_jpgBuf;


	char	m_codecName[5];

	
};

#endif //__CAviVideoDecoder__


#endif //defined WIN32 || defined _WINDOWS 
