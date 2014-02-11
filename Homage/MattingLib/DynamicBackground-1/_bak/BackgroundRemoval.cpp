/*********************************
 ***   BackgroundRemoval.cpp   ***
 *********************************/

#include	<stdio.h>
#include	<string.h>
#include	<math.h>

#include	"ImageType/ImageType.h"
#include	"ImageDump/ImageDump.h"

#include	"XtrBgRemoval.h"

#include	"BackgroundRemoval.h"
//#include	"BitMatrix.h"


//static void	image1_filter( image_type *sim );
//static void	image1_filter3( image_type *sim );

#define TAKE_DYN_MAX 250 




CBackgroundRemoval::CBackgroundRemoval()
{
	m_dynamicBgr = NULL;

	m_bgRemoval = NULL;

	m_bim = NULL;

	m_bimAbs = NULL;

	m_bg0 = 20;//20;
	m_bg1 = 48;//;//128;//96;//64;//36;

	m_nBgImage = 0;

	m_dynamicBgr = NULL;

	 m_dynamic = 0;

	 m_update = 1;

	 m_rgbBackground = 0;

}


CBackgroundRemoval::~CBackgroundRemoval()
{
	DeleteContents();

#ifdef _AA_
	if( m_bim != NULL ){
		image_destroy( m_bim, 1 );
		m_bim = NULL;
	}


	if( m_bimAbs != NULL ){
		image_destroy( m_bimAbs, 1 );
		m_bimAbs = NULL;
	}



	if (m_inpImage	!= NULL)
	{
		image_destroy( m_inpImage, 1 );
		m_inpImage = NULL;
	}

	if (m_dynamicBgr	!= NULL)
	{
		delete m_dynamicBgr;
		m_dynamicBgr = NULL;
	}
#endif
}


void CBackgroundRemoval::DeleteContents()
{
	if( m_bim != NULL ){
		image_destroy( m_bim, 1 );
		m_bim = NULL;
	}


	if( m_bimAbs != NULL ){
		image_destroy( m_bimAbs, 1 );
		m_bimAbs = NULL;
	}



	if (m_inpImage	!= NULL)
	{
		image_destroy( m_inpImage, 1 );
		m_inpImage = NULL;
	}

	if (m_dynamicBgr	!= NULL)
	{
		delete m_dynamicBgr;
		m_dynamicBgr = NULL;
	}
}


void	CBackgroundRemoval::SetUpdate( int  flag )
{
	m_update = flag;
	if( m_dynamicBgr != NULL )
		m_dynamicBgr->SetUpdate( flag );
}



int CBackgroundRemoval::Init( char *prmFile )
{
	m_iFrame = 0;




	// define dynamic background 
	if( m_dynamic == 1){
		if( m_dynamicBgr == NULL ){
			m_dynamicBgr = new CDynamicBackground();
			m_dynamicBgr->SetUpdate( m_update );

			m_dynamicBgr->SetRgbBackground( m_rgbBackground );
		}
//		else	m_dynamicBgr->DeleteContents();
	}



	m_inpImage		= NULL;



	return( 1 );
}




int CBackgroundRemoval::ProcessFrame0( image_type *sim, image_type *simg, facePose_type *face, int iFrame )
{
int	ret;
	
	m_iFrame++;

	if( m_dynamicBgr != NULL ){
		ret = m_dynamicBgr->ProcessFrame( sim, simg, face, iFrame, &m_bim );
		return( ret );
	}





	if( m_bgRemoval == NULL ){
		m_bgRemoval = new CXtrBgRemoval();
		m_bgRemoval->SetMode(BR_COLOR );//| BR_UPDATE);
//		m_bgRemoval->SetMode(BR_COLOR | BR_UPDATE);
		m_bgRemoval->SetThreshold( m_bg0, m_bg1 );
	}


	m_bgRemoval->UpdateBgImage( simg );


	m_nBgImage++;

	
	
	
	return( 1 );
}

int CBackgroundRemoval::GetSilhouette( image_type **bim )
{
	*bim = m_bim;

	if( m_bim == NULL )
		return( -1 );


	return( 1 );
}

int CBackgroundRemoval::GetBackground( image_type **bim )
{
	if( m_dynamicBgr == NULL ){
		*bim = NULL;
		return( -1 );
	}

	*bim = m_dynamicBgr->GetBackground();

	if( *bim == NULL )
		return( -1 );


	return( 1 );
}


int CBackgroundRemoval::GetRgbBackground( image_type **bim )
{
	if( m_dynamicBgr == NULL ){
		*bim = NULL;
		return( -1 );
	}

	*bim = m_dynamicBgr->GetRgbBackground();

	if( *bim == NULL )
		return( -1 );


	return( 1 );
}


int CBackgroundRemoval::ProcessFrame( image_type *sim, image_type *simg, facePose_type *face, int iFrame )
{
int	ret;

	m_iFrame++;

	if( m_dynamicBgr != NULL ){
		ret = m_dynamicBgr->ProcessFrame( sim, simg, face, iFrame, &m_bim );
		m_backgroundStatus = m_dynamicBgr->GetStatus();

		return( ret );
	}




	if (simg == NULL)
		return 1;



#ifdef _DUMP
	image_dump( simg, "im", m_iFrame );
#endif



	if( m_nBgImage == 0 )
		ProcessFrame0( sim, simg, face, iFrame );
	m_bgRemoval->ProcessFrame( simg, &m_bim );


	return( 1 );
}








