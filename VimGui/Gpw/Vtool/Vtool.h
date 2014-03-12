/***
***    author:		Yoram Elichai   yorame@gmail.com
***    Copyright (C) 2000 - All Rights Reserved
***/
#ifndef _VTOOL_
#define _VTOOL_





#import <UIKit/UIKit.h>

#import     "../FrameLabel/FrameLabelMac.h"
#import     "../FrameLabel/Ios/ImageLabelIos.h"


#include	"Uigp/igp.h"



struct image_type;




class CVtool
{
public:
	CVtool();
	virtual ~CVtool();



    
    static int SavePng( image_type *sim );

    
    static int SavePng( UIImage* imgTaken );
    
    
    static image_type *  LoadPng( char *file );
    
    
    static UIImage* CreateUIImage( image_type *im );
    
    static image_type * DecomposeUIimage( UIImage* image );
    
    static CFrameLabelMac* CreateFrameLabel( UIView *view, NSBundle *bundle,
                                          NSString *name, int fx, int fy );
    static CFrameLabelMac* CreateFrameLabelDouble( UIView *view, NSBundle *bundle,
                                           NSString *imageName1, NSString *imageName2, int fx, int fy );

    
    static CImageLabelIos * CreateImageLabel( UIView *view, NSBundle *bundle,
                                            NSString *name, int fx, int fy );
    
    static UIColor * CreateUIColor( int color, float alpha );
    
    const char* GetSessionID(  char *id);
    void clearSessionID();

protected:

private:
    NSString *sessionID;
};

#endif




