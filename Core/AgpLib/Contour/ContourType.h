/**************************
 ***    ContourType.h   ***
 **************************/
 
#ifndef		_CONTOUR_TYPE_H_
#define		_CONTOUR_TYPE_H_


#ifdef __cplusplus
extern "C" {
#endif



#include        "Uigp/igp.h"
#include		"GpType/LinkType.h"


#include		"PlinkType.h"



#define		MAX_POLYLINK	1024


typedef struct contour_type {

//	char	name[64];
	int	type;

	float	scale;
	float	angle;
	vec2d	ctr;

	vec2f_type	v;

	int	no;
	plink_type	*p[MAX_POLYLINK];

} contour_type;



typedef struct contourA_type {
	int	nC;
	int	NC;

	contour_type	**c;

} contourA_type;



contour_type *	contour_alloc();

void	contour_destroy( contour_type *c );


void	contour_set_ctr( contour_type *c );



contour_type *	contour_create( vec2d *ctr, link_type *link, int stat, int Fdata );

contour_type *	contour_createP( plink_type *pl, int Fdata );

contour_type *	contour_create_from_box( box2f_type *b );

void	contour_axis( contour_type *c );


int	contour_add_polylink( contour_type *c, vec2d *ctr, link_type *link,
									int stat, int Fdata );

int	contour_add_plink( contour_type *c, plink_type *pl, int Fdata );

void	contour_plink_destroy( contour_type *c, plink_type *pl );


contour_type *	contour_make_copy( contour_type *sc );

contour_type *	contour_make_copyS( contour_type *sc, int state );


contour_type *	contour_detach_plink( contour_type *sc, int iPlink );



void	contour_affine( contour_type *c, float a, float b, float s, float t );

void	contour_affine_lt2( contour_type *c, lt2_type *lt );


void	contour_affine_estimate( contour_type *c, float a, float b, float s, float t,
									float *dx, float *dy, float *ds, float *da );



void	contour_normelize( contour_type *c );

void	contour_unnormelize( contour_type *c );


void	contour_box( contour_type *c, box2d *box );

void	contour_center( contour_type *c, vec2d *p );

void	contourA_translate( contourA_type *ac, float x, float y );

void	contour_translate( contour_type *c, float x, float y );

void	contour_link_len( contour_type *c, float len );

void	contourA_link_len( contourA_type *ac, float len );



void	contour_translateA( contour_type *c, float x, float y );

void	contourA_clear_anchor( contourA_type *ac );

void	contour_clear_anchor( contour_type *c );

int	contour_is_point_inside( contour_type *c, vec2f_type *p );

void	contour_set_dirrection( contour_type *c );

void	contour_set_range( contour_type *c );

int		contour_check_cross( contour_type *c, float d_min, vec2f_type *mp );


void	contour_simplify( contour_type *c );

void	contour_simlifay_len( contour_type *c, float minLen, float maxLen );


contour_type *	contour_union( contour_type *ac, contour_type *c );

void	contour_inverse( contour_type *c );

float	contour_distance( contour_type *c, vec2d  *p, struct dLink_type *d );


contour_type *	contour_detach_transparent( contour_type *c );


	// ContourArea.c
float	contour_area( contour_type *c );

float	contour_areaS( contour_type *c );


	// ContourRead.c
int	contourA_read_from_file( char *file, contourA_type **ac );

int	contour_read_from_file( char *file, contour_type **c );

int	contour_read_from_buffer( char *data, int dataSize, contour_type **c1 );


	// ContourWrite.c
int	contourA_write_to_file( contourA_type *ac, char *file );

int	contour_write_to_file( contour_type *c, char *file );

int	contour_write_to_buffer( contour_type *c, char **data, int *dataSize );


	// ContourDump.c
void	contourA_dump( contourA_type *ac, char *prefix, int index, char *suffix );

void	contour_dump( contour_type *c, char *prefix, int index, char *suffix );

void	plink_dump( plink_type *pl, char *prefix, int index, char *suffix );


void	contour_dump_link( vec2f_type *ctr, link_type *link, char *prefix, int index, char *suffix );



	// ContourLt2.c
contour_type *	contour_lt2( contour_type *sc, lt2_type *lt, contour_type *c );

contour_type *	contour_scale( contour_type *sc, float scale, contour_type *c );

void	contourA_scale( contourA_type *ac, float scale, float maxLen );

void	contourA_scale_size( contourA_type *ac, float scale );


	// ContourflipH.c
contour_type * contour_flipH( contour_type *sc, float width, contour_type *c );

void	contour_set_aux( contour_type *c );


	// ContourImageMask.c
struct image_type *	contourA_image_mask( contourA_type *ac, int width, int height, struct image_type *im );

struct image_type *	contour_image_mask( contour_type *c, int width, int height, struct image_type *im );
struct image_type *	contour_image_maskN( contour_type *c, int width, int height, struct image_type *im );


	// ContourArray.c
contourA_type *	contourA_alloc( int nc );

void	contourA_destroy( contourA_type *ac );

void	contourA_clear( contourA_type *ac );


void	contourA_add( contourA_type *ac, contour_type *c );

void	contourA_append( contourA_type *ac, contourA_type *sac );

contourA_type *	contourA_make_copy( contourA_type *sac );

contourA_type *contourA_copy( contourA_type *sac, int type  );


contourA_type *	contourA_get( contourA_type *sac, int type, int detach );

int	contourA_no( contourA_type *ac, int type );

int	contourA_select( contourA_type *ac, int type, vec2f_type *p );

contour_type *	contourA_detouch( contourA_type *ac, int i );


contourA_type *	contour_split( contour_type *c );

contourA_type *	contourA_lt2( contourA_type *sac, lt2_type *lt );

	// ContourOverlap.c
float	contour_overlap( contour_type *c1, contour_type *c2, float dis );



	// ContourCircle.c
contour_type *	contour_from_circle( float R, float d );

contour_type *	contour_from_point( vec2f_type ap[], int nP, int Fclose );

plink_type *	plink_from_point( vec2f_type ap[], int nP, int Fclose );



	// PlinkUnion.c
int	contourA_union( contourA_type *ac );

int	contourC_union( contour_type *c );




	// ContourRadius.c 
float	contour_radius( contour_type *c );




#ifdef _DUMP
#define CONTOURA_DUMP( c, prefix, index, suffix )	contourA_dump( c, prefix, index, suffix )
#define CONTOUR_DUMP( c, prefix, index, suffix )	contour_dump( c, prefix, index, suffix )
#define PLINK_DUMP( c, prefix, index, suffix )	plink_dump( c, prefix, index, suffix )
#else
#define CONTOURA_DUMP( c, prefix, index, suffix )
#define CONTOUR_DUMP( c, prefix, index, suffix )
#define PLINK_DUMP( c, prefix, index, suffix )
#endif



#ifdef __cplusplus
}
#endif

#endif 
