 
#include	<string.h>
#include	<math.h>

#include	"Uigp/igp.h"
#include	"Ulog/Log.h"
#include "Uvl/Vl2fType.h"

#ifdef _DEBUG
#define _DUMP 
#endif


#include	"ImageType/ImageType.h"
#include	"ImageDump/ImageDump.h"
#include	"ImageMark/ImageMark.h"

#include "Uln/PlnType.h"





#include	"pEdgeType.h"
#include	"LineDetector.h"





CLineDetector::CLineDetector()
{

	m_gim =  NULL;
	m_gimS = NULL;

	m_yim = NULL;

	m_yim2 = NULL;


	m_ae = NULL;

	m_box.x0 = m_box.y0 = 0;


	m_prm = pEdgePrm_alloc();
}
	

CLineDetector::~CLineDetector()
{
	DeleteContents();
}


void CLineDetector::DeleteContents()
{
	if( m_gim != NULL ){
		image_destroy( m_gim, 1 );
		m_gim = NULL;
	}

	if( m_gimS != NULL ){
		image_destroy( m_gimS, 1 );
		m_gimS = NULL;
	}


	if( m_yim != NULL ){
		image_destroy( m_yim, 1 );
		m_yim = NULL;
	}

	if( m_yim2 != NULL ){
		image_destroy( m_yim2, 1 );
		m_yim2 = NULL;
	}


	if( m_ae != NULL ){
		plEdgeA_destroy( m_ae );
		m_ae = NULL;
	}



}



int CLineDetector::Init( char *prmFile )
{
	return( 1 );
}


int			
CLineDetector::Process( image_type *sim, box2i *box, int iFrame )
{
int	ret;
box2i	b;

	b.x0 = (box->x0 / m_prm->d) * m_prm->d;
	b.x1 = ((box->x1 + m_prm->d -1 ) / m_prm->d) * m_prm->d;

	b.y0 = (box->y0 / m_prm->d) * m_prm->d;
	b.y1 = ((box->y1 + m_prm->d -1 ) / m_prm->d) * m_prm->d;



	m_box = *box;

	IMAGE_DUMP( sim, "LD0", 1, NULL );
	image_type *im = image_cut( sim, box->y0, box->x0, box->y1-box->y0+1, box->x1-box->x0+1, NULL );
//	IMAGE_DUMP( im, "LD0", 1, "crop" );

	ret = Process( im, iFrame );

	

	PEDGE_DUMPT( m_gim,box->x0, box->y0, "gim", iFrame, NULL );


	vec2f_type	p;
	p.y = box->y0;
	p.x = box->x0;
	plEdgeA_translate( m_ae, &p );

	PLEDGE_DUMP( m_ae, "LD0", iFrame, NULL );


	image_destroy( im, 1 );

	return( ret );
}



int			
CLineDetector::Process( image_type *sim, int iFrame )
{


	m_yim = image1_from( sim, m_yim );



	if( m_ae != NULL ){
		plEdgeA_destroy( m_ae );
		m_ae = NULL;
	}

	m_ae = plEdgeA_alloc( 1000 );


	if( m_prm->scale != 1 ){
		m_yim2 = image1_sample2( m_yim, m_yim2 );

		m_gim = pEdge_detector( m_yim2, m_prm, m_gim );

		pEdge_linking( m_gim );

		m_gimS = pEdge_static( m_gimS, m_gim );


		pEdge_line(  m_gim, 0, m_prm, m_ae );

		m_scale = 2;
		plEdgeA_scale( m_ae, 2 );

	

	}
	else	{
		m_gim = pEdge_detector( m_yim, m_prm, m_gim );

		pEdge_linking( m_gim );

//		m_gimS = pEdge_static( m_gimS, m_gim );
		m_gimS = pEdge_staticN( m_gimS, m_gim );


		pEdge_line(  m_gim, 0, m_prm, m_ae );

		m_scale = 1;
	}


//	GPLOG( ("L: %d", m_nL ) );


	IMAGE_DUMP( sim, "LD", 1, NULL );
	PLEDGE_DUMP( m_ae, "LD", iFrame, NULL );

	if( m_yim == sim )
		m_yim = NULL;

	return( 1 );
}



plnA_type *		
CLineDetector::Get( int fCopy )
{
	plnA_type *apl;

	apl =  plEdgeA_to_plnA( m_ae, 0.0, 1 );

	return( apl );
}

plnA_type *		
CLineDetector::Get( int minLen, int fCopy )
{
	plnA_type *apl;

	apl =  plEdgeA_to_plnA( m_ae, minLen, fCopy );

	return( apl );
}

void		
CLineDetector::Write( char *outFile )
{
char	file[256];

	plEdgeA_write( m_ae, outFile );




	gpFilename_force_extension( outFile, ".pt", file );
	pEdge_write_to_file( m_gim, file );
}






int	
CLineDetector::RrapproximateStraightLine( int i0, int i1, vl2f_type *vl )
{

	if( m_ae->a[i0]->rp == NULL || m_ae->a[i1]->rp == NULL )
		return( -1 );

	int ret = pEdge_straight_line(  m_gim, m_ae->a[i0]->rp, m_ae->a[i1]->rp, m_prm, vl );
	vl->p.x += m_box.x0;
	vl->p.y += m_box.y0;

	return( ret );
}
