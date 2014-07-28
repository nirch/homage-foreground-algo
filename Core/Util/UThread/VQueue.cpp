
#include	<string.h>
#include	"Uigp/igp.h"

#include "VQueue.h"



CVQueue::CVQueue( int no )
{
	m_aq = (qData_type **)malloc( no * sizeof(qData_type) );
	m_NQ = no;

	m_nQ = 0;

	m_semIn.Create( NULL, 0, 1, NULL);

	m_semIn.Release( 1 );
}


CVQueue::~CVQueue( void )
{

}

int CVQueue::Add( void *data[], int nData )
{
int	i;
	m_semIn.WaitForSingleObject();

	for( i = 0 ; i < nData && m_nQ < m_NQ ; i++ ){

	//	m_aq[m_nQ++] = CopyData( (qData_type *)data[i] );

		m_aq[m_nQ++] =(qData_type *)data[i];
	}

	m_semIn.Release( 1 );

	return 1;
}

int CVQueue::Add( void *data )
{

	m_semIn.WaitForSingleObject();

	
	m_aq[m_nQ++] = CopyData( (qData_type *)data );


	m_semIn.Release( 1 );

	return 1;
}

int CVQueue::Get( void *data[], int *nData )
{
	int	i;
	m_semIn.WaitForSingleObject();

	for( i = 0 ; i < m_nQ  ; i++ ){

		data[i] = m_aq[i];
	}

	*nData = m_nQ;

	m_nQ = 0;
	m_semIn.Release( 1 );

	Spy( data, *nData );

	return 1;
}


int CVQueue::SetIn()
{

	m_semIn.Release( 1 );

	return 1;
}


qData_type* CVQueue::CopyData( qData_type *d )
{
	void *c = malloc( d->dataSize );
	memcpy( c, d,  d->dataSize );

	return( (qData_type *)c );
}


int CVQueue::Init( char *dir, char *prefix, int spy )
{
	strcpy( m_dir, dir );

	strcpy( m_prefix, prefix );

	m_spy = spy;

	return( 1 );

}

int CVQueue::Init( char *dir, int id, int spy )
{
	strcpy( m_dir, dir );

	
	sprintf( m_prefix, "q%d", id );

	m_spy = spy;

	return( 1 );

}

int CVQueue::Spy( void *data[], int nData )
{
	char file[256];

	if( m_spy == 0 )	return( -1 );


	char	buf[256];
	gpTime_string( buf, 0, 2 );


	sprintf( file, "%s/%s-%s.log", m_dir, m_prefix, buf );

	Write( data, nData, file );

	return( 1 );
}


int CVQueue::Dump( void *data[], int nData, char *prefix, int index, char *suffix  )
{
char	file[256];


	if( gpDump_filename( prefix, index, suffix, ".pt", file ) < 0 )
		return( -1 );

	int ret = Write( data, nData, file  );

	return( ret );
}



int CVQueue::Write( void *data[], int nData, char *file )
{
FILE *fp;
int i;

	if( nData == 0 )	return( -1 );


	if( ( fp = fopen( file, "wb" )) == NULL )
		return( -1 );

	fwrite( &nData, 1, 4, fp );
	qData_type *d = (qData_type *)data[0];


	int size = d->dataSize;
	fwrite( &size, 1, 4, fp );

	for( i = 0 ; i < nData ; i++ )
		fwrite( data[i], size, 1, fp );


	fclose( fp );
	return( 1 );
}


int CVQueue::Read( void *data[], int *nData, char *file )
{
FILE *fp;
int i;


	if( ( fp = fopen( file, "rb" )) == NULL )
		return( -1 );

	fread( nData, 1, 4, fp );
	qData_type *d = (qData_type *)data[0];

	int size;
	fread( &size, 1, 4, fp );

	for( i = 0 ; i < *nData ; i++ ){
		 qData_type *d = (qData_type *)malloc( size );

		fread( d, size, 1, fp );

		data[i] = d;
	}


	fclose( fp );
	return( 1 );
}