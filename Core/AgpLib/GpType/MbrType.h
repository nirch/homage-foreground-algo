/**********************
 ***	 MbrType.h	***
 **********************/
  
#ifndef		_MBR_TYPE_
#define		_MBR_TYPE_

#include	"Uigp/igp.h"

#ifdef __SYMBIAN32__
#define	LAYER32
#endif


#ifdef	LAYER32
#define	MAX_LAYER_BIT	32
typedef u_int	mbr_type;
#else

#define MAX_LAYER_BIT	63

#ifdef WIN32
#define MAX_LAYER_BIT	63
typedef _int64	mbr_type;
#else
typedef long long mbr_type;
#endif
#endif


#define	MBR_BIT( br )	(((mbr_type)1)<<br)
#define	MBR_SET( mbr, br )		( mbr |= (((mbr_type)1)<<br) )
#define	MBR_IS_SET( mbr, br )	( mbr & (((mbr_type)1)<<br) )


#endif
