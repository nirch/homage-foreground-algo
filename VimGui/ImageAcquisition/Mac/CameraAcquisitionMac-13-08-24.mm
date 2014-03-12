/**********************************
 ***   CameraAcquisition.cpp   ***
 **********************************/
#include	<string.h>

#include	"Uigp/igp.h"
#include	"Ulog/Log.h"
#include	"Utime/GpTime.h"
#include	"ImageType/ImageType.h"

#include	"CameraAcquisitionMac.h"

#include <sys/types.h>
#include <sys/sysctl.h>


static image_type *    image3_iphone_camera( image_type *sim, int width, int height, image_type *im );

static image_type *image3_iphone_camera_1( image_type *sim, image_type *im );

static image_type * image3_iphone_camera_1( image_type *sim, int width, int height, image_type *im );


static image_type * image3_iphone_camera_1( image_type *sim, int x0, int y0,
                                           int width, int height, image_type *im );

static image_type * image3_flipVH( image_type *sim, image_type *im );
static image_type * image3_flipH( image_type *sim, image_type *im );


#ifdef  __APPLE__
CImageAcquisition *CreateCameraAcquisition()
{
	CImageAcquisition	*vc;

	vc = new CCameraAcquisitionMac();

	return( vc );
}
#endif


CCameraAcquisitionMac::CCameraAcquisitionMac()
{


	m_image = NULL;
    temp_img = NULL;
    
	m_acq = 1;


	m_active = 1;
    
    m_resolution = 1;       // default 480x360
    //m_resolution = 2;       // default 640x480

	m_rWidth = -1;//320;
	m_rHeight = -1;//480;
    
    m_protrait = 1;
    
    m_width = m_rWidth;
    m_height = m_rHeight;
    
    m_cameraOpen = false;
    m_cWidth = m_cHeight = -1;
    
    // IPHONE5
    m_handset = HANDSET_IPHONE_5;
    m_ccdWidth = 4.54;
    m_focalLength = 4.1;
    
#if TARGET_OS_IPHONE
    camera = [[CameraControllerIOS alloc] init];
#else
    camera = [[CameraControllerMac alloc] init];
#endif
    
#ifdef _AA_
    int handsetVal = HANDSET_IPHONE_5;
    char *platformString = this->platformString();
    if (strcmp(platformString, "iPhone3,1") == 0){
        handsetVal = HANDSET_IPHONE_4;
    }
    else if (strcmp(platformString, "iPhone4,1") == 0){
        handsetVal = HANDSET_IPHONE_4S;
    }
    else if ((strcmp(platformString, "iPhone5,1") == 0) || ((strcmp(platformString, "iPhone5,2") == 0))){
        handsetVal = HANDSET_IPHONE_5;
    }
    
    free(platformString);
#endif
    
    int  handsetVal = GetPlatform();
    
    this->SetHandset(handsetVal);
}


CCameraAcquisitionMac::~CCameraAcquisitionMac()
{
	Close();



	if( m_image != NULL ){
		//image_destroy( m_image, 0);
		m_image = NULL;
	}
    
    if (temp_img){
        image_destroy(temp_img, 0);
        temp_img = NULL;
    }
    
    [camera release];
}

char* CCameraAcquisitionMac::platformString(){
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    char *model = (char*)malloc(size);
    sysctlbyname("hw.machine", model, &size, NULL, 0);
    
    return model;
}


int CCameraAcquisitionMac::GetPlatform()
{

    int handsetVal = HANDSET_IPHONE_5;
    char *platformString = this->platformString();
    if (strcmp(platformString, "iPhone3,1") == 0){
        handsetVal = HANDSET_IPHONE_4;
    }
    else if (strcmp(platformString, "iPhone4,1") == 0){
        handsetVal = HANDSET_IPHONE_4S;
    }
    else if ((strcmp(platformString, "iPhone5,1") == 0) || ((strcmp(platformString, "iPhone5,2") == 0))){
        handsetVal = HANDSET_IPHONE_5;
    }
    
    free(platformString);
    
    return handsetVal;
}



