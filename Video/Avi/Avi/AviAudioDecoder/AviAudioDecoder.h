#ifndef _AVI_AUDIO_DECODER_H_
#define _AVI_AUDIO_DECODER_H_



#define AUDIO_ERROR_INTERNAL_ERROR				 (-100)
#define AUDIO_ERROR_COULD_NOT_OPEN_STREAM		 (-101)
#define AUDIO_ERROR_CORRUPTED_STREAM			(-102)

#include	"AudioLib/AudioCoder/AudioDecoder.h"


#include	<vfw.h>


extern "C"
{
#include	"AudioLib/Audio/AudioType.h"
}



class CAviAudioDecoder: public CAudioDecoder
{
public:
	CAviAudioDecoder();
	virtual ~CAviAudioDecoder();	


	int Open( char *data, int bytes );

	int Open(const char *filename );

	int ReOpen();

	int Close();


	int	ReadFrame( char **data, int *bytes, int max_bytes  );

	int IsMimeSupport( char *mime );


	int GetMIMEType( char *mime, int mimeLen );
	int GetExtension( char *extension, int extensionLen );
	int ReadEncodedFrame( u_char *data, int maxBytes )	{ return -1; }



public:
private:

	int OpenMp3( int formatTag );
	int ExtractAudio( char *extension, char *file );

protected:

	PAVISTREAM     m_pStream;

	int		m_Pos;

	int		m_sec1bytes;

	char	*m_data;	// use by read_frame

	int     m_dataSize;

	char	*m_tempFile;

	char	*m_audioTrackFile;

	CAudioDecoder	*m_aDecoder;
};

#endif