static void
image1_filter( image_type *sim )
{
	u_char	*sp,	*sp0;
	u_char	*tp;
	int	i,	j;
	int	sum;
	image_type	*tim;


	//	if( tim == NULL )
	tim = image_create( sim->height, sim->width, 1, 1, NULL );


	for( i = 0 ; i < sim->row ; i++ ){
		sp = IMAGE_PIXEL( sim, i, 0 );
		tp = IMAGE_PIXEL( tim, i, 2 );

		sp0 = sp;
		sum = (*sp++); sum += *sp++;  sum += *sp++;  sum += *sp++;  sum += *sp++;
		*tp++ = sum/5;

		for( j = 3 ; j < tim->column-2 ; j++ ){
			sum = sum + *sp++ - *sp0++;
			*tp++ = sum/5;
		}
	}



	for( j = 0 ; j < sim->width ; j++ ){
		tp = IMAGE_PIXEL( sim, 2, j );
		sp = IMAGE_PIXEL( tim, 0, j );

		sp0 = sp;
		sum =  (*sp); sp += sim->width;
		sum += (*sp); sp += sim->width;
		sum += (*sp); sp += sim->width;
		sum += (*sp); sp += sim->width;
		sum += (*sp); sp += sim->width;

		*tp = sum/5;
		tp += sim->width;

		for( i = 3 ; i < sim->height-2 ; i++ ){
			sum = sum + *sp - *sp0;
			sp += tim->width;
			sp0 += tim->width;

			*tp = sum/5;
			tp += sim->width;
		}
	}

	image_destroy( tim, 1 );
}



static void
image1_filter3( image_type *sim )
{
	u_char	*sp,	*sp0;
	u_char	*tp;
	int	i,	j;
	int	sum;
	image_type	*tim;


	//	if( tim == NULL )
	tim = image_create( sim->height, sim->width, 1, 1, NULL );


	for( i = 0 ; i < sim->row ; i++ ){
		sp = IMAGE_PIXEL( sim, i, 0 );
		tp = IMAGE_PIXEL( tim, i, 1 );

		sp0 = sp;
		sum = (*sp++); sum += *sp++;  sum += *sp++; 
		*tp++ = sum/3;

		for( j = 2 ; j < tim->column-1 ; j++ ){
			sum = sum + *sp++ - *sp0++;
			*tp++ = sum/3;
		}
	}



	for( j = 0 ; j < sim->width ; j++ ){
		tp = IMAGE_PIXEL( sim, 1, j );
		sp = IMAGE_PIXEL( tim, 0, j );

		sp0 = sp;
		sum =  (*sp); sp += sim->width;
		sum += (*sp); sp += sim->width;
		sum += (*sp); sp += sim->width;

		*tp = sum/3;
		tp += sim->width;

		for( i = 2 ; i < sim->height-1 ; i++ ){
			sum = sum + *sp - *sp0;
			sp += tim->width;
			sp0 += tim->width;

			*tp = sum/3;
			tp += sim->width;
		}
	}

	image_destroy( tim, 1 );
}




int CBackgroundRemoval::GetBoxImage( image_type *sim, image_type **im )
{
	m_dynamicBgr->GetBoxImage( m_bim, im );

	return( 1 );
}

int CBackgroundRemoval::GetBoxImage( image_type **im )
{
	m_dynamicBgr->GetBoxImage( im );

	return( 1 );
}

int CBackgroundRemoval::SetTno( int tno )
{
	m_dynamicBgr->SetTno( tno );

	return( 1 );
}




void CBackgroundRemoval::SetUpdateBodyHistogram( int flag )
{
	m_dynamicBgr->SetUpdateBodyHistogram( flag  );
}

void CBackgroundRemoval::SetUseBodyHistogram( int flag )
{
	m_dynamicBgr->SetUseBodyHistogram( flag  );
}

float CBackgroundRemoval::GetUpdatePercent()
{
float	pUpdate;

	pUpdate = m_dynamicBgr->GetUpdatePercent();

	return( pUpdate );
}



void CBackgroundRemoval::Trace( FILE *fp )
{

	if( m_dynamicBgr != NULL )
		m_dynamicBgr->Trace( fp );

}


void CBackgroundRemoval::SetCloseBody( int flag )
{
	if( m_dynamicBgr != NULL )
		m_dynamicBgr->SetCloseBody( flag );

}
image_type * CBackgroundRemoval::GetSilhouetteImage()
{
	return m_dynamicBgr->GetSilhouetteImage();
}

void CBackgroundRemoval::SetSilhouetteUpdate( int flag)
{
	m_dynamicBgr->SetSilhouetteUpdate( flag );
}


void CBackgroundRemoval::SetDbEdge( int flag)
{
	m_dynamicBgr->SetDbEdge( flag );
}


void CBackgroundRemoval::SetDbRgb( int flag)
{
	m_dynamicBgr->SetDbRgb( flag );
}


image_type * CBackgroundRemoval::GetNccImage()
{
	if( m_dynamicBgr == NULL )
		return( NULL );

	return m_dynamicBgr->GetNccImage();

}