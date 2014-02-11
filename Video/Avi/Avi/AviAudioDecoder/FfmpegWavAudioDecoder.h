#ifndef __FFMPEG_WAV_AUDIODECODER_H__
#define __FFMPEG_WAV_AUDIODECODER_H__

#include "AudioLib\AudioCoder\AudioDecoder.h"
#include "AudioLib\WavAudioCoder/WavAudioDecoder.h"

class CFfmpegWavAudioDecoder : public CWavAudioDecoder
{
public:

	CFfmpegWavAudioDecoder();

	virtual ~CFfmpegWavAudioDecoder();

	int OpenFfmpeg( char*data, int bytes, char *extension );

	int OpenFfmpeg( char *inFile );

protected:



protected:

	char *m_tempFile;



};



#endif //__WAV_AUDIODECODER_H__