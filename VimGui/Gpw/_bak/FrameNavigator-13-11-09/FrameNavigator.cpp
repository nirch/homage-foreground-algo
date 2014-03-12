/******************************
 ***   FrameNavigator.cpp   ***
 ******************************/


#include "FrameNavigator.h"



CFrameNavigator::CFrameNavigator( int wWidth, int wHeight, int width, int height )
{
	m_sWidth = wWidth;
	m_sHeight = wHeight;

	//m_width = width;
	//m_height = height;


	//m_b.x0 = 0;
	//m_b.x1 = m_width;

	//m_b.y0 = 0;
	//m_b.y1 = m_height;

	//m_scale = m_sWidth / (float)( m_b.x1 - m_b.x0);

	SetSize( width, height );
}



CFrameNavigator::~CFrameNavigator()
{
}



void CFrameNavigator::SetWinSize( int width, int height )
{
	m_sWidth = width;
	m_sHeight = height;
}

void CFrameNavigator::SetSize( int width, int height )
{
	m_width = width;
	m_height = height;

	m_b.x0 = 0;
	m_b.x1 = m_width;

	m_b.y0 = 0;
	m_b.y1 = m_height;

	m_scale = m_sWidth / (float)( m_b.x1 - m_b.x0);
}

int CFrameNavigator::Move( vec2i_type p0[], vec2i_type p1[], int n )
{
	if( n == 2 ){
		Move2( &p0[0], &p1[0],  &p0[1], &p1[1] );
		return( 1 );
	}

	if( n == 1 ){
		Move( &p0[0], &p1[0] );
		return( 1 );
	}

	return( -1 );
}


int CFrameNavigator::Move( vec2i_type *p0, vec2i_type *p1 )
{


	int	dx = p1->x - p0->x;
	int dy = p1->y - p0->y;

	
	m_b.x0 += dx;
	m_b.x1 += dx;
	m_b.y0 += dy;
	m_b.y1 += dy;


	PushTo();

	return( 1 );
}



int CFrameNavigator::Move2( vec2i_type *p0, vec2i_type *p1, vec2i_type *q0, vec2i_type *q1 )
{
float	a0,	b0;
float	a1,	b1;

	a0 = (q1->x - p1->x )/ (float)( q0->x - p0->x);
	b0 = p1->x - a0 *p0->x;
    
    float t0 = a0 * p0->x + b0;
    float t1 = a0 * q0->x  + b0;

	a1 = (q1->y - p1->y )/ (float)( q0->y - p0->y);
	b1 = p1->y - a1 *p0->y;
    
    
    float t2 = a1 * p0->y + b1;
    float t3 = a1 * q0->y  + b1;


	m_b.x0 = (int)(a0*m_b.x0 + b0 + 0.5);
	m_b.x1 = (int)(a0*m_b.x1 + b0 + 0.5);

	m_b.y0 = (int)(a1*m_b.y0 + b1 + 0.5);
	m_b.y1 = (int)(a1*m_b.y1 + b1 + 0.5);



	PushTo();

	return( 1 );

}

void CFrameNavigator::PushTo()
{
int	t;

	if( m_b.x1 - m_b.x0 > m_width ){
		m_b.x0 = 0;
		m_b.x1 = m_width;
	}



	if( m_b.x0 < 0 ){
		m_b.x1 += -m_b.x0;
		m_b.x0 = 0;
	}
	if( m_b.x1 > m_width ){
		t = m_b.x1 - m_width;
		m_b.x0 -= t;
		m_b.x1 -= t;
	}





	if( m_b.y1 - m_b.y0 > m_height ){
		m_b.y0 = 0;
		m_b.y1 = m_height;
	}


	if( m_b.y0 < 0 ){
		m_b.y1 += -m_b.y0;
		m_b.y0 = 0;
	}
	if( m_b.y1 > m_height ){
		t = m_b.y1 - m_height;
		m_b.y0 -= t;
		m_b.y1 -= t;
	}


	m_scale = m_sWidth / (float)( m_b.x1 - m_b.x0);
}



