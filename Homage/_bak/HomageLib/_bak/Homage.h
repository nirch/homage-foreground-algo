// Homage.h: interface for the VimArRenderer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _HOMAGE_LIB_
#define _HOMAGE_LIB_

#if defined _DEBUG || defined DEBUG
#pragma comment( lib, "HomageLibD.lib" )
#else
#pragma comment( lib, "HomageLib.lib" )
#endif





#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Uvec/Vec3d.h"
#include "Utime/GpTime.h"
#include "Umedia/MediaDataType.h"

#include "ImageType/ImageType.h"
#include "Gpw/FrameBuffer/FrameBuffer.h"
#include "Gpw/Gpw.h"





class CHomage
{
public:
	CHomage(  CFrameBuffer *fb);
	virtual ~CHomage();

	void	DeleteContents();
    
 
	int Init();


	int	IsEmpty()	{ return ( m_im == NULL); }
	int	IsReady()	{ return (  m_im != NULL); }


	
	int	Process( int iFrame );

	int Process( image_type *im, int iFrame );



	int GetProcessTime();

	void Trace( FILE *fp );

	void Write( char *file );




private:


public:

    CFrameBuffer *m_fb;

	int m_iFrame;

	image_type *m_im;
    
    
    class CUniformBackground *m_cb;
    


	gpTime_type	m_gTime;
	gpTime_type	m_tProcess;
};
#endif 


