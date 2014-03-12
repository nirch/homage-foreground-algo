/***************************
 ***   FrameLabel.cpp   ***
 ***************************/


#include "FrameLabel.h"



CFrameLabelMultiple::CFrameLabelMultiple()
{
    m_fx = 0;
    m_fy = 0;
    
    m_scale = 1.0;
}



CFrameLabelMultiple::~CFrameLabelMultiple()
{

}







int  CFrameLabelMultiple::Init( char *file )
{
	//m_drag = drag;

	return( 1 );

}

int  CFrameLabelMultiple::Init( int x, int y, char *file )
{
	//m_drag = drag;
    
	return( 1 );
    
}


void CFrameLabelMultiple::SetFocus( int x, int y )
{
    m_fx = x;
    m_fy = y;
}


void CFrameLabelMultiple::Set( int visable, int x, int y )
{
    SetBasePose( x, y );
    
    SetShow( visable );
}


void CFrameLabelMultiple::SetBasePose( int x, int y )
{
    m_x0 = x;
    m_y0 = y;
    
    SetPose( m_x0, m_y0 );
}

void CFrameLabelMultiple::SetPose( float x, float y )
{
	m_x = x;
	m_y = y;
}

void CFrameLabelMultiple::SetPose( vec2f_type *p )
{
    int x = p->x;
    int y = p->y;
    
    SetPose( x, y );
}


void CFrameLabelMultiple::StartMove( int x, int y )
{
    m_mx = x;
    m_my = y;
}


void CFrameLabelMultiple::MoveTo( int x, int y )
{
    
    SetMove( x - m_mx, y - m_my );
    m_mx = x;
    m_my = y;
}



void CFrameLabelMultiple::SetMove( int ix, int iy )
{
float   x,  y;
//	m_x = x;
//	m_y = y;
    
    
    x = ix / m_scale;
    y = iy / m_scale;
    
    
    
    
    m_x0 += x;
    m_y0 += y;
    
    SetPose( x + m_x, y + m_y );
}


void CFrameLabelMultiple::GetPose( int *x, int *y )
{
	*x = m_x0;
	*y = m_y0;
}

void CFrameLabelMultiple::GetPose( float *x, float *y )
{
	*x = m_x0;
	*y = m_y0;
}

void CFrameLabelMultiple::GetPose( vec2f_type *p )
{
	p->x = m_x0;
	p->y = m_y0;
}

