#ifndef __WBMP_ENCODER_H__
#define __WBMP_ENCODER_H__
#include "Codecs/ImageCodec.h"



struct image_type;
struct palette_type;





class CWBMPEncoder :public CImageEncoder
{
public:
	CWBMPEncoder();
	virtual ~CWBMPEncoder();

	void SetParams( int *bitsPerPixel, int *colorSpace, int quality );

	virtual bool CanEncode(const char *filename);
	virtual bool CanEncode(char* data, int bytes, int bCopyData);

	virtual int Encode(struct image_type *im,const char *path) ;
	virtual int Encode(struct image_type* im,unsigned char**pTargetBuffer) ;


};


#endif //__WBMP_CODEC_H__
