

#ifndef __VIM_GET_VIDEO_DECODER__
#define __VIM_GET_VIDEO_DECODER__

#if defined _DEBUG || defined DEBUG
#pragma comment( lib, "ImageVideoCodecD.lib" )
#else
#pragma comment( lib, "ImageVideoCodec.lib" )
#endif


class CVideoDecoder;


CVideoDecoder *GetImageVideoDecoder();

#endif
