/**********************************
 ***   Vtool.mm   ***
 **********************************/
#include	<string.h>

#include	"Uigp/igp.h"
#include	"Ulog/Log.h"
#include	"Utime/GpTime.h"
#include	"ImageType/ImageType.h"

#import     "../FrameLabel/FrameLabelMac.h"
#import     "../FrameLabel/Ios/ImageLabelIos.h"
#include	"Vtool.h"


CVtool::CVtool()
{
    sessionID = nil;


}


CVtool::~CVtool()
{
    if (sessionID){
        [sessionID release];
    }
}




int CVtool::SavePng( image_type *sim )
{
    image_type *im = image4_from( sim, NULL );
    
    UIImage* imgTaken = CreateUIImage( im );
    
    if( im != sim  )
    image_destroy( im, 1 );
    
    SavePng( imgTaken );
    
    return( 1 );
}



int CVtool::SavePng( UIImage* imgTaken )
{
    //UIImageWriteToSavedPhotosAlbum(imgTaken, nil, nil, nil);
    
    NSData *pngData = UIImagePNGRepresentation(imgTaken);
    UIImage  *img = [[UIImage alloc] initWithData: pngData];
    UIImageWriteToSavedPhotosAlbum(img, nil, nil, nil);
    
    NSLog(@"%f, %f", imgTaken.size.width, imgTaken.size.height);
    
    [img release];
    
    return( 1 );
}


image_type *  CVtool::LoadPng( char *file )
{
	//m_drag = drag;
    
    NSString *filename = [NSString stringWithUTF8String:file];
    UIImage *image = [UIImage imageWithContentsOfFile:filename];
    

    image_type *im =  DecomposeUIimage( image );
    
	return( im );
    
}




UIImage* CVtool::CreateUIImage(image_type *imageData)
{
    unsigned char *pixels        = imageData->data;
    int size = imageData->width * imageData->height * 4;
    
    size_t width                    = imageData->width;
    size_t height                   = imageData->height;
    size_t bitsPerComponent         = 8;
    size_t bitsPerPixel             = 32;
    size_t bytesPerRow              = imageData->width * 4;
    
    CGColorSpaceRef colorspace      = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo         = kCGBitmapByteOrderDefault;
    
    NSData* newPixelData = [NSData dataWithBytes:pixels length:size];
    CFDataRef imgData = (CFDataRef)newPixelData;
    CGDataProviderRef imgDataProvider = CGDataProviderCreateWithCFData(imgData);
    
    CGImageRef newImageRef = CGImageCreate (
                                            width,
                                            height,
                                            bitsPerComponent,
                                            bitsPerPixel,
                                            bytesPerRow,
                                            colorspace,
                                            bitmapInfo,
                                            imgDataProvider,
                                            NULL,
                                            NO,
                                            kCGRenderingIntentDefault
                                            );
    
    UIImage *newImage   = [[UIImage alloc] initWithCGImage:newImageRef];//[UIImage imageWithCGImage:newImageRef];
    
    CGColorSpaceRelease(colorspace);
    CGDataProviderRelease(imgDataProvider);
    CGImageRelease(newImageRef);
    
    return [newImage autorelease];
}




image_type * CVtool::DecomposeUIimage( UIImage* image )
{
    
    image_type *im;
    
    
    int width = image.size.width;
    int height = image.size.height;
    im = image_alloc( width, height, 4, IMAGE_TYPE_U8, 1 );
        

    
    
    CGImageRef imageRef = image.CGImage;
    
   size_t bit =  CGImageGetBitsPerPixel( imageRef );
    CFDataRef dataRef = CGDataProviderCopyData(CGImageGetDataProvider(imageRef));
    NSData *data      = (NSData *)dataRef;
    
    unsigned char *pixels        = (unsigned char *)[data bytes];
    
    memcpy(im->data, pixels, [data length]);
    
    CFRelease(dataRef);
    
    return( im );
}


CFrameLabelMac * CVtool::CreateFrameLabel( UIView *view, NSBundle *bundle, NSString *name,
                                    int fx, int fy )
{
    
    CFrameLabelMac  *fl  = new CFrameLabelMac( view );
    

    NSString *path = [bundle  pathForResource:name ofType:@"png"];

   
    fl->Init( fx, fx, (char*)path.UTF8String );
                      

    
    return( fl );
}


CImageLabelIos * CVtool::CreateImageLabel( UIView *view, NSBundle *bundle, NSString *name,
                                          int fx, int fy )
{
    
    CImageLabelIos  *fl  = new CImageLabelIos( view );
    
    
    NSString *path = [bundle  pathForResource:name ofType:@"png"];
    
    
    fl->Init(  (char*)path.UTF8String, fx, fx);
    
    
    
    return( fl );
}


UIColor * CVtool::CreateUIColor( int color, float alpha )
{
  	CGFloat red = (color >> 16) & 0xFF;
	CGFloat green = (color >> 8) & 0xFF;
	CGFloat blue = color & 0xFF;
    
	UIColor *ucolor = [UIColor colorWithRed:red/255.0 green:green/255.0 blue:blue/255.0 alpha:alpha];
    
	return( ucolor );
}


