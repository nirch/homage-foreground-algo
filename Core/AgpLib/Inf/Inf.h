#ifndef		_INF_
#define		_INF_


#ifdef __cplusplus
extern "C" {
#endif

#include        "GpType/GpType.h"

	/* InfAgp.c  */

void	inf_agp_init();

void	inf_agp( gp_array *agp );

void	inf_agp_print( FILE *fp );


#ifdef __cplusplus
}
#endif

#endif /* #ifndef _INF_ */
