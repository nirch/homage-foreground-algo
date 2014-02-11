/**************************
 *** VideoEncoder.cpp   ***
 **************************/
#include	<stdio.h>
#include	<malloc.h>
#include	<string.h>

#include "Uigp/igp.h"

#include "VideoEncoder.h"



CVideoEncoder::CVideoEncoder()
{
	m_VideoStream = NULL;
	m_AudioStream = NULL;

	m_sizeLimit = 0;
	m_optimal = 0;
	m_duration = 0;

	m_sFilename = NULL;

	m_vimatixData = NULL;


}

CVideoEncoder::~CVideoEncoder()
{

	if (m_AudioStream != 0) {
		delete m_AudioStream;
		m_AudioStream = 0;
	}


	if (m_VideoStream != 0) {

		delete m_VideoStream;
		m_VideoStream = 0;
	}


	if( m_vimatixData != NULL ){
		free( m_vimatixData );
		m_vimatixData = NULL;
	}
}


void CVideoEncoder::SetVimatixData( char *data )
{
	if( data == NULL || data[0] == 0 )	return;

	if( m_vimatixData != NULL )
		free( m_vimatixData );

	m_vimatixData = strdup( data );
}




int CVideoEncoder::CloseAllStreams()
{
int	size;

	size = 0;


	if (m_AudioStream != 0) {
		m_AudioStream->Close();
		size += m_AudioStream->m_size;
//		delete m_AudioStream;
//		m_AudioStream = 0;
	}

  

	if (m_VideoStream != 0) {

		if( m_sizeLimit > 0 ){
			m_VideoStream->SetSizeLimit( m_sizeLimit - size - 1000 );
			m_VideoStream->SetOptimal( m_optimal );
		}

		m_VideoStream->Close();
		size += m_VideoStream->m_size;

		m_duration = m_VideoStream->GetDuration();

//		delete m_VideoStream;
//		m_VideoStream = 0;
	}


	return 1;
}



