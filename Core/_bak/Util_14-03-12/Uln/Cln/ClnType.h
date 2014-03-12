/**********************
 ***    ClnType.h   ***
 **********************/
 
#ifndef		_CLN_TYPE_H_
#define		_CLN_TYPE_H_


#ifdef __cplusplus
extern "C" {
#endif



#include        "Uigp/igp.h"

#include		"../PlnType.h"



#define		MAX_PLN		32


typedef struct cln_type {

	int iFrame;

	int	type;

	float	scale;
	float	angle;
	vec2d	ctr;
	vec2f_type	v;

	int	nA;
	pln_type	*a[MAX_PLN];

} cln_type;



typedef struct clnA_type {
	int	nC;
	int	NC;

	cln_type	**c;

} clnA_type;



cln_type *	cln_alloc();

void	cln_destroy( cln_type *c );


void	cln_set_ctr( cln_type *c );



cln_type *	cln_create( pln_type *pl, int Fdata );


void	cln_axis( cln_type *c );


int	cln_add( cln_type *c, pln_type *pl, int Fdata );

void	cln_plink_destroy( cln_type *c, pln_type *pl );


cln_type *	cln_make_copy( cln_type *sc );

cln_type *	cln_make_copyS( cln_type *sc, int state );


cln_type *	cln_detach_plink( cln_type *sc, int iPlink );



void	cln_affine( cln_type *c, float a, float b, float s, float t );

void	cln_affine_lt2( cln_type *c, lt2_type *lt );


void	cln_affine_estimate( cln_type *c, float a, float b, float s, float t,
									float *dx, float *dy, float *ds, float *da );



void	cln_normelize( cln_type *c );

void	cln_unnormelize( cln_type *c );


void	cln_box( cln_type *c, box2f_type *box );

void	cln_center( cln_type *c, vec2d *p );

void	clnA_translate( clnA_type *ac, float x, float y );

void	cln_translate( cln_type *c, float x, float y );

void	cln_link_len( cln_type *c, float len );

void	clnA_link_len( clnA_type *ac, float len );



void	cln_translateA( cln_type *c, float x, float y );

void	clnA_clear_anchor( clnA_type *ac );

void	cln_clear_anchor( cln_type *c );

int	cln_is_point_inside( cln_type *c, vec2f_type *p );

void	cln_set_dirrection( cln_type *c );

void	cln_set_range( cln_type *c );

int		cln_check_cross( cln_type *c, float d_min, vec2f_type *mp );


void	cln_simplify( cln_type *c );

void	cln_simlifay_len( cln_type *c, float minLen, float maxLen );


cln_type *	cln_union( cln_type *ac, cln_type *c );

void	cln_inverse( cln_type *c );

float	cln_distance( cln_type *c, vec2d  *p, struct dPln_type *d );


cln_type *	cln_detach_transparent( cln_type *c );



	// ClnWrite.cpp
void cln_dump( cln_type *cln, char *prefix, int index, char *suffix );

int		cln_write(cln_type *cln, char *file );

int		cln_read(cln_type **cln, char *file );


plnA_type *	cln_to_plnA( cln_type *cln, int fData );

cln_type *	cln_from_plnA( plnA_type *apl, int fData );


#ifdef _AA_
	// ContourArea.c
float	cln_area( cln_type *c );

float	cln_areaS( cln_type *c );


	// ContourRead.c
int	clnA_read_from_file( char *file, clnA_type **ac );

int	cln_read_from_file( char *file, cln_type **c );

int	cln_read_from_buffer( char *data, int dataSize, cln_type **c1 );


	// ContourWrite.c
int	clnA_write_to_file( clnA_type *ac, char *file );

int	cln_write_to_file( cln_type *c, char *file );

int	cln_write_to_buffer( cln_type *c, char **data, int *dataSize );


	// ContourDump.c
void	clnA_dump( clnA_type *ac, char *prefix, int index, char *suffix );

void	cln_dump( cln_type *c, char *prefix, int index, char *suffix );

void	plink_dump( pln_type *pl, char *prefix, int index, char *suffix );


void	cln_dump_link( vec2f_type *ctr, link_type *link, char *prefix, int index, char *suffix );



	// ContourLt2.c
cln_type *	cln_lt2( cln_type *sc, lt2_type *lt, cln_type *c );

cln_type *	cln_scale( cln_type *sc, float scale, cln_type *c );

void	clnA_scale( clnA_type *ac, float scale, float maxLen );

void	clnA_scale_size( clnA_type *ac, float scale );


	// ContourflipH.c
cln_type * cln_flipH( cln_type *sc, float width, cln_type *c );

void	cln_set_aux( cln_type *c );


	// ContourImageMask.c
struct image_type *	clnA_image_mask( clnA_type *ac, int width, int height, struct image_type *im );

struct image_type *	cln_image_mask( cln_type *c, int width, int height, struct image_type *im );
struct image_type *	cln_image_maskN( cln_type *c, int width, int height, struct image_type *im );


	// ContourArray.c
clnA_type *	clnA_alloc( int nc );

void	clnA_destroy( clnA_type *ac );

void	clnA_clear( clnA_type *ac );


void	clnA_add( clnA_type *ac, cln_type *c );

void	clnA_append( clnA_type *ac, clnA_type *sac );

clnA_type *	clnA_make_copy( clnA_type *sac );

clnA_type *clnA_copy( clnA_type *sac, int type  );


clnA_type *	clnA_get( clnA_type *sac, int type, int detach );

int	clnA_no( clnA_type *ac, int type );

int	clnA_select( clnA_type *ac, int type, vec2f_type *p );

cln_type *	clnA_detouch( clnA_type *ac, int i );


clnA_type *	cln_split( cln_type *c );

clnA_type *	clnA_lt2( clnA_type *sac, lt2_type *lt );

	// ContourOverlap.c
float	cln_overlap( cln_type *c1, cln_type *c2, float dis );



	// ContourCircle.c
cln_type *	cln_from_circle( float R, float d );

cln_type *	cln_from_point( vec2f_type ap[], int nP, int Fclose );

pln_type *	plink_from_point( vec2f_type ap[], int nP, int Fclose );



	// PlinkUnion.c
int	clnA_union( clnA_type *ac );

int	contourC_union( cln_type *c );




	// ContourRadius.c 
float	cln_radius( cln_type *c );
#endif



#ifdef _DUMP
#define CLNA_DUMP( c, prefix, index, suffix )	clnA_dump( c, prefix, index, suffix )
#define CLN_DUMP( c, prefix, index, suffix )	cln_dump( c, prefix, index, suffix )
#else
#define CLNA_DUMP( c, prefix, index, suffix )
#define CLN_DUMP( c, prefix, index, suffix )
#endif



#ifdef __cplusplus
}
#endif

#endif 
