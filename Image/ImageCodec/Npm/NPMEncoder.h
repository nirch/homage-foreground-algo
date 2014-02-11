#ifndef __NPM_CODEC_H__
#define __NPM_CODEC_H__
#include "Codecs/ImageCodec.h"



struct image_type;
struct palette_type;







class CNPMEncoder :public CImageEncoder
{
public:
	CNPMEncoder ();
	virtual ~CNPMEncoder ();

	virtual bool CanEncode(const char *filename);
	virtual bool CanEncode(char* data, int bytes, int bCopyData);

	virtual int Encode(struct image_type *im,const char *path) ;
	virtual int Encode(struct image_type* im,unsigned char**pTargetBuffer) ;
};


#endif //__NPM_CODEC_H__
