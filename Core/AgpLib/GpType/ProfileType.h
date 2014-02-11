/**************************
 ***	ProfileType.h   ***
 **************************/

#ifndef         PROFILE_TYPE
#define         PROFILE_TYPE

#include	"Uigp/igp.h"


#include	"Uvec/Vec2d.h"


#include	"RidgeType.h"
#include	"EdgeType.h"
#include	"N3Type.h"





typedef struct pskl_type {
	float	depth;
//	float	rdepth;

}	profileT_type;



typedef union {
	ridge_type      *ridge;
	edge_type       *edge;
	n3_type       *n3;

	profileT_type    *p;

}	profile_type;






profile_type    profile_alloc( int type );
profile_type    profile_make_copy( profile_type ppr, int type );

void	profile_afine( int type, profile_type pr0, profile_type pr1,
						float t, profile_type pr );
	
void	profile_copy_inverse( int type, profile_type spr, profile_type tpr );
void	profile_copy( int type, profile_type spr, profile_type tpr );

#endif
