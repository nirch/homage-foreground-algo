/*****************************
 ***   AviAudioStram.cpp   ***
 *****************************/

#include	"Uigp/igp.h"

#include "AviAudioStreamEncoder.h"


#include "AudioLib/Audio/AudioType.h"



CAviAudioStreamEncoder::CAviAudioStreamEncoder(int SampleRate, int BitRate,
							int BitPerSample, int Channels, int codec )
{
	m_sampleRate = SampleRate;
	m_bitrate = BitRate;
	m_bitsPerSample  = BitPerSample;
	m_codec = codec;
	m_channels = Channels;
//	m_quality = quality;

//	if( m_quality == 0 )
//		m_quality = 75;

	if( m_bitrate < 0 || m_bitrate > 10000 )
		m_bitrate = -1;


	m_samples = 0;

	m_size = 0;

	
}


CAviAudioStreamEncoder::CAviAudioStreamEncoder(PAVISTREAM stream, int SampleRate, int BitRate, int BitPerSample, int Channels, int codecType ) : 
	CAudioStreamEncoder(SampleRate, BitRate, BitPerSample, Channels, codecType )
{

	m_samples = 0;

	m_size = 0;

	m_psStream = NULL;





	m_psStream = stream;

	m_sampleRate = SampleRate;
	m_bitrate = BitRate;
	m_bitsPerSample  = BitPerSample;
	m_codec = codecType;
	m_channels = Channels;
}


CAviAudioStreamEncoder::~CAviAudioStreamEncoder()
{

	Close();
}




int CAviAudioStreamEncoder::Create( PAVIFILE m_afFile )
{

AVISTREAMINFO    strhdr;
	

	memset(&strhdr,0,sizeof(AVISTREAMINFO));
//	strhdr.dwQuality = m_quality * 100;
	strhdr.dwQuality = m_bitrate;
	strhdr.dwSuggestedBufferSize  = 0;
	strhdr.dwRate = m_sampleRate;
	strhdr.dwScale = 1;
	strhdr.fccHandler = 0;
	strhdr.fccType = streamtypeAUDIO;
	strhdr.dwSampleSize  = m_bitsPerSample/8;

	HRESULT hr = AVIFileCreateStream(m_afFile, &m_psStream, &strhdr); 
    if (hr != AVIERR_OK) 
		return -1; 
 

	return( 1 );
}


	
int CAviAudioStreamEncoder::Open()
{
	
	HRESULT hr 	;
	PCMWAVEFORMAT fmtWav;
	fmtWav.wBitsPerSample = m_bitsPerSample;
	fmtWav.wf.nChannels = m_channels;
	fmtWav.wf.nSamplesPerSec = m_sampleRate;
	fmtWav.wf.wFormatTag = WAVE_FORMAT_PCM;

	fmtWav.wf.nBlockAlign = (m_bitsPerSample/8) * m_channels;

	fmtWav.wf.nAvgBytesPerSec = (int)m_sampleRate * fmtWav.wf.nBlockAlign;
	

	AVISTREAMINFO siAudio;
	hr = AVIStreamInfo(m_psStream, &siAudio, sizeof(AVISTREAMINFO));
	if(hr != AVIERR_OK)
	{
#ifdef _DEBUG	
		printf("%s\n",TranslateAVIERR_to_string(hr));
#endif
		return -1;
	}


	hr = AVIStreamSetFormat(m_psStream, 0, &fmtWav, sizeof(fmtWav));
	if ( AVIERR_OK != hr)
	{
#ifdef _DEBUG
		printf("%s\n",TranslateAVIERR_to_string(hr));
#endif
		return -1;
	}

	return 1;
}


int CAviAudioStreamEncoder::Close()
{


	if ( m_psStream )
	{
		HRESULT hr = AVIStreamRelease( m_psStream );
#ifdef _DEBUG
		if( AVIERR_OK != hr )
		printf("%s\n",TranslateAVIERR_to_string(hr));
#endif

	}

	m_psStream = NULL;

	return 1;
}






int CAviAudioStreamEncoder::Write(audio_type *ad) 
{
	HRESULT hr ;


	if ( (NULL == m_psStream))		
		return -1;

	long samplesWritten = 0;
	long bytesWritten = 0;
	
	AVISTREAMINFO siAudio;
	
	hr = AVIStreamWrite(m_psStream, m_samples, ad->samples, ad->data, ad->depth * ad->samples, AVIIF_KEYFRAME, &samplesWritten, &bytesWritten);
    if(hr != AVIERR_OK)
	{
#ifdef _DEBUG	
		printf("%s\n",TranslateAVIERR_to_string(hr));
#endif
		return -1;
	}
	hr = AVIStreamInfo(m_psStream, &siAudio, sizeof(AVISTREAMINFO));
	if(hr != AVIERR_OK)
	{
#ifdef _DEBUG	
		printf("%s\n",TranslateAVIERR_to_string(hr));
#endif
		return -1;
	}

	m_samples += ad->samples;//samplesWritten;
	m_size += bytesWritten;

	return 1;
	
}


