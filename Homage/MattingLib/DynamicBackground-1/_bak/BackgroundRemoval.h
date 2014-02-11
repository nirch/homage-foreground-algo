#pragma once
#ifndef _BACKGROUND_REMOVAL_H_
#define _BACKGROUND_REMOVAL_H_

#include	<stdio.h>
#include	"DynamicBackground.h"
#include	"HeadDetection/FaceTracking.h"



#define DB_FRAMES_BACK 3 // dynamic background frames back


class CXtrBgRemoval;



class CBackgroundRemoval 
{
public:
	
	CBackgroundRemoval();

	~CBackgroundRemoval();

	void DeleteContents();

	int Init( char *prmFile=NULL );


	int	ProcessFrame0( image_type *sim, image_type *simg, facePose_type *face, int iFrame );

	int ProcessFrame( image_type *sim, image_type *simg, facePose_type *face, int iFrame );

	int GetSilhouette( image_type **bim );

	int GetBackground( image_type **bim );
	int GetRgbBackground( image_type **bim );

	void SetDynamicBackground()	{ m_dynamic = 1; }

	int SetTno( int tno );


	void	SetUpdate( int  flag );

	void	SetUpdateBodyHistogram( int flag );
	void	SetUseBodyHistogram( int flag );


	void	SetCloseBody( int flag );

	void	SetRgbBackground( int flag )	{ m_rgbBackground = flag; }


	int		GetBoxImage( image_type *sim, image_type **im );

	int		GetBoxImage( image_type **im );

	float	GetUpdatePercent();
	/* get status of dynamic background processing */
	int getBackgroundStatus(){return m_backgroundStatus;};


	image_type * GetSilhouetteImage();//	{ return m_silhouetteIm; }

	void SetSilhouetteUpdate( int flag );

	void SetDbEdge( int flag );
	void SetDbRgb( int flag);

	void	Trace( FILE *fp );

	image_type * GetNccImage();

public:
	CDynamicBackground *m_dynamicBgr;
private:
	int	m_bg0;
	int	m_bg1;

	int	m_nBgImage;

	int	m_iFrame;

	image_type *m_inpImage; // input Image

protected:
	
	CXtrBgRemoval	*m_bgRemoval;

	image_type	*m_bim;

	image_type	*m_bimAbs;


	int	m_dynamic;
	int	m_update;
	int m_backgroundStatus;

	int	m_rgbBackground;
};


#endif