int CCameraAcquisitionMac::SetHandset( int handset )
{
    m_handset = handset;
    if( m_iCamera != 0 ){
    switch( m_handset ){
            
        case HANDSET_IPAD_4:
            m_ccdWidth = 4.54;
            m_focalLength = 4.3;
            break;
            
        case HANDSET_IPAD_5:
            m_ccdWidth = 4.54;
            m_focalLength = 4.3;
            break;
            
        case HANDSET_IPHONE_5:
            m_ccdWidth = 4.54;
            m_focalLength = 4.1;
            break;
            
        case HANDSET_IPHONE_4S:
            m_ccdWidth = 4.54;
            m_focalLength = 4.28;
            break;
            
        case HANDSET_IPHONE_4:
        default:
            m_ccdWidth = 4.54;
            m_focalLength = 3.85;
            break;
	}
    }
    else {
        
        switch( m_handset ){
                
            case HANDSET_IPAD_4:
                m_ccdWidth = 4.54;
                m_focalLength = 2.2;
                break;
                
            case HANDSET_IPAD_5:
                m_ccdWidth = 4.54;
                m_focalLength = 2.2;
                break;
                
            case HANDSET_IPHONE_5:
                m_ccdWidth = 4.54;
                m_focalLength = 4.1;
                break;
                
            case HANDSET_IPHONE_4S:
                m_ccdWidth = 4.54;
                m_focalLength = 2.2;
                break;
                
            case HANDSET_IPHONE_4:
            default:
                m_ccdWidth = 4.54;
                m_focalLength = 3.85;
                break;
        }
        
    }
    
	return( 1  );
}


int CCameraAcquisitionMac::OpenWithPreview( int iCamera, CGRect *previewLayer )
{

	
	GPLOG(("Camera Open\n" ) );
	GPLOG_FLUSH();



	m_iCamera = iCamera;

	
	

	GPLOG_FLUSH();
    
    [camera setResolution:m_resolution ];
    //[camera setResolution:5 ];

#if TARGET_OS_IPHONE
    [camera setCameraDevice:(iCamera == 0) ? UIImagePickerControllerCameraDeviceFront : UIImagePickerControllerCameraDeviceRear];
#endif
    
    if (previewLayer != NULL){
        [camera setupCaptureSessionWithPreviewLayer:*previewLayer];
    }
    else{
        [camera setupCaptureSession];
    }
    
    m_cameraOpen = true;
    
    m_cWidth = 480;
    m_cHeight = 360;
    
    
    
    int  handsetVal = GetPlatform();
    this->SetHandset(handsetVal);
   
    
	return 1;
}


int CCameraAcquisitionMac::Open( int iCamera ) {
    return this->OpenWithPreview(iCamera, NULL);
}


int CCameraAcquisitionMac::AddPreviewLayer( CGRect *rect )
{
    [camera addVideoPreviewLayer:*rect];
    return( 1 );
}

#if TARGET_OS_IPHONE
AVCaptureVideoPreviewLayer * CCameraAcquisitionMac::GetPreviewLayer()
{
    AVCaptureVideoPreviewLayer *previewLayer = [ camera previewLayer];
    
    return( previewLayer );
    
}
#endif

