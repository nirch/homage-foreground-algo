/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/

#ifndef __AVI_GET_ENCODER__
#define __AVI_GET_ENCODER__



#ifdef _DEBUG 
#pragma comment( lib, "AviD.lib" )
#pragma comment( lib, "VideoCodecD.lib" )
#else
#pragma comment( lib, "Avi.lib" )
#pragma comment( lib, "VideoCodec.lib" )
#endif
#pragma comment( lib, "vfw32.lib" )

#include "../AviCodec.h"

//#define AVI_CODEC_UNKNOEN 0
//#define AVI_CODEC_RAW  1
//#define AVI_CODEC_IV32 2		// Intel - Indeo Video 3 codec
//#define AVI_CODEC_IV50 3		// Intel - Indeo 5.0
//#define AVI_CODEC_INDEO50 3
//#define AVI_CODEC_MSVC 4
//#define AVI_CODEC_MP42 5
//#define AVI_CODEC_CVID 6
//#define AVI_CODEC_MJPG 7


class CVideoEncoder;


CVideoEncoder *GetAviEncoder();

#endif//__AVI_GET_DECODER__
