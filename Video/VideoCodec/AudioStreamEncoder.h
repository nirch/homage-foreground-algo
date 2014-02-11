#ifndef __AUDIO_STREAM_ENCODER__H_
#define __AUDIO_STREAM_ENCODER__H_

extern "C"
{
	struct audio_type;
}


class CAudioStreamEncoder
{
public:
	CAudioStreamEncoder();
	CAudioStreamEncoder( int SampleRate, int BitRate, int BitPerSample,
									int Channels, int codec );

	virtual ~CAudioStreamEncoder();	

	


	virtual void SetSampleRate( int sampleRate ) { m_sampleRate = sampleRate; }
	virtual void SetBitRate(int bitrate )		{ m_bitrate = bitrate; }
	virtual void SetBitPerSample( int bitsPerSample )	{ m_bitsPerSample = bitsPerSample; }
	virtual void SetChannels( int channels )		{ m_channels = channels; }

	void	SetSizeLimit( int sizeLimit )	{ m_sizeLimit = sizeLimit; }


	virtual int Open();

	virtual int Write( struct audio_type *ad) = 0;

	virtual int Close();



	int GetSampleRate()		{ return m_sampleRate; }
	int GetBitPerSample()	{ return m_bitsPerSample; }
	int GetChannels()		{ return m_channels; }


	int GetSamples()		{ return m_samples; }


protected:

public:



	int m_codec;

	int	m_channels;			/* mono == 1, stereo = 2, etc */

	int	m_bitsPerSample;	/* int each channels: 8 bit, 16 bite, etc */

	int	m_sampleRate;		/* KHZ = sample per second */

	int m_bitrate;

	int	m_sizeLimit;


	int	m_samples;			// samples wirten
	int m_size;				// byte wirten

	struct audio_type *m_ad;
};



#endif //__VISUAL_STREAM_ENCODER__H_
