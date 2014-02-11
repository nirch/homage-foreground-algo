
#ifndef _COLOR_BACKGROUND_H_
#define _COLOR_BACKGROUND_H_


#include "Uvec/Vec3d.h"
#include "Utime/GpTime.h"
#include "ImageType/ImageType.h"





class CUniformBackground 
{
public:
	
	CUniformBackground();

	~CUniformBackground();

	void DeleteContents();

	void	SetRoi( box2i_type *b );

	int	ProcessHistogram( image_type *sim, image_type *mim );


	int	Process( image_type *sim, int iFrame, image_type **cim );


	void SetDframe( int iFrame )	{ m_dFrame = iFrame; }


	void	Trace( FILE *fp );

protected:

	int	ProcessBn( image_type *sim );

	int	ProcessUpdate( image_type *sim );

	int	m_iFrame;
	int	m_dFrame;

	float m_T;
	
	float m_bT;

	float m_bnT;


	vec2i_type	m_v;

	box2i_type	m_roi;
	int	m_N;

	image_type	*m_bim;

	image_type	*m_bimC;



	image_type *m_yim;
	image_type *m_bnIm;
	image_type *m_bnImD;


public:
//	image_type *m_him;
	image_type *m_cim;

	gpTime_type	m_rTime;
	gpTime_type	m_tCompare;
	gpTime_type	m_tUpdate;
	gpTime_type	m_gTime;

	gpTime_type	m_tBn;
};


#endif


