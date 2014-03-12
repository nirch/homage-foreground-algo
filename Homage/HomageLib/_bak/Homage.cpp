// Brandwit.cpp: implementation of the CHomage class.
//
//////////////////////////////////////////////////////////////////////

#include <math.h>
#include <string.h>



#ifdef _DEBUG
#define _DUMP
#endif

#include "Uigp/igp.h"
#include "Ulog/Log.h"
#include "Uln/PlnType.h"

#include "Gpw/Gpw.h"


#include "Homage.h"


CHomage::CHomage( CFrameBuffer *fb )
{
	m_fb = fb;

	m_im = NULL;


	gpTime_init( &m_gTime );
    
   
}



CHomage::~CHomage()
{



	if( m_im != NULL ){
		image_destroy( m_im, 1 );
		m_im = NULL;
	}




	DeleteContents();
}






void CHomage::DeleteContents()
{


}











int CHomage::Init() 
{

	gpTime_init( &m_tProcess );
    

	return( 1 );
}






int CHomage::Process( image_type *im, int iFrame )
{
    

	m_fb->Set( m_im );
    
    
    
	return( 1 );
}




