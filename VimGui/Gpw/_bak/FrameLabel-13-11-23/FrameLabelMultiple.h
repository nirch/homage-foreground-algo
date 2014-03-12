// Vimage.h: interface for the CVimage class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _FRAME_LABEL_MULTIPLE_
#define _FRAME_LABEL_MULTIPLE_

#include "Uigp/igp.h"
#include "UVec/Vec2d.h"

#include "FrameLabel.h"


class CFrameLabelMultiple : public CFrameLabel
{
public:
		CFrameLabelMultiple();

		virtual ~CFrameLabelMultiple();



public:

	virtual int Init( char *file );
    
    virtual int Init( int x, int y, char *file );
    
    

	virtual int Draw()	{ return(0); }


    virtual void SetFocus( int x, int y );
    
    
    virtual void Set( int visable, int x, int y );
    
    
    virtual void SetBasePose( int x, int y );

	virtual void SetPose( float x, float y );
    virtual void SetPose( vec2f_type *p );
    
    virtual void SetMove( int x, int y );
    
    virtual void StartMove( int x, int y );
    
    virtual void MoveTo( int x, int y );
    
    
    


	virtual void GetPose( int *x, int *y );
    virtual void GetPose( float *x, float *y );
    
    virtual void GetPose( vec2f_type *p );
    


	virtual void SetShow( int flag )	{ m_show = flag; }

	virtual void SetDrag( int flag )	{ m_drag = flag; }
    
    virtual void SetScale( float scale )    { m_scale = scale; }
    


    int m_fx;
    int m_fy;
    
	float	m_x;
	float	m_y;
    
    float m_x0;
    float m_y0;

	int	m_show;

	int m_drag;
    
    float m_scale;
    
    
    
    int m_mx;
    int m_my;
    
    


};




#endif