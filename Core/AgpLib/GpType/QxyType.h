/**********************
 ***	QxyType.h   ***
 **********************/

#ifndef         QXY_TYPE
#define         QXY_TYPE

#include	"Configuration.h"
#include        "Uvec/Vec2d.h" 


//#define QXY_FLOAT
#define QXY_SHORT


#ifdef QXY_SHORT
typedef short qxy_type;

#define QXY_SFP		4
#define	QXY_F2FP	16
#define QXY_UNIT	16


#define	QXY2F( a )	( (a) * 0.0625 )
#define	F2QXY( a )	( (int)((a) * 16.0) )


typedef struct vec2dF {
        qxy_type        x;
        qxy_type        y;
} vec2dF;


#endif




#ifdef QXY_FLOAT
typedef float qxy_type;
 
#define QXY_UNIT     1
 
#define QXY2F( a )   ( a )
#define F2QXY( a )   ( a )


typedef vec2d  vec2dF;

 
#endif



/*
#define	F2QXY16( a )	(((int)(a*16))*0.0625)
#define	F2QXY16( a )	(a)

#define F2QXY16( a )           ( ( (a) < 0 )?  \
                                (( ((int)((a)*8)) - 0.5) *0.125 ) : \
                                (( ((int)((a)*8)) + 0.5) *0.125 ) )
*/


#define F2QXY16( a )           (( ((int)((a)*8)) + 0.5) *0.125 )






#endif
