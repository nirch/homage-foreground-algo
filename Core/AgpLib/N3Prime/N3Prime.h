/***********************
 ***    N3Prime.h    ***
 ***********************/

#ifndef		_N3_PRIME_
#define		_N3_PRIME_

#include	"GpType/GpType.h"


	/* N3Prime.c */
void	n3_prime_agp( gp_array *agp );


	/* N3PrimeFree.c */
void	n3_prime_free( gp_array *agp );


	/* N3PrimeLoad.c */
void	n3_prime_load( gp_array *agp );


	/* N3PrimeN3ToEdge.c */
void	n3_prime_n3_to_edge( gp_array *agp );

#endif
