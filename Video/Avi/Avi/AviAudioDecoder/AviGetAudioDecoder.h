#if	defined WIN32 || defined _WINDOWS 

#ifndef __AVI_AUDIO_GET_DECODER__
#define __AVI_AUDIO_GET_DECODER__


#ifdef _DEBUG 
#pragma comment( lib, "AviD.lib" )
#else
#pragma comment( lib, "Avi.lib" )
#endif
#pragma comment( lib, "vfw32.lib" )

class CAudioDecoder;


CAudioDecoder *GetAviAudioDecoder();

#endif//__AVI_AUDIO_GET_DECODER__
#endif //WIN32 || _WINDOWS 