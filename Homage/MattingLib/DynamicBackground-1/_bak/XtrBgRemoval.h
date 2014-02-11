/************************
 ***  XtrBgRemoval.h  ***
 ************************/


#ifndef _XTR_BG_REMOVAL_H_
#define _XTR_BG_REMOVAL_H_


#if defined _DEBUG || defined DEBUG
#pragma comment( lib, "DynamicBackgroundD.lib" )
#else
#pragma comment( lib, "DynamicBackground.lib" )
#endif

#include	"ImageType/ImageType.h"


class CXtrBgRemoval
{
public:

	CXtrBgRemoval();

	~CXtrBgRemoval();


	void DeleteContent();


	void UpdateBgImage( image_type *im );


	void ProcessFrame( image_type *im, image_type **mim );




	void CompleteBackground( image_type *im );

	void CompleteBackgroundEnd();



	void SetMode( int mode )	{ m_mode = mode; }

	void SetThreshold( float t0, float t1 );

	void Dump( char *outFile );
	


//private:

public:

	float	w;	// new bg image weight
	int	m_T0,	m_T1;
	int	m_mode;

	int	m_state;

	int	m_bgFrame;
	image_type	*m_mim;
	image_type	*m_var;

	image_type	*m_sbim;
	image_type	*m_svar;

	image_type	*m_xim;
	image_type	*m_yim;

};


#define	BR_COLOR	1
#define BR_GRAD		2
#define BR_UPDATE_FOREGROUND	4
#define BR_UPDATE	8



#define	BG_INIT		1
#define BG_COMPLETE	2
#define BG_REMOVE	3;
#endif