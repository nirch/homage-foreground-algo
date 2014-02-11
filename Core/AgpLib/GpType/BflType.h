/**************************
 ***	 ZpType.h	***
 **************************/
  
#ifndef		_BFL_TYPE_
#define		_BFL_TYPE_

#include	"Uigp/igp.h"


#define BF32

#ifdef BF32
typedef struct  bfL_type {

	u_int	f0;
}	bfL_type;




#define		BFL_CLEAR( b )		( (b).f0 = 0 )

#define		BFL_IS_CLEAR( bf )	( (bf).f0 == 0 )

#define		BFL_SET_BIT( b, i )		( (b).f0 |= ( 1L<<i ))

#define		BFL_IS_BIT_SET( b, i )	( (b).f0 & ( 1L<<i ))

#define		BFL_SET_OR( bf, b )	((bf).f0 |= (b).f0 ) 
#define		BFL_SET( bf, b )	((bf).f0 |= (b).f0 ) 

#define		BFL_UNSET( bf, b )	((bf).f0 &= ~(b).f0 ) 

#define		BFL_AND( b, b1 )		( (b).f0 & (b1).f0 )


#define		BFL_EQUAL( b, b1 )		( (b).f0 == (b1).f0 )



#define		BFL_IS_IN( b, b1 )		( ( (b).f0 & (b1).f0 ) == (b1).f0 )

#endif



#ifdef BF64
typedef struct  bfL_type {

	u_int	f0;
	u_int	f1;
}	bfL_type;




#define		BFL_CLEAR( bf )		( bf.f0 = bf.f1 = 0 )
#define		BFL_IS_CLEAR( bf )	( bf.a0 == 0 && bf.a1 == 0)

#define		BFL_SET_BIT( b, i )		if( i < 32 )	b.f0 | = ( 1<<i ); \
									else	b.f1 |= ( 1 << ( i - 32 );
#define		BFL_IS_BIT_SET( b, i )		( i < 32 ) ? ( b.f0 & ( 1<<i )) : ( b.f1 & ( 1<<(i-32) )) )


#define		BFL_SET_OR( bf, b )	((bf).f0 |= (b).f0, (bf).f1 |= (b).f1  ) 
#define		BFL_SET( bf, b )	((bf).f0 |= (b).f0, (bf).f1 |= (b).f1  ) 

#define		BFL_UNSET( bf, b )	((bf).f0 &= ~(b).f0, (bf).f1 &= ~(b).f1 ) 

#define		BFL_AND( b, b1 )		( ((b).f0 & (b1).f0) || ((b).f1 & (b1).f1) )


#define		BFL_EQUAL( b, b1 )		( (b).f0 == (b1).f0 && (b).f1 == (b1).f1 )



#define		BFL_IS_IN( b, b1 )		( ( (b).f0 & (b1).f0 ) == (b1).f0 && ( (b).f1 & (b1).f1 ) == (b1).f1 )


#endif





#endif
