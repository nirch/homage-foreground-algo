/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#ifndef __AVI_VIDEO_ENCODER__H_
#define __AVI_VIDEO_ENCODER__H_
#include	<windows.h>
#include	<vfw.h>

extern "C"
{
#include "Uigp/igp.h"
}



#include "VideoEncoder.h"
#include "AviVideoStreamEncoder.h"
#include "AviAudioStreamEncoder.h"

const char *TranslateAVIERR_to_string(HRESULT avierr_code);



//#define  FOURCC_from_codecType(a, b, c, d) mmioFOURCC('a', 'b', 'c', 'd')





int FOURCC_from_codecType(int codecType);



class CAviVideoEncoder: public CVideoEncoder
{
	
public:
	CAviVideoEncoder();
	virtual ~CAviVideoEncoder();
	
	int GetMIMEType( char *mime, int mimeLen );
	int GetExtension( char *extension, int extensionLen );

	virtual int Open() ;
	virtual int Open(const char *filename ) ;	
	virtual int Close() ;

	int	GetData( char **data, int *bytes, int DetauchData );

	virtual int CloseAllStreams();

	virtual CVideoStreamEncoder *CreateVideoStream(int codec, int frameRate, int width, int height, int quality) ;

	virtual CAudioStreamEncoder *CreateAudioStream( int sampleRate,
				int bitRate,int bitPerSample, int codecType, int channels) ;

protected:

private:
	PAVIFILE m_afFile;
	AVIFILEINFO m_fiInfo;


};//CVideoEncoder



#endif //__AVI_VIDEO_ENCODER__H_