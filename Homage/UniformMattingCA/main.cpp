
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

//#include "Wutil/UWgpw/GpwType.h"	



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



#include "ImageCodec\ImageRead.h"


#include "MattingLib/UniformBackground/UniformBackground.h"




static void		read_command_line(int argc, char *argv[],
									int *contour,
									int	*dFrame,
									char *mFile,
									char *roiFile,
									int *F, char *inFile, 
									int *outType, int *frameRate, int *codec, char *outFile );



image_type *ReadMask( char *inFile, int width, int height );

image_type *	ReadMaskPlnA( char *inFile, int width, int height );



int	WriteEndFile( char *str, char *outFile );

int	WriteEndFile_delete( char *outFile );




int
main( int argc, char **argv )
{
char	inFile[256],	outFile[256],	mFile[256],	roiFile[256], file[256];
int		outFormat;
image_type	*tim,	*sim;
int	frames,	contour;
int	i;

gp_time_type	hmiTime;
int	ret,	dFrame,	frameRate,	codec;


	read_command_line( argc, argv, &contour, &dFrame, mFile, roiFile, &frames, inFile, &outFormat, &frameRate, &codec, outFile );




	image_dump_set_dir( "_dump" );

	gpDump_set_dir( "_dump" );

	WriteEndFile_delete( outFile );


	char	dir[256];
	gpFilename_dir( outFile, dir );
	gpDir_force_exist( dir );

//	sprintf( file, "%s\\log.txt", "_dump" );
	gp_filename_force_extension( outFile, ".txt" );
	GPLOG_OPEN( outFile );


	


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
	if( box2i_read_from_file( roiFile, &roi, NULL ) < 0 ){
		BOX2D_SET(roi, 0, 0, width, height );
//		gpError( "FaceTrackingAvi", "Reading  %s  failed", roiFile  );
	}

	if( roi.x0 < 0 || roi.y0 < 0 || roi.x1 > videoDecoder->GetWidth() || roi.y1 > videoDecoder->GetHeight() ){
		gpWarning( "FaceTrackingAvi", "ROI out of range" );
		box2i_crop( &roi, 0, 0, width, height );
	}

	m_mat->SetRoi( &roi );


#ifdef _AA_
	image_type *mim;
	mim = ReadMask( mFile, videoDecoder->GetWidth(),videoDecoder->GetHeight() );

	

	if( mim == NULL ){
		gpFilename_force_extension( mFile, "-m.bmp", file );
		mim = image1_read_file( file );

		if( mim == NULL ){
			mim = image_alloc( videoDecoder->GetWidth(),videoDecoder->GetHeight(), 1, IMAGE_TYPE_U8, 1 );
			image1_const( mim,  255 );
			image1_color(mim, 0, 490, 96, 1420-490, 1080-96 );;
		}
	
		IMAGE_DUMP( mim, "mask", 1, NULL );
	}
#endif

	m_mat->ReadMask( mFile, videoDecoder->GetWidth(),videoDecoder->GetHeight() );

//	m_mat->SetDframe( 90 );



	gp_time_init( &hmiTime );

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




#ifdef _AA_
		if( i < 1 )
			m_mat->ProcessHistogram( sim, mim );
#endif

		
		ret = m_mat->Process( sim, i, &bim );

		if( ret < 0 ){
			WriteEndFile( "Failed\nEXCEPTION", outFile );
			return( -1 );
		}




		gp_time_stop( &hmiTime );





//		m_mat->GetSilhouette( &bim );




		if( ret > 0 )
			tim = image4_from( bim, tim );

		else
			tim = image4_from( sim, tim );



		if( outFormat == 1 ){
			sprintf( file, "%s-%.2d.bmp", outFile, i );
			image_write_bmp( bim, file );
		}


		if( outFormat == 2 ){
			sprintf( file, "%s-%.2d.png", outFile, i );
			aim = imageA_set_alpha( sim, 255, bim, aim );
			image_write_png_TA( aim, file );
		}


		if( outFormat == 3 ){
//			aim = imageA_set_alpha( sim, 255, bim, aim );
//			tim = imageA_final( aim, 0xFFFFFF, tim );

			aim = imageA_set_color( sim, bim, 255, 0xFFFFFF, aim );
			tim = image4_from( aim, tim );

		}

		if( outFormat == 4 ){
			aim = imageA_set_alpha( sim, 255, bim, aim );
			tim = imageA_finalB( aim, 0x02FE05, tim );
		}


		if( tim != NULL )
			videoStream->WriteFrame( tim, 0 );



//		sprintf( file, "%s-%.3d.pl", outFile, i );
//		m_mat->WriteContour( file );

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

	gpTime_print( stderr, "total", &hmiTime );
	fprintf( stderr, "fps: %f\n", hmiTime.no / hmiTime.sec );


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


#ifdef _AA_
image_type *
ReadMask( char *inFile, int width, int height )
{
image_type *im;


	contourA_type *ac;
	if( contourA_read_from_file( inFile, &ac ) < 0 )
		return( NULL );
//		gpError( "ReadMask", "Read %s failed", inFile );



	im = contourA_image_mask(  ac, width, height, NULL );

	IMAGE_DUMP( im, "mask", 2, NULL );

	return( im );
}


image_type *
ReadMaskPlnA( char *inFile, int width, int height )
{
	image_type *im;


	plnA_type *apl;
	if( plnA_read( inFile, &apl ) < 0 )
		return( NULL );
	


//	im = image1_mask_plnA(  apl, width, height, NULL );
	im = image1_mask_pln(  apl->a[0], width, height, NULL );


	IMAGE_DUMP( im, "mask", 2, "pln" );

	return( im );
}
#endif





static char *Usage = 
	"Usage: UniformMattingCA    [-C]  [-D#]  ctrFile   roiFile  [-F#]   inFile  [-bmp/-png/-avi/-avic] [-R#] [-MSVC/-mp4/-indeo] outFile";



static void	
read_command_line(int argc, char *argv[],
	int *contour,
				int	*dFarme,
				char *mFile,
				char *roiFile,
				int *F,
				char *inFile, 
				int *outType, int *frameRate, int *codec, char *outFile )
{
int     k;

	k = 1;

	*contour = 0;
	if (k < argc && gp_strnicmp(argv[k], "-c", 2) == 0  ){
		*contour = 1;
		k++;
	}


	*dFarme = -1;
	if (k < argc && gp_strnicmp(argv[k], "-D", 2) == 0  ){
		sscanf( argv[k]+2, "%d", dFarme );
		k++;
	}


	if (k < argc) {
		sprintf( mFile, "%s", argv[k]);
		k++;
	}

	if (k < argc) {
		sprintf( roiFile, "%s", argv[k]);
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
