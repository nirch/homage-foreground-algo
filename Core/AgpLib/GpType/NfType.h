/**********************
 ***    NfType.h    ***
 *********************/
 
#ifndef         _NF_TYPE_ 
#define         _NF_TYPE_

#include	"LinkType.h"



#define		NF_TYPES	10

#define		NF_HUNCH	0x00
#define		NF_RH		0x01
#define		NF_RIDGE	0x02
#define		NF_EDGE		0x03
#define		NF_N3		0x04
#define		NF_N3R		0x06
#define		NF_JNT		0x07

#define		NF_N3_P		0x09
#define		NF_N3_J		0x11	// 

#define		NF_IS_EDGE( type )	( type & 0x01 )


#endif
