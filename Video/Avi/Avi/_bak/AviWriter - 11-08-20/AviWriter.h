
#ifndef __AVI_WRITER__H_
#define __AVI_WRITER__H_

#include "../AviEncoder/AviCodec.h"



#ifdef _DEBUG 
#pragma comment( lib, "AviD.lib" )
#pragma comment( lib, "VideoCodecD.lib" )
#else
#pragma comment( lib, "Avi.lib" )
#pragma comment( lib, "VideoCodec.lib" )
#endif


#define		MAX_IM		500


class CAviWriter
{
private:
	class CVideoEncoder *m_videoEncoder;

	class CVideoStreamEncoder *m_videoStream;

	int m_synchrony;

	int		m_nIm;
	image_type *m_aIm[MAX_IM];

	int m_index;

public:
	CAviWriter(void);
	~CAviWriter(void);

	int Open ( int width, int height, int frameRate, int codec, char *outFile );
	int WriteFrame( image_type *im );
	int Close();
	void  SetSynchrony( int flag );
};

#endif __AVI_WRITER__H_