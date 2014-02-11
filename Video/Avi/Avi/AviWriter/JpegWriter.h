/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#ifndef __JPEG_WRITER__H_
#define __JPEG_WRITER__H_

#include "../AviCodec.h"

#include "UThread/VThread.h"
#include "Uthread/VSemaphore.h"



#ifdef _DEBUG 
#pragma comment( lib, "AviD.lib" )
#pragma comment( lib, "VideoCodecD.lib" )
#else
#pragma comment( lib, "Avi.lib" )
#pragma comment( lib, "VideoCodec.lib" )
#endif


#define		MAX_IM		5000

#define		AW_SYNCHRONY	0
#define		AW_ASYNCHRONY   1
#define		AW_ASYNCHRONY_THREAD   2





class CJepgWriter :public CVThread
{
private:




public:
	CJepgWriter( int synchrony = AW_ASYNCHRONY_THREAD );
	~CJepgWriter(void);

	int Open ( int width, int height, int frameRate, int quality, char *outFile );

	int WriteFrame( image_type *im );
	int Close();
//	void  SetSynchrony( int flag );


	static int Write( imageA_type *aim, int frameRate, int quality, char *outFile );


private:
	void		Run();


private:
	char	m_dir[256];
	int		m_quality;
	int		m_iFrame;

	int m_synchron;

	int		m_nIm;
	int		m_iIm;
	image_type *m_aIm[MAX_IM];

	int m_index;

	FILE *m_fp;
	vTime_type	m_time0;


	CVSemaphore m_semIn;
	CVSemaphore m_semOut;
};

#endif __JPEG_WRITER__H_