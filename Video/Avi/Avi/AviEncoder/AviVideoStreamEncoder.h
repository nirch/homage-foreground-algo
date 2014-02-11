#ifndef __AVI_VIDEO_STREAM_ENCODER__H_
#define __AVI_VIDEO_STREAM_ENCODER__H_

#include "VideoStreamEncoder.h"

#include "AviUtil/AviInclude.h"

extern "C"
{
	struct image_type;
}

class CDib;


const char *TranslateAVIERR_to_string(HRESULT avierr_code);
int FOURCC_from_codecType(int codecType);


class CAviVideoStreamEncoder : public CVideoStreamEncoder
{
public:
	CAviVideoStreamEncoder(int codec, float frameRate,
									int width, int height, int quality );

	virtual ~CAviVideoStreamEncoder();


	int Create( PAVIFILE m_afFile );

	virtual int Open() ;
	virtual int Close() ;	

	virtual int WriteFrame(image_type *frame, int SetKeyFrame) ;	
	

protected:	
	void CreateDib(int row,int col, int bits);
	PAVISTREAM m_psStream;
	PAVISTREAM m_psCompressed ;
	PAVISTREAM m_psCurrent;
	CDib *m_pDib;


	int	m_quality;

};




#endif //__AVI_VIDEO_STREAM_ENCODER__H_