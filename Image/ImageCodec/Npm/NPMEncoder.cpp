#include "NPMEncoder.h"


extern "C"
{
#include "ImageType/ImageType.h"
#include "ImageType/PaletteType.h"
#include "Uigp/igp.h"
#include "Ugio/GioType.h"

#include "ImageNpm.h"
}


CNPMEncoder::CNPMEncoder():CImageEncoder()
{
}

CNPMEncoder::~CNPMEncoder()
{
}

/*********  CNPMCodec::Encode  **********
* @Description	:  Encodes an image to the specific path
* 
* @Param  struct image_type *im :  image to write
* @Param  const char *path :  path to write to
* @Param  int quality:  ignored 
* @Return  int  :  number of bytes written
*****************************************/
int CNPMEncoder::Encode(struct image_type *im,const char *path) 
{	
	char dir[256],name[256],ext[256];
	gp_filename_split((char*)path, dir,name,ext);
	int ret = image_write_npm(im,dir,name) == 0 ;
	if ( ret > 0 )
	{
		m_dataSize = ret;
		m_iErrCode = 0;
		return 1;
	}
	m_dataSize = 0;
	switch (ret)
	{ 	
	case -1:
		m_iErrCode = IMAGE_CODEC_COULD_NOT_OPEN_STREAM;
		return m_iErrCode;
	case -2:
		m_iErrCode = IMAGE_CODEC_ERROR_WHILE_WRITING_OUT;
		return m_iErrCode;
	default:
		m_iErrCode = IMAGE_CODEC_INTERNAL_ERROR;
		return m_iErrCode;
	}
	 
}



/*********  CNPMCodec::Encode  **********
* @Description	: writes the image into the buffer
* 
* @Param  struct image_type* im :  image to write
* @Param  unsigned char**pTargetBuffer :  pointer to a buffer to allocate
* @Param  int quality :  ignored
* @Return  int  :  actual length of the buffer
*****************************************/
int CNPMEncoder::Encode(struct image_type* im,unsigned char**pTargetBuffer) 
{
	*pTargetBuffer = NULL;
	cst_type *cst = image_write_npm_cst( im);

	if ( cst == NULL ) 
	{
		m_iErrCode = IMAGE_CODEC_ERROR_WHILE_WRITING_OUT;
		m_dataSize = 0;
		return m_iErrCode;
	}
	
	
	*pTargetBuffer = cst->data;
	m_dataSize = CST_BYTES(cst);
	cst_destroy(cst, 0);
	m_iErrCode = 0;
	return m_dataSize ;
}




bool CNPMEncoder::CanEncode(const char *filename)
{ 
	return true;
}

bool CNPMEncoder::CanEncode(char* data, int bytes, int bCopyData)
{
	return true;
}





