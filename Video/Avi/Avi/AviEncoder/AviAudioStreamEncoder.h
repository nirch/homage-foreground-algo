#ifndef __AVI_AUDIO_STREAM_ENCODER__H_
#define __AVI_AUDIO_STREAM_ENCODER__H_
#include "windows.h"
#include "vfw.h"

extern "C"
{
	struct audio_type;
}
#include "AudioStreamEncoder.h"


const char *TranslateAVIERR_to_string(HRESULT avierr_code);
int FOURCC_from_codecType(int codecType);


class CAviAudioStreamEncoder : public CAudioStreamEncoder
{
public:
	CAviAudioStreamEncoder( int SampleRate, int BitRate, int BitPerSample,
								int Channels, int codec );

	CAviAudioStreamEncoder(PAVISTREAM stream, int SampleRate, int BitRate, int BitPerSample, int Channels, int codecType );
	~CAviAudioStreamEncoder();	

	int Create( PAVIFILE m_afFile );

	virtual int Open();
	virtual int Close();	
//	virtual void SetSampleRate( int rate) ;
//	virtual void SetBitRate(int rate) ;
//	virtual void SetBitPerSample(int bps) ;

	virtual int Write(struct audio_type *ad) ;

protected:

	
protected:
    PAVISTREAM m_psStream;
	

	
};



#endif 