/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#if	defined WIN32 || defined _WINDOWS 

#ifndef __AVI_GET_DECODER__
#define __AVI_GET_DECODER__


#ifdef _DEBUG 
#pragma comment( lib, "AviD.lib" )
#pragma comment( lib, "VideoCodecD.lib" )
#else
#pragma comment( lib, "Avi.lib" )
#pragma comment( lib, "VideoCodec.lib" )
#endif
#pragma comment( lib, "vfw32.lib" )


class CVideoDecoder;


CVideoDecoder *GetAviDecoder();

#endif//__AVI_GET_DECODER__
#endif //WIN32 || _WINDOWS 