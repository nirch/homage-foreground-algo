/*************************
 ***    N3PrimeIn.h    ***
 *************************/

#ifndef		_N3_PRIME_IN_
#define		_N3_PRIME_IN_

#include	"GpType/GpType.h"

	/* N3PrimeLink.c */
void	n3_prime_link_seg( vec2d *ctr, link_type *link, int side, in_type *in0,
				link_type *link1, in_type *in1,
				jnt_type *jnt0, jnt_type *jnt1, width_type width[] );

link_type *	n3_prime_link_in( vec2d *ctr, link_type *l, int side,
				vec2d *ctr0, in_type *in0,
				vec2d *ctr1, in_type *in1, width_type width[] );

void	n3_prime_link_connect_jnt( jnt_type *jnt, link_type *link, int direct );


	/* N3PrimeProfile.c */
edge_type *	n3_prime_profile( link_type *link, int side, int direct );

edge_type *	n3_prime_profile_in( link_type *link, int side, float t0 );

edge_type *	n3_prime_profile1( jnt_type *jnt, int bno, int side, int flag );

edge_type *	n3_prime_profile11( jnt_type *jnt, int bno, int direct );



	/* N3PrimeInNull.c */
void	n3_prime_in_null( gp_array *agp );

void	n3_prime_in_null_init( gp_array *agp );

#endif
