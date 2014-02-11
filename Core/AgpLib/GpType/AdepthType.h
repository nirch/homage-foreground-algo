/*************************
 ***	AdepthType.h   ***
 *************************/
#ifndef         _ADEPTH_TYPE_
#define         _ADEPTH_TYPE_

#include	"Uigp/igp.h"

#include	"Uview/ViewType.h"

#include	"MbrType.h"



#define		MAX_BR	30



typedef struct adepth_type {

	view_type	*vw;

	vec3d	N,	P;



	struct dmArray_type	*adm;

	mbr_type	Mbr;

}	adepth_type;





adepth_type *	adepth_alloc();



void	adepth_destroy( adepth_type *ad );

adepth_type * 	adepth_copy( adepth_type *ad );

adepth_type *	adepth_copy_sub( adepth_type *ad, int mbr );

void	adepth_append( adepth_type *ad, adepth_type *sad );


void	adepth_delete_layer( adepth_type *ad, int mbr );




adepth_type *	adepth_default( float depth, int row, int column );

//void	adepth_set_plane( adepth_type *ad, int layer, vec3d *N, vec3d *P );

void	adepth_set_planeD( adepth_type *ad, int layer, vec3d *N, float depth );

void	adepth_set_planeND( adepth_type *ad, int layer, float depth );

int	adepth_get_plane( adepth_type *ad, int layer, vec3d *N, float *d );

void	adepth_rescale( adepth_type *ad, float fk );

void	adepth_global_plane( adepth_type *ad );


#endif
