/************************
 ***    AttPrm.h      ***
 ************************/
 
#ifndef         _ATT_PRM_H_
#define         _ATT_PRM_H_


#ifdef __cplusplus
extern "C" {
#endif

#include        "Uigp/igp.h"
#include		"Uprm/prm.h"




typedef struct attPrm_type {
	int		step;
	float	radius1;
	float	radius0;
	float	radius;

	float	cover;

	float	minLen;

	//float	minDt1;
} attPrm_type;






void mold_attPrm_init( attPrm_type *attPrm );



#ifdef __cplusplus
}
#endif

#endif //_MOLD_H_
 