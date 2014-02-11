#ifndef _EMS_DECODER_H_
#define _EMS_DECODER_H_

#include "Codecs/ImageDecoder.h"



class CEmsDecoder :public CImageDecoder
{
public:
	CEmsDecoder();
	virtual ~CEmsDecoder();
	
//	virtual int GetMIMEType( char *mime, int mimeLen );
//	virtual int GetExtension( char *extension, int extensionLen );
		

	virtual int Decode(const char *filename, image_type **im);
	virtual int Decode(char *data, int bytes, image_type **im );
};


#endif //__BMP_CODEC_H__
