/***********************
 ***   VimLib.h   ***
 ***********************/


#ifndef _VIM_LIB_H_
#define _VIM_LIB_H_




#if defined _DEBUG || defined DEBUG
#pragma comment( lib, "AgpD.lib" )
#pragma comment( lib, "UtilD.lib" )
#pragma comment( lib, "ImageD.lib" )
#else
#pragma comment( lib, "Agp.lib" )
#pragma comment( lib, "Util.lib" )
#pragma comment( lib, "Image.lib" )
#endif


#endif