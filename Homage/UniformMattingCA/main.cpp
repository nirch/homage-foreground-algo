
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<string.h>


//#ifdef _DEBUG
#define _DUMP 
//#endif


#include	"Uigp/igp.h"
#include	"Utime\GpTime.h"
#include	"Ulog/Log.h"




#include	"ImageType/ImageType.h"
#include	"ImageMark/ImageMark.h"
#include	"ImageDump/ImageDump.h"

#include "ImageCodec/ImageRead.h"

#include "Png/PngCodec/Png/ImageWritePng.h"



#include	"VideoCodec\VideoEncoder.h"
#include	"VideoCodec\VideoDecoder.h"
#include	"Avi\Avi\AviEncoder\AviGetEncoder.h"
#include	"Avi\Avi\AviDecoder\\AviGetDecoder.h"
#include "ImageVideoCodec\\ImageGetVideoDecoder.h"


//#include "Contour/ContourType.h"
#include "VimLib.h"






#include "MattingLib/UniformBackground/UniformBackground.h"




static void		read_command_line(int argc, char *argv[],
									int *contour,
									int	*dFrame,
									char *prmFile,
									char *mFile,
									char *bFile,
									int *flip,
									int *F, char *inFile, 
									int *outType, int *frameRate, int *codec, char *outFile );






int	WriteEndFile( char *str, char *outFile );

int	WriteEndFile_delete( char *outFile );




int
main( int argc, char **argv )
{
char	inFile[256],	outFile[256],	mFile[256],	file[256],	xmlFile[256],	bFile[256];
int		outFormat;
image_type	*tim,	*sim;
int	frames,	contour;
int	i;

gp_time_type	hmiTime,	aTime;
int	ret,	dFrame,	frameRate,	codec,	flip;


	read_command_line( argc, argv, &contour, &dFrame, xmlFile, mFile, bFile, &flip, &frames, inFile, &outFormat, &frameRate, &codec, outFile );




//	image_dump_set_dir( "_dump" );

	gpDump_set_dir( "_dump" );

	WriteEndFile_delete( outFile );


	char	dir[256];
	gpFilename_dir( outFile, dir );
	gpDir_force_exist( dir );

//	sprintf( file, "%s\\log.txt", "_dump" );
	gpFilename_force_extension( outFile, ".log", file );
	GPLOG_OPEN( file );


	gp_filename_force_extension( outFile, ".txt" );


	image_type *gim = NULL;

	if(  bFile[0] != 0 ){
		if( ( gim = image3_read_file( bFile ) ) == NULL )
			gpError( "UniformMattingCA", "Open  %s  failed", bFile  );

		outFormat = 5;
	}

	


	CVideoDecoder	*videoDecoder = NULL;
	if( gpFilename_compare_extension( inFile, ".avi") == 1)
			videoDecoder = GetAviDecoder();
	else
			videoDecoder = GetImageVideoDecoder();


	videoDecoder->SetImageFormat( IMAGE_FORMAT_RGB );

	if( videoDecoder->Open( inFile ) < 0  ){
		WriteEndFile( "Failed\nOpen input file", outFile );
		gpError( "UniformMattingCA", "Open  %s  failed", inFile  );
	}



	int	sample = 0;//1;
	float	scale = 1;//0.5;


	int	width = videoDecoder->GetWidth()*scale;
	int	height = videoDecoder->GetHeight()*scale;


	CVideoEncoder *videoEncoder = GetAviEncoder();//GetVideoEncoder( ".avi" );


	gp_filename_force_extension( outFile, ".avi" );
	
	if ( videoEncoder->Open(outFile) < 0 )
		error( "UniformMattingCA", "videoEncoder->open failed" );



	CVideoStreamEncoder *videoStream = videoEncoder->CreateVideoStream( frameRate,
							 width,
							 height,
							 AVI_CODEC_MSVC,
							 //AVI_CODEC_MP42,//AVI_CODEC_INDEO50,//1,
							// AVI_CODEC_INDEO50,//1,
							 10000 );


	if( videoStream->Open() == NULL )
		error( "FaceTrackingAvi", "videoStream->open failed" );


	gpFilename_remove_extension( outFile );



	CUniformBackground  *m_mat;
	m_mat = new CUniformBackground();

	m_mat->SetDframe( dFrame );

	m_mat->SetContour( contour );





	box2i_type roi;
	box2i_crop( &roi, 0, 0, width, height );
	m_mat->SetRoi( &roi );


	if( gp_stricmp( xmlFile, "none" ) == 0 )
		gpFilename_force_extension( mFile, ".xml", xmlFile );

	m_mat->Init( xmlFile, mFile, videoDecoder->GetWidth(),videoDecoder->GetHeight() );

//	m_mat->ReadMask( mFile, videoDecoder->GetWidth(),videoDecoder->GetHeight() );

	if( flip == 1 )
		m_mat->SetFlip( 1 );



	gp_time_init( &hmiTime );
	gp_time_init( &aTime );

	tim = image_alloc( videoDecoder->GetWidth(),videoDecoder->GetHeight(), 4, IMAGE_TYPE_U8, 1 );

//	gpw_type *gpw = gpw_image( tim );

	image_type *aim;
	aim = NULL;
	
	image_type *bim = NULL;

	for( i = 0 ; frames < 0 || i < frames ; i++ ){

		GPLOG( ("%2d   ",  i) );
		
		if( videoDecoder->ReadFrame( i, &sim ) < 0 )
			break;
		
		gp_time_start( &hmiTime );


		
		ret = m_mat->Process( sim, i, &bim );


		if( ret < 0 ){
			WriteEndFile( "Failed\nEXCEPTION", outFile );
			return( -1 );
		}




		gp_time_stop( &hmiTime );



		tim = image4_from( bim, tim );



		switch( outFormat ){
		case 1:
			sprintf( file, "%s-%.2d.bmp", outFile, i );
			image_write_bmp( bim, file );

			break;


		case 2:
			sprintf( file, "%s-%.2d.png", outFile, i );
			aim = imageA_set_alpha( sim, 255, bim, aim );
		
			image_write_png_TA( aim, file );
			break;


		case 3:		
			aim = m_mat->GetImage( 0xFFFFFF, aim );
			
			tim = image4_from( aim, tim );
			break;

		case 4:		
			aim = m_mat->GetImage( 0x02FE05, aim );
			tim = image4_from( aim, tim );
			break;

		case 5:		
	
			aim = m_mat->GetImage( gim, aim );
			tim = image4_from( aim, tim );
			break;
		

		default:
			break;
		}

			
		if( tim != NULL )
			videoStream->WriteFrame( tim, 0 );



		fprintf( stderr, " ." );
		GPLOG( ("\n") );
	}

	fprintf( stderr, "\n" );


	sprintf( file, "%s.plf", outFile, i );
	m_mat->Write( file );

	m_mat->Trace( stdout );


	if( tim != NULL )
		image_destroy( tim, 1 );



	delete videoDecoder;


	videoEncoder->Close();
	if( videoEncoder != NULL )	delete videoEncoder;



	fprintf( stderr, "\n" );


	WriteEndFile( "success", outFile );

 
//	m_mat->Trace( stdout );

	delete m_mat;

	GPLOG_CLOSE();

	gpTime_print( stderr, "Alpha", &aTime );
	gpTime_print( stderr, "total", &hmiTime );
//	fprintf( stderr, "fps: %f\n", hmiTime.no / hmiTime.sec );


	return( 1 );
}