int CCameraAcquisitionMac::Get( image_type **im, int iFrame )
{
    
    //UIImage *image = camera.lastFrame;
    //NSData *imageData = camera.lastFrameData;
    //CGSize imageSize = camera.imageSize;
    
    CGImageRef cgImage = camera.lastFrame;
    CGSize size = CGSizeMake(CGImageGetWidth(cgImage), CGImageGetHeight(cgImage));
    
    //UIImage *img = [UIImage imageWithCGImage:cgImage];

    //if (!image) {
    if (!cgImage){
        return (-1);
    }
    
    //if (temp_img && ((m_cWidth != image.size.width) || (m_cHeight != image.size.height))){
    if (temp_img && ((m_cWidth != size.width) || (m_cHeight != size.height))){
        if (temp_img) {             // camera gave a new frame size, we need to reset the temp_img
            delete temp_img;
            temp_img = NULL;
        }
    }
    
    
	if ( temp_img == NULL ){
        //m_cWidth = image.size.width;
        //m_cHeight = image.size.height;
        m_cWidth = size.width;
        m_cHeight = size.height;
		temp_img = image_alloc( m_cWidth, m_cHeight, 4, IMAGE_TYPE_U8, 1 );
        
 //       if( m_iCamera == 1 ){
        if( m_rWidth == -1 || m_rHeight == -1 ){
            m_height = m_cHeight;
            m_width = m_cWidth;
        }
        
        if (m_protrait == 0){
            if( m_height > m_cHeight )
                m_height = m_cHeight;
        
            if( m_width > m_cWidth )
                m_cWidth = m_width;
        }
        
        
        SetFoucusPixel( m_fx, m_fy );
	}
    
    
   // NSLog(@"%.1f %.1f", image.size.width, image.size.height);

    //CGImageRef imageRef = img.CGImage;
    CGImageRef imageRef = cgImage;
    CFDataRef dataRef = CGDataProviderCopyData(CGImageGetDataProvider(imageRef));
    NSData *data      = (NSData *)dataRef;
    //NSData *data = imageData;
    unsigned char *pixels        = (unsigned char *)[data bytes];
    //NSLog(@"%d", [data length]);
    memcpy(temp_img->data, pixels, [data length]);

    CFRelease(dataRef);
    //CGImageRelease(imageRef);
    
    

    

    if( m_protrait == 3 )
        m_image = image3_flipH( temp_img,  m_image );
    else
    if( m_protrait == 1 )
        m_image = image3_iphone_camera( temp_img, m_width, m_height, m_image );
          
    else
//        m_image = image3_iphone_camera_1( temp_img, m_width, m_height, m_image );
        m_image = image3_iphone_camera_1( temp_img, m_x0, m_y0, m_width, m_height, m_image );

    
	*im = m_image;

	m_iFrame++;

/*
    static int frames = 0;
    if (frames < 5){
        CFURLRef url = (CFURLRef)[NSURL fileURLWithPath:[NSString stringWithFormat:@"/Users/orenshtark/Pictures/CGImage%d.png", frames]];
        CGImageDestinationRef destination = CGImageDestinationCreateWithURL(url, kUTTypePNG, 1, NULL);
        CGImageDestinationAddImage(destination, cgImage, nil);
        if (!CGImageDestinationFinalize(destination)) {
            //NSLog(@"Failed to write image to %@", path);
        }
        CFRelease(destination);
        
        image_write_bmp(temp_img, (char*)[[NSString stringWithFormat:@"/Users/orenshtark/Pictures/temp_img%d.png", frames] UTF8String]);
        
        image_write_bmp(m_image, (char*)[[NSString stringWithFormat:@"/Users/orenshtark/Pictures/m_image%d.png", frames] UTF8String]);
        frames++;
    }*/
    
    CGImageRelease(cgImage);
    
	return( 1 );
}


void CCameraAcquisitionMac::SetFoucusPixel( int x, int y )
{
	m_fx = x;
	m_fy = y;
    
    if( m_cWidth <= 0 )
        return;
    
    if( m_fx > 0 ){
        m_x0 = m_fx - 0.5*m_width;
        if( m_x0 < 0 )  m_x0 = 0;
    }
    else
        m_x0 = 0.5 * ( m_cWidth - m_width );
    
    
    if( m_fy > 0 ){
        m_y0 = m_fy - 0.5*m_height;
        if( m_y0 < 0 )  m_y0 = 0;
    }
    else
        m_y0 = 0.5 * ( m_cHeight - m_height );
}
        


void CCameraAcquisitionMac::SetResolution( int resolution )
{
    m_resolution = resolution;
    if (m_cameraOpen){                          // if camera not open, Open method will call the camera set method
        [camera setPreset:resolution];          // we use setPreset because the session is already working
    }
}


int CCameraAcquisitionMac::GetWhiteBalance( long *value, long *type )
{

	return( 1 );
}

int CCameraAcquisitionMac::SetWhiteBalance( long value, long type )
{

	return( 1 );
}





