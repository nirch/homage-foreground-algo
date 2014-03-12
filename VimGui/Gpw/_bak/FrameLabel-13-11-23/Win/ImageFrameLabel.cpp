/******************************
 ***   TextFrameLabel.cpp   ***
 ******************************/

#include "Utime/GpTime.h"
#include "ImageFrameLabel.h"

#include "Wutil/UWdib/Cdib.h"

#include "ImageType/ImageType.h"

#include "ImageCodec/ImageRead.h"
#include "Png\PngCodec\Png\ImageReadPng.h"



static void	imageT_PreAlpahBlend( image_type *sim );

CDib * Create_Dib( image_type *im );



CImageFrameLabel::CImageFrameLabel()
{

	m_hdc = NULL;
	m_hBitmap = NULL;


}



CImageFrameLabel::~CImageFrameLabel()
{

}



int  CImageFrameLabel::Init( char *inFile )
{
image_type	*sim;

//	if( (sim = image_read_file( inFile )) == NULL )
	if( (sim = image_read_png_file( inFile )) == NULL )
		return( -1 );

	imageT_PreAlpahBlend( sim );


//	m_dib = Create_Dib( sim );



	m_hBitmap = CreateBitmap( sim->width, sim->height, 1, 32, sim->data );


//	m_dib = CDib

	m_width = sim->width;
	m_height = sim->height;

	image_destroy( sim, 1 );

	return( 1 );
}


int  CImageFrameLabel::Init( HINSTANCE hInstance,  int ID, int fx, int fy )
{
	HBITMAP hb = LoadBitmap( hInstance, MAKEINTRESOURCE(ID) );
	if( hb == NULL )	return( -1 );

	int ret = Init( hb, fx, fy );
	return( ret );
}


int  CImageFrameLabel::Init( HBITMAP hBitmap, int fx, int fy )
{
	m_hBitmap = hBitmap;

	BITMAP bm;
	::GetObject( m_hBitmap, sizeof( bm ), &bm );
	m_width = bm.bmWidth;
	m_height = bm.bmHeight;

	SetFocus( fx, fy );

	return( 1 );
}





CDib * Create_Dib( image_type *im )
{

	CDib *dib = new CDib( im->height, im->width, 32 );
	dib->CreateSection();

	dib->data_image( im, 0 );

	image_destroy( im, 0 );


	return( dib );
}


typedef struct argb_type {
	u_char	b;
	u_char	g;
	u_char	r;
	u_char	a;
} rgba_type;


static void
imageT_PreAlpahBlend( image_type *sim )
{
int	i,	j;

	rgba_type *sp = (rgba_type *)sim->data;
	for( i = 0; i < sim->height ; i++ ){
		for( j = 0; j < sim->width ; j++, sp++ ){

			sp->a = 255 - sp->a;
			if( sp->a == 0 ){
				sp->r = sp->g = sp->b = 0;
				continue;
			}

			if( sp->r == 0 && sp->g == 0 && sp->b == 0 ){
				sp->a = 0;
				continue;
			}


			sp->r = (sp->r *sp->a)/255.0;
			sp->g = (sp->g *sp->a)/255.0;
			sp->b = (sp->b *sp->a)/255.0;
		}
	}

}




void CImageFrameLabel::Draw( HDC hdc )
{
	if( m_show == 0 )
		return;

	if( m_hdc == NULL ){
		m_hdc =  ::CreateCompatibleDC( hdc );

		HGDIOBJ hOld = ::SelectObject( m_hdc, m_hBitmap );
	}


	BLENDFUNCTION ftn;
	ftn.BlendOp = AC_SRC_OVER;
	ftn.BlendFlags = 0;
	ftn.SourceConstantAlpha = 255;//(BYTE)(m_transparent *255);
	ftn.AlphaFormat = AC_SRC_ALPHA;//0;


	AlphaBlend( hdc, m_x - m_fx, m_y - m_fy, m_width, m_height, 
				m_hdc, 0, 0, m_width, m_height,
				ftn );

}





int CImageFrameLabel::HandleLButtonUp(u_int nFlags, int x, int y )
{

	//x -= m_x0;
	//y -= m_y0;


	//if( m_show == 1 ){
	//	if( BOX2D_IS_IN( m_xBox, x, y ) ){
	//		SetShow( 0 );
	//		return( 1 );
	//	}
	//}

	return( -1 );
}




