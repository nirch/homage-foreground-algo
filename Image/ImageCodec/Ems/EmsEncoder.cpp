#include "EmsEncoder.h"


extern "C"
{
#include "ImageType/ImageType.h"
#include "ImageType/PaletteType.h"
#include "Uigp/igp.h"
#include "Ugio/GioType.h"

#include "ImageEms.h"
}


CEMSEncoder::CEMSEncoder():CImageEncoder()
{
}

CEMSEncoder::~CEMSEncoder()
{
}




/*********  CEMSDecoder::Encode  **********
* @Description	:  Encodes an image to the specific path
* 
* @Param  struct image_type *im :  image to write
* @Param  const char *path :  path to write to
* @Param  int quality:  ignored 
* @Return  int  :  number of bytes written
*****************************************/
int CEMSEncoder::Encode(struct image_type *im,const char *path) 
{	
	m_dataSize = 0;
	char dir[256],name[256],ext[256];
	gp_filename_split((char*)path, dir,name,ext);
	int retCode = image_write_ems(im,dir,name,1,1);
	if ( retCode > 0 )
	{
		m_iErrCode = 0;
		m_dataSize = retCode;
		return 1;

	}
	switch ( retCode )
	{	
	case -1 : 
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



/*********  CEMSEncoder::Encode  **********
* @Description	: writes the image into the buffer
* 
* @Param  struct image_type* im :  image to write
* @Param  unsigned char**pTargetBuffer :  pointer to a buffer to allocate
* @Param  int quality :  ignored
* @Return  int  :  actual length of the buffer (positive num)
					or m_iErrCode (negative value) 
*****************************************/
int CEMSEncoder::Encode(struct image_type* im,unsigned char**pTargetBuffer) 
{
image_type *sim;

	*pTargetBuffer = NULL;

	
	sim = image_extend( im, 32, 32, 0xffffff, NULL );
	cst_type *cst = image_write_ems_cst( sim, 1, 1);
	image_destroy( sim, 1 );
	
	if ( cst == NULL ) 
	{
		m_dataSize = 0;
		m_iErrCode = IMAGE_CODEC_ERROR_WHILE_WRITING_OUT;
		return m_iErrCode;
	}
	
	*pTargetBuffer = cst->data;
	m_dataSize = CST_BYTES(cst);
	cst_destroy(cst, 0);
	m_iErrCode = 0;
	return m_dataSize;
}





bool CEMSEncoder::CanEncode(const char *filename)
{ 
	return true;
}

bool CEMSEncoder::CanEncode(char* data, int bytes, int bCopyData)
{
	return true;
}