int CCameraAcquisitionMac::SetAutoFocus( float x, float y )
{
    if( x < 0 || y < 0 )
        x = y = 0.5;
    

    [ camera SetAutoFocusAtPoint:CGPointMake(x, y)];
    
//    [ camera SetContinuousFocusAtPoint:CGPointMake(.5f, .5f)];
    
	return( 1 );
}

int CCameraAcquisitionMac::SetContinuousAutoFocus( float x, float y )
{
    if( x < 0 || y < 0 )
        x = y = 0.5;
    
    
    [ camera SetContinuousFocusAtPoint:CGPointMake(x, y)];
        
	return( 1 );
}


int CCameraAcquisitionMac::GetFocusState()
{
    if( [ camera isAdjustingFocus] == true )
        return( 1 );
    
	return( -1 );
}


int CCameraAcquisitionMac::GetFocus( long *value, long *type )
{
    //  [ camera SetContinuousFocusAtPoint:CGPointMake(.5f, .5f)];
    //    [ camera SetAutoFocusAtPoint:CGPointMake(.5f, .5f)];
	return( 1 );
}

int CCameraAcquisitionMac::SetFocus( long value, long type )
{
  //  [ camera SetContinuousFocusAtPoint:CGPointMake(.5f, .5f)];
//    [ camera SetAutoFocusAtPoint:CGPointMake(.5f, .5f)];
	return( 1 );
}




int CCameraAcquisitionMac::GetSharpness( long *value, long *type )
{

	return( 1 );
}

int CCameraAcquisitionMac::SetSharpness( long value, long type )
{

	return( 1 );
}



int CCameraAcquisitionMac::GetPowerLineFrequency( long *value, long *type )
{

	return( 1 );
}

int CCameraAcquisitionMac::SetPowerLineFrequency( long value, long type )
{

	return( 1 );
}


int CCameraAcquisitionMac::GetExposure( long *value, long *type )
{

	return( 1 );
}

int CCameraAcquisitionMac::SetExposure( long value, long type )
{

	return( 1 );
}












int CCameraAcquisitionMac::LogStatus()
{
#ifndef WINCE
	long value,	flag;

	GPLOG(("Camera Setting - BEGIN\n" ) );
	
	if( GetWhiteBalance( &value, &flag ) >= 0 )
		GPLOG(("WhiteBalance  %d  %d\n", (int)flag, (int)value ) );


	if(GetSharpness( &value, &flag ) >= 0 )
		GPLOG(("Sharpness  %d  %d\n", (int)flag, (int)value ) );


	if( GetFocus( &value, &flag ) >= 0 )
		GPLOG(("Focus  %d  %d\n", (int)flag, (int)value ) );


	if( GetPowerLineFrequency( &value, &flag  ) > 0 )
		GPLOG(("Power Line Frequency  %d  %d\n", (int)flag, (int)value ) );




	if( GetExposure( &value, &flag ) >= 0 )
		GPLOG(("Exposure  %d  %d\n", (int)flag, (int)value ) );


	GPLOG(("Camera Setting - END\n" ) );

	GPLOG_FLUSH();

#endif
	return( 1 );
}



static image_type *
image3_iphone_camera( image_type *sim, int width, int height, image_type *im )
{
	u_char	*tp;
	u_int	*sp;
	int	i,	j,	y0;
    
    
    
	im = image_realloc( im, width, height, 3, IMAGE_TYPE_U8, 1 );
    
    
  //  y0 = sim->height - 0.5*( sim->height - width );
//	int align = -sim->width;
    y0 =0.5*( sim->height - width );
	int align = sim->width;

    
	sp = (u_int *)sim->data;
	tp = im->data;
	for( i = 0 ; i < im->row ; i++ ){
	//	sp = (u_int *)IMAGE_PIXEL( sim, y0, im->height-1 - i );
        sp = (u_int *)IMAGE_PIXEL( sim, y0, i );
		for( j = 0 ; j < im->column ; j++, sp += align ){
			*tp++ = IMAGE4_BLUE(*sp );
			*tp++ = IMAGE4_GREEN(*sp );
			*tp++ = IMAGE4_RED(*sp );
		}
	}
    
	return( im );
}


