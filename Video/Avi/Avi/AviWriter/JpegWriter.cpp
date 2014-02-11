
#include	<string.h>
#include	"Uigp/igp.h"




#include "Jpeg/JpegCodec/ImageWriteJpeg.h"


#include "ImageType/ImageType.h"


#include "JpegWriter.h"




CJepgWriter::CJepgWriter( int synchron )
{

	
	m_nIm = 0;
	m_iIm = 0;
	for (int i = 0; i < MAX_IM ; i++ )
		m_aIm[i] = NULL;


	m_synchron = synchron;


}

CJepgWriter::~CJepgWriter( void )
{



	for( int i = 0 ; i < m_nIm; i++ ){
		image_destroy(m_aIm[i], 1);
	}

}

int CJepgWriter::Open( int width, int height, int frameRate, int quality, char *outDir )
{
	strcpy( m_dir, outDir );
	

	gpDir_force_exist( m_dir );


	if( frameRate <= 0 )	frameRate = 10;


	m_quality = quality;
	m_iFrame = 0;



	char  file[256];
	sprintf( file, "%s/time.log", m_dir );
	m_fp = fopen( file, "wb" );
	m_time0 = vTime();

	

	if( m_synchron == AW_ASYNCHRONY_THREAD ){
		m_semIn.Create( NULL, 0, MAX_IM, NULL);
		m_semOut.Create( NULL, 0, MAX_IM, NULL);
		StartThread();
	}

	return 1;
}

int CJepgWriter::WriteFrame( image_type *im )
{
	if( m_synchron == AW_SYNCHRONY ){
		char	file[256];
		sprintf( file, "%s/im-%.4d.jpg", m_dir, m_iFrame++ );

		if( m_fp != NULL ){
			int dt = im->timeStamp - m_time0;
			fprintf( m_fp, "%d    %d\n", m_iFrame, dt );
		}

		image_write_jpeg( im, m_quality, file );
		return( 1 );
	}


	if( m_nIm >= MAX_IM )
		return( -1 );
	m_aIm[m_nIm++] = image_copyN( im, NULL );

	if( m_synchron == AW_ASYNCHRONY_THREAD )
		m_semIn.Release( 1 );

	return 1;
}

int CJepgWriter::Close()
{
int	i;
	if( m_synchron == AW_ASYNCHRONY ){
		for( int i = 0; i < m_nIm; i++ ){
			char	file[256];
			sprintf( file, "%s/im-%.4d.jpg", m_dir, m_iFrame++ );
			image_write_jpeg( m_aIm[i], m_quality, file );

			if( m_fp != NULL ){
				int dt = m_aIm[i]->timeStamp - m_time0;
				fprintf( m_fp, "%d    %d\n", m_iFrame, dt );
			}

			image_destroy( m_aIm[i], 1 );
			m_aIm[i] = NULL;
		}
	}
	else {
		if( m_synchron == AW_ASYNCHRONY_THREAD ){
			for( i = 0 ; i < m_nIm ; i++ )
				m_semOut.WaitForSingleObject();
		}
	}


	if( m_fp != NULL )
		fclose( m_fp );


	return 1;
}

//void CJepgWriter::SetSynchrony( int flag ) 
//{ 
//	m_synchron = flag; 
//}


	


void CJepgWriter::Run()
{

	while( 1 ) {
		m_semIn.WaitForSingleObject();

	
		char	file[256];
		sprintf( file, "%s/im-%.4d.jpg", m_dir, m_iFrame++ );
		image_write_jpeg( m_aIm[m_iIm], m_quality, file );

		if( m_fp != NULL ){
			vTime_type dt = m_aIm[m_iIm]->timeStamp - m_time0;
			fprintf( m_fp, "%d    %d\n", m_iFrame, (int)dt );
		}

		image_destroy( m_aIm[m_iIm], 1 );
		m_aIm[m_iIm] = NULL;

		m_iIm++;

		m_semOut.Release( 1 );
	}
}



	


int CJepgWriter::Write( imageA_type *aim, int frameRate, int quality, char *dir )
{




	if( frameRate <= 0 )	frameRate = 10;




	int	iFrame = 0;

	for( int i = 0 ; i < aim->nA ; i++ ){
		if( aim->a[i] != NULL ){
			char	file[256];
			sprintf( file, "%s/im-%.4d.jpg", dir, iFrame++ );
			image_write_jpeg( aim->a[i], quality, file );
		}

	}




	return 1;
}