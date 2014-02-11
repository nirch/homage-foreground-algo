#ifndef _WBMAP_DECODER_H_
#define _WBMAP_DECODER_H_

#include "Codecs/ImageDecoder.h"



class CWbmapDecoder :public CImageDecoder
{
public:
	CWbmapDecoder();
	virtual ~CWbmapDecoder();
	
//	virtual int GetMIMEType( char *mime, int mimeLen );
//	virtual int GetExtension( char *extension, int extensionLen );
		

	virtual int Decode(const char *filename, image_type **im);
	virtual int Decode(char *data, int bytes, image_type **im );
};


#endif