static image_type *
image3_iphone_camera_1( image_type *sim, image_type *im )
{
	u_char	*tp;
	u_int	*sp;
	int	i,	j;
    
    
    
	im = image_realloc( im, sim->width, sim->height, 3, IMAGE_TYPE_U8, 1 );
    
    
	sp = (u_int *)sim->data;
	tp = im->data;
	for( i = 0 ; i < im->row ; i++ ){
		for( j = 0 ; j < im->column ; j++, sp++ ){
			*tp++ = IMAGE4_BLUE(*sp );
			*tp++ = IMAGE4_GREEN(*sp );
			*tp++ = IMAGE4_RED(*sp );
		}
	}
    
	return( im );
}


static image_type *
image3_iphone_camera_1( image_type *sim, int width, int height, image_type *im )
{
	u_char	*tp;
	u_int	*sp;
	int	i,	j;
    
    
    
	im = image_realloc( im, width, height, 3, IMAGE_TYPE_U8, 1 );
    
    int x0 = 0.5*( sim->width - width );
    int y0 = 0.5*( sim->height - height );
    
    
	sp = (u_int *)sim->data;
	tp = im->data;
	for( i = 0 ; i < im->height ; i++ ){
        sp = IMAGE4_PIXEL( sim, i+y0, x0 );
		for( j = 0 ; j < im->width ; j++, sp++ ){
			*tp++ = IMAGE4_BLUE(*sp );
			*tp++ = IMAGE4_GREEN(*sp );
			*tp++ = IMAGE4_RED(*sp );
		}
	}
    
	return( im );
}



static image_type *
image3_iphone_camera_1( image_type *sim, int x0, int y0, int width, int height, image_type *im )
{
	u_char	*tp;
	u_int	*sp;
	int	i,	j;
    
    
    
	im = image_realloc( im, width, height, 3, IMAGE_TYPE_U8, 1 );
    
 //   int x0 = 0.5*( sim->width - width );
 //   int y0 = 0.5*( sim->height - height );
    
    
	sp = (u_int *)sim->data;
	tp = im->data;
	for( i = 0 ; i < im->height ; i++ ){
        sp = IMAGE4_PIXEL( sim, i+y0, x0 );
		for( j = 0 ; j < im->width ; j++, sp++ ){
			*tp++ = IMAGE4_BLUE(*sp );
			*tp++ = IMAGE4_GREEN(*sp );
			*tp++ = IMAGE4_RED(*sp );
		}
	}
    
	return( im );
}

static image_type *
image3_flipVH( image_type *sim, image_type *im )
{
    int    i,     j;
    
    
    im = image_realloc( im, sim->width, sim->height, 3, IMAGE_TYPE_U8, 1 );
    
    
    for( i = 0 ; i < sim->height ; i++ ){
        u_char *tp = IMAGE_PIXEL( im, i, 0 );
        u_int *sp = IMAGE4_PIXEL( sim, sim->height-1-i, sim->width-1 );
        for( j = 0 ; j < im->column ; j++, tp, sp-- ){
            *tp++ = IMAGE4_BLUE(*sp );
            *tp++ = IMAGE4_GREEN(*sp );
            *tp++ = IMAGE4_RED(*sp );
            
        }
    }
    
    return( im );
}

static image_type *
image3_flipH( image_type *sim, image_type *im )
{
    int    i,     j;
    
    
    im = image_realloc( im, sim->width, sim->height, 3, IMAGE_TYPE_U8, 1 );
    
    
    for( i = 0 ; i < sim->height ; i++ ){
        u_char *tp = IMAGE_PIXEL( im, i, 0 );
        u_int *sp = IMAGE4_PIXEL( sim, i, sim->width-1 );
        for( j = 0 ; j < im->column ; j++, sp-- ){
            *tp++ = IMAGE4_BLUE(*sp );
            *tp++ = IMAGE4_GREEN(*sp );
            *tp++ = IMAGE4_RED(*sp );
            
        }
    }
    
    return( im );
}

