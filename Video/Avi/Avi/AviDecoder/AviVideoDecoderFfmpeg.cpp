/*********************************
 ***   ImageVideoDecoder.cpp   ***
 *********************************/
#include <string.h>
#include "Uigp/igp.h"


#include "AviVideoDecoder.h"


#include "ImageCodec/ImageRead.h"

static int excute_cmd( char *cmd );






int CAviVideoDecoder::OpenFfmpeg( char*data, int bytes, char *extension )
{
	char  inFile[2048];
	int	ret;

	gp_filename_get_temporary("vid", 0, extension, inFile );
	gp_file_create(data, bytes, inFile);

	ret = OpenFfmpeg( inFile );

	unlink( inFile );


	if( ret < 0 )
		return( VD_UNSUPPORTED_INPUT_CODEC );

	return( ret );
}



int CAviVideoDecoder::OpenFfmpeg( char *inFile )
{
char	outFile[512],	cmd[1024];
int	ret;

	gp_filename_get_temporary("vid", 0, ".avi", outFile );

	sprintf( cmd, "ffmpeg.exe -y -i  %s  -an -vcodec rawvideo   %s", inFile, outFile );


	if( excute_cmd( cmd ) < 0 )
		return( -1 );



	ret = Open( outFile );

	m_bTempFile = true;


	return( ret );
}



static int excute_cmd( char *cmd )
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );



	// Start the child process. 
	if( !CreateProcess( NULL,   // No module name (use command line)
		cmd,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi )           // Pointer to PROCESS_INFORMATION structure
		) 
	{
//		printf( "CreateProcess failed (%d).\n", GetLastError() );
		return(- 1 );
	}

	// Wait until child process exits.
	WaitForSingleObject( pi.hProcess, INFINITE );

	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return( 1 );
}

