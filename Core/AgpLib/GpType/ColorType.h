/***********************
 ***	ColorType.h   ***
 ***********************/

#ifndef         COLOR_TYPE
#define         COLOR_TYPE

#include	"Configuration.h"


#define		SP_Y	0
#define		SP_Q	1
#define		SP_A	2


#define		SP_R	0
#define		SP_G	1
#define		SP_B	2


/*
#define	QSHORT
define	in Configuration.h
*/




#ifdef QSHORT
typedef short qcolor_type;

#define COLOR_SFP	4
#define	COLOR_F2FP	16
#define QCOLOR_UNIT	16


#define	QCOLOR2F( a )	( (a) * 0.0625 )
#define	F2QCOLOR( a )	( (int)((a) * 16.0) )

#define	I2QCOLOR( a )	( ((int)(a))<<4)

#endif




#ifdef QFLOAT
typedef float qcolor_type;
 
#define QCOLOR_UNIT     1
 
#define QCOLOR2F( a )   ( a )
#define F2QCOLOR( a )   ( a )
#define I2QCOLOR( a )   ( a )
 
#endif


#define QCOLOR_RGB2Y( c )	((qcolor_type)(0.29900*c[0] + 0.58700*c[1] + 0.11400*c[2]))

#endif
