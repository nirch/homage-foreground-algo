/***********************
 ***   N3AuxType.h   ***
 ***********************/

#ifndef		_N3_AUX_IN_
#define		_N3_AUX_IN_

#include	"GpType/GpType.h"
#include	"N3AuxType.h"


	// N3AuxTool.c
void	n3_aux_no( gp_array *agp, int *n3_no, int *in_no, int *link_no );


	// N3AuxIn.c
void	n3_aux_in( gp_array *agp, n3Aux_type *na );

void	n3_aux_in_set( jnt_type *jnt, int bno, n3Aux_type *na );

void	n3Aux_reorder_in( n3Aux_type *na );



	// N3AuxInNull.c
void	n3_aux_in_null( n3Aux_type *na );
void	n3_aux_in_nullO( gp_array *agp );

	// N3AuxJnt.c
void	n3_aux_jnt( gp_array *agp );

	// N3AuxInDegenric.c
void	n3_aux_in_degenric( n3Aux_type *na );


	// N3AuxLink.c
void	n3_aux_link( n3Aux_type *na );


	// N3AuxProfile.c
edge_type *	n3_aux_profile( link_type *link, int side, int direct );

edge_type *	n3_aux_profile_in( link_type *link, int side, float t0 );

edge_type *	n3_aux_profile1( jnt_type *jnt, int bno, int side, int flag );

edge_type *	n3_aux_profile11( jnt_type *jnt, int bno, int direct );

#endif
