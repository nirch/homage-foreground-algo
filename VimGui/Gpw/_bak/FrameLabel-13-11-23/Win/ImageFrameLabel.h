// Vimage.h: interface for the CVimage class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _IMAGE_FRAME_LABEL_
#define _IMAGE_FRAME_LABEL_

#include <windows.h>
#include "UVec/Vec2d.h"
#include "Ubox/Box2d.h"

#include "../FrameLabel.h"


#define TEXT_LEN 512

class CImageFrameLabel : public CFrameLabel
{
public:
		CImageFrameLabel();

		virtual ~CImageFrameLabel();


		int Init( char *file );

		int  Init( HBITMAP hBitmap, int fx, int fy );

		int  Init( HINSTANCE hInstance, int ID, int fx, int fy );


		void Draw( HDC hdc );

		int HandleLButtonUp(u_int nFlags, int x, int y );

public:


private:

	HDC m_hdc;


	HBITMAP m_hBitmap;

	int	m_width;
	int	m_height;


	class CDib *m_dib;

};




#endif