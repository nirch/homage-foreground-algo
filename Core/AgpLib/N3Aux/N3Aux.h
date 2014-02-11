/*******************
 ***   N3Aux.h   ***
 ******************/

#ifndef		_N3_AUX_
#define		_N3_AUX_

#ifdef __cplusplus
extern "C" {
#endif

#define		N3_AUX_VER0		0	// == 0x0007
#define		N3_AUX_VER1		1	// == 0x0007


#include	"GpType/GpType.h"


	// N3Aux.c
void	n3_aux( gp_array *agp, int version, int Fclear );


void	n3_aux_clear( gp_array *agp );

	
	// N3AuxLoad.c
void	n3_aux_load( gp_array *agp );



	// N3AuxFree.c
void	n3_aux_free( gp_array *agp );




#ifdef __cplusplus
}
#endif


#endif
