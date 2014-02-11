#include "AudioStreamEncoder.h"

extern "C" {
#include	"Audio/AudioType.h"
}

	int m_codec;


CAudioStreamEncoder::CAudioStreamEncoder()
{
	m_samples = 0;
	m_size = 0;
	m_ad = NULL;

	m_codec = 0;
	m_sampleRate = 0;
	m_bitsPerSample = 0;
	m_channels = 0;
	m_bitrate = 0;
}



CAudioStreamEncoder::CAudioStreamEncoder( int SampleRate, int BitRate, int BitPerSample,
										 int Channels, int codec )
{
	m_samples = 0;

	m_size = 0;


	m_ad = NULL;



	m_codec = codec;

	m_sampleRate = SampleRate;

	m_bitsPerSample = BitPerSample;

	m_channels = Channels;
	m_bitrate = BitRate;
}

CAudioStreamEncoder::~CAudioStreamEncoder()
{

	Close();

	if( m_ad != NULL )
		audio_destroy(m_ad, 1);
}

	
int CAudioStreamEncoder::Open()
{
	return 1;
}

int CAudioStreamEncoder::Close()
{
	return 1;
}

