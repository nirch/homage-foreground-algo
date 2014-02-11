/*****************************
 ***	DepthModelType.h   ***
 *****************************/

#ifndef		_DEPTH_MODEL_TYPE_
#define		_DEPTH_MODEL_TYPE_

#ifdef __cplusplus
extern "C" {
#endif


#include	"DmPlaneType.h"
#include	"DmCornerType.h"
#include	"DmBottleType.h"



#define		DM_PLANE	1
#define		DM_CORNER	2
#define		DM_BOTTLE	3



typedef struct dmBase_type {

	int type;

	int	iLayer;	

}	dmBase_type;



typedef union dm_type {

	dmBase_type		*b;

	struct dmPlane_type		*plane;

	struct dmCorner_type	*corner;

	struct dmBottle_type	*bottle;

}	dm_type;


/*
typedef struct depthModel_type {

	int type;

	int	iLayer;	

	union {
		struct dmPlane_type	*plane;
		struct dmCorner_type	*corner;
		struct dmBottle_type		*bottle;
	} p;

}	depthModel_type;
*/



typedef struct dmArray_type {
	int	size;	// array size
	int	nDm;

	dm_type	*dm;

}	dmArray_type;


/*
	// DepthModel.c 
depthModel_type	* depthModel_alloc( int type );


void	depthModel_destroy( depthModel_type *dm );
*/


	// DmTool.c
dm_type		dm_alloc( int type );

void	dm_destroy( dm_type dm );

dm_type	dm_make_copy( dm_type sdm );

void	dm_aux( dm_type dm, view_type *vw );

float	dm_depth( dm_type dm, vec2d *v );



dmArray_type	* dmArray_alloc( int size );

void	dmArray_destroy( dmArray_type *dmArray );

dmArray_type *	dmArray_copy( dmArray_type *sadm, int mbr );

void	dmArray_append( dmArray_type **adm, dmArray_type *sadm );

void	dmArray_merge( dmArray_type **padm, dmArray_type *sadm );	// sadm is delete





void	dmArray_resize( dmArray_type *dmArray, int size );

void	dmArray_remove( dmArray_type *adm, int mbr );


void	dmArray_insert( dmArray_type **adm, dm_type dm );

dm_type	dmArray_get( dmArray_type *adm, int layer, int Fcopy );



void	dmArray_set_plane( dmArray_type **adm, int iLayer, vec3d *N, float depth );

void	dmArray_layerId_renumbering( dmArray_type *adm, int aId[] );

void	dmArray_layerId_order( dmArray_type *adm );


void	dmArray_layerId_add( dmArray_type *adm, int delta );


void	dmArray_flipH( view_type *vw, dmArray_type *adm );

void	dmArray_flipV( view_type *vw, dmArray_type *adm );


void	dmArray_global_plane( view_type *vw, dmArray_type *adm, vec3d *N, vec3d *P );
int		dmArray_get_plane( dmArray_type *adm, int layer, vec3d *N, float *depth );


int		dmArray_depth_value( view_type *vw, dmArray_type *adm, int layer, vec2d *p, float *depth );



#ifdef __cplusplus
}
#endif

#endif
