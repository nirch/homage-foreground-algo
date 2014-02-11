#ifndef __VIDEO_ENCODER__H_
#define __VIDEO_ENCODER__H_


#if defined _DEBUG || defined DEBUG
#pragma comment( lib, "VideoCodecD.lib" )
#else
#pragma comment( lib, "VideoCodec.lib" )
#endif



#include "VideoStreamEncoder.h"
#include "AudioStreamEncoder.h"




#define	AUDIO_CODEC( codec )	( codec & 0x0f )
#define	VIDEO_CODEC( codec )	( (codec>>4) & 0x0f )



class CVideoEncoder
{
public:

	CVideoEncoder();
	virtual ~CVideoEncoder();

	virtual int GetMIMEType( char *mime, int mimeLen ) = 0;
	virtual int GetExtension( char *extension, int extensionLen ) = 0;

	virtual int Open() = 0;
	virtual int Open(const char *filename ) = 0;
	virtual int Close() = 0;

	virtual int	GetData( char **data, int *bytes, int DetauchData )=0;


	virtual int CloseAllStreams();


	void	SetSizeLimit( int sizeLimit )	{ m_sizeLimit = sizeLimit; }
	void	SetOptimal( int optimal )	{ m_optimal = optimal; }



	virtual CVideoStreamEncoder *CreateVideoStream(int frameRate, int width, int height,
										int codec, int bitrate ) = 0;

	virtual CAudioStreamEncoder *CreateAudioStream(int sampleRate, int bitRate,
										int bitPerSample, int codecType,
										int channels ) = 0;


	int	GetDuration()	{ return( m_duration ); }

	virtual void SetVimatixData( char *data );

protected:

	int	m_sizeLimit;
	int	m_optimal;
	int	m_duration;

	char *m_sFilename;

	char	*m_vimatixData;



	CVideoStreamEncoder *m_VideoStream;
	CAudioStreamEncoder *m_AudioStream;

};



#endif
