#ifndef __VIDEO_STREAM_ENCODER__H_
#define __VIDEO_STREAM_ENCODER__H_

extern "C"
{
	struct image_type;
}


class CVideoStreamEncoder
{
public:

	CVideoStreamEncoder();
	CVideoStreamEncoder(int codec, float frameRate, int width, int height, int bitrate);
	virtual ~CVideoStreamEncoder();

	virtual int Open() ;
	virtual int Close();

	virtual void SetFrameRate(int frameRate)	{ m_frameRate = (float)frameRate; }

	virtual int WriteFrame(image_type *im, int SetKeyFrame) = 0;	



	float GetFrameRate()	{ return m_frameRate; }

	int GetWidth()	{ return m_width; }
	int GetHeight()	{ return m_height; }
	int GetFramesNo() { return m_numberOfFrames; }

	int GetBitRate() { return m_bitRate; }

	int GetDuration() { return( (int)((m_numberOfFrames / m_frameRate) * 1000) ); }

	void	SetSizeLimit( int sizeLimit )	{ m_sizeLimit = sizeLimit; }
	void	SetOptimal( int optimal )		{ m_optimal = optimal; }

protected:


public:

	

	int m_codec;
	int m_width;
	int m_height;
	float m_frameRate;

	int	m_bitRate;
//	int m_quality;

	int	m_size;
	int	m_sizeLimit;
	int m_optimal;


	int m_numberOfFrames;


};//CVideoStreamEncoder




#endif //__VIDEO_STREAM_ENCODER__H_