int
WriteEndFile( char *str, char *outFile )
{
	char	file[256];
	gpFilename_force_extension( outFile, ".txt", file );

	gpFile_write_buffer( file, str, strlen(str) );

	return( 1 );
}


int
WriteEndFile_delete( char *outFile )
{
	char	file[256];
	gpFilename_force_extension( outFile, ".txt", file );

	gpFile_delete( file );

	return( 1 );
}







static char *Usage = 
	"Usage: UniformMattingCA    [-C/-CA]  [-D#]  prmFile  ctrFile [-B#]   [-Flip]  [-F#]   inFile  [-bmp/-png/-avi/-avic] [-R#] [-MSVC/-mp4/-indeo] outFile";



static void	
read_command_line(int argc, char *argv[],
				int *contour,
				int	*dFarme,
				char *prmFile,
				char *mFile,
				char *bFile,
				int *flip,
				int *F,
				char *inFile, 
				int *outType, int *frameRate, int *codec, char *outFile )
{
int     k;

	k = 1;

	*contour = 0;
	if (k < argc && gp_strnicmp(argv[k], "-CA", 3) == 0  ){
		*contour = 2;
		k++;
	}

	if (k < argc && gp_strnicmp(argv[k], "-C", 2) == 0  ){
		*contour = 1;
		k++;
	}


	*dFarme = -1;
	if (k < argc && gp_strnicmp(argv[k], "-D", 2) == 0  ){
		sscanf( argv[k]+2, "%d", dFarme );
		k++;
	}

	if (k < argc) {
		sprintf( prmFile, "%s", argv[k]);
		k++;
	}


	if (k < argc) {
		sprintf( mFile, "%s", argv[k]);
		k++;
	}


	bFile[0] = 0;
	if (k < argc && gp_strnicmp(argv[k], "-B", 2) == 0  ){
		sscanf( argv[k]+2, "%s", bFile );
		k++;
	}



	*flip = -1;
	if (k < argc && gp_strnicmp(argv[k], "-Flip", 5 ) == 0  ){
		*flip = 1;
		k++;
	}


	*F = -1;
	if (k < argc && gp_strnicmp(argv[k], "-F", 2) == 0  ){
		sscanf( argv[k]+2, "%d", F );
		k++;
	}




	if (k < argc) {
		sprintf( inFile, "%s", argv[k]);
		k++;
	}
	else	error("read_command_line", Usage);



	*outType = 0;
	if (k < argc && gp_strnicmp(argv[k], "-bmp", 4) == 0  ){
		*outType = 1;
		k++;

	}

	if (k < argc && gp_strnicmp(argv[k], "-png", 4) == 0  ){
		*outType = 2;
		k++;
	}

	if (k < argc && gp_strnicmp(argv[k], "-avic", 5) == 0  ){
		*outType = 4;
		k++;
	}

	if (k < argc && gp_strnicmp(argv[k], "-avig", 5) == 0  ){
		*outType = 5;
		k++;
	}


	if (k < argc && gp_strnicmp(argv[k], "-avi", 4) == 0  ){
		*outType = 3;
		k++;
	}


	*frameRate = 30;
	if (k < argc && gp_strnicmp(argv[k], "-R", 2) == 0  ){
		sscanf( argv[k]+2, "%d", frameRate );
		k++;
	}




	// [-MSVC/-mp4/-indeo]
	*codec = AVI_CODEC_MSVC;
	if (k < argc && gp_strnicmp(argv[k], "-msvc", 5) == 0  ){
		*codec = AVI_CODEC_MSVC;
		k++;
	}

	if (k < argc && gp_strnicmp(argv[k], "-mp4", 4) == 0  ){
		*codec = AVI_CODEC_MP42;
		k++;
	}

	if (k < argc && gp_strnicmp(argv[k], "-indeo", 6) == 0  ){
		*codec = AVI_CODEC_INDEO50;
		k++;
	}
	
	if (k < argc) {
		sprintf( outFile, "%s", argv[k]);
		k++;
	}
	else	error("read_command_line", Usage);
}
